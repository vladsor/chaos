#include <enviroment.h>

#include <Interfaces/pci_bus.h>
#include <Interfaces/pci_device.h>

#include "interface.h"
#include "realtek-pci.h"

#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

#define PCI_RESOURCE_IO                 0x00000100
#define PCI_RESOURCE_MEMORY             0x00000200
#define PCI_RESOURCE_IRQ                0x00000400
#define PCI_RESOURCE_DMA                0x00000800

int realtek_debug = 10;
int max_interrupt_work = 20;

#define REALTEK_VENDOR_ID               0x10EC

typedef struct
{
    uint16_t vendor_id;
    uint16_t device_id;
} pci_device_probe_t;

pci_device_probe_t pci_device_probe[] =
{
  /* Realtek 8139. */

  { REALTEK_VENDOR_ID, 0x8139 },

  /* End of list. */

  { 0xFFFF, 0xFFFF }
};


#if 0
      case IPC_ETHERNET_REGISTER_TARGET:
      {
        /* FIXME: Check if the protocol is already registered */

        device->target[device->number_of_targets].mailbox_id = 
          ipc_structure.output_mailbox_id;
        device->target[device->number_of_targets].protocol_type =
          system_byte_swap_u16 (data[0]);
        device->number_of_targets++;
        break;
      }

void ethernet_send_packet (context_t *context, uint8_t *data, size_t length)
{
    realtek_device_t *device = NULL;

    if (!realtek_start_transmit (data, length, device))
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, "Failed to send an ethernet packet.");

          /* FIXME: Do something. */
    }
}

      case IPC_ETHERNET_ADDRESS_GET:
      {
        memory_copy (data, &device->ethernet_address, 6);
        message_parameter.length = 6;
        system_call_mailbox_send (ipc_structure.output_mailbox_id,
                                  &message_parameter);
        break;
      }
#endif

