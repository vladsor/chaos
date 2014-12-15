#include <enviroment.h>

#include <Interfaces/pci_bus.h>
#include "Include/pci_bus_interface.h"

#define DEBUG_MODULE_NAME "pci_bus"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include <debug/macros.h>
#include <exception/macros.h>

static method_description_t method_get_amount_description =
{
/*    method_id_t id; */
    METHOD_PCI_BUS_GET_AMOUNT_ID,
    
/*    wchar_t name[WSTRING_MAX_LENGTH]; */
    L"get_amount",

/*    uint32_t type; */
    METHOD_TYPE_DYNAMIC,

/*    p_parameter_description_t return_type; */
    NULL,

/*    sequence_t parameter_descriptions; */
    { NULL, 0, 0 },

/*    sequence_t exceptions; */
    { NULL, 0, 0 },
};

static void get_amount_wrapper (p_void_t function, context_t context, 
    sequence_t return_value, sequence_t parameters UNUSED)
{
    uint32_t count;
    p_pci_bus_get_amount_t get_amount;
    
    get_amount = (p_pci_bus_get_amount_t) function;
    
    count = get_amount (context);

    (uint32_t) ((p_uint32_t) return_value.data)[0] = count;
}

static method_description_t method_get_devices_description =
{
/*    method_id_t id; */
    METHOD_PCI_BUS_GET_DEVICES_ID,
    
/*    wchar_t name[WSTRING_MAX_LENGTH]; */
    L"get_devices",

/*    uint32_t type; */
    METHOD_TYPE_DYNAMIC,

/*    p_parameter_description_t return_type; */
    NULL,

/*    sequence_t parameter_descriptions; */
    { NULL, 0, 0 },

/*    sequence_t exceptions; */
    { NULL, 0, 0 },
};

static void get_devices_wrapper (p_void_t function, context_t context, 
    sequence_t return_value, sequence_t parameters)
{
    p_pci_bus_get_devices_t get_devices;
    sequence_t devices;
    uint32_t start;
    uint32_t count;
    
    get_devices = (p_pci_bus_get_devices_t) function;
    
    devices.data = (p_void_t) ((p_uint32_t) (parameters.data))[0];
    devices.count = (uint32_t) ((p_uint32_t) (parameters.data))[1];
    devices.block_size = (uint32_t) ((p_uint32_t) (parameters.data))[2];
    start = (uint32_t) ((p_uint32_t) (parameters.data))[3];
    
    count = get_devices (context, devices, start);

    (uint32_t) ((p_uint32_t) return_value.data)[0] = count;
}

static method_description_t method_find_devices_description =
{
/*    method_id_t id; */
    METHOD_PCI_BUS_FIND_DEVICES_ID,
    
/*    wchar_t name[WSTRING_MAX_LENGTH]; */
    L"find_devices",

/*    uint32_t type; */
    METHOD_TYPE_DYNAMIC,

/*    p_parameter_description_t return_type; */
    NULL,

/*    sequence_t parameter_descriptions; */
    { NULL, 0, 0 },

/*    sequence_t exceptions; */
    { NULL, 0, 0 },
};

static void find_devices_wrapper (p_void_t function, context_t context, 
    sequence_t return_value, sequence_t parameters)
{
    p_pci_bus_find_devices_t find_devices;
    
    uint16_t vendor_id;
    uint16_t device_id;
    uint8_t class_id;
    uint8_t subclass_id;
    uint8_t interface_id;
    sequence_t devices;
    uint32_t start;
    
    uint32_t count;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s: (%p, %p, %p, %p, %p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        function, context.object_data, context.handle_data, 
        return_value.data, parameters.data);
    
    find_devices = (p_pci_bus_find_devices_t) function;
    
    vendor_id = (uint32_t) ((p_uint32_t) (parameters.data))[0];
    device_id = (uint32_t) ((p_uint32_t) (parameters.data))[1];
    class_id = (uint32_t) ((p_uint32_t) (parameters.data))[2];
    subclass_id = (uint32_t) ((p_uint32_t) (parameters.data))[3];
    interface_id = (uint32_t) ((p_uint32_t) (parameters.data))[4];
    devices.data = (p_void_t) ((p_uint32_t) (parameters.data))[5];
    devices.count = (uint32_t) ((p_uint32_t) (parameters.data))[6];
    devices.block_size = (uint32_t) ((p_uint32_t) (parameters.data))[7];
    start = (uint32_t) ((p_uint32_t) (parameters.data))[8];
    
    count = find_devices (context, vendor_id, device_id, class_id, subclass_id,
        interface_id, devices, start);

    (uint32_t) ((p_uint32_t) return_value.data)[0] = count;
}

static method_reference_t methods[METHOD_PCI_BUS_NUMBER];
static sequence_t seq = {(void *) methods, METHOD_PCI_BUS_NUMBER, 
    sizeof (method_reference_t) };

static interface_description_t interface_description =
{
/*    interface_id_t id; */
    INTERFACE_PCI_BUS_ID,
    
/*    wchar_t name[WSTRING_MAX_LENGTH]; */
    L"pci_bus",
    
/*    uint32_t interface_type; */
    INTERFACE_TYPE_DYNAMIC,

/*    uint32_t number_of_references; */
    0
};

interface_reference_t pci_bus_interface_register (
    p_pci_bus_interface_table_t table)
{
    interface_reference_t interface;
    
    methods[METHOD_PCI_BUS_GET_AMOUNT_ID] = 
        method_create (&method_get_amount_description, 
            (p_method_function_t) get_amount_wrapper, 
            (p_void_t) table->get_amount);

    methods[METHOD_PCI_BUS_GET_DEVICES_ID] = 
        method_create (&method_get_devices_description, 
            (p_method_function_t) get_devices_wrapper, 
            (p_void_t) table->get_devices);

    methods[METHOD_PCI_BUS_FIND_DEVICES_ID] = 
        method_create (&method_find_devices_description, 
            (p_method_function_t) find_devices_wrapper, 
            (p_void_t) table->find_devices);
    
    interface = interface_create (&interface_description, seq);
    
    return interface;
}

