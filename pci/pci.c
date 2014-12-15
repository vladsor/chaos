/* $Id: pci.c,v 1.7 2000/10/15 21:15:32 plundis Exp $ */
/* Abstract: PCI server. (It should also support AGP sometime, but
   currently, it hardly does PCI right...) */
/* Author: Per Lundberg <plundis@chaosdev.org>. Heaviliy inspired by
 * the Linux source, but not by far as obnoxious... */

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

#include <ipc/ipc.h>
#include <string/string.h>
#include <system/system.h>

#include "config.h"
#include "pci.h"

/* Define as TRUE if you are debugging this server. */

#define DEBUG FALSE

/* Linked list of all PCI devices. */

static pci_device_type *pci_device_list = NULL;

/* Linked list of all buses. */

static pci_bus_type *root_bus = NULL;

tag_type empty_tag =
{
  0, 0, ""
};

/* Functions for accessing PCI configuration space with type 1
   accesses. */

#define CONFIG_COMMAND(device, where) \
   (0x80000000 | (device->bus->number << 16) | \
    (device->device_function << 8) | \
    (where & ~3))

static u8 pci_type1_read_config_u8 (pci_device_type *device, int where)
{
  system_port_out_u32 (PCI_BASE, CONFIG_COMMAND (device, where));
  return system_port_in_u8 (PCI_DATA + (where & 3));
}

static u16 pci_type1_read_config_u16 (pci_device_type *device, int where)
{
  system_port_out_u16 (PCI_BASE, CONFIG_COMMAND (device, where));
  return system_port_in_u16 (PCI_DATA + (where & 2));
}

static u32 pci_type1_read_config_u32 (pci_device_type *device, int where)
{
  system_port_out_u32 (PCI_BASE, CONFIG_COMMAND (device, where));
  return system_port_in_u32 (PCI_DATA);
}

static void pci_type1_write_config_u8 (pci_device_type *device, int where,
                                      u8 value)
{
  system_port_out_u32 (PCI_BASE, CONFIG_COMMAND (device, where));    
  system_port_out_u8 (PCI_DATA + (where & 3), value);
}

static void pci_type1_write_config_u16 (pci_device_type *device, int where,
                                        u16 value)
{
  system_port_out_u32 (PCI_BASE, CONFIG_COMMAND (device, where));
  system_port_out_u16 (PCI_DATA + (where & 2), value);
}

static void pci_type1_write_config_u32 (pci_device_type *device, int where,
                                        u32 value)
{
  system_port_out_u32 (PCI_BASE, CONFIG_COMMAND (device, where));
  system_port_out_u32 (PCI_DATA, value);
}

static pci_operation_type pci_type1_operation = 
{
  pci_type1_read_config_u8,
  pci_type1_read_config_u16,
  pci_type1_read_config_u32,
  pci_type1_write_config_u8,
  pci_type1_write_config_u16,
  pci_type1_write_config_u32
};

/* Functions for accessing PCI configuration space with type 2 accesses. */

#define IOADDR(device_function, where) \
   ((0xC000 | ((device_function & 0x78) << 5)) + where)

#define FUNC(device_function) \
   (((device_function & 7) << 1) | 0xF0)

#define SET(device) \
    system_port_out_u8 (PCI_BASE, FUNC (device->device_function)); \
    system_port_out_u8 (PCI_BASE + 2, device->bus->number);

static u8 pci_type2_read_config_u8 (pci_device_type *device, int where)
{
  u8 return_value;

  SET (device);
  return_value = system_port_in_u8 (IOADDR (device->device_function, where));
  system_port_out_u8 (PCI_BASE, 0);
  return return_value;
}

static u16 pci_type2_read_config_u16 (pci_device_type *device, int where)
{
  u16 return_value;

  SET (device);
  return_value = system_port_in_u16 (IOADDR (device->device_function, where));
  system_port_out_u8 (PCI_BASE, 0);
  return return_value;
}

static u32 pci_type2_read_config_u32 (pci_device_type *device, int where)
{
  u16 return_value;

  SET (device);
  return_value = system_port_in_u16 (IOADDR (device->device_function, where));
  system_port_out_u8 (PCI_BASE, 0);
  return return_value;
}

