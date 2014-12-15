/* $Id: pci.h,v 1.5 2000/10/15 11:22:23 plundis Exp $ */
/* Abstract: Protocol for commuicating with the PCI server. */
/* Author: Per Lundberg <plundis@chaosdev.org> */

/* Copyright 1999 chaos development. */

/* This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public License
   as published by the Free Software Foundation; either version 2 of
   the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
   USA. */

#ifndef __LIBRARY_IPC_PCI_H__
#define __LIBRARY_IPC_PCI_H__

#include <ipc/protocols.h>

enum
{
  /* Used for functions wishing to return a return value. */

  IPC_PCI_RETURN_VALUE  = (IPC_PROTOCOL_PCI << 16),

  /* Check if a device with the given vendor and device ID exists. */

  IPC_PCI_DEVICE_EXISTS,

  /* Get the amount of PCI devices in this system. */

  IPC_PCI_DEVICE_GET_AMOUNT,

  /* Get brief information about all devices in the system. */

  IPC_PCI_DEVICE_GET_INFO,

  /* Get state for a given device. */

  IPC_PCI_DEVICE_GET_STATE,

  /* Set PCI configuration state. */

  IPC_PCI_DEVICE_SET_STATE,

  IPC_PCI_DEVICE_CLASS_EXISTS,
};

/* Return values. */

enum
{
  /* One or more devices of the specified type exists in the
     system. */

  IPC_PCI_RETURN_DEVICE_EXISTS,

  /* No device of the given type could be found. */

  IPC_PCI_RETURN_DEVICE_ABSENT,
};

/* Miscellaneous defines. */

#define PCI_NUMBER_OF_RESOURCES         12
#define PCI_NUMBER_OF_REGULAR_RESOURCES 6

#define PCI_ROM_RESOURCE 6
#define PCI_BRIDGE_RESOURCES 7

//#define PCI_BASE_ADDRESS_0	0x10	/* 32 bits */
//#define PCI_BASE_ADDRESS_1	0x14	/* 32 bits [htype 0,1 only] */
//#define PCI_BASE_ADDRESS_2	0x18	/* 32 bits [htype 0 only] */
//#define PCI_BASE_ADDRESS_3	0x1c	/* 32 bits */
//#define PCI_BASE_ADDRESS_4	0x20	/* 32 bits */
//#define PCI_BASE_ADDRESS_5	0x24	/* 32 bits */


/* IO resources have these defined flags. */
/* Bus-specific bits. */

#define PCI_RESOURCE_BITS               0x000000FF

/* Resource type. */

#define PCI_RESOURCE_IO                 0x00000100
#define PCI_RESOURCE_MEMORY             0x00000200
#define PCI_RESOURCE_IRQ                0x00000400
#define PCI_RESOURCE_DMA                0x00000800

/* No side effects. */

#define PCI_RESOURCE_PREFETCH           0x00001000
#define PCI_RESOURCE_READONLY           0x00002000
#define PCI_RESOURCE_CACHEABLE          0x00004000
#define PCI_RESOURCE_RANGELENGTH        0x00008000
#define PCI_RESOURCE_SHADOWABLE         0x00010000

#define PCI_RESOURCE_UNSET              0x20000000
#define PCI_RESOURCE_AUTO               0x40000000

/* Driver has marked this resource busy. */

#define PCI_RESOURCE_BUSY               0x80000000

/* This structure is passed into IPC_PCI_DEVICE_EXISTS. */

typedef struct
{
  u16 vendor_id;
  u16 device_id;
} pci_device_probe_type;

typedef struct
{
  u8 class_id;
  u8 subclass_id;
  u8 interface_id;
} pci_device_class_type;

/* Resources are tree-like, allowing nesting etc.. */

typedef struct 
{
  const char *name;
  unsigned long start, end;
  unsigned long flags;
} pci_resource_type;

typedef struct
{
  u16 vendor_id;
  char vendor_name[80];

  u16 device_id;
  char device_name[80];

  unsigned int irq;
  
  pci_resource_type resource[PCI_NUMBER_OF_RESOURCES];
} pci_device_info_type;

typedef struct
{
  u8 data[256];
} pci_configuration_space_type;

#endif /* !__LIBRARY_IPC_PCI_H__ */
