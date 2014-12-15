#include <enviroment.h>

#include <Classes/kernel.h>

#include <Interfaces/pci_bus_control.h>

#include "Include/interface.h"
#include "Include/types.h"
#include "Include/pcnet32.h"

#include "Include/pcnet32_manager_class.h"

#include "Include/debug_event_class.h"
#include "Include/irq_event_class.h"

#define DEBUG_MODULE_NAME L"PCNet32"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#ifndef __STORM_KERNEL__
#   define DEBUG_SUPPLIER (pcnet32_debug_supplier)
#endif

#include <debug/macros.h>

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

event_supplier_reference_t pcnet32_debug_supplier = REFERENCE_NULL;
static object_reference_t manager_object;
static class_reference_t manager_class;

event_supplier_reference_t irq_supplier;
event_consumer_reference_t irq_consumer;

return_t pcnet32_main (int argc UNUSED, char *argv[] UNUSED, char **envp UNUSED)
{
    sequence_t empty_seq = {data: NULL, count: 0};
    pci_device_info_t device_info;
    unsigned int number_of_devices;
    unsigned int probe_counter;
    event_supplier_interface_reference_t manager_supplier_interfaces[1];
    event_consumer_interface_reference_t manager_consumer_interfaces[1];
    cpu_reference_t irq_handler_cpu;
    
    object_reference_t pci_bus_object = REFERENCE_NULL;
    handle_reference_t pci_bus = REFERENCE_NULL;
    
    object_reference_t pci_device_object = REFERENCE_NULL;
    handle_reference_t pci_device = REFERENCE_NULL;
    
    sequence_t dev_seq = {data: &pci_device_object, count: 1};
    
    pci_bus_object = namespace$resolve (kernel_handle_namespace, 
        L"/devices/bus/pci");
    
    pci_bus = pci_bus_control$handle$create (pci_bus_object);

    manager_supplier_interfaces[0] = debug_supplier_interface_register (
        EVENT_CONSUMER_TYPE_PUSH, NULL, REFERENCE_NULL);
    irq_handler_cpu = cpu_create (0);
    manager_consumer_interfaces[0] = irq_consumer_interface_register (
        EVENT_CONSUMER_TYPE_PUSH, &pcnet32_irq_handler, irq_handler_cpu);
    manager_class = pcnet32_manager_class_register (NULL, 
        manager_supplier_interfaces, manager_consumer_interfaces);
    manager_object = object_create (manager_class, SECURITY_CURRENT, 
        empty_seq, 0);

    pcnet32_debug_supplier = debug$supplier$create (manager_object);
    event_supplier_set_queue (pcnet32_debug_supplier, kernel_debug_queue);
/*
    pcnet32_irq_supplier = irq$supplier$create (OBJECT_KERNEL, KEYBOARD_IRQ);
    pcnet32_irq_consumer = irq$consumer$create (manager_object);

    pcnet32_irq_queue = event_queue_create (irq_description_register (), 
        EVENT_QUEUE_TYPE_ASYNCHRONOUS, 1);
    event_supplier_set_queue (pcnet32_irq_supplier, pcnet32_irq_queue);
    event_consumer_set_queue (pcnet32_irq_consumer, pcnet32_irq_queue);
*/  
    for (probe_counter = 0; pci_device_probe[probe_counter].vendor_id != 
        0xFFFF; probe_counter++)
    {
        uint32_t device_count = 0;

        number_of_devices = pci_bus_control$find_devices (pci_bus, 
            pci_device_probe[probe_counter].vendor_id,
            pci_device_probe[probe_counter].device_id, 0xFF, 0xFF, 0xFF, 
            dev_seq, device_count);

        if (number_of_devices == 1)
        {
            ethernet_device_t *dev;
            
            DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE, 
                L"%S: Found adapter.\n",
                DEBUG_MODULE_NAME);
            
            pci_device = pci_device_control$handle$create (pci_device_object);

            pci_device_control$get_info (pci_device, &device_info);

            dev = pcnet32_probe_pci (pci_device, &device_info);            
            pcnet32_open (dev);
        }
    }
    
    handle_destroy (pci_bus);
    reference_release (pci_bus_object);

    return STORM_RETURN_SUCCESS;
}