static void pci_type2_write_config_u8 (pci_device_type *device, int where, 
                                       u8 value)
{
  SET (device);
  system_port_out_u16 (IOADDR (device->device_function, where), value);
  system_port_out_u8 (PCI_BASE, 0);
}

static void pci_type2_write_config_u16 (pci_device_type *device, int where,
                                         u16 value)
{
  SET (device);
  system_port_out_u16 (IOADDR (device->device_function, where), value);
  system_port_out_u8 (PCI_BASE, 0);
}

static void pci_type2_write_config_u32 (pci_device_type *device, int where,
                                        u32 value)
{
  SET (device);
  system_port_out_u32 (IOADDR(device->device_function, where), value);
  system_port_out_u8 (PCI_BASE, 0);
}

static pci_operation_type pci_type2_operation = 
{
  pci_type2_read_config_u8,
  pci_type2_read_config_u16,
  pci_type2_read_config_u32,
  pci_type2_write_config_u8,
  pci_type2_write_config_u16,
  pci_type2_write_config_u32
};

extern pci_device_id_type pci_device_id[];
extern unsigned int number_of_devices;
extern pci_vendor_id_type pci_vendor_id[];
extern unsigned int number_of_vendors;
extern pci_class_id_type pci_class_id[];
extern unsigned int number_of_classes;

/* The operations we should use to access the PCI host. */

static pci_operation_type *pci_operation = NULL;

/* Meta-functions for reading and writing PCI data. */

static u32 pci_read_config_u32 (pci_device_type *device, int where)
{
  return ((pci_operation_type *) device->bus->operation)->read_u32 (device, 
                                                                    where);
}

static u16 pci_read_config_u16 (pci_device_type *device, int where)
{
  return ((pci_operation_type *) device->bus->operation)->read_u16 (device,
                                                                    where);
}
                       
static u8 pci_read_config_u8 (pci_device_type *device, int where)
{
  return ((pci_operation_type *) device->bus->operation)->read_u8 (device,
                                                                  where);
}

static void pci_write_config_u32 (pci_device_type *device, int where, u32 data)
{
  ((pci_operation_type *) device->bus->operation)->write_u32 (device, where,
                                                              data);
}

static void pci_write_config_u16 (pci_device_type *device, int where, u32 data)
{
  ((pci_operation_type *) device->bus->operation)->write_u16 (device, where,
                                                              data);
}

static void pci_write_config_u8 (pci_device_type *device, int where, u32 data)
{
  ((pci_operation_type *) device->bus->operation)->write_u8 (device, where,
                                                             data);
}

/* Get the vendor name for the given ID. */

static const char *vendor_get_name (u16 vendor_id)
{
  unsigned int range_begin = 0;
  unsigned int range_end = number_of_vendors - 1;
  unsigned int range_median = (range_end - range_begin) >> 1;

  while (pci_vendor_id[range_median].vendor_id != vendor_id)
  {
    if (range_begin == range_end)
    {
      return NULL;
    }
    
    if (pci_vendor_id[range_median].vendor_id > vendor_id)
    {
      range_end = range_median - 1;
      range_median = (range_begin + range_end) >> 1;
      
      if (range_end < range_begin)
      {
        return NULL;
      }
    }
    else
    {
      range_begin = range_median + 1;
      range_median = (range_begin + range_end) >> 1;

      if (range_end < range_begin)
      {
        return NULL;
      }
    }
  }
  
  return pci_vendor_id[range_median].name;
}

/* Get the device name for the given ID. */

static const char *device_get_name (u16 vendor_id, u16 device_id)
{
  unsigned int range_begin = 0;
  unsigned int range_end = number_of_devices - 1;
  unsigned int range_median = (range_end - range_begin) >> 1;

  while (pci_device_id[range_median].vendor_id != vendor_id ||
         pci_device_id[range_median].device_id != device_id)
  {
    if (range_begin == range_end)
    {
      return NULL;
    }
    
    if (pci_device_id[range_median].vendor_id > vendor_id)
    {
      range_end = range_median - 1;
      range_median = (range_begin + range_end) >> 1;

      if (range_end < range_begin)
      {
        return NULL;
      }
    }
    else if (pci_device_id[range_median].vendor_id < vendor_id)
    {
      range_begin = range_median + 1;
      range_median = (range_begin + range_end) >> 1;

      if (range_end < range_begin)
      {
        return NULL;
      }
    }
    else
    {
      if (pci_device_id[range_median].device_id > device_id)
      {
        range_end = range_median - 1;
        range_median = (range_begin + range_end) >> 1;
  
        if (range_end < range_begin)
        {
          return NULL;
        }
      }
      else
      {
        range_begin = range_median + 1;
        range_median = (range_begin + range_end) >> 1;

        if (range_end < range_begin)
        {
          return NULL;
        }
      }
    }
  }

  return pci_device_id[range_median].name;
}

