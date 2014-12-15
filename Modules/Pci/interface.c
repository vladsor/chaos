#include <enviroment.h>

#include <Classes/pci_bus.h>
#include <Classes/pci_device.h>

#include "interface.h"
#include "pci.h"

//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

/* Get the amount of PCI devices in this system. */
static return_t pci_bus_get_amount (context_t *context UNUSED, 
    uint32_t *devices)
{
    (*devices) = pci_device_list.number_of_nodes;
    
    return 0;
}

static pci_bus_get_amount_method_t pci_bus_get_amount_method =
{
    PCI_BUS_GET_AMOUNT_METHOD (pci_bus_get_amount)
};

/* Get brief information about all devices in the system. */
static return_t pci_bus_get_devices (context_t *context UNUSED, uint32_t start, 
    uint32_t count, handle_t *devices)
{
#if 0
    pci_device_type *device = (pci_device_type *) pci_device_list.first;
        static pci_device_info_type *device_info = NULL;
        unsigned int counter = 0;
        unsigned int devices = 0;
    
    while(device != NULL)
    {
      devices++;
      device = (pci_device_type *) device->next;
    }

        /* Allocate memory to hold this many devices. */
        
        memory_allocate ((void **) &device_info,
                         devices * sizeof (pci_device_info_type));

        device = (pci_device_type *) pci_device_list.first;

        while (device != NULL && counter < devices)
        {
          string_copy(device_info[counter].vendor_name, device->vendor_name);
          string_copy(device_info[counter].device_name, device->device_name);
          device_info[counter].irq = device->irq;

          memory_copy (&device_info[counter].resource, device->resource,
                       sizeof (pci_resource_type) * PCI_NUMBER_OF_RESOURCES);
          counter++;

          device = (pci_device_type *) device->next;
        }

        message_parameter.data = device_info;
        message_parameter.length = devices * sizeof (pci_device_info_type);
        message_parameter.block = FALSE;
        ipc_send (ipc_structure.output_mailbox_id, &message_parameter);
        memory_deallocate ((void **) &device_info);
        message_parameter.block = TRUE;
#endif 
    return 0;
}

static pci_bus_get_devices_method_t pci_bus_get_devices_method =
{
    PCI_BUS_GET_DEVICES_METHOD (pci_bus_get_devices)
};


static return_t pci_bus_find_devices (context_t *context UNUSED, 
    uint16_t vendor_id, uint16_t device_id, uint8_t class_id, 
    
uint8_t subclass_id, uint8_t interface_id, uint32_t start, 
    uint32_t *number_of_devices, handle_t *devices)
{
    pci_device_t *device = (pci_device_t *) pci_device_list.first;
    uint32_t counter;
    uint32_t real_devices = 0;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
         "%s::%s (%X, %X, %X, %X, %X, %u, %p, %p)\n",
        __FILE__, __FUNCTION__,
        vendor_id, device_id, class_id, subclass_id, interface_id,
        start, number_of_devices, devices);

    for (counter = 0; (device != NULL) && 
        (counter < (start + (*number_of_devices))); 
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
                register_handle_clone (&device->handle, &devices[real_devices], 
                    0);
                real_devices++;
            }

        }
    }

    (*number_of_devices) = real_devices;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
         "%s::%s DONE (%u)\n",
        __FILE__, __FUNCTION__, real_devices);

    return 0;
}

static pci_bus_find_devices_method_t pci_bus_find_devices_method =
{
    PCI_BUS_FIND_DEVICES_METHOD (pci_bus_find_devices)
};

static method_t *bus_methods[] =
{
    (method_t *) &pci_bus_get_amount_method,
    (method_t *) &pci_bus_get_devices_method,
    (method_t *) &pci_bus_find_devices_method,
};

#define number_of_bus_methods 3

static return_t pci_device_get_info (context_t *context, 
    pci_device_info_t *device_info)
{
    pci_device_t *device = (pci_device_t *) context->object_data;

    device_info->vendor_id = device->vendor_id;
    string_copy_max (device_info->vendor_name, device->vendor_name, 80);

    device_info->device_id = device->device_id;
    string_copy_max (device_info->device_name, device->device_name, 80);

    device_info->irq = device->irq;

    memory_copy (device_info->resource, device->resource, 
        sizeof (pci_resource_t) * PCI_NUMBER_OF_RESOURCES);
    
    return 0;
}

static pci_device_get_info_method_t pci_device_get_info_method =
{
    PCI_DEVICE_GET_INFO_METHOD (pci_device_get_info)
};

