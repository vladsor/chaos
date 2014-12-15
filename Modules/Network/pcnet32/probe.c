#include <enviroment.h>

#include <Interfaces/pci_device.h>

#include "types.h"
#include "pcnet32_lowlevel.h"
#include "pcnet32.h"
#include "pci-util.h"

#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>

#define PCNET32_DMA_MASK 0xffffffff

/*
 * table to translate option values from tulip
 * to internal options
 */
static unsigned char options_mapping[] = {
    PORT_ASEL,			   /*  0 Auto-select	  */
    PORT_AUI,			   /*  1 BNC/AUI	  */
    PORT_AUI,			   /*  2 AUI/BNC	  */ 
    PORT_ASEL,			   /*  3 not supported	  */
    PORT_10BT | PORT_FD,	   /*  4 10baseT-FD	  */
    PORT_ASEL,			   /*  5 not supported	  */
    PORT_ASEL,			   /*  6 not supported	  */
    PORT_ASEL,			   /*  7 not supported	  */
    PORT_ASEL,			   /*  8 not supported	  */
    PORT_MII,			   /*  9 MII 10baseT	  */
    PORT_MII | PORT_FD,		   /* 10 MII 10baseT-FD	  */
    PORT_MII,			   /* 11 MII (autosel)	  */
    PORT_10BT,			   /* 12 10BaseT	  */
    PORT_MII | PORT_100,	   /* 13 MII 100BaseTx	  */
    PORT_MII | PORT_100 | PORT_FD, /* 14 MII 100BaseTx-FD */
    PORT_ASEL			   /* 15 not supported	  */
};

#define MAX_UNITS 8
static int options[MAX_UNITS];
static int full_duplex[MAX_UNITS];

/* pcnet32_probe1 
 *  Called from both pcnet32_probe_vlbus and pcnet_probe_pci.  
 *  pdev will be NULL when called from pcnet32_probe_vlbus.
 */
static ethernet_device_t * pcnet32_probe1 (unsigned long ioaddr, unsigned char irq_line, 
    int shared, int card_idx, handle_t *device)
{
    pcnet32_private_t *lp;
    pci_resource_t *res;
    dma_addr_t lp_dma_addr;
    int i, media, fdx = 0, mii = 0, fset = 0;
#ifdef DO_DXSUFLO
    int dxsuflo = 0;
#endif
    int ltint = 0;
    int chip_version;
    char *chipname = "UNKNOWN";
    ethernet_device_t *dev;
    pcnet32_access_t *a = NULL;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "%s ().\n", __FUNCTION__);

    /* reset the chip */
    pcnet32_dwio_reset (ioaddr);
    pcnet32_wio_reset (ioaddr);

    /* NOTE: 16-bit check is first, otherwise some older PCnet chips fail */
    if (pcnet32_wio_read_csr (ioaddr, 0) == 4 && pcnet32_wio_check (ioaddr)) 
    {
        a = &pcnet32_wio;
    }
    else 
    {
        if (pcnet32_dwio_read_csr (ioaddr, 0) == 4 && pcnet32_dwio_check(ioaddr)) 
        {
            a = &pcnet32_dwio;
        } 
        else
        {
           return -1;
        }
    }

    chip_version = a->read_csr (ioaddr, 88) | (a->read_csr (ioaddr,89) << 16);
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "  PCnet chip version is %#x.\n", chip_version);
        
    if ((chip_version & 0xFFF) != 0x003)
    {
        return -1;
    }
    
    chip_version = (chip_version >> 12) & 0xFFFF;
    
    switch (chip_version) 
    {
        case 0x2420:
        {
            chipname = "PCnet/PCI 79C970"; /* PCI */
            break;
        }
        
        case 0x2430:
        {
            if (shared)
                chipname = "PCnet/PCI 79C970"; /* 970 gives the wrong chip id back */
            else
                chipname = "PCnet/32 79C965"; /* 486/VL bus */
            break;
        }
        
        case 0x2621:
        {
            chipname = "PCnet/PCI II 79C970A"; /* PCI */
            fdx = 1;
            break;
        }
        
        case 0x2623:
        {
            chipname = "PCnet/FAST 79C971"; /* PCI */
            fdx = 1; mii = 1; fset = 1;
            ltint = 1;
            break;
        }
        
        case 0x2624:
        {
            chipname = "PCnet/FAST+ 79C972"; /* PCI */
            fdx = 1; mii = 1; fset = 1;
            break;
        }
        
        case 0x2625:
        {
            chipname = "PCnet/FAST III 79C973"; /* PCI */
            fdx = 1; mii = 1;
            break;
        }
        
        case 0x2626:
        {
            chipname = "PCnet/Home 79C978"; /* PCI */
            fdx = 1;
            /* 
             * This is based on specs published at www.amd.com.  This section
             * assumes that a card with a 79C978 wants to go into 1Mb HomePNA
             * mode.  The 79C978 can also go into standard ethernet, and there
             * probably should be some sort of module option to select the
             * mode by which the card should operate
             */
            /* switch to home wiring mode */
            media = a->read_bcr (ioaddr, 49);
#if 0
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
                "pcnet32: pcnet32 media value %#x.\n",  media);
            media &= ~3;
            media |= 1;
#endif
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
                "pcnet32: pcnet32 media reset to %#x.\n",  media);

            a->write_bcr (ioaddr, 49, media);
            break;
        }
        
        case 0x2627:
        {
            chipname = "PCnet/FAST III 79C975"; /* PCI */
            fdx = 1; mii = 1;
            break;
        }
        
        default:
        {
            DEBUG_PRINT (DEBUG_LEVEL_WARNING,
                "pcnet32: PCnet version %#x, no PCnet32 chip.\n", chip_version);
            
            return -1;
        }
    }

    /*
     *  On selected chips turn on the BCR18:NOUFLO bit. This stops transmit
     *  starting until the packet is loaded. Strike one for reliability, lose
     *  one for latency - although on PCI this isnt a big loss. Older chips 
     *  have FIFO's smaller than a packet, so you can't do this.
     */
     
    if (fset)
    {
        a->write_bcr (ioaddr, 18, (a->read_bcr(ioaddr, 18) | 0x0800));
        a->write_csr (ioaddr, 80, (a->read_csr(ioaddr, 80) & 0x0C00) | 0x0c00);
#ifdef DO_DXSUFLO
        dxsuflo = 1;
#endif
        ltint = 1;
    }
