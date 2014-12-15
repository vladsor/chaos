#include <enviroment.h>

#include "Include/types.h"
#include "Include/pcnet32_lowlevel.h"
#include "Include/pcnet32.h"

#define DEBUG_MODULE_NAME "PCNet32"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

static const int max_interrupt_work = 80;

/* The PCNET32 interrupt handler. */
void pcnet32_interrupt (unsigned int irq_number UNUSED, p_void_t parameter, 
    irq_cpu_registers_t registers UNUSED)
{
    ethernet_device_t *dev = (ethernet_device_t *) parameter;
    
    pcnet32_private_t *lp;
    unsigned long ioaddr;
    uint16_t csr0, rap;
    int boguscnt =  max_interrupt_work;
    int must_restart;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s: %s: (%p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__, dev);
        
	asm volatile ("lock; addl $0,0(%%esp); invd": : :"memory");

    if (dev == NULL) 
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
            "pcnet32_interrupt(): irq %d for unknown device.\n", dev->irq);
        
        return;
    }

    ioaddr = dev->base_addr;
    lp = dev->priv;
    
    spin_lock (&lp->lock);
    
    rap = lp->a.read_rap (ioaddr);
    
    while ((csr0 = lp->a.read_csr (ioaddr, 0)) & 0x8600 && --boguscnt >= 0)
    {
        /* Acknowledge all of the current interrupt sources ASAP. */
        lp->a.write_csr (ioaddr, 0, csr0 & ~0x004f);

        must_restart = 0;

        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
            "%s: interrupt  csr0=%#2.2x new csr=%#2.2x.\n",
            DEBUG_MODULE_NAME, 
            csr0, lp->a.read_csr (ioaddr, 0));

        if (csr0 & 0x0400)      /* Rx interrupt */
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
                "%s: Rx interrupt.\n",
                DEBUG_MODULE_NAME);
                
            pcnet32_rx (dev);
        }

        if (csr0 & 0x0200)
        {       /* Tx-done interrupt */
            unsigned int dirty_tx = lp->dirty_tx;

            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
                "Tx-done interrupt.\n");

            while (dirty_tx < lp->cur_tx) 
            {
                int entry = dirty_tx & TX_RING_MOD_MASK;
                int status = (short) little_endian_to_native_uint16 (
                    lp->tx_ring[entry].status);
            
                if (status < 0)
                {
                    break;      /* It still hasn't been Txed */
                }

                lp->tx_ring[entry].base = 0;

                if (status & 0x4000) 
                {
                    /* There was an major error, log it. */
                    int err_status = little_endian_to_native_uint32 (
                        lp->tx_ring[entry].misc);
                    lp->stats.tx_errors++;
                    
                    if (err_status & 0x04000000) lp->stats.tx_aborted_errors++;
                    if (err_status & 0x08000000) lp->stats.tx_carrier_errors++;
                    if (err_status & 0x10000000) lp->stats.tx_window_errors++;
                    
#ifndef DO_DXSUFLO
                    if (err_status & 0x40000000) 
                    {
                        lp->stats.tx_fifo_errors++;
                        
                        /* Ackk!  On FIFO errors the Tx unit is turned off! */
                        /* Remove this verbosity later! */
                        DEBUG_PRINT (DEBUG_LEVEL_ERROR,
                            "%s: Tx FIFO error! CSR0=%4.4x\n",
                            dev->name, csr0);
                            
                        must_restart = 1;
                    }
#else
                    if (err_status & 0x40000000) 
                    {
                        lp->stats.tx_fifo_errors++;
                        
                        if (! lp->dxsuflo) 
                        {  /* If controller doesn't recover ... */
                            /* Ackk!  On FIFO errors the Tx unit is turned off! */
                            /* Remove this verbosity later! */
                            DEBUG_PRINT (DEBUG_LEVEL_ERROR,
                                "%s: Tx FIFO error! CSR0=%4.4x\n",
                                dev->name, csr0);
                                
                            must_restart = 1;
                        }
                    }
#endif
                } 
                else 
                {
                    if (status & 0x1800)
                    {
                        lp->stats.collisions++;
                    }
                    lp->stats.tx_packets++;
                }

                /* We must free the original skb */
                if (lp->tx_skbuff[entry]) 
                {
/*                
                    pci_unmap_single (lp->pci_dev, lp->tx_dma_addr[entry], 
                        lp->tx_skbuff[entry]->len, PCI_DMA_TODEVICE);
                        
                    dev_kfree_skb_irq (lp->tx_skbuff[entry]);
*/
                    memory_deallocate (lp->tx_skbuff[entry]);

                    lp->tx_skbuff[entry] = 0;
                    lp->tx_dma_addr[entry] = 0;

                }
                dirty_tx++;
            }

#ifndef final_version
            if (lp->cur_tx - dirty_tx >= TX_RING_SIZE) 
            {
                DEBUG_PRINT (DEBUG_LEVEL_ERROR,
                    "out-of-sync dirty pointer, %d vs. %d, full=%d.\n",
                    dirty_tx, lp->cur_tx, lp->tx_full);
                    
                dirty_tx += TX_RING_SIZE;
            }
#endif

            if (lp->tx_full &&
                /*netif_queue_stopped (dev) &&
*/
                dirty_tx > lp->cur_tx - TX_RING_SIZE + 2) 
            {
                /* The ring is no longer full, clear tbusy. */
                lp->tx_full = 0;
//                netif_wake_queue (dev);
            }

            lp->dirty_tx = dirty_tx;
        }

        /* Log misc errors. */
        if (csr0 & 0x4000) 
        {
            lp->stats.tx_errors++; /* Tx babble. */
        }
        
        if (csr0 & 0x1000)
        {
            /*
             * this happens when our receive ring is full. This shouldn't
             * be a problem as we will see normal rx interrupts for the frames
             * in the receive ring. But there are some PCI chipsets (I can reproduce
             * this on SP3G with Intel saturn chipset) which have sometimes problems
             * and will fill up the receive ring with error descriptors. In this
             * situation we don't get a rx interrupt, but a missed frame interrupt sooner
             * or later. So we try to clean up our receive ring here.
             */
            pcnet32_rx (dev);
            lp->stats.rx_errors++; /* Missed a Rx frame. */
        }
    
        if (csr0 & 0x0800) 
        {
            DEBUG_PRINT (DEBUG_LEVEL_ERROR,
                "%s: Bus master arbitration failure, status %4.4x.\n",
                dev->name, csr0);
            /* unlike for the lance, there is no restart needed */
        }

        if (must_restart)
        {
            /* stop the chip to clear the error condition, then restart */
            lp->a.write_csr (ioaddr, 0, 0x0004);
            pcnet32_restart (dev, 0x0002);
        }
    }

    /* Clear any other interrupt, and set interrupt enable. */
    lp->a.write_csr (ioaddr, 0, 0x7940);
    lp->a.write_rap (ioaddr, rap);
    
    if (pcnet32_debug > 4)
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
            "%s: exiting interrupt, csr0=%#4.4x.\n",
            DEBUG_MODULE_NAME, lp->a.read_csr (ioaddr, 0));
    }

    spin_unlock (&lp->lock);
}

