/* $Id: pnic.c,v 1.3 2000/10/17 21:18:12 doa Exp $ */
/* Abstract: PNIC (?) funktions for the tulip driver series. */
/* Author: Anders Ohrt <doa@chaosdev.org> */

/* Copyright 2000 chaos development. */

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

/* Partially based on the Linux driver, written by Donald Becker. */

#include <linux/kernel.h>
#include "tulip.h"


void pnic_do_nway(struct net_device *dev)
{
	struct tulip_private *tp = (struct tulip_private *)dev->priv;
	long ioaddr = dev->base_addr;
	u32 phy_reg = inl(ioaddr + 0xB8);
	u32 new_csr6 = tp->csr6 & ~0x40C40200;

	if (phy_reg & 0x78000000) { /* Ignore baseT4 */
		if (phy_reg & 0x20000000)		dev->if_port = 5;
		else if (phy_reg & 0x40000000)	dev->if_port = 3;
		else if (phy_reg & 0x10000000)	dev->if_port = 4;
		else if (phy_reg & 0x08000000)	dev->if_port = 0;
		tp->nwayset = 1;
		new_csr6 = (dev->if_port & 1) ? 0x01860000 : 0x00420000;
		outl(0x32 | (dev->if_port & 1), ioaddr + CSR12);
		if (dev->if_port & 1)
			outl(0x1F868, ioaddr + 0xB8);
		if (phy_reg & 0x30000000) {
			tp->full_duplex = 1;
			new_csr6 |= 0x00000200;
		}
		if (tulip_debug > 1)
			printk(KERN_DEBUG "%s: PNIC autonegotiated status %8.8x, %s.\n",
				   dev->name, phy_reg, medianame[dev->if_port]);
		if (tp->csr6 != new_csr6) {
			tp->csr6 = new_csr6;
			/* Restart Tx */
			tulip_restart_rxtx(tp, tp->csr6);
			dev->trans_start = jiffies;
		}
	}
}


void pnic_link_change(struct net_device *dev, int csr5)
{
	struct tulip_private *tp = (struct tulip_private *)dev->priv;
	long ioaddr = dev->base_addr;
	int phy_reg = inl(ioaddr + 0xB8);

	if (tulip_debug > 1)
		printk(KERN_DEBUG "%s: PNIC link changed state %8.8x, CSR5 %8.8x.\n",
			   dev->name, phy_reg, csr5);
	if (inl(ioaddr + CSR5) & TPLinkFail) {
		outl((inl(ioaddr + CSR7) & ~TPLinkFail) | TPLinkPass, ioaddr + CSR7);
		if (! tp->nwayset  ||  jiffies - dev->trans_start > 1*HZ) {
			tp->csr6 = 0x00420000 | (tp->csr6 & 0x0000fdff);
			tulip_outl_csr(tp, tp->csr6, CSR6);
			outl(0x30, ioaddr + CSR12);
			outl(0x0201F078, ioaddr + 0xB8); /* Turn on autonegotiation. */
			dev->trans_start = jiffies;
		}
	} else if (inl(ioaddr + CSR5) & TPLinkPass) {
		pnic_do_nway(dev);
		outl((inl(ioaddr + CSR7) & ~TPLinkPass) | TPLinkFail, ioaddr + CSR7);
	}
}


void pnic_timer(unsigned long data)
{
	struct net_device *dev = (struct net_device *)data;
	struct tulip_private *tp = (struct tulip_private *)dev->priv;
	long ioaddr = dev->base_addr;
	int next_tick = 60*HZ;

	if (tulip_media_cap[dev->if_port] & MediaIsMII) {
		if (tulip_check_duplex(dev) > 0)
			next_tick = 3*HZ;
	} else {
		int csr12 = inl(ioaddr + CSR12);
		int new_csr6 = tp->csr6 & ~0x40C40200;
		int phy_reg = inl(ioaddr + 0xB8);
		int csr5 = inl(ioaddr + CSR5);

		if (tulip_debug > 1)
			printk(KERN_DEBUG "%s: PNIC timer PHY status %8.8x, %s "
				   "CSR5 %8.8x.\n",
				   dev->name, phy_reg, medianame[dev->if_port], csr5);
		if (phy_reg & 0x04000000) {	/* Remote link fault */
			outl(0x0201F078, ioaddr + 0xB8);
			next_tick = 1*HZ;
			tp->nwayset = 0;
		} else if (phy_reg & 0x78000000) { /* Ignore baseT4 */
			pnic_do_nway(dev);
			next_tick = 60*HZ;
		} else if (csr5 & TPLinkFail) { /* 100baseTx link beat */
			if (tulip_debug > 1)
				printk(KERN_DEBUG "%s: %s link beat failed, CSR12 %4.4x, "
					   "CSR5 %8.8x, PHY %3.3x.\n",
					   dev->name, medianame[dev->if_port], csr12,
					   inl(ioaddr + CSR5), inl(ioaddr + 0xB8));
			next_tick = 3*HZ;
			if (tp->medialock) {
			} else if (tp->nwayset  &&  (dev->if_port & 1)) {
				next_tick = 1*HZ;
			} else if (dev->if_port == 0) {
				dev->if_port = 3;
				outl(0x33, ioaddr + CSR12);
				new_csr6 = 0x01860000;
				outl(0x1F868, ioaddr + 0xB8);
			} else {
				dev->if_port = 0;
				outl(0x32, ioaddr + CSR12);
				new_csr6 = 0x00420000;
				outl(0x1F078, ioaddr + 0xB8);
			}
			if (tp->csr6 != new_csr6) {
				tp->csr6 = new_csr6;
				/* Restart Tx */
				tulip_restart_rxtx(tp, tp->csr6);
				dev->trans_start = jiffies;
				if (tulip_debug > 1)
					printk(KERN_INFO "%s: Changing PNIC configuration to %s "
						   "%s-duplex, CSR6 %8.8x.\n",
						   dev->name, medianame[dev->if_port],
						   tp->full_duplex ? "full" : "half", new_csr6);
			}
		}
	}
	tp->timer.expires = RUN_AT(next_tick);
	add_timer(&tp->timer);
}