/*    
    dev = init_etherdev (NULL, 0);
    
    if (dev == NULL)
    {
        return -1;
    }
*/
    memory_allocate ((void **) &dev, sizeof (ethernet_device_t));
    memory_set_uint8 ((uint8_t *) dev, 0, sizeof (ethernet_device_t));

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "\"%s\": \"%s\" at %#3lx,\n", dev->name, chipname, ioaddr);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "EA: ");
    /* In most chips, after a chip reset, the ethernet address is read from the
     * station address PROM at the base address and programmed into the
     * "Physical Address Registers" CSR12-14.
     * As a precautionary measure, we read the PROM values and complain if
     * they disagree with the CSRs.  Either way, we use the CSR values, and
     * double check that they are valid.
     */
    for (i = 0; i < 3; i++) 
    {
        unsigned int val;
        
        val = a->read_csr (ioaddr, i + 12) & 0x0ffff;
        
        /* There may be endianness issues here. */
        dev->ethernet_address[2 * i] = val & 0x0ff;
        dev->ethernet_address[2 * i + 1] = (val >> 8) & 0x0ff;

        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
            ".%2.2x.%2.2x", 
            dev->ethernet_address[2 * i], dev->ethernet_address[2 * i + 1]);
    }
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "\n");
    
    {
        uint8_t promaddr[6];

        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "EA: ");
        for (i = 0; i < 6; i++) 
        {
            promaddr[i] = port_uint8_in (ioaddr + i);
            
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
              ".%2.2x", promaddr[i]);
        }
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "\n");
        
        if (!memory_compare (promaddr, dev->ethernet_address, 6))
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
                " warning PROM address does not match CSR address\n");
#if defined(__i386__)
            DEBUG_PRINT (DEBUG_LEVEL_WARNING,
                "%s: Probably a Compaq, using the PROM address of", dev->name);
            memory_copy (dev->ethernet_address, promaddr, 6);