/* Get the class name for the given ID. */

static const char *class_get_name (u8 class_id)
{
  unsigned int range_begin = 0;
  unsigned int range_end = number_of_classes - 1;
  unsigned int range_median = (range_end - range_begin) >> 1;

  while (pci_class_id[range_median].class_id != class_id)
  {
    if (range_begin == range_end)
    {
      return NULL;
    }
    
    if (pci_class_id[range_median].class_id > class_id)
    {
      range_end = range_median - 1;
      range_median = (range_begin + range_end) >> 1;
      
      if (range_end < range_begin)
      {
        return NULL;
      }
    }
    else
    {
      range_begin = range_median + 1;
      range_median = (range_begin + range_end) >> 1;

      if (range_end < range_begin)
      {
        return NULL;
      }
    }
  }
  
  return pci_class_id[range_median].class_name;
}


/* Handle an IPC connection request. */

static void handle_connection (mailbox_id_type reply_mailbox_id)
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

  message_parameter.block = TRUE;

  while (!done)
  {
    message_parameter.data = data;
    message_parameter.protocol = IPC_PROTOCOL_PCI;
    message_parameter.message_class = IPC_CLASS_NONE;
    message_parameter.length = data_size;
    
    if (ipc_receive (ipc_structure.input_mailbox_id, &message_parameter,
                     &data_size) != IPC_RETURN_SUCCESS)
    {
      continue;
    }
    
    switch (message_parameter.message_class)
    {

      /* Get the amount of PCI devices in this system. */
 
      case IPC_PCI_DEVICE_GET_AMOUNT:
      {
        static unsigned int devices;
	pci_device_type *device = pci_device_list;
	devices = 0;
	
	while(device != NULL)
	{
	  devices++;
	  device = (pci_device_type *) device->next;
	}

        message_parameter.data = &devices;
        message_parameter.length = sizeof (unsigned int);
        message_parameter.block = FALSE;
        ipc_send (ipc_structure.output_mailbox_id, &message_parameter);
        message_parameter.block = TRUE;

        break;
      }

      /* Get brief information about all devices in the system. */

      case IPC_PCI_DEVICE_GET_INFO:
      {
	pci_device_type *device = pci_device_list;
        static pci_device_info_type *device_info = NULL;
        unsigned int counter = 0;
        unsigned int devices = 0;
	
	while(device != NULL)
	{
	  devices++;
	  device = (pci_device_type *) device->next;
	}

        /* Allocate memory to hold this many devices. */
        
        memory_allocate ((void **) &device_info,
                         devices * sizeof (pci_device_info_type));

        device = pci_device_list;

        while (device != NULL && counter < devices)
        {
          string_copy(device_info[counter].vendor_name, device->vendor_name);
          string_copy(device_info[counter].device_name, device->device_name);
	  device_info[counter].irq = device->irq;

          memory_copy (&device_info[counter].resource, device->resource,
                       sizeof (pci_resource_type) * PCI_NUMBER_OF_RESOURCES);
          counter++;

          device = (pci_device_type *) device->next;
        }

        message_parameter.data = device_info;
        message_parameter.length = devices * sizeof (pci_device_info_type);
        message_parameter.block = FALSE;
        ipc_send (ipc_structure.output_mailbox_id, &message_parameter);
        memory_deallocate ((void **) &device_info);
        message_parameter.block = TRUE;

        break;
      }

      /* Get the resource information for the device matching the
         input vendor and device ID. */

      case IPC_PCI_DEVICE_EXISTS:
      {
        pci_device_probe_type *probe = (pci_device_probe_type *) data;
        unsigned int devices = 0;
        pci_device_type *device = pci_device_list;
        pci_device_info_type *device_info = NULL;
        unsigned int counter = 0;

        while (device != NULL)
        {
          if (probe->vendor_id == device->vendor_id &&
              probe->device_id == device->device_id)
          {
            devices++;
          }

          device = (pci_device_type *) device->next;
        }

        /* Allocate memory to hold this many devices. */
        
        memory_allocate ((void **) &device_info,
                         devices * sizeof (pci_device_info_type));

        device = pci_device_list;

        while (device != NULL && counter < devices)
        {
          if (probe->vendor_id == device->vendor_id &&
              probe->device_id == device->device_id)
          {
            string_copy(device_info[counter].vendor_name, device->vendor_name);
            string_copy(device_info[counter].device_name, device->device_name);

            memory_copy (&device_info[counter].resource, device->resource,
                         sizeof (pci_resource_type) * PCI_NUMBER_OF_RESOURCES);
            counter++;
          }

          device_info->irq = device->irq;

          device = (pci_device_type *) device->next;
        }

        message_parameter.data = device_info;
        message_parameter.length = devices * sizeof (pci_device_info_type);
        ipc_send (ipc_structure.output_mailbox_id, &message_parameter);
        memory_deallocate ((void **) &device_info);

        break;
      }

      /* Get the resource information for the device matching the
         input vendor and device ID. */

      case IPC_PCI_DEVICE_CLASS_EXISTS:
      {
        pci_device_class_type *probe = (pci_device_class_type *) data;
        unsigned int devices = 0;
        pci_device_type *device = pci_device_list;
        pci_device_info_type *device_info = NULL;
        unsigned int counter = 0;

        while (device != NULL)
        {
          if ( (probe->class_id == 0xFF || 
	        probe->class_id == device->class_id) &&
               (probe->subclass_id == 0xFF || 
	        probe->subclass_id == device->subclass_id) )
          {
            devices++;
          }

          device = (pci_device_type *) device->next;
        }

        /* Allocate memory to hold this many devices. */
        
        memory_allocate ((void **) &device_info,
                         devices * sizeof (pci_device_info_type));

        device = pci_device_list;

        while (device != NULL && counter < devices)
        {
          if ( (probe->class_id == 0xFF || 
	        probe->class_id == device->class_id) &&
               (probe->subclass_id == 0xFF || 
	        probe->subclass_id == device->subclass_id) )
          {
            string_copy(device_info[counter].vendor_name, device->vendor_name);
            string_copy(device_info[counter].device_name, device->device_name);

            memory_copy (&device_info[counter].resource, device->resource,
                         sizeof (pci_resource_type) * PCI_NUMBER_OF_RESOURCES);
            counter++;
          }

          device_info->irq = device->irq;

          device = (pci_device_type *) device->next;
        }

        message_parameter.data = device_info;
        message_parameter.length = devices * sizeof (pci_device_info_type);
        ipc_send (ipc_structure.output_mailbox_id, &message_parameter);
        memory_deallocate ((void **) &device_info);

        break;
      }
    }
  }
}

