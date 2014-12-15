/* $Id: pci.h,v 1.5 2000/10/08 15:05:59 plundis Exp $ */
/* Abstract: Type definitions and function prototypes for the PCI
   server. */
/* Author: Per Lundberg <plundis@chaosdev.org> */

/* Copyright 2000 chaos development. */


#ifndef __PCI_H__
#define __PCI_H__

#include "types.h"

/* Linked list of all PCI devices. */

extern list_t pci_device_list;

/* Linked list of all buses. */

extern list_t pci_bus_list;

extern bool pci_init (void);
extern uint8_t device_bist (pci_device_t *pci_device);

#endif /* !__PCI_H__ */