#endif
        }               
    }
    
    /* if the ethernet address is not valid, force to 00:00:00:00:00:00 */
    if (!is_valid_ethernet_address (dev->ethernet_address))
    {
        for (i = 0; i < 6; i++)
        {
            dev->ethernet_address[i]=0;
        }
    }
    
    for (i = 0; i < 6; i++)
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
            " %2.2x", dev->ethernet_address[i]);
    }

    if (((chip_version + 1) & 0xfffe) == 0x2624)
    { /* Version 0x2623 or 0x2624 */
    
        i = a->read_csr (ioaddr, 80) & 0x0C00;  /* Check tx_start_pt */
        
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
            "\n    tx_start_pt(0x%04x):", i);
        
        switch (i>>10) 
        {
            case 0:
            {
                DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "  20 bytes,"); 
                break;
            }
            
            case 1:
            {
                DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "  64 bytes,"); 
                break;
            }
            
            case 2:
            {
                DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, " 128 bytes,"); 
                break;
            }
            
            case 3:
            {
                DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "~220 bytes,"); 
                break;
            }
        }
        
        i = a->read_bcr (ioaddr, 18);  /* Check Burst/Bus control */
        
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, " BCR18(%x):", i & 0xFFFF);
        
        if (i & (1<<5)) DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "BurstWrEn ");
        
        if (i & (1<<6)) DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "BurstRdEn ");
        
        if (i & (1<<7)) DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "DWordIO ");
        
        if (i & (1<<11)) DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "NoUFlow ");
        
        i = a->read_bcr (ioaddr, 25);
        
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "    SRAMSIZE=0x%04x,",i<<8);
        
        i = a->read_bcr (ioaddr, 26);
        
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, " SRAM_BND=0x%04x,",i<<8);
        
        i = a->read_bcr (ioaddr, 27);
    
        if (i & (1<<14)) 
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "LowLatRx");
        }
    }

    dev->base_addr = ioaddr;
//    res = request_region (ioaddr, PCNET32_TOTAL_SIZE, chipname);
/*    
    if (res == NULL)
    {
        return -EBUSY;
    }
*/    
    /* pci_alloc_consistent returns page-aligned memory, so we do not have to 
       check the alignment */
/*       
    if ((lp = pci_alloc_consistent(pdev, sizeof(*lp), &lp_dma_addr)) == NULL) 
    {
        release_resource(res);
        return -1;
    }
*/
    memory_allocate ((void **) &lp, sizeof(*lp));
    lp_dma_addr = lp;

    memory_set_uint8 ((uint8_t *) lp, 0, sizeof(*lp));
    lp->dma_addr = lp_dma_addr;
    register_handle_clone (device, &lp->pci_device, 0);
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "pcnet32: pcnet32_private lp=%p lp_dma_addr=%#08x\n", 
        lp, lp_dma_addr);

//    spin_lock_init(&lp->lock);
    spin_init (&lp->lock);
    
    dev->priv = lp;
    string_copy (lp->name, chipname);
    lp->shared_irq = shared;
    lp->full_duplex = fdx;
#ifdef DO_DXSUFLO
    lp->dxsuflo = dxsuflo;
#endif
    lp->ltint = ltint;
    lp->mii = mii;
    
    if (options[card_idx] > sizeof (options_mapping))
    {
        lp->options = PORT_ASEL;
    }
    else
    {
        lp->options = options_mapping[options[card_idx]];
    }
    
    if (fdx && !(lp->options & PORT_ASEL) && full_duplex[card_idx])
    {
        lp->options |= PORT_FD;
    }
    
    if (a == NULL) 
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, "pcnet32: No access methods\n");
        
