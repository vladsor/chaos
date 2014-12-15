/* $Id: ata.c,v 1.9 2000/10/18 00:15:51 plundis Exp $ */
/* Abstract: ATA server for chaos. Follows the standard chaos block
   service format. */
/* Author: Henrik Hallin <hal@chaosdev.org>
           Anders Öhrt <doa@chaosdev.org> 
           Per Lundberg <plundis@chaosdev.org> */

/* Copyright 1999-2000 chaos development. */

/* This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
   USA. */

#include "ata.h"
#include "config.h"
#include "partition.h"

static log_structure_type log_structure;
static tag_type empty_tag =
{
  0, 0, ""
};

static inline u8 lba_to_sector_number (device_type *device, u32 linear_sector)
{
  return (linear_sector %
          device->sectors_per_track) + 1;
}

static inline u8 lba_to_cylinder_low (device_type *device, u32 linear_sector)
{
  return (linear_sector /
          (device->number_of_heads *
           device->sectors_per_track)) & 0xFF;
}

static inline u8 lba_to_cylinder_high (device_type *device, u32 linear_sector)
{
  return ((linear_sector /
           (device->number_of_heads *
            device->sectors_per_track)) >> 8) & 0xFF;
}

static inline u8 lba_to_head (device_type *device, u32 linear_sector)
{
  return ((linear_sector /
           device->sectors_per_track) %
          device->number_of_heads);
}

static void interrupt_handler (interface_type *interface)
{
  message_parameter_type message_parameter;

  if (system_call_irq_register (interface->irq, "ATA interface") !=
      SYSTEM_RETURN_SUCCESS)
  {
    log_print_formatted (&log_structure, LOG_URGENCY_DEBUG,
                         "Could not allocate IRQ %u.",
                         interface->irq);
    return;
  }

  message_parameter.length = 0;
  message_parameter.block = TRUE;
  message_parameter.data = NULL;

  while (TRUE)
  {
    system_call_irq_wait (interface->irq);
    system_call_irq_acknowledge (interface->irq);

    log_print_formatted (&log_structure, LOG_URGENCY_DEBUG,
                         "IRQ %u.", interface->irq);
    system_call_mailbox_send (interface->mailbox_id, &message_parameter);
  }
}

/* Send a command and await an IRQ. */

static void send_command (interface_type *interface, u8 command)
{
  message_parameter_type message_parameter;

  message_parameter.length = 0;
  message_parameter.block = TRUE;
  message_parameter.data = NULL;

  system_port_out_u8 (interface->io_base + REGISTER_COMMAND, command);
  system_call_mailbox_receive (interface->mailbox_id, &message_parameter);
}

/* Read one or more sectors from a device. */
/* FIXME: Do rangechecking in all neccessary ways. */

