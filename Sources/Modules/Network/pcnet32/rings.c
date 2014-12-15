
#include <enviroment.h>

#include <Interfaces/pci_device.h>

#include "Include/types.h"
#include "Include/pcnet32_lowlevel.h"
#include "Include/pcnet32.h"

#define DEBUG_MODULE_NAME "PCNet32"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>

#define PKT_BUF_SZ		1544

static const int rx_copybreak = 200;

/*
 * The LANCE has been halted for one reason or another (busmaster memory
 * arbitration error, Tx FIFO underflow, driver stopped it to reconfigure,
 * etc.).  Modern LANCE variants always reload their ring-buffer
 * configuration when restarted, so we must reinitialize our ring
 * context before restarting.  As part of this reinitialization,
 * find all packets still on the Tx ring and pretend that they had been
 * sent (in effect, drop the packets on the floor) - the higher-level
 * protocols will time out and retransmit.  It'd be better to shuffle
 * these skbs to a temp list and then actually re-Tx them after
 * restarting the chip, but I'm too lazy to do so right now.  dplatt@3do.com
 */

void pcnet32_purge_tx_ring (ethernet_device_t *dev)
{
    pcnet32_private_t *lp = dev->priv;
    int i;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p)\n", 
        DEBUG_MODULE_NAME, __FUNCTION__,
        dev);

    for (i = 0; i < TX_RING_SIZE; i++) 
    {
        if (lp->tx_skbuff[i] != NULL) 
        {
//            pci_unmap_single(lp->pci_dev, lp->tx_dma_addr[i], 
//                lp->tx_skbuff[i]->len, PCI_DMA_TODEVICE);
//            dev_kfree_skb (lp->tx_skbuff[i]); 
            memory_deallocate (lp->tx_skbuff[i]);
            
            lp->tx_skbuff[i] = NULL;
            lp->tx_dma_addr[i] = 0;
        }
    }
}

/* Initialize the PCNET32 Rx and Tx rings. */
int pcnet32_init_ring (ethernet_device_t *dev)
{
    pcnet32_private_t *lp = dev->priv;
    int i;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p)\n", 
        DEBUG_MODULE_NAME, __FUNCTION__,
        dev);

    lp->tx_full = 0;
    lp->cur_rx = lp->cur_tx = 0;
    lp->dirty_rx = lp->dirty_tx = 0;

    for (i = 0; i < RX_RING_SIZE; i++)
    {
//        struct sk_buff *rx_skbuff = lp->rx_skbuff[i];
        void *rx_skbuff = lp->rx_skbuff[i];

        if (rx_skbuff == NULL) 
        {
//            if (!(rx_skbuff = lp->rx_skbuff[i] = dev_alloc_skb (PKT_BUF_SZ)))
//            {
//                /* there is not much, we can do at this point */
//                DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
//                    "%s: pcnet32_init_ring dev_alloc_skb failed.\n",
//                    dev->name);
//                    
//                return -1;
//            }
            memory_allocate (&rx_skbuff, PKT_BUF_SZ);
            memory_clear (rx_skbuff, PKT_BUF_SZ);
            lp->rx_skbuff[i] = rx_skbuff;

//            skb_reserve (rx_skbuff, 2);
//            rx_skbuff += 2;
        }
        
//        lp->rx_dma_addr[i] = pci_map_single (lp->pci_dev, rx_skbuff->tail, 
//            rx_skbuff->len, PCI_DMA_FROMDEVICE);
        lp->rx_dma_addr[i] = (dma_addr_t) rx_skbuff;
            
        lp->rx_ring[i].base = (uint32_t) little_endian_to_native_uint32 (
            lp->rx_dma_addr[i]);
        lp->rx_ring[i].buf_length = little_endian_to_native_uint16 (
            -PKT_BUF_SZ);
        lp->rx_ring[i].status = little_endian_to_native_uint16 (0x8000);
    }
    
    /* The Tx buffer address is filled in as needed, but we do need to clear
       the upper ownership bit. */
    for (i = 0; i < TX_RING_SIZE; i++) 
    {
        lp->tx_ring[i].base = 0;
        lp->tx_ring[i].status = 0;
        lp->tx_dma_addr[i] = 0;
    }

    lp->init_block.tlen_rlen = little_endian_to_native_uint16 (
        TX_RING_LEN_BITS | RX_RING_LEN_BITS);
    
    for (i = 0; i < 6; i++)
    {
        lp->init_block.phys_addr[i] = dev->ethernet_address[i];

        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1, 
            " %x", lp->init_block.phys_addr[i]);
    }
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1, "\n");
        
    lp->init_block.rx_ring = little_endian_to_native_uint32 (lp->dma_addr + 
        offset_of (pcnet32_private_t, rx_ring));
        
    lp->init_block.tx_ring = little_endian_to_native_uint32 (lp->dma_addr + 
        offset_of (pcnet32_private_t, tx_ring));

	asm volatile ("wbinvd": : :"memory");
        
    return 0;
}


