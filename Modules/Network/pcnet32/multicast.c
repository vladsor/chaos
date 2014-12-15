#include <enviroment.h>

#include <Interfaces/pci_device.h>

#include "types.h"
#include "pcnet32_lowlevel.h"
#include "pcnet32.h"

#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>

#define CRC_POLYNOMIAL_LE 0xedb88320UL	/* Ethernet CRC, little endian */


/* taken from the sunlance driver, which it took from the depca driver */
void pcnet32_load_multicast (ethernet_device_t *dev)
{
    pcnet32_private_t *lp = dev->priv;
    volatile pcnet32_init_block_t *ib = &lp->init_block;
    volatile uint16_t *mcast_table = (uint16_t *) &ib->filter;
    multicast_list_t *dmi = dev->mc_list;
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
        dmi   = (multicast_list_t *) dmi->next;
	
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