static bool sectors_read (interface_type *interface, unsigned int device,
                          u32 sector_number, unsigned int number_of_sectors,
                          void *buffer)
{
  u8 status, error;

  /* Range check number of sectors to read, and convert to ATA way. */

  if (number_of_sectors == 0 || number_of_sectors > 256)
  {
    return FALSE;
  }
  if (number_of_sectors == 256)
  {
    number_of_sectors = 0;
  }

  log_print_formatted (&log_structure, LOG_URGENCY_DEBUG,
                       "Reading %u sectors...", number_of_sectors);

  /* Wait for BSY to clear. */

  while ((system_port_in_u8 (interface->io_base + REGISTER_ALTERNATE_STATUS) & BIT_BSY) != 0);

  /* FIXME: Investigate this!!! */

#if FALSE
  if (interface->device[device]->lba)
  {
    /* This device supports LBA addressing mode. */

    log_print (&log_structure, LOG_URGENCY_DEBUG, "LBA");
    
    system_port_out_u8 (interface->io_base + REGISTER_DEVICE_HEAD,
                        ((sector_number >> 24) & 0x0F) | BIT_LBA |
                        (device == 0) ? DEVICE_MASTER : DEVICE_SLAVE);

    /* Wait for controller. */

    while ((system_port_in_u8 (interface->io_base + REGISTER_ALTERNATE_STATUS) & BIT_BSY) != 0 ||
           (system_port_in_u8 (interface->io_base + REGISTER_ALTERNATE_STATUS) & BIT_DRDY) == 0);

    system_port_out_u8 (interface->io_base + REGISTER_SECTOR_NUMBER,
                        sector_number & 0xFF);
    system_port_out_u8 (interface->io_base + REGISTER_CYLINDER_LOW,
                        (sector_number >> 8) & 0xFF);
    system_port_out_u8 (interface->io_base + REGISTER_CYLINDER_HIGH,
                        (sector_number >> 16) & 0xFF);
  }
  else
#endif

  {
    /* CHS addressing mode. */

    log_print (&log_structure, LOG_URGENCY_DEBUG, "CHS");

    system_port_out_u8 (interface->io_base + REGISTER_DEVICE_HEAD,
                        lba_to_head (interface->device[device],
                                     sector_number) |
                        (device == 0) ? DEVICE_MASTER : DEVICE_SLAVE);

    /* Wait for controller. */

    while ((system_port_in_u8 (interface->io_base + REGISTER_ALTERNATE_STATUS) & BIT_BSY) != 0 ||
           (system_port_in_u8 (interface->io_base + REGISTER_ALTERNATE_STATUS) & BIT_DRDY) == 0);

    system_port_out_u8 (interface->io_base + REGISTER_SECTOR_NUMBER,
                        lba_to_sector_number (interface->device[device],
                                              sector_number));
    system_port_out_u8 (interface->io_base + REGISTER_CYLINDER_LOW,
                        lba_to_cylinder_low (interface->device[device],
                                             sector_number));
    system_port_out_u8 (interface->io_base + REGISTER_CYLINDER_HIGH,
                        lba_to_cylinder_high (interface->device[device],
                                              sector_number));
  }

  /* How many sectors to read? */

  system_port_out_u8 (interface->io_base + REGISTER_SECTOR_COUNT,
                      number_of_sectors);

  /* Send the command. */

  send_command (interface, COMMAND_READ_SECTORS_RETRY);

  /* Read status and ACK controller. */

  status = system_port_in_u8 (interface->io_base + REGISTER_STATUS);
  error = system_port_in_u8 (interface->io_base + REGISTER_ERROR);

  if ((error & BIT_ABRT) == 0 &&
      (status & BIT_ERR) == 0)
  {
    /* Read the sector(s). */

    log_print_formatted (&log_structure, LOG_URGENCY_DEBUG,
                         "Status OK, reading %d bytes from device...",
                         512 * number_of_sectors);

    system_port_in_u16_string (interface->io_base + REGISTER_DATA,
                               (u16 *) buffer, 256 * number_of_sectors);
    return TRUE;
  }
  else
  {
    log_print_formatted (&log_structure, LOG_URGENCY_DEBUG,
                         "An error occured while reading sector(s). status = 0x%X, error = 0x%X.",
                         status, error);

    return FALSE;
  }
}

/* Handle a client connection. */

static void handle_connection (mailbox_id_type reply_mailbox_id,
                               service_type *service)
{
  message_parameter_type message_parameter;
  ipc_structure_type ipc_structure;
  bool done = FALSE;
  u32 *data;
  unsigned int data_size = 1024;

  memory_allocate ((void **) &data, data_size);

  /* Accept the connection. */ 

  ipc_structure.output_mailbox_id = reply_mailbox_id;
  ipc_connection_establish (&ipc_structure);

  message_parameter.data = data;
  message_parameter.block = TRUE;

  while (!done)
  {
    message_parameter.protocol = IPC_PROTOCOL_BLOCK;
    message_parameter.message_class = IPC_CLASS_NONE;
    message_parameter.length = data_size;
    
    if (ipc_receive (ipc_structure.input_mailbox_id, &message_parameter,
                     &data_size) != IPC_RETURN_SUCCESS)
    {
      continue;
    }
    
    switch (message_parameter.message_class)
    {
      case IPC_BLOCK_READ:
      {
        ipc_block_read_type *ipc_block_read = (ipc_block_read_type *) data;

        /* Do some boundary checking. */
        
        if (ipc_block_read->start_block_number +
            ipc_block_read->number_of_blocks > service->number_of_sectors)
        {
          /* FIXME: Should we do the error handling in some other way? */

          message_parameter.data = NULL;
          message_parameter.length = 0;
          log_print (&log_structure, LOG_URGENCY_ERROR,
                     "Tried to read out of range.");
        }
        else
        {
          if (!sectors_read (service->interface, service->device,
                             ipc_block_read->start_block_number + service->start_sector,
                             ipc_block_read->number_of_blocks,
                             message_parameter.data))
          {
            log_print (&log_structure, LOG_URGENCY_ERROR,
                       "Could not read requested sector(s).");
          }

          message_parameter.length = (ipc_block_read->number_of_blocks * 512);
        }
        message_parameter.block = TRUE;
        
        ipc_send (ipc_structure.output_mailbox_id, &message_parameter);
        break;
      }

      case IPC_BLOCK_WRITE:
      {
        break;
      }
      
      case IPC_BLOCK_GET_INFO:
      {
        break;
      }
    }
  }
}

