/* pcnet32.c: An AMD PCnet32 ethernet driver for linux. */
#include <enviroment.h>

#include <Interfaces/pci_device.h>

#include "types.h"
#include "pcnet32_lowlevel.h"
#include "pcnet32.h"

#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>

static unsigned int pcnet32_portlist[] = {0x300, 0x320, 0x340, 0x360, 0};

#define PCI_ANY_ID 0

static int tx_start = 1; /* Mapping -- 0:20, 1:64, 2:128, 3:~220 (depends on chip vers) */

/*
 *				Theory of Operation
 * 
 * This driver uses the same software structure as the normal lance
 * driver. So look for a verbose description in lance.c. The differences
 * to the normal lance driver is the use of the 32bit mode of PCnet32
 * and PCnetPCI chips. Because these chips are 32bit chips, there is no
 * 16MB limitation and we don't need bounce buffers.
 */


#define PCNET32_TOTAL_SIZE 0x20

#define CRC_POLYNOMIAL_LE 0xedb88320UL	/* Ethernet CRC, little endian */

int pcnet32_open (ethernet_device_t *dev)
{
    pcnet32_private_t *lp = dev->priv;
    unsigned long ioaddr = dev->base_addr;
    uint16_t val;
    int i;

    if (dev->irq == 0 || irq_register (dev->irq, &pcnet32_interrupt, 
        (p_void_t) dev) != 0) {
		    
        return -1;
    }

    /* Check for a valid station address */
    if (!is_valid_ethernet_address (dev->ethernet_address))
    {
        return -1;
    }

    /* Reset the PCNET32 */
    lp->a.reset (ioaddr);

    /* switch pcnet32 to 32bit mode */
    lp->a.write_bcr (ioaddr, 20, 2);

    if (pcnet32_debug > 1)
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
            "\"%s\": pcnet32_open() irq %d tx/rx rings %#x/%#x init %#x.\n",
            dev->name, dev->irq,
            (uint32_t) (lp->dma_addr + offset_of (pcnet32_private_t, tx_ring)),
            (uint32_t) (lp->dma_addr + offset_of (pcnet32_private_t, rx_ring)),
            (uint32_t) (lp->dma_addr + 
                offset_of (pcnet32_private_t, init_block)));
    }
        
    /* set/reset autoselect bit */
    val = lp->a.read_bcr (ioaddr, 2) & ~2;
    
    if (lp->options & PORT_ASEL)
    {
        val |= 2;
    }
    
    lp->a.write_bcr (ioaddr, 2, val);
    
    /* handle full duplex setting */
    if (lp->full_duplex)
    {
        val = lp->a.read_bcr (ioaddr, 9) & ~3;
	
        if (lp->options & PORT_FD)
        {
            val |= 1;
            if (lp->options == (PORT_FD | PORT_AUI))
            {
                val |= 2;
            }
        }
        lp->a.write_bcr (ioaddr, 9, val);
    }
    
    /* set/reset GPSI bit in test register */
    val = lp->a.read_csr (ioaddr, 124) & ~0x10;
    
    if ((lp->options & PORT_PORTSEL) == PORT_GPSI)
    {
        val |= 0x10;
    }
    
    lp->a.write_csr (ioaddr, 124, val);
    
    if (lp->mii && !(lp->options & PORT_ASEL))
    {
        val = lp->a.read_bcr (ioaddr, 32) & ~0x38; /* disable Auto Negotiation, set 10Mpbs, HD */
        
        if (lp->options & PORT_FD)
        {
            val |= 0x10;
        }
        
        if (lp->options & PORT_100)
        {
            val |= 0x08;
        }
        lp->a.write_bcr (ioaddr, 32, val);
    } 
    else 
    {
        if (lp->options & PORT_ASEL) 
        {  /* enable auto negotiate, setup, disable fd */
            val = lp->a.read_bcr(ioaddr, 32) & ~0x98;
            val |= 0x20;
            lp->a.write_bcr(ioaddr, 32, val);
        }
    }

