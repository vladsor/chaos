
#ifndef __PCI_LOWLEVEL_H__
#define __PCI_LOWLEVEL_H__

/* Functions for accessing PCI configuration space with type 1
   accesses. */

#define CONFIG_COMMAND(device, where) \
   (0x80000000 | (device->bus->number << 16) | \
    (device->device_function << 8) | \
    (where & ~3))

extern uint8_t pci_type1_read_config_u8 (pci_device_t *device, int where);

extern uint16_t pci_type1_read_config_u16 (pci_device_t *device, int where);

extern uint32_t pci_type1_read_config_u32 (pci_device_t *device, int where);

extern void pci_type1_write_config_u8 (pci_device_t *device, int where,
    uint8_t value);

extern void pci_type1_write_config_u16 (pci_device_t *device, int where,
    uint16_t value);

extern void pci_type1_write_config_u32 (pci_device_t *device, int where,
    uint32_t value);

extern pci_operation_t pci_type1_operation;

/* Functions for accessing PCI configuration space with type 2 accesses. */

#define IOADDR(device_function, where) \
   ((0xC000 | ((device_function & 0x78) << 5)) + where)

#define FUNC(device_function) \
   (((device_function & 7) << 1) | 0xF0)

#define SET(device) \
    port_uint8_out (PCI_BASE, FUNC (device->device_function)); \
    port_uint8_out (PCI_BASE + 2, device->bus->number);

extern uint8_t pci_type2_read_config_u8 (pci_device_t *device, int where);

extern uint16_t pci_type2_read_config_u16 (pci_device_t *device, int where);

extern uint32_t pci_type2_read_config_u32 (pci_device_t *device, int where);

extern void pci_type2_write_config_u8 (pci_device_t *device, int where, 
    uint8_t value);

extern void pci_type2_write_config_u16 (pci_device_t *device, int where,
    uint16_t value);

extern void pci_type2_write_config_u32 (pci_device_t *device, int where,
    uint32_t value);

extern pci_operation_t pci_type2_operation;

/* Meta-functions for reading and writing PCI data. */

static inline uint32_t pci_read_config_u32 (pci_device_t *device, int where)
{
    return ((pci_operation_t *) device->bus->operation)->read_u32 (
        device, where);
}

static inline uint16_t pci_read_config_u16 (pci_device_t *device, int where)
{
    return ((pci_operation_t *) device->bus->operation)->read_u16 (
        device, where);
}
                       
static inline uint8_t pci_read_config_u8 (pci_device_t *device, int where)
{
    return ((pci_operation_t *) device->bus->operation)->read_u8 (
        device, where);
}

static inline void pci_write_config_u32 (pci_device_t *device, int where, 
    uint32_t data)
{
    ((pci_operation_t *) device->bus->operation)->write_u32 (
        device, where, data);
}

static inline void pci_write_config_u16 (pci_device_t *device, int where, 
    uint32_t data)
{
    ((pci_operation_t *) device->bus->operation)->write_u16 (
        device, where, data);
}

static inline void pci_write_config_u8 (pci_device_t *device, int where, 
    uint32_t data)
{
    ((pci_operation_t *) device->bus->operation)->write_u8 (
        device, where, data);
}

#endif /* !__PCI_LOWLEVEL_H__ */

