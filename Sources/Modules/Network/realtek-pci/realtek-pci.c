/* $Id: realtek-pci.c,v 1.4 2000/10/18 00:01:35 plundis Exp $ */
/* Abstract: Realtek PCI server. */
/* Author: Per Lundberg <plundis@chaosdev.org> */

/* Copyright 2000 chaos development. */

/* Partially based on the Linux driver, written by Donald Becker. */

#include <enviroment.h>

#include "realtek-pci.h"

#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

/* User-tunable variables. */

extern int realtek_debug;
extern int max_interrupt_work;

/* Delay between EEPROM clock transitions.  No extra delay is needed
   with 33Mhz PCI, but 66Mhz may change this. */

#define eeprom_delay()  port_uint32_in (eeprom_address)


#define mdio_delay()    port_uint8_in (mdio_address)

static char mii_2_8139_map[8] = 
{
    MII_BMCR, MII_BMSR, 0, 0, NWayAdvert, NWayLPAR, NWayExpansion, 0 
};

void set_rx_mode (realtek_device_t *device)
{
  long io_address = device->port_base;
  int rx_mode;
  
  rx_mode = AcceptBroadcast | AcceptMyPhysical;

  /* We can safely update without stopping the chip. */

  port_uint8_out (io_address + RxConfig, rx_mode);
}

/* Syncronize the MII management interface by shifting 32 one bits out. */

static void mdio_sync (uint16_t mdio_address)
{
  int counter;
  
  for (counter = 32; counter >= 0; counter--)
  {
    port_uint8_out (mdio_address, MDIO_WRITE1);
    mdio_delay ();
    port_uint8_out (mdio_address, MDIO_WRITE1 | MDIO_CLOCK);
    mdio_delay();
  }
}

/* Read from the MII device. */

int mdio_read (uint16_t base_address, int physical_id, int location)
{
  long mdio_address = base_address + MII_SMI;
  int mii_command = (0xF6 << 10) | (physical_id << 5) | location;
  int return_value = 0;
  int counter;
  
  /* Really a 8139.  Use internal registers. */

  if (physical_id > 31)
  {
    return (location < 8 && mii_2_8139_map[location] ?
            port_uint16_in (base_address + mii_2_8139_map[location]) : 0);
  }

  mdio_sync (mdio_address);

  /* Shift the read command bits out. */
  
  for (counter = 15; counter >= 0; counter--) 
  {
    int data_value = (mii_command & (1 << counter)) ? MDIO_DATA_OUT : 0;
    
    port_uint8_out (mdio_address, MDIO_DIR | data_value);
    mdio_delay ();
    port_uint8_out (mdio_address, MDIO_DIR | data_value | MDIO_CLOCK);
    mdio_delay ();
  }
  
  /* Read the two transition, 16 data, and wire-idle bits. */

  for (counter = 19; counter > 0; counter--) 
  {
    port_uint8_out (mdio_address, 0);
    mdio_delay ();
    return_value = (return_value << 1) | ((port_uint8_in (mdio_address) & 
                                           MDIO_DATA_IN) ? 1 : 0);
    port_uint8_out (mdio_address, MDIO_CLOCK);
    mdio_delay ();
  }

  return (return_value >> 1) & 0xFFFF;
}

/* Read an EEPROM register. */