/* Create a service and listen to it. */

static void handle_service (service_type *service)
{
  ipc_structure_type ipc_structure;

  if (ipc_service_create ("block", &ipc_structure, 
                          &empty_tag) != IPC_RETURN_SUCCESS)
  {
    log_print (&log_structure, LOG_URGENCY_ERROR,
               "Couldn't create block service.");
    system_exit ();
  }

  /* Main loop. */
  
  system_thread_name_set ("Service handler");
  
  while (TRUE)
  {
    mailbox_id_type reply_mailbox_id;
    
    ipc_service_connection_wait (&ipc_structure);
    reply_mailbox_id = ipc_structure.output_mailbox_id;
    
    if (system_thread_create () == SYSTEM_RETURN_THREAD_NEW)
    {
      system_thread_name_set ("Handling connection");
      handle_connection (reply_mailbox_id, service);
    }
  }    
}

/* This is a recursive function which will (hopefully ;) find all
   partitions on a disk. */

static bool check_partitions (interface_type *interface, unsigned int device,
                              u32 sector_number)
{
  u8 *sector_buffer;
  partition_entry_type *partition;
  int index;
  service_type *service;

  memory_allocate ((void **) &sector_buffer, 512);

  /* Now, read the first sector of the disk to access the partition table. */

  if (!sectors_read (interface, device, sector_number, 1, sector_buffer))
  {
    return FALSE;
  }

  /* Parse the partition table. */

  partition = (partition_entry_type *) &sector_buffer[446];

  for (index = 0; index < 4; index++)
  {
    if (partition[index].type != 0 && partition[index].type != 5)
    {
      log_print_formatted (&log_structure, LOG_URGENCY_INFORMATIVE,
                           "  Partition: Type 0x%02X, starts at sector %lu, size: %lu MB. %s",
                           partition[index].type,
                           partition[index].lba_starting_sector_number,
                           partition[index].lba_number_of_sectors * 512 / 1024 / 1024,
                           (partition[index].active == 1) ? "(Active)" : "");

      memory_allocate ((void **) &service, sizeof (service_type));

      service->interface = interface;
      service->device = device;
      service->start_sector = partition[index].lba_starting_sector_number;
      service->number_of_sectors = partition[index].lba_number_of_sectors;

      /* Create a block service for this partition. */
      
      if (system_thread_create () == SYSTEM_RETURN_THREAD_NEW)
      {
        handle_service (service);
      }
    }
    else if (partition[index].type == 5)
    {
      /* Extended partition. */

      log_print_formatted (&log_structure, LOG_URGENCY_INFORMATIVE,
                           "  Extended Partition: Starts at sector %lu, size: %lu MB. %s",
                           partition[index].lba_starting_sector_number,
                           partition[index].lba_number_of_sectors * 512 / 1024 / 1024,
                           (partition[index].active == 1) ? "(Active)" : "");

      if (!check_partitions (interface, device,
                             partition[index].lba_starting_sector_number))
      {
        return FALSE;
      }
    }
  }

  memory_deallocate ((void **) &sector_buffer);
  return TRUE;
}

/* Initialise a device. */

static void init_device (interface_type *interface, unsigned int device)
{
  service_type *service;

  /* First of all, create a service and a thread for the whole
     disk. */

  memory_allocate ((void **) &service, sizeof (service_type));

  service->interface = interface;
  service->device = device;
  service->start_sector = 0;
  service->number_of_sectors = interface->device[device]->number_of_sectors;

  if (system_thread_create () == SYSTEM_RETURN_THREAD_NEW)
  {
    handle_service (service);
  }

  /* Now, create block services for all partitions on the disk. */

  if (!check_partitions (interface, device, 0))
  {
    log_print (&log_structure, LOG_URGENCY_ERROR,
               "Reading partition tables failed.");
  }
}

/* Allocate resources for an interface and try to identify all devices
   on it. */