/* handle interrupts. */
static void rt_irq_handler (p_void_t parameter, 
    irq_cpu_registers_t irq_cpu_registers UNUSED)    
{
    int bogus_count = max_interrupt_work;
    unsigned status, link_changed = 0;
    realtek_device_t *device = (realtek_device_t *) parameter;
      
    do 
    {
        status = port_uint16_in (device->port_base + InterruptStatus);
        
        /* Acknowledge all of the current interrupt sources ASAP, but
           an first get an additional status bit from CSCR. */
        
        if ((status & RxUnderrun) && 
            port_uint16_in (device->port_base + CSCR) & CSCR_LinkChangeBit)
        {
            link_changed = 1;
        }
        
        port_uint16_out (device->port_base + InterruptStatus, status);
        
        if ((status & (PCIError | PCSTimeout | RxUnderrun | RxOverflow | 
                       RxFIFOOverrun | TxError | TxOK | RxError | RxOK)) == 0)
        {
            break;
        }
        
        /* Rx interrupt. */
        
        if ((status & (RxOK | RxUnderrun | RxOverflow | RxFIFOOverrun)) != 0)
        {
            realtek_receive (device);
        }
        
        if ((status & (TxOK | TxError)) != 0) 
        {
            unsigned int dirty_tx = device->dirty_tx;
          
            while (device->current_tx - dirty_tx > 0) 
            {
                int entry = dirty_tx % NUMBER_OF_TX_DESCRIPTORS;
                int txstatus = port_uint32_in (device->port_base + TxStatus0 + 
                    entry * 4);
            
                if ((txstatus & (TxStatusOK | TxUnderrun | TxAborted)) == 0)
                {
                    /* It still hasn't been transmitted. */
              
                    break;
                }
            
                /* Note: TxCarrierLost is always asserted at 100 Mbps. */
            
                if ((txstatus & (TxOutOfWindow | TxAborted)) != 0)
                {
                    /* There was an major error, log it. */
              
                    // device->stats.tx_errors++;

                    if ((txstatus & TxAborted) != 0)
                    {
                        // tp->stats.tx_aborted_errors++;

                        port_uint32_out (device->port_base + TxConfig, 
                            (TX_DMA_BURST << 8) | 0x03000001);
                    }
              
                    if ((txstatus & TxCarrierLost) != 0)
                    {
                        // tp->stats.tx_carrier_errors++;
                    }
              
                    if ((txstatus & TxOutOfWindow) != 0)
                    {
                        // tp->stats.tx_window_errors++;
                    }
                }
                else 
                {
                    if ((txstatus & TxUnderrun) != 0)
                    {
                        /* Add 64 to the Tx FIFO threshold. */
                
                        if (device->tx_flag < 0x00300000)
                        {
                            device->tx_flag += 0x00020000;
                        }
                
                        // tp->stats.tx_fifo_errors++;
                    }
              
                    // tp->stats.collisions += (txstatus >> 24) & 15;
                    // tp->stats.tx_bytes += txstatus & 0x7ff;
                    // tp->stats.tx_packets++;
                }
            
                // if (tp->tx_info[entry].mapping != 0)
                // {
                //   pci_unmap_single (tp->pdev,
                //                     tp->tx_info[entry].mapping,
                //                     tp->tx_info[entry].skb->len,
                //                     PCI_DMA_TODEVICE);
                // tp->tx_info[entry].mapping = 0;
                // }
          
                /* Free the original skb. */
            
                // dev_kfree_skb_irq (tp->tx_info[entry].skb);
                //          tp->tx_info[entry].skb = NULL;
            
                if (device->tx_full) 
                {
                    /* The ring is no longer full, wake the queue. */
              
                    device->tx_full = FALSE;
              
                    // netif_wake_queue(dev);
                }
            
                dirty_tx++;
            }
          
            device->dirty_tx = dirty_tx;
        }
        
        /* Check uncommon events with one test. */
        
        if ((status & (PCIError | PCSTimeout | RxUnderrun | RxOverflow | 
            RxFIFOOverrun | TxError | RxError)) != 0)
        {
            if (realtek_debug > 2)
            {
                DEBUG_PRINT (DEBUG_LEVEL_WARNING,
                    "Abnormal interrupt, status %8.8x.\n",
                    status);
            }
          
            if (status == 0xFFFFFFFF)
            {
                break;
            }
          
            /* Update the error count. */
          
            // tp->stats.rx_missed_errors += inl(port_base + RxMissed);
            port_uint32_out (device->port_base + RxMissed, 0);
          
            if ((status & RxUnderrun) != 0 && link_changed)
            {
                /* Really link-change on new chips. */
            
                int lpar = port_uint16_in (device->port_base + NWayLPAR);
                int duplex = (lpar & 0x0100) || (lpar & 0x01C0) == 0x0040; 
            
                if (device->full_duplex != duplex) 
                {
                    device->full_duplex = duplex;
              
                    port_uint8_out (device->port_base + Config9346, 0xC0);
                    port_uint8_out (device->port_base + Config1, 
                        device->full_duplex ? 0x60 : 0x20);
                    port_uint8_out (device->port_base + Config9346, 0x00);
                }
                
                status &= ~RxUnderrun;
            }
          
            if ((status & (RxUnderrun | RxOverflow | RxError | RxFIFOOverrun)) 
                != 0)
            {
                // tp->stats.rx_errors++;
            }
          
            if ((status & (PCSTimeout)) != 0)
            {
                // tp->stats.rx_length_errors++;
            }
          
            if ((status & (RxUnderrun | RxFIFOOverrun)) != 0)
            {
                //  tp->stats.rx_fifo_errors++;
            }
          
            if ((status & RxOverflow) != 0)
            {
                // tp->stats.rx_over_errors++;
                device->current_rx = 
                    (port_uint16_in (device->port_base + RxBufferAddress) % 
                        RX_BUFFER_LENGTH);
                port_uint16_out (device->port_base + RxBufferPointer, 
                    device->current_rx - 16);
            }
          
            if ((status & PCIError) != 0) 
            {
                DEBUG_PRINT (DEBUG_LEVEL_WARNING, "PCI Bus error.\n");
            }
        }
        
        if (--bogus_count < 0) 
        {
            DEBUG_PRINT (DEBUG_LEVEL_WARNING,
                "Too much work at interrupt, InterruptStatus = 0x%4.4x.\n",
                status);
          
            /* Clear all interrupt sources. */
          
            port_uint16_out (device->port_base + InterruptStatus, 0xFFFF);
            break;
        }
        
    } while (TRUE);
}