/* Detect the presence of a PCI host, and if found, return a pointer
   to the functions that should be used when accessing it. Otherwise,
   return NULL. */

static pci_operation_type *pci_detect (void)
{
  pci_operation_type *operation = NULL;

  system_port_out_u8 (PCI_BASE, 0);
  system_port_out_u8 (PCI_BASE + 2, 0);

  if ((system_port_in_u8 (PCI_BASE) == 0) &&
      (system_port_in_u8 (PCI_BASE + 2) == 0))
  {
    operation = &pci_type2_operation;
  }
  else
  {
    u32 tmp = system_port_in_u32 (PCI_BASE);
    system_port_out_u32 (PCI_BASE, 0x80000000);

    if (system_port_in_u32 (PCI_BASE) == 0x80000000)
    {
      operation = &pci_type1_operation;
    }

    system_port_out_u32 (PCI_BASE, tmp);
  }

  return operation;
}

static bool device_has_bist (pci_device_type *pci_device)
{
  return ((pci_read_config_u8 (pci_device, PCI_BIST) & PCI_BIST_CAPABLE) != 0);
}


static u8 device_bist (pci_device_type *pci_device)
{
  time_type start_time, current_time;
  
  pci_write_config_u8 (pci_device, PCI_BIST, PCI_BIST_START);

  system_call_timer_read (&start_time);
  
  while ((pci_read_config_u8 (pci_device, PCI_BIST) & PCI_BIST_START) != 0)
  {
    system_call_timer_read (&current_time);
    if ((current_time - start_time) > 2000)
    {
      return 0xFF;
    }
  }
  return (pci_read_config_u8 (pci_device, PCI_BIST) & PCI_BIST_CODE_MASK);
}