static bool init_interface (interface_type *interface)
{
  u8 status;
  unsigned int device;
  int index;
  unsigned int timeout = 0;

  if (system_call_port_range_register (interface->io_base, 8, "ATA interface")
      != STORM_RETURN_SUCCESS)
  {
    log_print_formatted (&log_structure, LOG_URGENCY_DEBUG,
                         "Could not allocate hardware ports 0x%X-0x%X.",
                         interface->io_base,
                         interface->io_base + 7);
    return FALSE;
  }

  if (system_call_port_range_register (interface->io_base + REGISTER_DEVICE_CONTROL, 1, "ATA interface")
      != STORM_RETURN_SUCCESS)
  {
    log_print_formatted (&log_structure, LOG_URGENCY_DEBUG,
                         "Could not allocate hardware port 0x%X.",
                         interface->io_base + REGISTER_DEVICE_CONTROL);
    return FALSE;
  }

  /* Create a mailbox for this interface. */
  /* FIXME: The mailbox system needs to be modified slightly to
     support NULL messages correctly. */

  system_call_mailbox_create (&interface->mailbox_id, 1000,
                              PROCESS_ID_NONE,
                              CLUSTER_ID_NONE,
                              THREAD_ID_NONE);

  if (system_thread_create () == SYSTEM_RETURN_THREAD_NEW)
  {
    system_thread_name_set ("IRQ handler");
    interrupt_handler (interface);
    log_print (&log_structure, LOG_URGENCY_DEBUG,
               "Unexpected return from interrupt handler.");
    system_exit ();
  }

  /* Software reset the interface. */

  log_print (&log_structure, LOG_URGENCY_DEBUG,
             "Software resetting interface...");

  system_port_out_u8 (interface->io_base + REGISTER_DEVICE_CONTROL,
                      BIT_SRST | REGISTER_DEVICE_CONTROL_DEFAULT);
  system_sleep_microseconds (1);
  system_port_out_u8 (interface->io_base + REGISTER_DEVICE_CONTROL,
                      REGISTER_DEVICE_CONTROL_DEFAULT);
  system_sleep_microseconds (1);

  /* Wait for up to 5 seconds (Should be 31) or until BSY is cleared. */

  while (timeout < 50 &&
         (system_port_in_u8 (interface->io_base + REGISTER_ALTERNATE_STATUS) & BIT_BSY) != 0)
  {
    timeout++;
    system_sleep (100);
  }

  if ((system_port_in_u8 (interface->io_base + REGISTER_ALTERNATE_STATUS) & BIT_BSY) == 0)
  {
    /* The device did not time out. */

    log_print (&log_structure, LOG_URGENCY_DEBUG,
               "BSY bit cleared correctly.");
  }
  else
  {
    log_print (&log_structure, LOG_URGENCY_DEBUG,
               "Software reset failed (BSY timeout).");
    return FALSE;
  }

  /* Now wait for DRDY to be set. */

  timeout = 0;

  while (timeout < 50 &&
         (system_port_in_u8 (interface->io_base + REGISTER_ALTERNATE_STATUS) & BIT_DRDY) == 0)
  {
    timeout++;
    system_sleep (100);
  }

  if ((system_port_in_u8 (interface->io_base + REGISTER_ALTERNATE_STATUS) & BIT_DRDY) != 0)
  {
    /* The device did not time out. */

    log_print (&log_structure, LOG_URGENCY_DEBUG,
               "DRDY bit set correctly.");
  }
  else
  {
    log_print (&log_structure, LOG_URGENCY_DEBUG,
               "Software reset failed (DRDY timeout).");
    return FALSE;
  }

  /* The software reset was successful. */

  log_print (&log_structure, LOG_URGENCY_DEBUG,
             "Software reset succeeded.");

  /* Ok. We have things set up for this interface. Now, let's probe
     for devices on it. */
  
  for (device = 0; device < 2; device++)
  {
    /* Select the correct device. */

    system_port_out_u8 (interface->io_base + REGISTER_DEVICE_HEAD,
                        (device == 0) ? DEVICE_MASTER : DEVICE_SLAVE);

    while ((system_port_in_u8 (interface->io_base + REGISTER_ALTERNATE_STATUS) & BIT_BSY) != 0 ||
           (system_port_in_u8 (interface->io_base + REGISTER_ALTERNATE_STATUS) & BIT_DRDY) == 0);

    if (system_port_in_u8 (interface->io_base + REGISTER_ALTERNATE_STATUS) != 0xFF)
    {
      log_print_formatted (&log_structure, LOG_URGENCY_DEBUG,
                           "Found a %s device on interface.",
                           (device == 0) ? "master" : "slave");
      
      memory_allocate ((void **) &interface->device[device], sizeof (device_type));

      log_print_formatted (&log_structure, LOG_URGENCY_DEBUG,
                           "Sending identify command to device.");
      send_command (interface, COMMAND_IDENTIFY_DEVICE);
      
      /* Read the status register and ACK the controller at the same time. */
      
      status = system_port_in_u8 (interface->io_base + REGISTER_STATUS);
      log_print_formatted (&log_structure, LOG_URGENCY_DEBUG,
                           "Command status was 0x%X. Reading data...", status);

      /* Read the identification data from the device. */

      system_port_in_u16_string (interface->io_base + REGISTER_DATA,
                                 (u16 *) interface->device[device]->id,
                                 IDENTIFY_WORDS);

      /* Copy out some strings, byteswap them and NULL-terminate them. */

      for (index = 0; index < 20; index++)
      {
        interface->device[device]->model_number[index * 2 + 1] =
          interface->device[device]->id[27 + index];
        interface->device[device]->model_number[index * 2] =
          (interface->device[device]->id[27 + index] >> 8);
      }

      index = 39;

      while (interface->device[device]->model_number[index] == ' ' &&
        index >= 0)
      {
        index--;
      }

      interface->device[device]->model_number[index + 1] = '\0';

      /* Take the important information out of the identification structure. */

      interface->device[device]->number_of_cylinders = interface->device[device]->id[1];
      interface->device[device]->number_of_heads = interface->device[device]->id[3];
      interface->device[device]->sectors_per_track = interface->device[device]->id[6];
      interface->device[device]->number_of_sectors = 
        interface->device[device]->number_of_cylinders *
        interface->device[device]->number_of_heads *
        interface->device[device]->sectors_per_track;

      interface->device[device]->lba = ((interface->device[device]->id[49] & BIT_VALUE (9)) != 0);
      interface->device[device]->dma = ((interface->device[device]->id[49] & BIT_VALUE (8)) != 0);

      log_print_formatted (&log_structure, LOG_URGENCY_INFORMATIVE,
                           "Device: %s. Capacity: %u MB. %s %s",
                           interface->device[device]->model_number,
                           (unsigned int) interface->device[device]->number_of_sectors * 512 / 1024 / 1024,
                           interface->device[device]->lba ? "(LBA)" : "",
                           interface->device[device]->dma ? "(DMA)" : "");

      log_print_formatted (&log_structure, LOG_URGENCY_INFORMATIVE,
                           "Geometry: Cylinders: %lu, heads: %lu, sectors: %lu.",
                           interface->device[device]->number_of_cylinders,
                           interface->device[device]->number_of_heads,
                           interface->device[device]->sectors_per_track);

      /* Initialise this device. This includes reading the partition
         table and create a thread and a service for each found
         partition. */
      
      init_device (interface, device);
    }
    else
    {
      log_print_formatted (&log_structure, LOG_URGENCY_DEBUG,
                           "No %s device found on interface.",
                           (device == 0) ? "master" : "slave");
    }
  }

  if (interface->device[0] == NULL &&
      interface->device[1] == NULL)
  {
    /* No devices on interface. */

    system_call_irq_unregister (interface->irq);
    system_call_port_range_unregister (interface->io_base);
    system_call_port_range_unregister (interface->io_base + REGISTER_DEVICE_CONTROL);

    /* FIXME: Do something about the IRQ handler as well. I think that
       we can do without any IRQ handler at all. */

    return FALSE;
  }
  else
  {
    /* One or more devices found on this interface. */

    return TRUE;
  }
}

