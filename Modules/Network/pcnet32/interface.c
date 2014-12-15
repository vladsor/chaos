#include <enviroment.h>

#include <Interfaces/pci_bus.h>
#include <Interfaces/pci_device.h>

#include "interface.h"
#include "types.h"
#include "pcnet32.h"

#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

#define PCI_RESOURCE_IO                 0x00000100
#define PCI_RESOURCE_MEMORY             0x00000200
#define PCI_RESOURCE_IRQ                0x00000400
#define PCI_RESOURCE_DMA                0x00000800

const char *version = "pcnet32.c:v1.25kf 26.9.1999 tsbogend@alpha.franken.de\n";

int pcnet32_debug = 10;

#define PCI_VENDOR_ID_AMD		0x1022
#define PCI_DEVICE_ID_AMD_LANCE		0x2000
#define PCI_DEVICE_ID_AMD_LANCE_HOME	0x2001

typedef struct
{
    uint16_t vendor_id;
    uint16_t device_id;
} pci_device_probe_t;

pci_device_probe_t pci_device_probe[] =
{
    { PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_LANCE_HOME },
    { PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_LANCE },

    /* End of list. */

    { 0xFFFF, 0xFFFF }
};

return_t pcnet32_main (int argc UNUSED, char *argv[] UNUSED)
{
    pci_device_info_t device_info;
    unsigned int number_of_devices;
    unsigned int probe_counter;
    handle_t pci;
    handle_t rt_device;
    
    global_namespace_resolve ("/devices/pci", &pci);
    register_object_open (&pci, IID_PCI_BUS);
  
    for (probe_counter = 0; pci_device_probe[probe_counter].vendor_id != 
        0xFFFF; probe_counter++)
    {
        uint32_t device = 0;
        number_of_devices = 1;
        
        pci_bus$find_devices (&pci, pci_device_probe[probe_counter].vendor_id,
            pci_device_probe[probe_counter].device_id, 0xFF, 0xFF, 0xFF, device, 
            &number_of_devices, &rt_device);

        if (number_of_devices == 1)
        {
            ethernet_device_t *dev;
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Found PCNET32 adapter.\n");
            
            register_object_open (&rt_device, IID_PCI_DEVICE);
            pci_device$get_info (&rt_device, &device_info);

            dev = pcnet32_probe_pci (&rt_device, &device_info);            
            pcnet32_open (dev);
        }
    }

    return 0;
}