/* Read interrupt line. */

static void pci_read_irq (pci_device_type *device)
{
  unsigned int irq;
  
  irq = pci_read_config_u8 (device, PCI_INTERRUPT_PIN);
  
  if (irq != 0)
  {
    /* The value 255 is defined as meaning "unknown" or "no connection" 
       to the interrupt controller (as sample: IDE controller say so).  */
    irq = pci_read_config_u8 (device, PCI_INTERRUPT_LINE);
  }

  device->irq = irq;
}

/* Translate the low bits of the PCI base to the resource type. */

static unsigned int pci_get_resource_type (unsigned int flags)
{
  if ((flags & PCI_BASE_ADDRESS_SPACE_IO) != 0)
  {
    return PCI_RESOURCE_IO;
  }
  
  if ((flags & PCI_BASE_ADDRESS_MEM_PREFETCH) != 0)
  {
    return PCI_RESOURCE_MEMORY | PCI_RESOURCE_PREFETCH;
  }
  
  return PCI_RESOURCE_MEMORY;
}

/* Read PCI base addresses. */

static void pci_read_bases (pci_device_type *device, unsigned int amount,
                            int rom)
{
  unsigned int position, register_number, next;

  /* FIXME: Find a better name for the 'l' variable. */

  u32 l, size;
  pci_resource_type *resource;
  
  for (position = 0; position < amount; position = next) 
  {
    next = position + 1;
    resource = &device->resource[position];
    resource->name = device->device_name;
    register_number = PCI_BASE_ADDRESS_0 + (position << 2);

    l = pci_read_config_u32 (device, register_number);
    pci_write_config_u32 (device, register_number, MAX_U32);
    size = pci_read_config_u32 (device, register_number);
    pci_write_config_u32 (device, register_number, l);

    if (size == 0 || size == 0xFFFFFFFF)
    {
      continue;
    }

    if (l == 0xFFFFFFFF)
    {
      l = 0;
    }

    if ((l & PCI_BASE_ADDRESS_SPACE) == PCI_BASE_ADDRESS_SPACE_MEMORY) 
    {
      resource->start = l & PCI_BASE_ADDRESS_MEM_MASK;
      size = ~(size & PCI_BASE_ADDRESS_MEM_MASK);
    }
    else 
    {
      resource->start = l & PCI_BASE_ADDRESS_IO_MASK;
      size = ~(size & PCI_BASE_ADDRESS_IO_MASK) & 0xFFFF;
    }

    resource->end = resource->start + (unsigned long) size;
    resource->flags |= (l & 0xF) | pci_get_resource_type (l);

    if ((l & (PCI_BASE_ADDRESS_SPACE | PCI_BASE_ADDRESS_MEM_TYPE_MASK)) ==
        (PCI_BASE_ADDRESS_SPACE_MEMORY | PCI_BASE_ADDRESS_MEM_TYPE_64)) 
    {
      l = pci_read_config_u32 (device, register_number + 4);
      next++;
      
      if (l != 0) 
      {
        resource->start = 0;
        resource->flags = 0;
        continue;
      }
    }
  }

  if (rom != 0)
  {
    device->rom_base_reg = rom;
    resource = &device->resource[PCI_ROM_RESOURCE];
    l = pci_read_config_u32 (device, rom);
    pci_write_config_u32 (device, rom, ~PCI_ROM_ADDRESS_ENABLE);
    size = pci_read_config_u32 (device, rom);
    pci_write_config_u32 (device, rom, l);

    if (l == 0xFFFFFFFF)
    {
      l = 0;
    }

    if (size != 0 && size != 0xFFFFFFFF) 
    {
      resource->flags = ((l & PCI_ROM_ADDRESS_ENABLE) |
                         PCI_RESOURCE_MEMORY | PCI_RESOURCE_PREFETCH | 
                         PCI_RESOURCE_READONLY | PCI_RESOURCE_CACHEABLE);
      resource->start = l & PCI_ROM_ADDRESS_MASK;
      size = ~(size & PCI_ROM_ADDRESS_MASK);
      resource->end = resource->start + (unsigned long) size;
    }
    
    resource->name = device->device_name;
  }

}