#ifdef DO_DXSUFLO 
    if (lp->dxsuflo) 
    { /* Disable transmit stop on underflow */
        val = lp->a.read_csr (ioaddr, 3);
        val |= 0x40;
        lp->a.write_csr (ioaddr, 3, val);
    }
#endif

    if (lp->ltint) 
    { /* Enable TxDone-intr inhibitor */
        val = lp->a.read_csr (ioaddr, 5);
        val |= (1<<14);
        lp->a.write_csr (ioaddr, 5, val);
    }
   
    lp->init_block.mode = little_endian_to_native_uint16 (
        (lp->options & PORT_PORTSEL) << 7);
    lp->init_block.filter[0] = 0x00000000;
    lp->init_block.filter[1] = 0x00000000;

    if (pcnet32_init_ring (dev))
    {
        return -1;
    }
    
    /* Re-initialize the PCNET32, and start it when done. */
    lp->a.write_csr (ioaddr, 1, (lp->dma_addr + offset_of (
        pcnet32_private_t, init_block)) &0xffff);
    lp->a.write_csr (ioaddr, 2, (lp->dma_addr + offset_of (
        pcnet32_private_t, init_block)) >> 16);

    lp->a.write_csr (ioaddr, 4, 0x0915);
    lp->a.write_csr (ioaddr, 0, 0x0001);

//    netif_start_queue(dev);

    i = 0;
    
    while (i++ < 100)
    {
        if (lp->a.read_csr (ioaddr, 0) & 0x0100)
        {
            break;
        }
    }
    /* 
     * We used to clear the InitDone bit, 0x0100, here but Mark Stockton
     * reports that doing so triggers a bug in the '974.
     */
    lp->a.write_csr (ioaddr, 0, 0x0042);

    if (pcnet32_debug > 2)
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
            "\"%s\": pcnet32 open after %d ticks, init block %#x csr0 %4.4x.\n",
            dev->name, i, (uint32_t) (lp->dma_addr + offset_of (
                pcnet32_private_t, init_block)), lp->a.read_csr (ioaddr, 0));
    }
    
    return 0;	/* Always succeed */
}

void pcnet32_restart (ethernet_device_t *dev, unsigned int csr0_bits)
{
    pcnet32_private_t *lp = dev->priv;
    unsigned long ioaddr = dev->base_addr;
    int i;
    
    pcnet32_purge_tx_ring (dev);
    
    if (pcnet32_init_ring (dev))
    {
        return;
    }
    
    /* ReInit Ring */
    lp->a.write_csr (ioaddr, 0, 1);
    i = 0;
    
    while (i++ < 100)
    {
        if (lp->a.read_csr (ioaddr, 0) & 0x0100)
        {
            break;
        }
    }

    lp->a.write_csr (ioaddr, 0, csr0_bits);
}

int pcnet32_close (ethernet_device_t *dev)
{
    unsigned long ioaddr = dev->base_addr;
    pcnet32_private_t *lp = dev->priv;
    int i;

//    netif_stop_queue(dev);

    lp->stats.rx_missed_errors = lp->a.read_csr (ioaddr, 112);

    if (pcnet32_debug > 1)
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
            "%s: Shutting down ethercard, status was %2.2x.\n",
                dev->name, lp->a.read_csr (ioaddr, 0));
    }

    /* We stop the PCNET32 here -- it occasionally polls memory if we don't. */
    lp->a.write_csr (ioaddr, 0, 0x0004);

    /*
     * Switch back to 16bit mode to avoid problems with dumb 
     * DOS packet driver after a warm reboot
     */
    lp->a.write_bcr (ioaddr, 20, 4);