//        pci_free_consistent(lp->pci_dev, sizeof(*lp), lp, lp->dma_addr);
//        release_resource(res);
        memory_deallocate (lp);
        
        return -1;
    }
    
    lp->a = *a;
    
    /* detect special T1/E1 WAN card by checking for MAC address */
    if ((dev->ethernet_address[0] == 0x00) && (dev->ethernet_address[1] == 0xe0) && 
      (dev->ethernet_address[2] == 0x75))
    {
        lp->options = PORT_FD | PORT_GPSI;
    }

    /* Disable Rx and Tx. */
    lp->init_block.mode = little_endian_to_native_uint16 (0x0003);
    lp->init_block.tlen_rlen = little_endian_to_native_uint16 (
        TX_RING_LEN_BITS | RX_RING_LEN_BITS); 
    
    for (i = 0; i < 6; i++)
    {
        lp->init_block.phys_addr[i] = dev->ethernet_address[i];
    }
    
    lp->init_block.filter[0] = 0x00000000;
    lp->init_block.filter[1] = 0x00000000;
    
    lp->init_block.rx_ring = (uint32_t) little_endian_to_native_uint32 (
        lp->dma_addr + offset_of (pcnet32_private_t, rx_ring));
    lp->init_block.tx_ring = (uint32_t) little_endian_to_native_uint32 (
        lp->dma_addr + offset_of (pcnet32_private_t, tx_ring));
    
    /* switch pcnet32 to 32bit mode */
    a->write_bcr (ioaddr, 20, 2);

    a->write_csr (ioaddr, 1, (lp->dma_addr + offset_of (pcnet32_private_t, 
        init_block)) & 0xffff);
    a->write_csr (ioaddr, 2, (lp->dma_addr + offset_of (pcnet32_private_t, 
        init_block)) >> 16);
    
    if (irq_line)
    {
        dev->irq = irq_line;
    }
    
    if (dev->irq >= 2)
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, " assigned IRQ %d.\n", dev->irq);
    }
    else
    {
//        unsigned long irq_mask = probe_irq_on ();
    
        /*
         * To auto-IRQ we enable the initialization-done and DMA error
         * interrupts. For ISA boards we get a DMA error, but VLB and PCI
         * boards will work.
         */
         
        /* Trigger an initialization just for the interrupt. */
        a->write_csr (ioaddr, 0, 0x41);
        timer_sleep_milli (1);
    
//        dev->irq = probe_irq_off (irq_mask);
        
        if (dev->irq)
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
                ", probed IRQ %d.\n", 
                dev->irq);
        }
        else 
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
                ", failed to detect IRQ line.\n");
//            pci_free_consistent(lp->pci_dev, sizeof(*lp), lp, lp->dma_addr);
//            release_resource(res);
            memory_deallocate (lp);

            return -1;
        }
    }

    if (pcnet32_debug > 0)
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "%s\n", version);
    }
    
    /* The PCNET32-specific entries in the device structure. */
/*    
    dev->open = &pcnet32_open;
    dev->hard_start_xmit = &pcnet32_start_xmit;
    dev->stop = &pcnet32_close;
    dev->get_stats = &pcnet32_get_stats;
    dev->set_multicast_list = &pcnet32_set_multicast_list;
    
#ifdef HAVE_PRIVATE_IOCTL
    dev->do_ioctl = &pcnet32_mii_ioctl;
#endif
    dev->tx_timeout = pcnet32_tx_timeout;
*/    
    dev->watchdog_timeo = (100 >> 1);

//    lp->next = pcnet32_dev;
//    pcnet32_dev = dev;

    /* Fill in the generic fields of the device structure. */
//    ether_setup(dev);
    
    return dev;
}

ethernet_device_t * pcnet32_probe_pci (handle_t *device, pci_device_info_t *device_info)
{
    static int card_idx;
    long ioaddr;
    int err = 0;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: found device %#08x.%#08x\n", 
        __FUNCTION__, device_info->vendor_id, device_info->device_id);

    if ((err = pci_device$enable (device)) != 0) 
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
            "pcnet32.c: failed to enable device -- err=%d\n", err);
        
        return err;
    }
    
    pci_device$set_master (device);

    ioaddr = pci_resource_start (device_info, 0);
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "    ioaddr=%#08lx  resource_flags=%#08lx\n", 
        ioaddr, pci_resource_flags (device_info, 0));

    if (!ioaddr) 
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR,
            "no PCI IO resources, aborting\n");
        
        return -1;
    }
    
    if (!pci_dma_supported (device, PCNET32_DMA_MASK)) 
    {
       DEBUG_PRINT (DEBUG_LEVEL_ERROR,
           "pcnet32.c: architecture does not support 32bit PCI busmaster DMA\n");
       
       return -1;
    }

    return pcnet32_probe1 (ioaddr, device_info->irq, 1, card_idx, device);
}