/* Fill in class and map information of a device. */

static bool pci_setup_device (pci_device_type *device)
{
  u32 class;
  char *p;

  /* Set the name. */

  string_print (device->slot_name, "%02x:%02x.%d", device->bus->number, 
                PCI_SLOT (device->device_function), 
                PCI_FUNC (device->device_function));

  p = (char *)device_get_name(device->vendor_id, device->device_id);

  if( p != NULL)
  {
    string_copy (device->device_name, p);
  }
  else
  {
    string_copy (device->device_name, "unknown");
  }

  p = (char *)vendor_get_name(device->vendor_id);

  if( p != NULL)
  {
    string_copy (device->vendor_name, p);
  }
  else
  {
    string_copy (device->device_name, "unknown");
  }

  /* Read the 3-byte class. (?) */
  
  class = pci_read_config_u32 (device, PCI_CLASS_REVISION);

  device->revision_id = class & 0xFF;
  class >>= 8;
  device->class = class;

//  device->class_id = (class >> 16) & 0xFF;
  device->subclass_id = (class >> 8) & 0xFF;
  device->interface_id = class & 0xFF;

  class >>= 8;

  /* Handle erroneous cases first. (In Linux, they use evil gotos for
     this...) */

  if ((device->header_type == PCI_HEADER_TYPE_BRIDGE && 
       class != PCI_CLASS_BRIDGE_PCI) ||
      (device->header_type == PCI_HEADER_TYPE_CARDBUS &&
       class != PCI_CLASS_BRIDGE_CARDBUS))
  {
    device->class = PCI_CLASS_NOT_DEFINED;

    return TRUE;
  }       
  
  switch (device->header_type)
  {
    /* Standard header. */

    case PCI_HEADER_TYPE_NORMAL:
    {
      pci_read_irq (device);
      pci_read_bases (device, 6, PCI_ROM_ADDRESS);
      device->subsystem_vendor_id = pci_read_config_u16 
        (device, PCI_SUBSYSTEM_VENDOR_ID);
      device->subsystem_device_id = pci_read_config_u16
        (device, PCI_SUBSYSTEM_ID);
      break;
    }

    /* Bridge header. */

    case PCI_HEADER_TYPE_BRIDGE:
    {
      pci_read_bases (device, 2, PCI_ROM_ADDRESS1);
      break;
    }
        
    /* CardBus bridge header. */

    case PCI_HEADER_TYPE_CARDBUS:
    {
      pci_read_irq (device);
      pci_read_bases (device, 1, 0);
      device->subsystem_vendor_id = pci_read_config_u16
	(device, PCI_CARDBUS_SUBSYSTEM_VENDOR_ID);
      device->subsystem_device_id = pci_read_config_u16 
	(device, PCI_CARDBUS_SUBSYSTEM_ID);
      break;
     }

    /* Unknown header. */

    default:
    {
      return FALSE;
    }
  }

  device->class_id = (device->class >> 16) & 0xFF;
  p = (char *)class_get_name(device->class_id);
  
  if( p != NULL)
  {
    string_copy (device->class_name, p);
  }
  else
  {
    string_copy (device->class_name, "unknown");
  }

  /* We found a fine healthy device, go go go... */

  return TRUE;
}

/* Read the config data for a PCI device, sanity-check it and fill in
   the device structure... */