static void rt_register_irq_handler (int irq, realtek_device_t *device)
{
//    system_thread_name_set ("IRQ handler");

    irq_register (irq, rt_irq_handler, device);
}

/* Handle a given Realtek 8139 adapter. */

static void handle_8139 (pci_device_info_t *device_info)
{
    unsigned int counter;
    uint16_t port_base = UINT16_MAX;
    uint16_t ports = 0;
    realtek_device_t *device;
    unsigned int physical, physical_index;

//    system_thread_name_set ("Initialising");
  
    for (counter = 0; counter < PCI_NUMBER_OF_RESOURCES; counter++)
    {
        if ((device_info->resource[counter].flags & PCI_RESOURCE_IO) != 0)
        {
            port_base = device_info->resource[counter].start;
            ports = (device_info->resource[counter].end -
                device_info->resource[counter].start + 1);
        }
    }

    if (port_base == UINT16_MAX)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
            "No port range found -- hardware possibly broken or incompatible?");
            
        return;
    }

    io_port_register (port_base, ports, "Realtek 8139");

    memory_allocate ((void **) &device, sizeof (realtek_device_t));

    device->port_base = port_base;
    device->irq = device_info->irq;

    /* Initialise the adapter. */

    port_uint8_out (port_base + Config1, 0x00);
  
    if (read_eeprom (port_base, 0) != 0xFFFF) 
    {
        for (counter = 0; counter < 3; counter++) 
        {
            ((uint16_t *)(device->ethernet_address))[counter] =
                little_endian_to_native_uint16 (read_eeprom (port_base, 
                    counter + 7));
        }
    }
    else 
    {
        for (counter = 0; counter < 6; counter++)
        {
            device->ethernet_address[counter] = 
                port_uint8_in (port_base + MAC0 + counter);
        }
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "Realtek 8139 at 0x%X, IRQ %d, \
        ethernet address: %02X:%02X:%02X:%02X:%02X:%02X\n",
        port_base, device_info->irq, device->ethernet_address[0], 
        device->ethernet_address[1], device->ethernet_address[2], 
        device->ethernet_address[3], device->ethernet_address[4],
        device->ethernet_address[5]);

    /* Find the connected MII transceivers. */

    for (physical = 0, physical_index = 0; 
        physical < 32 && physical_index < sizeof (device->mii_address); 
        physical++)
    {
        int mii_status = mdio_read (port_base, physical, 1);

        if (mii_status != 0xFFFF && mii_status != 0x0000) 
        {
            device->mii_address[physical_index] = physical;
            physical_index++;

            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
               "MII transceiver found at address %d.\n",
               physical);
        }
    }

    if (physical_index == 0) 
    {
        if (realtek_debug > 1)
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
                "No MII transceivers found! Assuming SYM transceiver.\n");
        }

        device->mii_address[0] = -1;
    }

    /* Soft reset the chip. */

    port_uint8_out (port_base + ChipCommand, CommandReset);