//    free_irq (dev->irq, dev);
    irq_unregister (dev->irq);
    
    /* free all allocated skbuffs */
    for (i = 0; i < RX_RING_SIZE; i++)
    {
        lp->rx_ring[i].status = 0;			    
        if (lp->rx_skbuff[i])
        {
//            pci_unmap_single(lp->pci_dev, lp->rx_dma_addr[i], 
//                lp->rx_skbuff[i]->len, PCI_DMA_FROMDEVICE);
//            dev_kfree_skb(lp->rx_skbuff[i]);
        }
        lp->rx_skbuff[i] = NULL;
        lp->rx_dma_addr[i] = 0;
    }
    
    for (i = 0; i < TX_RING_SIZE; i++)
    {
        if (lp->tx_skbuff[i]) 
        {
//            pci_unmap_single(lp->pci_dev, lp->tx_dma_addr[i], 
//                lp->tx_skbuff[i]->len, PCI_DMA_TODEVICE);
//            dev_kfree_skb(lp->tx_skbuff[i]);
        }
        lp->tx_skbuff[i] = NULL;
        lp->tx_dma_addr[i] = 0;
    }
    
//    MOD_DEC_USE_COUNT;

    return 0;
}

net_device_stats_t * pcnet32_get_stats (ethernet_device_t *dev)
{
    pcnet32_private_t *lp = dev->priv;
    unsigned long ioaddr = dev->base_addr;
    uint16_t saved_addr;
    unsigned long flags;

    spin_lock_irqsave (&lp->lock, flags);
    
    saved_addr = lp->a.read_rap(ioaddr);
    lp->stats.rx_missed_errors = lp->a.read_csr (ioaddr, 112);
    lp->a.write_rap (ioaddr, saved_addr);
    
    spin_unlock_irqrestore (&lp->lock, flags);

    return &lp->stats;
}
#if 0
/* taken from the sunlance driver, which it took from the depca driver */
void pcnet32_load_multicast (ethernet_device_t *dev)
{
    pcnet32_private_t *lp = dev->priv;
    volatile struct pcnet32_init_block *ib = &lp->init_block;
    volatile uint16_t *mcast_table = (uint16_t *)&ib->filter;
    struct dev_mc_list *dmi = dev->mc_list;
    char *addrs;
    int i, j, bit, byte;
    uint32_t crc, poly = CRC_POLYNOMIAL_LE;
	
    /* set all multicast bits */
    if (dev->flags & IFF_ALLMULTI)
    { 
        ib->filter [0] = UINT32_MAX;
        ib->filter [1] = UINT32_MAX;
        return;
    }
    /* clear the multicast filter */
    ib->filter [0] = 0;
    ib->filter [1] = 0;

    /* Add addresses */
    for (i = 0; i < dev->mc_count; i++)
    {
        addrs = dmi->dmi_addr;
        dmi   = dmi->next;
	
        /* multicast address? */
        if (!(*addrs & 1))
        {
            continue;
        }
	
        crc = UINT32_MAX;
        for (byte = 0; byte < 6; byte++)
        {
	        for (bit = *addrs++, j = 0; j < 8; j++, bit >>= 1)
            {
                int test;
		
                test = ((bit ^ crc) & 0x01);
                crc >>= 1;
		
                if (test)
                {
                    crc = crc ^ poly;
                }
           }
       }
	
        crc = crc >> 26;
        mcast_table [crc >> 4] |= 1 << (crc & 0xf);
    }
    
    return;
}

/*
 * Set or clear the multicast filter for this adaptor.
 */
void pcnet32_set_multicast_list (ethernet_device_t *dev)
{
    unsigned long ioaddr = dev->base_addr;
    pcnet32_private_t *lp = dev->priv;	 

    if (dev->flags & IFF_PROMISC)
    {
        /* Log any net taps. */
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
            "\"%s\": Promiscuous mode enabled.\n", dev->name);
        lp->init_block.mode = little_endian_to_native_uint16 (
            0x8000 | (lp->options & PORT_PORTSEL) << 7);
    }
    else
    {
        lp->init_block.mode = little_endian_to_native_uint16 (
            (lp->options & PORT_PORTSEL) << 7);
        pcnet32_load_multicast (dev);
    }
    
    lp->a.write_csr (ioaddr, 0, 0x0004); /* Temporarily stop the lance. */

    pcnet32_restart (dev, 0x0042); /*  Resume normal operation */
}
#endif