int main (void)
{
  unsigned int interface_index;
  bool found_device = FALSE;

  interface_type interface[2] =
  {
    {
      14,
      0x1f0,
      MAILBOX_ID_NONE,
      {
        NULL,
        NULL
      }
    },
    {
      15,
      0x170,
      MAILBOX_ID_NONE,
      {
        NULL,
        NULL
      }
    }
  };

  log_init (&log_structure, PACKAGE_NAME, &empty_tag);

  system_process_name_set (PACKAGE_NAME);
  system_thread_name_set ("Initialising");

  /* Try to probe for devices on the interfaces. */

  for (interface_index = 0;
       interface_index < sizeof (interface) / sizeof (interface_type);
       interface_index++)
  {
    if (init_interface (&interface[interface_index]))
    {
      /* We have at least one device on this interface. */

      log_print_formatted (&log_structure, LOG_URGENCY_DEBUG,
                           "Initialisation of ATA interface at 0x%X succeeded.",
                           interface[interface_index].io_base);

      found_device = TRUE;
    }
  }

  /* If we didn't find any devices at all, exit. */

  if (!found_device)
  {
    log_print (&log_structure, LOG_URGENCY_EMERGENCY, "No ATA devices found.");
    system_exit ();
  }

  /* We are finished with the initialisation. */

  system_call_process_parent_unblock ();

  return 0;
}
