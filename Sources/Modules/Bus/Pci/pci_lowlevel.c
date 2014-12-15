#include <enviroment.h>

#include "Include/types.h"
#include "Include/pci_lowlevel.h"

/* Functions for accessing PCI configuration space with type 1
   accesses. */

uint8_t pci_type1_read_config_u8 (pci_device_t *device, int where)
{
    port_uint32_out (PCI_BASE, CONFIG_COMMAND (device, where));
    return port_uint8_in (PCI_DATA + (where & 3));
}

uint16_t pci_type1_read_config_u16 (pci_device_t *device, int where)
{
    port_uint16_out (PCI_BASE, CONFIG_COMMAND (device, where));
    return port_uint16_in (PCI_DATA + (where & 2));
}

uint32_t pci_type1_read_config_u32 (pci_device_t *device, int where)
{
    port_uint32_out (PCI_BASE, CONFIG_COMMAND (device, where));
    return port_uint32_in (PCI_DATA);
}

void pci_type1_write_config_u8 (pci_device_t *device, int where, uint8_t value)
{
    port_uint32_out (PCI_BASE, CONFIG_COMMAND (device, where));    
    port_uint8_out (PCI_DATA + (where & 3), value);
}

void pci_type1_write_config_u16 (pci_device_t *device, int where, 
    uint16_t value)
{
    port_uint32_out (PCI_BASE, CONFIG_COMMAND (device, where));
    port_uint32_out (PCI_DATA + (where & 2), value);
}

void pci_type1_write_config_u32 (pci_device_t *device, int where, 
    uint32_t value)
{
    port_uint32_out (PCI_BASE, CONFIG_COMMAND (device, where));
    port_uint32_out (PCI_DATA, value);
}

pci_operation_t pci_type1_operation = 
{
    pci_type1_read_config_u8,
    pci_type1_read_config_u16,
    pci_type1_read_config_u32,
    pci_type1_write_config_u8,
    pci_type1_write_config_u16,
    pci_type1_write_config_u32
};

/* Functions for accessing PCI configuration space with type 2 accesses. */

uint8_t pci_type2_read_config_u8 (pci_device_t *device, int where)
{
    uint8_t return_value;

    SET (device);
    return_value = port_uint8_in (IOADDR (device->device_function, where));
    port_uint8_out (PCI_BASE, 0);
  
    return return_value;
}

uint16_t pci_type2_read_config_u16 (pci_device_t *device, int where)
{
    uint16_t return_value;

    SET (device);
    return_value = port_uint16_in (IOADDR (device->device_function, where));
    port_uint8_out (PCI_BASE, 0);

    return return_value;
}

uint32_t pci_type2_read_config_u32 (pci_device_t *device, int where)
{
    uint32_t return_value;

    SET (device);
    return_value = port_uint32_in (IOADDR (device->device_function, where));
    port_uint8_out (PCI_BASE, 0);

    return return_value;
}

void pci_type2_write_config_u8 (pci_device_t *device, int where, uint8_t value)
{
    SET (device);
    port_uint8_out (IOADDR (device->device_function, where), value);
    port_uint8_out (PCI_BASE, 0);
}

void pci_type2_write_config_u16 (pci_device_t *device, int where, 
    uint16_t value)
{
    SET (device);
    port_uint16_out (IOADDR (device->device_function, where), value);
    port_uint8_out (PCI_BASE, 0);
}

void pci_type2_write_config_u32 (pci_device_t *device, int where, 
    uint32_t value)
{
    SET (device);
    port_uint32_out (IOADDR(device->device_function, where), value);
    port_uint8_out (PCI_BASE, 0);
}

pci_operation_t pci_type2_operation = 
{
    pci_type2_read_config_u8,
    pci_type2_read_config_u16,
    pci_type2_read_config_u32,
    pci_type2_write_config_u8,
    pci_type2_write_config_u16,
    pci_type2_write_config_u32
};