int read_eeprom (uint16_t io_address, int location)
{
  int counter;
  unsigned return_value = 0;
  long eeprom_address = io_address + Config9346;
  int read_command = location | EEPROM_READ_COMMAND;
  
  port_uint8_out (eeprom_address, EEPROM_ENB & ~EEPROM_CHIP_SELECT);
  port_uint8_out (eeprom_address, EEPROM_ENB);
  
  /* Shift the read command bits out. */

  for (counter = 10; counter >= 0; counter--)
  {
    int dataval = (read_command & (1 << counter)) ? EEPROM_DATA_WRITE : 0;

    port_uint8_out (eeprom_address, EEPROM_ENB | dataval);
    eeprom_delay ();
    port_uint8_out (eeprom_address, EEPROM_ENB | dataval | 
                        EEPROM_SHIFT_CLOCK);
    eeprom_delay ();
  }

  port_uint8_out (eeprom_address, EEPROM_ENB);
  eeprom_delay ();
  
  for (counter = 16; counter > 0; counter--) 
  {
    port_uint8_out (eeprom_address, EEPROM_ENB | EEPROM_SHIFT_CLOCK);
    eeprom_delay ();
    return_value = (return_value << 1) | 
      ((port_uint8_in (eeprom_address) & EEPROM_DATA_READ) ? 1 : 0);
    port_uint8_out (eeprom_address, EEPROM_ENB);
    eeprom_delay ();
  }
  
  /* Terminate the EEPROM access. */

  port_uint8_out (eeprom_address, ~EEPROM_CHIP_SELECT);
  return return_value;
}

/* Receive a packet from the Realtek device. */

int realtek_receive (realtek_device_t *device)
{
  long io_address = device->port_base;
  unsigned char *rx_ring = device->rx_ring;
  uint16_t current_rx = device->current_rx;
  unsigned int counter;
  
  if (realtek_debug > 4)
  {
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
                         "In %s (), current %4.4x BufAddr %4.4x,"
                         " free to %4.4x, Command %2.2x.\n",
                         __FUNCTION__, current_rx, 
                         port_uint16_in (io_address + RxBufferAddress),
                         port_uint16_in (io_address + RxBufferPointer),
                         port_uint8_in (io_address + ChipCommand));
  }
  
  while ((port_uint8_in (io_address + ChipCommand) & 1) == 0) 
  {
    int ring_offset = current_rx % RX_BUFFER_LENGTH;
    uint32_t rx_status = little_endian_to_native_uint32 
      (* (uint32_t *) (rx_ring + ring_offset));
    int rx_size = rx_status >> 16;
    
    if (realtek_debug > 4) 
    {
      // int i;
      DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
                           "%s () status %x, size %x, current %x.\n",
                           __FUNCTION__, rx_status, rx_size, current_rx);

      //      printk(KERN_DEBUG"%s: Frame contents ", device->name);
      //      for (i = 0; i < 70; i++)
      //      {
      //        printk(" %2.2x", le32_to_cpu(rx_ring[ring_offset + i]));
      //      printk(".\n");
    }

    if ((rx_status & RxTooLong) != 0)
    {
      if (realtek_debug > 0)
      {
        DEBUG_PRINT (DEBUG_LEVEL_WARNING,
                             "Oversized Ethernet frame, status %x!\n",
                             rx_status);
      }

      // tp->stats.rx_length_errors++;
    }
    else if ((rx_status & (RxBadSymbol | RxRunt | RxTooLong | RxCRCError | 
                           RxBadAlign)) != 0)
    {
      if (realtek_debug > 1)
      {
        DEBUG_PRINT (DEBUG_LEVEL_WARNING, 
          "Ethernet frame had errors, status %x.\n", rx_status);
      }

      // tp->stats.rx_errors++;

      if ((rx_status & (RxBadSymbol | RxBadAlign)) != 0)
      {
        // tp->stats.rx_frame_errors++;
      }

      if ((rx_status & (RxRunt | RxTooLong)) != 0)
      {
        // tp->stats.rx_length_errors++;
      }

      if (rx_status & RxCRCError) 
      {
        // tp->stats.rx_crc_errors++;
      }

      /* Reset the receiver, based on RealTek recommendation. (Bug?) */

      device->current_rx = 0;
      port_uint8_out (io_address + ChipCommand, CommandTxEnable);
      port_uint8_out (io_address + ChipCommand, CommandRxEnable |
                          CommandTxEnable);
      port_uint32_out (io_address + RxConfig, (RX_FIFO_THRESHOLD << 13) |
                           (RX_BUFFER_LENGTH_INDEX << 11) | (RX_DMA_BURST << 8));
    }
    else 
    {
      uint8_t *data;
      
      memory_allocate ((void **) &data, rx_size);

      if (ring_offset + rx_size + 4 > RX_BUFFER_LENGTH)
      {
        int semi_count = RX_BUFFER_LENGTH - ring_offset - 4;
       
        memory_copy (data, &rx_ring[ring_offset + 4],
                     semi_count);
        memory_copy (&data[semi_count], rx_ring,
                     rx_size - semi_count);

        if (realtek_debug > 4) 
        {
          DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
                               "Frame wrap @%d.\n", semi_count);
          memory_set_uint8 (rx_ring, 0xCC, 16);
        }
      } 
      else 
      {
        memory_copy (data, &rx_ring[ring_offset + 4], rx_size);
      }

      /* Check if this packet should be delivered somewhere. */
      
      for (counter = 0; counter < device->number_of_targets; counter++)
      {          
        if (device->target[counter].protocol_type ==
            ((network_ethernet_header_t *) data)->protocol_type)
        {
/*        
          message_parameter_type message_parameter;
          
          message_parameter.protocol = IPC_PROTOCOL_ETHERNET;
          message_parameter.message_class = IPC_ETHERNET_PACKET_RECEIVED;
          message_parameter.length = rx_size;
          message_parameter.block = FALSE;
          message_parameter.data = data;
          
          if (realtek_debug > 2)
          {
            log_print_formatted (&log_structure, LOG_URGENCY_DEBUG, 
                                 "Sending to mailbox ID %u", 
                                 device->target[counter].mailbox_id);
          }
          
          ipc_send (device->target[counter].mailbox_id, &message_parameter);
*/          
          break;
        }
      }

      // memory_deallocate ((void **) &data);

