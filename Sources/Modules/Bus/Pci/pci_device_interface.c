#include <enviroment.h>

#include <Interfaces/pci_device.h>
#include "Include/pci_device_interface.h"

#define DEBUG_MODULE_NAME "pci_device"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include <debug/macros.h>
#include <exception/macros.h>

static method_description_t method_get_info_description =
{
/*    method_id_t id; */
    METHOD_PCI_DEVICE_GET_INFO_ID,
    
/*    wchar_t name[WSTRING_MAX_LENGTH]; */
    L"get_info",

/*    uint32_t type; */
    METHOD_TYPE_DYNAMIC,

/*    p_parameter_description_t return_type; */
    NULL,

/*    sequence_t parameter_descriptions; */
    { NULL, 0, 0 },

/*    sequence_t exceptions; */
    { NULL, 0, 0 },
};

static void get_info_wrapper (p_void_t function, context_t context, 
    sequence_t return_value UNUSED, sequence_t parameters)
{
    p_pci_device_get_info_t get_info;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s: (%p, %p, %p, %p, %p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        function, context.object_data, context.handle_data, 
        return_value.data, parameters.data);
    
    get_info = (p_pci_device_get_info_t) function;
    
    get_info (context, 
        (pci_device_info_t *) ((p_uint32_t) (parameters.data))[0]);
}

static method_description_t method_enable_description =
{
/*    method_id_t id; */
    METHOD_PCI_DEVICE_ENABLE_ID,
    
/*    wchar_t name[WSTRING_MAX_LENGTH]; */
    L"enable",

/*    uint32_t type; */
    METHOD_TYPE_DYNAMIC,

/*    p_parameter_description_t return_type; */
    NULL,

/*    sequence_t parameter_descriptions; */
    { NULL, 0, 0 },

/*    sequence_t exceptions; */
    { NULL, 0, 0 },
};

static void enable_wrapper (p_void_t function, context_t context, 
    sequence_t return_value UNUSED, sequence_t parameters UNUSED)
{
    p_pci_device_enable_t enable;
    
    enable = (p_pci_device_enable_t) function;
    
    enable (context);
}

static method_description_t method_disable_description =
{
/*    method_id_t id; */
    METHOD_PCI_DEVICE_DISABLE_ID,
    
/*    wchar_t name[WSTRING_MAX_LENGTH]; */
    L"disable",

/*    uint32_t type; */
    METHOD_TYPE_DYNAMIC,

/*    p_parameter_description_t return_type; */
    NULL,

/*    sequence_t parameter_descriptions; */
    { NULL, 0, 0 },

/*    sequence_t exceptions; */
    { NULL, 0, 0 },
};

static void disable_wrapper (p_void_t function, context_t context, 
    sequence_t return_value UNUSED, sequence_t parameters UNUSED)
{
    p_pci_device_disable_t disable;
    
    disable = (p_pci_device_disable_t) function;
    
    disable (context);
}

static method_description_t method_set_master_description =
{
/*    method_id_t id; */
    METHOD_PCI_DEVICE_SET_MASTER_ID,
    
/*    wchar_t name[WSTRING_MAX_LENGTH]; */
    L"set_master",

/*    uint32_t type; */
    METHOD_TYPE_DYNAMIC,

/*    p_parameter_description_t return_type; */
    NULL,

/*    sequence_t parameter_descriptions; */
    { NULL, 0, 0 },

/*    sequence_t exceptions; */
    { NULL, 0, 0 },
};

static void set_master_wrapper (p_void_t function, context_t context, 
    sequence_t return_value UNUSED, sequence_t parameters UNUSED)
{
    p_pci_device_set_master_t set_master;
    
    set_master = (p_pci_device_set_master_t) function;
    
    set_master (context);
}

static method_reference_t methods[METHOD_PCI_DEVICE_NUMBER];
static sequence_t seq = {(void *) methods, METHOD_PCI_DEVICE_NUMBER, 
    sizeof (method_reference_t) };

static interface_description_t interface_description =
{
/*    interface_id_t id; */
    INTERFACE_PCI_DEVICE_ID,
    
/*    wchar_t name[WSTRING_MAX_LENGTH]; */
    L"pci_device",
    
/*    uint32_t interface_type; */
    INTERFACE_TYPE_DYNAMIC,

/*    uint32_t number_of_references; */
    0
};

interface_reference_t pci_device_interface_register (
    p_pci_device_interface_table_t table)
{
    interface_reference_t interface;
    
    methods[METHOD_PCI_DEVICE_GET_INFO_ID] = 
        method_create (&method_get_info_description, 
            (p_method_function_t) get_info_wrapper, 
            (p_void_t) table->get_info);

    methods[METHOD_PCI_DEVICE_ENABLE_ID] = 
        method_create (&method_enable_description, 
            (p_method_function_t) enable_wrapper, 
            (p_void_t) table->enable);

    methods[METHOD_PCI_DEVICE_DISABLE_ID] = 
        method_create (&method_disable_description, 
            (p_method_function_t) disable_wrapper, 
            (p_void_t) table->disable);

    methods[METHOD_PCI_DEVICE_SET_MASTER_ID] = 
        method_create (&method_set_master_description, 
            (p_method_function_t) set_master_wrapper, 
            (p_void_t) table->set_master);
    
    interface = interface_create (&interface_description, seq);
    
    return interface;
}