void pcnet32_tx_timeout (ethernet_device_t *dev)
{
    pcnet32_private_t *lp = dev->priv;
    unsigned int ioaddr = dev->base_addr;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p)\n", 
        DEBUG_MODULE_NAME, __FUNCTION__,
        dev);

    /* Transmitter timeout, serious problems. */
	DEBUG_PRINT (DEBUG_LEVEL_ERROR,
        "%s: transmit timed out, status %4.4x, resetting.\n",
	    dev->name, lp->a.read_csr (ioaddr, 0));
           
	lp->a.write_csr (ioaddr, 0, 0x0004);
	lp->stats.tx_errors++;
    
	if (pcnet32_debug > 2)
    {
        int i;
        
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
            " Ring data dump: dirty_tx %d cur_tx %d%s cur_rx %d.",
            lp->dirty_tx, lp->cur_tx, lp->tx_full ? " (full)" : "",
            lp->cur_rx);

        for (i = 0 ; i < RX_RING_SIZE; i++)
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
                "%s %08x %04x %08x %04x", i & 1 ? "" : "\n ",
                lp->rx_ring[i].base, -lp->rx_ring[i].buf_length,
                lp->rx_ring[i].msg_length, (unsigned)lp->rx_ring[i].status);
        }
        
        for (i = 0 ; i < TX_RING_SIZE; i++)
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
                "%s %08x %04x %08x %04x", i & 1 ? "" : "\n ",
                lp->tx_ring[i].base, -lp->tx_ring[i].length,
                lp->tx_ring[i].misc, (unsigned)lp->tx_ring[i].status);
        }
           
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "\n");
	}
    
	pcnet32_restart (dev, 0x0042);

//	dev->trans_start = jiffies;
//	netif_start_queue(dev);
}

int pcnet32_start_xmit (ethernet_device_t *dev, void *data, size_t length)
{
    pcnet32_private_t *lp = dev->priv;
    unsigned int ioaddr = dev->base_addr;
    uint16_t status;
    int entry;
    unsigned long flags;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p)\n", 
        DEBUG_MODULE_NAME, __FUNCTION__,
        dev);

    if (pcnet32_debug > 3) 
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
            "%s: pcnet32_start_xmit() called, csr0 %4.4x.\n",
            dev->name, lp->a.read_csr (ioaddr, 0));
    }

    spin_lock_irqsave (&lp->lock, flags);

    /* Default status -- will not enable Successful-TxDone
     * interrupt when that option is available to us.
     */
    status = 0x8300;
    
    if ((lp->ltint) && ((lp->cur_tx - lp->dirty_tx == TX_RING_SIZE/2) ||
        (lp->cur_tx - lp->dirty_tx >= TX_RING_SIZE-2)))
    {
        /* Enable Successful-TxDone interrupt if we have
         * 1/2 of, or nearly all of, our ring buffer Tx'd
         * but not yet cleaned up.  Thus, most of the time,
         * we will not enable Successful-TxDone interrupts.
         */
        status = 0x9300;
    }
  
    /* Fill in a Tx ring entry */
  
    /* Mask to ring buffer boundary. */
    entry = lp->cur_tx & TX_RING_MOD_MASK;
  
    /* Caution: the write order is important here, set the base address
       with the "ownership" bits last. */

//    lp->tx_ring[entry].length = little_endian_to_native_uint16 (-skb->len);
    lp->tx_ring[entry].length = little_endian_to_native_uint16 (-length);

    lp->tx_ring[entry].misc = 0x00000000;

