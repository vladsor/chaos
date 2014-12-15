#include <enviroment.h>

#include "Include/types.h"
#include "Include/pcnet32_lowlevel.h"
#include "Include/pcnet32.h"
#include "Include/pci-util.h"
#include "Include/interface.h"

#define DEBUG_MODULE_NAME L"PCNet32"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#ifndef __STORM_KERNEL__
#   define DEBUG_SUPPLIER (pcnet32_debug_supplier)
#endif

#include <debug/macros.h>

#define PCNET32_DMA_MASK 0xffffffff
#define PCNET32_TOTAL_SIZE 0x20

/*
 * table to translate option values from tulip
 * to internal options
 */
static unsigned char options_mapping[] = 
{
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
static unsigned int options[MAX_UNITS];
static int full_duplex[MAX_UNITS];

/* pcnet32_probe1 
 *  Called from both pcnet32_probe_vlbus and pcnet_probe_pci.  
 *  pdev will be NULL when called from pcnet32_probe_vlbus.
 */
static ethernet_device_t * pcnet32_probe1 (unsigned long ioaddr, 
    unsigned char irq_line, int shared, int card_idx, handle_reference_t device)
{
    pcnet32_private_t *lp;
//    pci_resource_t *res;
    dma_addr_t lp_dma_addr;
    int i, media, fdx = 0, mii = 0, fset = 0;
#ifdef DO_DXSUFLO
    int dxsuflo = 0;
#endif
    int ltint = 0;
    int chip_version;
    const char *chipname;
    ethernet_device_t *dev;
    pcnet32_access_t *a = NULL;

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE, 
        L"%S: %s ().\n", 
        DEBUG_MODULE_NAME, __FUNCTION__);

    /* reset the chip */
    pcnet32_dwio_reset (ioaddr);
    pcnet32_wio_reset (ioaddr);

    /* NOTE: 16-bit check is first, otherwise some older PCnet chips fail */
    if ((pcnet32_wio_read_csr (ioaddr, 0) == 4) && (pcnet32_wio_check (ioaddr)))
    {
        DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1, 
            L"%S: Using 16 bits lowlevel routines.\n", 
            DEBUG_MODULE_NAME);
            
        a = &pcnet32_wio;
    }
    else 
    {
        if ((pcnet32_dwio_read_csr (ioaddr, 0) == 4) && 
            (pcnet32_dwio_check (ioaddr)))
        {
            DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1, 
                L"%S: Using 32 bits lowlevel routines.\n", 
                DEBUG_MODULE_NAME);
                
            a = &pcnet32_dwio;
        } 
        else
        {
           return NULL;
        }
    }

    chip_version = a->read_csr (ioaddr, 88) | (a->read_csr (ioaddr, 89) << 16);
    
    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1,
        L"%S: PCnet chip version is %#x.\n", 
        DEBUG_MODULE_NAME, 
        chip_version);
        
    if ((chip_version & 0xFFF) != 0x003)
    {
        return NULL;
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
            /* 970 gives the wrong chip id back */
                chipname = "PCnet/PCI 79C970"; 
            else
            /* 486/VL bus */
                chipname = "PCnet/32 79C965"; 
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
            DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1,
                L"%S: pcnet32 media value %#x.\n",
                DEBUG_MODULE_NAME, media);
                
            media &= ~3;
            media |= 1;