#if LINUX_VERSION_CODE > 0x20119
      // tp->stats.rx_bytes += rx_size;
#endif
      // tp->stats.rx_packets++;
    }
    
    current_rx = (current_rx + rx_size + 4 + 3) & ~3;
    port_uint16_out (io_address + RxBufferPointer, current_rx - 16);
  }

  if (realtek_debug > 4)
  {
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
                         "Done %s (), current %4.4x BufferAddress %4.4x,"
                         " free to %4.4x, Command %2.2x.\n",
                         __FUNCTION__, current_rx,
                         port_uint16_in (io_address + RxBufferAddress),
                         port_uint16_in (io_address + RxBufferPointer), 
                         port_uint8_in (io_address + ChipCommand));
  }

  device->current_rx = current_rx;

  return 0;
}

/* Start a transmit. */

bool realtek_start_transmit (uint8_t *data, unsigned int length,
    realtek_device_t *device)
{
  long io_address = device->port_base;
  int entry;
  
  // netif_stop_queue(dev);
  
  /* Calculate the next Tx descriptor entry. */

  entry = device->current_tx % NUMBER_OF_TX_DESCRIPTORS;
  
  // tp->tx_info[entry].skb = skb;

  // tp->tx_info[entry].mapping = 0;
  
    memory_copy (device->tx_buffer[entry], data, length);
    port_uint32_out (io_address + TxAddress0 + entry * 4, 
        (uint32_t) (device->tx_buffers_dma + (device->tx_buffer[entry] -
        device->tx_buffers)));
  
  /* Note: the chip doesn't have auto-pad! */
  
  port_uint32_out (io_address + TxStatus0 + entry * 4,
                       device->tx_flag | 
                       (length >= NETWORK_ETHERNET_MINIMUM_LENGTH ? 
                        length : NETWORK_ETHERNET_MINIMUM_LENGTH));
  
  /* Typical path */

  if (++device->current_tx - device->dirty_tx < NUMBER_OF_TX_DESCRIPTORS) 
  {
    // netif_start_queue(dev);
  }
  else 
  {
    device->tx_full = TRUE;
  }
  
  // dev->trans_start = jiffies;

  if (realtek_debug > 4)
  {
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
                         "Queued Tx packet at %p size %d to slot %d.\n",
                         data, length, entry);
  }
  
  return TRUE;
}