/*
    pci_allocate_buffer ((void **) &device->tx_buffers_dma,
        (void **) &device->tx_buffers, 
        TX_BUFFER_SIZE * NUMBER_OF_TX_DESCRIPTORS);
                       
    pci_allocate_buffer ((void **) &device->rx_ring_dma,
        (void **) &device->rx_ring,
        RX_BUFFER_LENGTH + 16);
*/
    memory_allocate ((void **) &device->tx_buffers, 
        TX_BUFFER_SIZE * NUMBER_OF_TX_DESCRIPTORS);
    device->tx_buffers_dma = device->tx_buffers;
    
    memory_allocate ((void **) &device->rx_ring,
        RX_BUFFER_LENGTH + 16);
    device->rx_ring_dma = device->rx_ring;

    device->tx_full = FALSE;
    device->current_rx = 0;
    device->dirty_tx = device->current_tx = 0;

    for (counter = 0; counter < NUMBER_OF_TX_DESCRIPTORS; counter++) 
    {
        device->tx_buffer[counter] = &device->tx_buffers[counter * TX_BUFFER_SIZE];
    }
  
    /* Check that the chip has finished the reset. */

    for (counter = 0; counter < 1000; counter++)
    {
        if ((port_uint8_in (port_base + ChipCommand) & CommandReset) == 0)
        {
            break;
        }
    }

    /* Must enable Tx/Rx before setting transfer thresholds! */

    port_uint8_out (port_base + ChipCommand, 
        CommandRxEnable | CommandTxEnable);
    port_uint32_out (port_base + RxConfig, 
        (RX_FIFO_THRESHOLD << 13) | 
        (RX_BUFFER_LENGTH_INDEX << 11) | 
        (RX_DMA_BURST << 8));

    port_uint32_out (port_base + TxConfig, (TX_DMA_BURST << 8) | 0x03000000);

    if (device->mii_address[0] >= 0) 
    {
        uint16_t mii_reg5 = mdio_read (port_base, device->mii_address[0], 5);

        if (mii_reg5 == 0xffff)
        {
        }
        else if ((mii_reg5 & 0x0100) == 0x0100 || 
            (mii_reg5 & 0x00C0) == 0x0040)
        {
            device->full_duplex = TRUE;
        }

        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
            "Setting %s%s-duplex based on"
            " auto-negotiated partner ability %4.4x.\n",
            mii_reg5 == 0 ? "" :
                ((mii_reg5 & 0x0180) != 0) ? "100 Mbps " : 
                "10 Mbps ",
            device->full_duplex ? "full" : "half", mii_reg5);
    }
  
    port_uint8_out (port_base + Config9346, 0xC0);
    port_uint8_out (port_base + Config1, device->full_duplex ? 0x60 : 0x20);
    port_uint8_out (port_base + Config9346, 0x00);

    port_uint32_out (port_base + RxBuffer, (uint32_t) device->rx_ring_dma);
  
    /* Start the chip's Tx and Rx process. */
  
    port_uint32_out (port_base + RxMissed, 0);
    set_rx_mode (device);
  
    port_uint8_out (port_base + ChipCommand, 
        CommandRxEnable | CommandTxEnable);
  
    /* Enable all known interrupts by setting the interrupt mask. */
  
    port_uint16_out (port_base + InterruptMask,
        PCIError | PCSTimeout | RxUnderrun | RxOverflow | 
        RxFIFOOverrun | TxError | TxOK | RxError | RxOK);

    rt_register_irq_handler (device_info->irq, device);

    /* Now, use the remaining thread for the service handler. */

//    system_thread_name_set ("Service handler");

  /* Create the service. */
/*
  if (ipc_service_create ("ethernet", &ipc_structure, &empty_tag) !=
      IPC_RETURN_SUCCESS)
  {
    log_print (&log_structure, LOG_URGENCY_EMERGENCY,
               "Couldn't create ethernet service.");
    return;
  }

  while (TRUE)
  {
    mailbox_id_type reply_mailbox_id;

    ipc_service_connection_wait (&ipc_structure);
    reply_mailbox_id = ipc_structure.output_mailbox_id;

    if (system_thread_create () == SYSTEM_RETURN_THREAD_NEW)
    {
      system_call_thread_name_set ("Handling connection");
      handle_connection (reply_mailbox_id, device);
    }
  }    
*/  
}

return_t realtek_pci_main (int argc UNUSED, char *argv[] UNUSED)
{
    pci_device_info_t device_info;
    unsigned int number_of_devices;
    unsigned int probe_counter;
    handle_t pci;
    handle_t rt_device;
    
    global_namespace_resolve ("/devices/pci", &pci);
    register_object_open (&pci, IID_PCI_BUS);
  
    for (probe_counter = 0; pci_device_probe[probe_counter].vendor_id != 
        0xFFFF; probe_counter++)
    {
        uint32_t device = 0;
        number_of_devices = 1;
        
        pci_bus$find_devices (&pci, pci_device_probe[probe_counter].vendor_id,
            pci_device_probe[probe_counter].device_id, 0xFF, 0xFF, 0xFF, device, 
            &number_of_devices, &rt_device);

        if (number_of_devices == 1)
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
                "Found Realtek8139 adapter.\n");
            
            register_object_open (&rt_device, IID_PCI_DEVICE);
            pci_device$get_info (&rt_device, &device_info);
            handle_8139 (&device_info);
        }
    }

    return 0;
}