static return_t interface_pci_device_enable (context_t *context)
{
    pci_device_t *device;
    
    device = (pci_device_t *) context->object_data;
    
    pci_enable_device (device);
    
    return 0;
}

static pci_device_enable_method_t pci_device_enable_method =
{
    PCI_DEVICE_ENABLE_METHOD (interface_pci_device_enable)
};

static return_t interface_pci_device_disable (context_t *context)
{
    pci_device_t *device;
    
    device = (pci_device_t *) context->object_data;
    
    pci_disable_device (device);
    
    return 0;
}

static pci_device_disable_method_t pci_device_disable_method =
{
    PCI_DEVICE_DISABLE_METHOD (interface_pci_device_disable)
};

static return_t interface_pci_device_set_master (context_t *context)
{
    pci_device_t *device;
    
    device = (pci_device_t *) context->object_data;
    
    pci_set_master (device);
    
    return 0;
}

static pci_device_set_master_method_t pci_device_set_master_method =
{
    PCI_DEVICE_SET_MASTER_METHOD (interface_pci_device_set_master)
};

static method_t *device_methods[] =
{
    (method_t *) &pci_device_get_info_method,
    
    (method_t *) &pci_device_enable_method,
    (method_t *) &pci_device_disable_method,
    (method_t *) &pci_device_set_master_method
};

#define number_of_device_methods 4

static return_t pci_device_create (context_t *context, 
    void *parameter)
{
    context->object_data = parameter;
    
    return 0;
}

object_create_method_t pci_device_create_method =
{
    &pci_device_create,
    MID_OBJECT_CREATE,
    sizeof (void *),
    1,
    {
        {sizeof (void *)}
    }
};

static return_t pci_device_destroy (context_t *context UNUSED)
{
//    memory_deallocate (context->object_data);
    
    return 0;
}

object_destroy_method_t pci_device_destroy_method =
{
    &pci_device_destroy,
    MID_OBJECT_DESTROY,
    0,
    0,
};

static method_t *control_methods[] = 
{
    (method_t *) &pci_device_create_method,
    (method_t *) &pci_device_destroy_method,
};

#define number_of_control_methods 2

static interface_id_t pci_bus_interface_id;
static class_id_t pci_bus_class_id;
static handle_t pci_bus = {HANDLE_HEADER_EMPTY, NULL};

static interface_id_t pci_device_control_id;
static interface_id_t pci_device_interface_id;
static class_id_t pci_device_class_id;


/* Main function. */

return_t pci_main (int argc UNUSED, char *argv[] UNUSED)
{
    pci_device_t *device;
    char device_name[256];

    /* Initialise the PCI support. */

    if (!pci_init ())
    {
        return -1;
    }

    register_interface_register (&pci_bus_interface_id, IID_PCI_BUS, 
        INTERFACE_TYPE_DYNAMIC, number_of_bus_methods, bus_methods, NULL);
    register_class_register (&pci_bus_class_id, CID_PCI_BUS, CLASS_TYPE_DYNAMIC,
        1, &pci_bus_interface_id, IID_NONE);
    
    register_object_create (&pci_bus, pci_bus_class_id, NULL);
    global_namespace_bind ("/devices/pci", &pci_bus);

    register_interface_register (&pci_device_control_id, IID_PCI_DEVICE_CONTROL,
        INTERFACE_TYPE_CONTROL, number_of_control_methods, control_methods, 
        NULL);
    register_interface_register (&pci_device_interface_id, IID_PCI_DEVICE, 
        INTERFACE_TYPE_DYNAMIC, number_of_device_methods, device_methods, NULL);
    register_class_register (&pci_device_class_id, CID_PCI_DEVICE, 
        CLASS_TYPE_DYNAMIC, 1, &pci_device_interface_id, pci_device_control_id);

    device = (pci_device_t *) pci_device_list.first;

    while (device != NULL)
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
            "PCI: Device: %s, BIST: %s\n",
            device->device_name, device->has_bist ? "TRUE" : "FALSE");

        memory_set_uint8 ((uint8_t *) &device->handle, 0, sizeof (handle_t));
        register_object_create (&device->handle, pci_device_class_id, device);
        
        string_print (device_name, "/devices/pci-devices/%s", 
            device->slot_name);
        global_namespace_bind (device_name, &device->handle);
            
        device = (pci_device_t *) device->next;
    }
    
    return 0;
}