//    lp->tx_skbuff[entry] = skb;
//    lp->tx_dma_addr[entry] = pci_map_single (lp->pci_dev, skb->data, skb->len, PCI_DMA_TODEVICE);
    lp->tx_skbuff[entry] = data;
    lp->tx_dma_addr[entry] = (dma_addr_t) data;

    lp->tx_ring[entry].base = little_endian_to_native_uint32 (
        lp->tx_dma_addr[entry]);
    lp->tx_ring[entry].status = little_endian_to_native_uint16 (status);

    lp->cur_tx++;
    lp->stats.tx_bytes += length;

    /* Trigger an immediate send poll. */
    lp->a.write_csr (ioaddr, 0, 0x0048);

//    dev->trans_start = jiffies;

    if (lp->tx_ring[(entry+1) & TX_RING_MOD_MASK].base == 0)
    {
//        netif_start_queue(dev);
    }
    else
    {
        lp->tx_full = 1;
//        netif_stop_queue(dev);
    }
    
    spin_unlock_irqrestore (&lp->lock, flags);
    
    return 0;
}

int pcnet32_rx (ethernet_device_t *dev)
{
    pcnet32_private_t *lp = dev->priv;
    int entry = lp->cur_rx & RX_RING_MOD_MASK;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p)\n", 
        DEBUG_MODULE_NAME, __FUNCTION__,
        dev);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1, 
        "%s: %s: Entry=%i, base=%x, buf_len=%x, status=%x, msg_len=%x\n", 
        DEBUG_MODULE_NAME, __FUNCTION__,
        entry, lp->rx_ring[entry].base, 
        (uint32_t) lp->rx_ring[entry].buf_length,
        (uint32_t) lp->rx_ring[entry].status, 
        lp->rx_ring[entry].msg_length);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1, 
        "%s: %s: rx=%x.%x.%x.%x.%x\n", 
        DEBUG_MODULE_NAME, __FUNCTION__,
        ((uint32_t *) lp->rx_ring[entry].base)[0],
        ((uint32_t *) lp->rx_ring[entry].base)[1],
        ((uint32_t *) lp->rx_ring[entry].base)[2],
        ((uint32_t *) lp->rx_ring[entry].base)[3],
        ((uint32_t *) lp->rx_ring[entry].base)[4]);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1, 
        "%s: %s: Init rx=%x, tx=%x mode=%x, rx=%x.%x.%x.%x.%x.%x.%x.%x\n", 
        DEBUG_MODULE_NAME, __FUNCTION__,
        lp->init_block.rx_ring, lp->init_block.tx_ring, lp->init_block.mode,
        ((uint32_t *)lp->init_block.rx_ring)[0],
        ((uint32_t *)lp->init_block.rx_ring)[1],
        ((uint32_t *)lp->init_block.rx_ring)[2],
        ((uint32_t *)lp->init_block.rx_ring)[3],
        ((uint32_t *)lp->init_block.rx_ring)[4],
        ((uint32_t *)lp->init_block.rx_ring)[5],
        ((uint32_t *)lp->init_block.rx_ring)[6],
        ((uint32_t *)lp->init_block.rx_ring)[7]);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1, 
        "%s: %s: Init tx=%x.%x.%x.%x.%x\n", 
        DEBUG_MODULE_NAME, __FUNCTION__,
        ((uint32_t *)lp->init_block.tx_ring)[0],
        ((uint32_t *)lp->init_block.tx_ring)[1],
        ((uint32_t *)lp->init_block.tx_ring)[2],
        ((uint32_t *)lp->init_block.tx_ring)[3],
        ((uint32_t *)lp->init_block.tx_ring)[4]);

    /* If we own the next entry, it's a new packet. Send it up. */
    while ((short) little_endian_to_native_uint16 (lp->rx_ring[entry].status) 
        >= 0)
    {
        int status = (short) little_endian_to_native_uint16 (
            lp->rx_ring[entry].status) >> 8;

        if (status != 0x03)
        {			/* There was an error. */
            /* 
             * There is a tricky error noted by John Murphy,
             * <murf@perftech.com> to Russ Nelson: Even with full-sized
             * buffers it's possible for a jabber packet to use two
             * buffers, with only the last correctly noting the error.
             */
            if (status & 0x01)	/* Only count a general error at the */
            {
                lp->stats.rx_errors++; /* end of a packet.*/
            }
            
            if (status & 0x20) lp->stats.rx_frame_errors++;
            if (status & 0x10) lp->stats.rx_over_errors++;
            if (status & 0x08) lp->stats.rx_crc_errors++;
            if (status & 0x04) lp->stats.rx_fifo_errors++;
            
            lp->rx_ring[entry].status &= little_endian_to_native_uint16 (
                0x03ff);
        } 
        else 
        {
            /* Malloc up new buffer, compatible with net-2e. */
            uint16_t pkt_len = (little_endian_to_native_uint32 (
                lp->rx_ring[entry].msg_length) & 0xfff) - 4;

//            sk_buff_t *skb;
            void *data = NULL;
            			
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1, 
                "%s: New packet: %u bytes.\n", 
                __FUNCTION__,
                pkt_len);

            if (pkt_len < 60) 
            {
                DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
                    "%s: Runt packet!\n", 
                    dev->name);

                lp->stats.rx_errors++;
            } 
            else 
            {
                int rx_in_place = 0;

                if (pkt_len > rx_copybreak)
                {
//                    struct sk_buff *newskb;
				
				    void *new_data;
                    memory_allocate (&new_data, PKT_BUF_SZ);
                    
//                    if ((newskb = dev_alloc_skb (PKT_BUF_SZ)))
                    if (new_data != NULL)
                    {
//                        skb_reserve (newskb, 2);
//                        new_data += 2;
                        
//                        skb = lp->rx_skbuff[entry];
                        data = lp->rx_skbuff[entry];
                        
//                        skb_put (skb, pkt_len);
                        
//                        lp->rx_skbuff[entry] = newskb;
                        lp->rx_skbuff[entry] = new_data;

//                        newskb->dev = dev;
//                        lp->rx_dma_addr[entry] = pci_map_single (lp->pci_dev, 
//                            newskb->tail, newskb->len, PCI_DMA_FROMDEVICE);
                        lp->rx_dma_addr[entry] = (dma_addr_t) new_data;
                        lp->rx_ring[entry].base = 
                            little_endian_to_native_uint32 (
                                lp->rx_dma_addr[entry]);
                        rx_in_place = 1;
                    }
                    else
                    {
//                        skb = NULL;
                        data = NULL;
                    }
                }
                else
                {
//                    skb = dev_alloc_skb(pkt_len+2);
                      memory_allocate (&data, pkt_len);
                }
			    
                if (data == NULL) 
                {
                    int i;
                
                    DEBUG_PRINT (DEBUG_LEVEL_ERROR,
                        "\"%s\": Memory squeeze, deferring packet.\n", 
                        dev->name);
                    
                    for (i = 0; i < RX_RING_SIZE; i++)
                    {
                        if ((short) little_endian_to_native_uint16 (
                            lp->rx_ring[(entry+i) & RX_RING_MOD_MASK].status) 
                            < 0)
                        {
                            break;
                        }
                    }

                    if (i > RX_RING_SIZE - 2)
                    {
                        lp->stats.rx_dropped++;
                        lp->rx_ring[entry].status |= 
                            little_endian_to_native_uint16 (0x8000);
                        lp->cur_rx++;
                    }
                    break;
                }
                
//                skb->dev = dev;
                
                if (!rx_in_place) 
                {
//                    skb_reserve(skb,2); /* 16 byte align */
//                    skb_put(skb,pkt_len);	/* Make room */
//                    eth_copy_and_sum(skb, 
//                        (unsigned char *)(lp->rx_skbuff[entry]->tail), 
//                        pkt_len, 0);
                    memory_copy (data, lp->rx_skbuff[entry], pkt_len);
                }
                
//                lp->stats.rx_bytes += skb->len;
//                skb->protocol = eth_type_trans(skb,dev);
//                netif_rx(skb);
                lp->stats.rx_packets++;

                DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1, 
                    "%s Receive packet: %lu (%u bytes).\n", 
                    __FUNCTION__,
                    lp->stats.rx_packets, pkt_len);
            }
        }
        
        /*
         * The docs say that the buffer length isn't touched, but Andrew Boyd
         * of QNX reports that some revs of the 79C965 clear it.
         */
        lp->rx_ring[entry].buf_length = little_endian_to_native_uint16 (
            -PKT_BUF_SZ);
        lp->rx_ring[entry].status |= little_endian_to_native_uint16 (0x8000);
        entry = (++lp->cur_rx) & RX_RING_MOD_MASK;
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1, 
        "%s: %s return.\n", 
        DEBUG_MODULE_NAME, __FUNCTION__);

    return 0;
}