#endif
            DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1,
                L"%S: pcnet32 media reset to %#x.\n",
                DEBUG_MODULE_NAME,
                media);

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
            DEBUG_PRINTW (DEBUG_LEVEL_WARNING,
                L"%S: PCnet version %#x, no PCnet32 chip.\n", 
                DEBUG_MODULE_NAME,
                chip_version);
            
            return NULL;
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
    memory_clear ((uint8_t *) dev, sizeof (ethernet_device_t));

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1,
        L"%S: \"%s\": \"%s\" at %#3lx,\n", 
        DEBUG_MODULE_NAME,
        dev->name, chipname, ioaddr);

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
    }
    
    {
        uint8_t promaddr[6];

        for (i = 0; i < 6; i++) 
        {
            promaddr[i] = port_uint8_in (ioaddr + i);
        }
        
        if (!memory_compare (promaddr, dev->ethernet_address, 6))
        {
            DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1, 
                L" warning PROM address does not match CSR address\n");
#if defined(__i386__)
            DEBUG_PRINTW (DEBUG_LEVEL_WARNING,
                L"%S: Probably a Compaq, using the PROM address of",
                DEBUG_MODULE_NAME);
                
            memory_copy (dev->ethernet_address, promaddr, 6);
#endif
        }               
    }
    
    /* if the ethernet address is not valid, force to 00:00:00:00:00:00 */
    if (!is_valid_ethernet_address (dev->ethernet_address))
    {
        for (i = 0; i < 6; i++)
        {
            dev->ethernet_address[i] = 0;
        }
    }
    
    for (i = 0; i < 6; i++)
    {
        DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1,
            L" %2.2x", dev->ethernet_address[i]);
    }
    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1, L"\n");

    if (((chip_version + 1) & 0xfffe) == 0x2624)
    { /* Version 0x2623 or 0x2624 */
    
        i = a->read_csr (ioaddr, 80) & 0x0C00;  /* Check tx_start_pt */
        
        DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1,
            L"    tx_start_pt(0x%04x):", i);
        
        switch (i>>10) 
        {
            case 0:
            {
                DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE, L"  20 bytes,"); 
                break;
            }
            
            case 1:
            {
                DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE, L"  64 bytes,"); 
                break;
            }
            
            case 2:
            {
                DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE, L" 128 bytes,"); 
                break;
            }
            
            case 3:
            {
                DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE, L"~220 bytes,"); 
                break;
            }
        }
        
        i = a->read_bcr (ioaddr, 18);  /* Check Burst/Bus control */
        
        DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1, L" BCR18(%x):", i & 0xFFFF);
        
        if (i & BIT_VALUE (5))
        {
            DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1, L"BurstWrEn ");
        }    
        
        if (i & BIT_VALUE (6))
        {
            DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1, L"BurstRdEn ");
        }    
        
        if (i & BIT_VALUE (7))
        {
            DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1, L"DWordIO ");
        }    
        
        if (i & BIT_VALUE (11))
        {
            DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1, L"NoUFlow ");
        }    
        
        i = a->read_bcr (ioaddr, 25);
        
        DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1, L"    SRAMSIZE=0x%04x,",i<<8);
        
        i = a->read_bcr (ioaddr, 26);
        
        DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1, L" SRAM_BND=0x%04x,",i<<8);
        
        i = a->read_bcr (ioaddr, 27);
    
        if (i & BIT_VALUE (14)) 
        {
            DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1, L"LowLatRx");
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
    io_port_register (ioaddr, PCNET32_TOTAL_SIZE, chipname);    
    
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
    lp_dma_addr = (dma_addr_t) lp;

    memory_clear (lp, sizeof(*lp));
    lp->dma_addr = lp_dma_addr;
    lp->pci_device = device;
    
    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1, 
        L"%S: lp=%p lp_dma_addr=%#08x\n", 
        DEBUG_MODULE_NAME,
        lp, lp_dma_addr);

//    spin_lock_init(&lp->lock);
    spin_init (&lp->lock);
    
    dev->priv = lp;
    lp->name = chipname;
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
        DEBUG_PRINTW (DEBUG_LEVEL_ERROR, 
            L"%S: No access methods.\n",
            DEBUG_MODULE_NAME);
        
//        pci_free_consistent(lp->pci_dev, sizeof(*lp), lp, lp->dma_addr);
//        release_resource(res);
        memory_deallocate (lp);
        
        return NULL;
    }
    
    lp->a = *a;
    
    /* detect special T1/E1 WAN card by checking for MAC address */
    if ((dev->ethernet_address[0] == 0x00) && 
        (dev->ethernet_address[1] == 0xe0) && 
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
        DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1, 
            L" assigned IRQ %d.\n", dev->irq);
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
        cpu_sleep_milli (CPU_CURRENT, 1);
    
//        dev->irq = probe_irq_off (irq_mask);
        
        if (dev->irq)
        {
            DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1, 
                L", probed IRQ %d.\n", 
                dev->irq);
        }
        else 
        {
            DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1, 
                L", failed to detect IRQ line.\n");
//            pci_free_consistent(lp->pci_dev, sizeof(*lp), lp, lp->dma_addr);
//            release_resource(res);
            memory_deallocate (lp);

            return NULL;
        }
    }

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1, 
        L"%S: %s\n",
        DEBUG_MODULE_NAME,
        version);
    
    /* The PCNET32-specific entries in the device structure. */
/*    
#ifdef HAVE_PRIVATE_IOCTL
    dev->do_ioctl = &pcnet32_mii_ioctl;
#endif
    dev->tx_timeout = pcnet32_tx_timeout;
*/    
    dev->watchdog_timeo = (100 >> 1);

    return dev;
}

ethernet_device_t * pcnet32_probe_pci (handle_reference_t device, 
    pci_device_info_t *device_info)
{
    static int card_idx;
    long ioaddr;

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE, 
        L"%S: %s: found device %#08x.%#08x\n", 
        DEBUG_MODULE_NAME, __FUNCTION__, 
        device_info->vendor_id, device_info->device_id);

    pci_device_control$enable (device);
    pci_device_control$set_master (device);

    ioaddr = pci_resource_start (device_info, 0);
    
    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1,
        L"%S: %s: ioaddr=%#08lx  resource_flags=%#08lx\n", 
        DEBUG_MODULE_NAME, __FUNCTION__,
        ioaddr, pci_resource_flags (device_info, 0));

    if (!ioaddr) 
    {
        DEBUG_PRINTW (DEBUG_LEVEL_ERROR,
            L"%S: %s: no PCI IO resources, aborting\n",
            DEBUG_MODULE_NAME, __FUNCTION__);
        
        return NULL;
    }
    
    if (!pci_dma_supported (device, PCNET32_DMA_MASK)) 
    {
       DEBUG_PRINTW (DEBUG_LEVEL_ERROR,
           L"%S: %s: architecture does not support 32bit PCI busmaster DMA\n",
           DEBUG_MODULE_NAME, __FUNCTION__);
       
       return NULL;
    }

    return pcnet32_probe1 (ioaddr, device_info->irq, 1, card_idx, device);
}

