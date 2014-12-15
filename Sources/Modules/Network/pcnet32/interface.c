#include <enviroment.h>

#include <Classes/kernel.h>

#include <Interfaces/pci_bus.h>
#include <Interfaces/pci_device.h>

#include "Include/interface.h"
#include "Include/types.h"
#include "Include/pcnet32.h"

#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

#define PCI_RESOURCE_IO                 0x00000100
#define PCI_RESOURCE_MEMORY             0x00000200
#define PCI_RESOURCE_IRQ                0x00000400
#define PCI_RESOURCE_DMA                0x00000800

const char *version = "pcnet32.c:v1.25kf 26.9.1999 tsbogend@alpha.franken.de";

int pcnet32_debug = 0;

#define PCI_VENDOR_ID_AMD               0x1022
#define PCI_DEVICE_ID_AMD_LANCE         0x2000
#define PCI_DEVICE_ID_AMD_LANCE_HOME    0x2001

typedef struct
{
    uint16_t vendor_id;
    uint16_t device_id;
} pci_device_probe_t;

pci_device_probe_t pci_device_probe[] =
{
    { PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_LANCE_HOME },
    { PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_LANCE },

    /* End of list. */

    { 0xFFFF, 0xFFFF }
};

extern handle_reference_t kernel_handle_namespace;

return_t pcnet32_main (int argc UNUSED, char *argv[] UNUSED, char **envp UNUSED)
{
    pci_device_info_t device_info;
    unsigned int number_of_devices;
    unsigned int probe_counter;
    
    object_reference_t pci_bus_object = REFERENCE_NULL;
    handle_reference_t pci_bus = REFERENCE_NULL;
    
    object_reference_t pci_device_object = REFERENCE_NULL;
    handle_reference_t pci_device = REFERENCE_NULL;
    
    sequence_t dev_seq = {data: &pci_device_object, count: 1, block_size: 0};
    
    pci_bus_object = namespace$resolve (kernel_handle_namespace, 
        L"/devices/pci");
    
    pci_bus = pci_bus$open (pci_bus_object);
  
    for (probe_counter = 0; pci_device_probe[probe_counter].vendor_id != 
        0xFFFF; probe_counter++)
    {
        uint32_t device_count = 0;

        number_of_devices = pci_bus$find_devices (pci_bus, 
            pci_device_probe[probe_counter].vendor_id,
            pci_device_probe[probe_counter].device_id, 0xFF, 0xFF, 0xFF, 
            dev_seq, device_count);

        if (number_of_devices == 1)
        {
            ethernet_device_t *dev;
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Found PCNET32 adapter.\n");
            
            pci_device = pci_device$open (pci_device_object);

            pci_device$get_info (pci_device, &device_info);

            dev = pcnet32_probe_pci (pci_device, &device_info);            
            pcnet32_open (dev);
        }
    }

    return 0;
}

