#include <enviroment.h>

#include "integer_control_interface.h"

#define MODULE_NAME "Repository"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>
#include <exception/macros.h>

static method_description_t method_create_description =
{
/*    method_id_t id; */
    METHOD_CONTROL_CREATE_ID,
    
/*    wchar_t name[WSTRING_MAX_LENGTH]; */
    L"create",

/*    uint32_t type; */
    METHOD_TYPE_DYNAMIC,

/*    p_parameter_description_t return_type; */
    NULL,

/*    sequence_t parameter_descriptions; */
    { NULL, 0, 0 },

/*    sequence_t exceptions; */
    { NULL, 0, 0 },
};

static method_description_t method_destroy_description =
{
/*    method_id_t id; */
    METHOD_CONTROL_DESTROY_ID,
    
/*    wchar_t name[WSTRING_MAX_LENGTH]; */
    L"destroy",

/*    uint32_t type; */
    METHOD_TYPE_DYNAMIC,

/*    p_parameter_description_t return_type; */
    NULL,

/*    sequence_t parameter_descriptions; */
    { NULL, 0, 0 },

/*    sequence_t exceptions; */
    { NULL, 0, 0 },
};

static method_reference_t methods[METHOD_CONTROL_NUMBER];

static interface_description_t interface_control_description =
{
/*    interface_id_t id; */
    INTERFACE_INTEGER_VALUE_CONTROL_ID,
    
/*    wchar_t name[WSTRING_MAX_LENGTH]; */
    L"integer::control",
    
/*    uint32_t interface_type; */
    INTERFACE_TYPE_CONTROL,

/*    uint32_t number_of_references; */
    0
};

interface_reference_t integer_control_interface_register (
    p_integer_control_interface_table_t table)
{
    sequence_t seq = {(void *) methods, METHOD_CONTROL_NUMBER, 
        sizeof (method_reference_t) };
    
    methods[0] = method_create (&method_create_description, 
        (p_method_function_t) table->create);
    methods[1] = method_create (&method_destroy_description, 
        (p_method_function_t) table->destroy);
    
    return interface_create (&interface_control_description, seq);
}

