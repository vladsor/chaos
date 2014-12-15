#include <enviroment.h>

#include <Interfaces/namespace.h>

#include <Classes/pci_bus_object.h>
#include <Classes/pci_device_object.h>

#include "Include/interface.h"
#include "Include/pci.h"

#include "Include/pci_bus_interface.h"
#include "Include/pci_device_interface.h"

#include "Include/pci_bus_object_class.h"
#include "Include/pci_device_object_class.h"

#define DEBUG_MODULE_NAME "PCI"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

/* Get the amount of PCI devices in this system. */
static uint32_t pci_bus_get_amount (context_t context UNUSED)
{
    return pci_device_list.number_of_nodes;
}

/* Get brief information about all devices in the system. */
static uint32_t pci_bus_get_devices (context_t context UNUSED, 
    sequence_t devices, uint32_t start)
{
    pci_device_t *device = (pci_device_t *) pci_device_list.first;
    uint32_t counter;
    uint32_t real_devices = 0;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
         "%s: %s (%p, %u, %u)\n",
        __FILE__, __FUNCTION__,
        devices.data, devices.count, start);

    for (counter = 0; (device != NULL) && 
        (counter < (start + devices.count)); 
        device = (pci_device_t *) device->next, counter++)
    {
        if (counter > start)
        {
            ((p_reference_t) (devices.data))[real_devices] = 
                device->reference;
            real_devices++;
        }
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
         "%s::%s DONE (%u)\n",
        __FILE__, __FUNCTION__, real_devices);

    return real_devices;
}


static uint32_t pci_bus_find_devices (context_t context UNUSED, 
    uint16_t vendor_id, uint16_t device_id, uint8_t class_id, 
    uint8_t subclass_id, uint8_t interface_id, 
    sequence_t devices, uint32_t start)
{
    pci_device_t *device = (pci_device_t *) pci_device_list.first;
    uint32_t counter;
    uint32_t real_devices = 0;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
         "%s::%s (%X, %X, %X, %X, %X, %p, %u, %u)\n",
        __FILE__, __FUNCTION__,
        vendor_id, device_id, class_id, subclass_id, interface_id,
        devices.data, devices.count, start);

    for (counter = 0; (device != NULL) && 
        (counter < (start + devices.count)); 
        device = (pci_device_t *) device->next)
    {

        if ((vendor_id == 0xFFFF || vendor_id == device->vendor_id) &&
            (device_id == 0xFFFF || device_id == device->device_id) &&
            (class_id == 0xFF || class_id == device->class_id) &&
            (subclass_id == 0xFF || subclass_id == device->subclass_id) &&
            (interface_id == 0xFF || interface_id == device->interface_id))
        {
            counter++;
              
            if (counter > start)
            {
                ((p_reference_t) (devices.data))[real_devices] = 
                    device->reference;
                real_devices++;
            }

        }
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
         "%s::%s DONE (%u)\n",
        __FILE__, __FUNCTION__, real_devices);

    return real_devices;
}


static pci_bus_interface_table_t pci_bus_table =
{
    pci_bus_get_amount,
    pci_bus_get_devices,
    pci_bus_find_devices,
};


static void interface_pci_device_get_info (context_t context, 
    pci_device_info_t *device_info)
{
    pci_device_t *device = (pci_device_t *) context.object_data;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
         "%s: %s (%p, %p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        device, device_info);

    device_info->vendor_id = device->vendor_id;
    string_copy_max (device_info->vendor_name, device->vendor_name, 80);

    device_info->device_id = device->device_id;
    string_copy_max (device_info->device_name, device->device_name, 80);

    device_info->irq = device->irq;

    memory_copy (device_info->resource, device->resource, 
        sizeof (pci_resource_t) * PCI_NUMBER_OF_RESOURCES);
}

static void interface_pci_device_enable (context_t context)
{
    pci_device_t *device;

    device = (pci_device_t *) context.object_data;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
         "%s: %s (%p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        device);
    
    pci_enable_device (device);
}

static void interface_pci_device_disable (context_t context)
{
    pci_device_t *device;

    device = (pci_device_t *) context.object_data;
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
         "%s: %s (%p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        device);
    
    pci_disable_device (device);
}

static void interface_pci_device_set_master (context_t context)
{
    pci_device_t *device;

    device = (pci_device_t *) context.object_data;
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
         "%s: %s (%p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        device);
    
    pci_set_master (device);
}

static pci_device_interface_table_t pci_device_table =
{
    interface_pci_device_get_info,
    interface_pci_device_enable,
    interface_pci_device_disable,
    interface_pci_device_set_master,
};

extern handle_reference_t kernel_handle_namespace;
static class_reference_t pci_bus_class = REFERENCE_NULL;
static object_reference_t pci_bus = REFERENCE_NULL;
static class_reference_t pci_device_class = REFERENCE_NULL;

/* Main function. */

return_t pci_main (int argc UNUSED, char *argv[] UNUSED, char **envp UNUSED)
{
    pci_device_t *device;
    wchar_t device_name[WSTRING_MAX_LENGTH];
    interface_reference_t pci_bus_interfaces[1];
    interface_reference_t pci_device_interfaces[1];

    /* Initialise the PCI support. */

    if (!pci_init ())
    {
        return -1;
    }
    
    pci_bus_interfaces[0] = pci_bus_interface_register (&pci_bus_table);
    pci_bus_class = pci_bus_object_class_register (pci_bus_interfaces);

    pci_bus = pci_bus_object$create (pci_bus_class);
    namespace$bind (kernel_handle_namespace, L"/devices/pci", pci_bus);

    pci_device_interfaces[0] = pci_device_interface_register (&pci_device_table);
    pci_device_class = pci_device_object_class_register (pci_device_interfaces);

    device = (pci_device_t *) pci_device_list.first;

    while (device != NULL)
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
            "PCI: Device: %s, BIST: %s\n",
            device->device_name, device->has_bist ? "TRUE" : "FALSE");

        device->reference = pci_device_object$create (pci_device_class, device);
        
        wstring_print (device_name, L"/devices/pci-devices/%s", 
            device->slot_name);
        namespace$bind (kernel_handle_namespace, device_name, device->reference);
            
        device = (pci_device_t *) device->next;
    }
    
    return 0;
}


