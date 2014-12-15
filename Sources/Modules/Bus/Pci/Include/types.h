/* $Id: types.h,v 1.2 2001/02/10 21:22:51 jojo Exp $ */
/* Abstract: List type definitions. */
/* Author: Per Lundberg <plundis@chaosdev.org> */

/* Copyright 2000 chaos development. */

#ifndef __PCI_TYPES_H__
#define __PCI_TYPES_H__

#include <list.h>
#include "defines.h"

typedef struct
{
    uint16_t vendor_id;

    uint16_t device_id;

} pci_device_probe_t;

typedef struct
{
    uint8_t class_id;
    uint8_t subclass_id;
    uint8_t interface_id;

} pci_device_class_t;

/* Resources are tree-like, allowing nesting etc.. */

#ifndef PCI_RESOURCE_DEFINED
#define PCI_RESOURCE_DEFINED

#define PCI_NUMBER_OF_RESOURCES         (12)

typedef struct 
{
    const char *name;
    unsigned long start, end;
    unsigned long flags;
} pci_resource_t;
#endif /* !PCI_RESOURCE_DEFINED */

/*
typedef struct
{
    uint16_t vendor_id;
    char vendor_name[80];

    uint16_t device_id;
    char device_name[80];

    unsigned int irq;
  
    pci_resource_t resource[PCI_NUMBER_OF_RESOURCES];

} pci_device_info_t;
*/
typedef struct
{
    uint8_t data[256];

} pci_configuration_space_t;

typedef struct
{
    /* Node in list of buses. */
    LIST_NODE_PART;

    /* List of devices on this bus. */

    struct pci_device_t *devices;

    /* Bridge device as seen by parent. */

    struct pci_device_t *self;

    /* Bus number. */
  
    unsigned char number;

    /* Number of primary bridge. */

    unsigned char primary;

    /* Number of secondary bridge. */

    unsigned char secondary;

    /* Max number of subordinate buses. */

    unsigned char subordinate;

    /* Pointer to the PCI functions we should use when accessing this
       bus. */
  
    struct pci_operation_t *operation;

    char name[48];
    uint16_t vendor_id;
    uint16_t device_id;

    /* Serial number. */

    unsigned int serial;

    /* Plug & Play version. */

    unsigned char plug_n_play_version;

    /* Product version. */

    unsigned char product_version;

    /* If zero - checksum passed. */

    unsigned char checksum;
    unsigned char pad1;

} pci_bus_t;

/*
typedef struct
{
    LIST_PART;

} pci_bus_list_t;
*/

#define SLOT_NAME_LENGTH    8
#define VENDOR_NAME_LENGTH  80
#define DEVICE_NAME_LENGTH  80

typedef struct
{
    LIST_NODE_PART;

    /* Bus this device is on. */

    pci_bus_t *bus;

    /* Bus this device bridges to. */

    pci_bus_t *subordinate;
  
    /* Encoded device & function index (7 bits device, 3 bits function). */

    unsigned int device_function;

    uint16_t vendor_id;
    uint16_t device_id;
    uint16_t subsystem_vendor_id;
    uint16_t subsystem_device_id;

    /* 3 bytes: (base, sub, prog-if) */

    uint32_t class;

    uint8_t class_id;
    uint8_t subclass_id;
    uint8_t interface_id;
  
    char class_name[80];

    /* Revision ID */
  
    uint8_t revision_id;

    /* PCI header type (`multi' flag masked out). */

    uint8_t header_type;

    /* if device has BIST */

    bool has_bist;

    /* Which config register controls the ROM? */

    uint8_t rom_base_reg;

    /* Current operating state. In ACPI-speak, this is D0-D3, D0 being fully 
       functional, and D3 being off. */
    uint32_t current_state;  
    
    /* Device is compatible with these IDs. */

    uint16_t vendor_compatible[PCI_DEVICE_COUNT_COMPATIBLE];
    uint16_t device_compatible[PCI_DEVICE_COUNT_COMPATIBLE];
  
    /* The IRQ line this device is using, if any. */
  
    unsigned int irq;
  
    /* I/O and memory regions + expansion ROMs. */

    pci_resource_t resource[PCI_NUMBER_OF_RESOURCES];

    /* Device name. */

    char device_name[DEVICE_NAME_LENGTH];

    /* Vendor name. */

    char vendor_name[VENDOR_NAME_LENGTH];

    /* Slot name. */

    char slot_name[SLOT_NAME_LENGTH];
    
    unsigned int command;
    unsigned int status;
    unsigned int min_dma_time;
    unsigned int max_dma_latency;

    object_reference_t reference;

} pci_device_t;
/*
typedef struct
{
    LIST_PART;

} pci_device_list_t;
*/

typedef struct
{
  uint8_t (*read_u8) (pci_device_t *, int where);
  uint16_t (*read_u16) (pci_device_t *, int where);
  uint32_t (*read_u32) (pci_device_t *, int where);
  void (*write_u8) (pci_device_t *, int where, uint8_t value);
  void (*write_u16) (pci_device_t *, int where, uint16_t value);
  void (*write_u32) (pci_device_t *, int where, uint32_t value);

} pci_operation_t;

typedef struct
{
  uint16_t vendor_id;

  uint16_t device_id;

  char *name;

} pci_device_id_t;

typedef struct
{
  uint16_t vendor_id;

  char *name;

} pci_vendor_id_t;

typedef struct
{
  uint8_t class_id;
  char *class_name;
//  u8 sub_class_id;
//  char *sub_class_name;
//  u8 programming_interface;
//  char *programming_interface_name;
} pci_class_id_t;


#endif /* !__PCI_TYPES_H__ */