static pci_device_type *pci_scan_device (pci_device_type *input_device)
{
  pci_device_type *device;
  u32 vendor_id;
  
  vendor_id = pci_read_config_u32 (input_device, PCI_VENDOR_ID);
  
  /* Some broken boards return 0 or ~0 if a slot is empty. */

  if (vendor_id == 0xFFFFFFFF || vendor_id == 0x00000000 || 
      vendor_id == 0x0000FFFF || vendor_id == 0xFFFF0000)
  {
    return NULL;
  }
  
  memory_allocate ((void **) &device, sizeof (pci_device_type));

  if (device == NULL)
  {
    return NULL;
  }
  
  memory_copy (device, input_device, sizeof (pci_device_type));

  device->vendor_id = vendor_id & 0xFFFF;
  device->device_id = (vendor_id >> 16) & 0xFFFF;
  
  /* Assume 32-bit PCI; let 64-bit PCI cards (which are far rarer)
     set this higher, assuming the system even supports it.  */

  if (!pci_setup_device (device)) 
  {
    memory_deallocate ((void **) &device);
  }

  return device;
}

/* Scan the given PCI slot. */

static pci_device_type *pci_scan_slot (pci_device_type *input_device)
{
  pci_device_type *device;
  pci_device_type *first_device = NULL;
  int function = 0;
  bool is_multi = FALSE;
  u8 header_type;
  
  for (function = 0; function < 8; function++, input_device->device_function++) 
  {
    if (function != 0 && !is_multi)
    {
      continue;
    }

    header_type = pci_read_config_u8 (input_device, PCI_HEADER_TYPE);
    input_device->header_type = header_type & 0x7F;
    device = pci_scan_device (input_device);

    if (device == NULL)
    {
      continue;
    }

    /* FIXME: Maybe set the device name here? */

    if (function == 0)
    {
      is_multi = (header_type & 0x80) == 0x80;
      first_device = device;
    }
    
    /* Add this device to the linked list. */

    list_node_insert ((list_type **) &pci_device_list, (list_type *) device);
  }

  return first_device;
}

/* Scan the given bus. */

static pci_bus_type *pci_scan_bus (int bus_number, 
                                   pci_operation_type *operation)
{
  pci_bus_type *bus;
  unsigned int device_function;
  pci_device_type device;

  memory_allocate ((void **) &bus, sizeof (pci_bus_type));
  bus->number = bus->secondary = bus_number;
  bus->operation = (struct pci_operation_type *) operation;

  device.bus = bus;

  /* Find all the devices on this bus. */

  for (device_function = 0; device_function < 0x100; device_function += 8) 
  {
    device.device_function = device_function;
    pci_scan_slot (&device);
  }

  return bus;
}

/* Initialisation code. */

static bool init (void)
{
  /* Set our names. */

  system_process_name_set (PACKAGE_NAME);
  system_thread_name_set ("Initialising");

  /* Register the ports we need. */

  system_call_port_range_register (PCI_BASE, PCI_PORTS, "PCI controller");

  pci_operation = pci_detect ();

  if (pci_operation == NULL)
  {
    return FALSE;
  }

  /* Scan this bus. */

  root_bus = pci_scan_bus (0, pci_operation);
  
  if (root_bus != NULL)
  {
    (pci_bus_type *)root_bus->next = pci_scan_bus (1, pci_operation);
  }
  return TRUE;
}

/* Main function. */

int main (void)
{
  ipc_structure_type ipc_structure;
  pci_device_type *device;

  /* Initialise the PCI support. */

  if (!init ())
  {
    return -1;
  }

  device = pci_device_list;

  while (device != NULL)
  {
    if (device_has_bist(device))
    {

    }
    device = (pci_device_type *) device->next;
  }

  /* Create the service. */

  if (ipc_service_create ("pci", &ipc_structure, 
                          &empty_tag) != IPC_RETURN_SUCCESS)
  {
    return -1;
  }

  system_thread_name_set ("Service handler");

  system_call_process_parent_unblock ();

  /* Main loop. Wait for messages and answer if someone asks us an
     appropriate question. */

  while (TRUE)
  {
    mailbox_id_type reply_mailbox_id;

    ipc_service_connection_wait (&ipc_structure);
    reply_mailbox_id = ipc_structure.output_mailbox_id;

    if (system_thread_create () == SYSTEM_RETURN_THREAD_NEW)
    {
      system_thread_name_set ("Handling connection");
      handle_connection (reply_mailbox_id);
    }
  }
}
