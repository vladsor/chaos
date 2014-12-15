#include <enviroment.h>

#include "integer_interface.h"

#define MODULE_NAME "Repository"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>
#include <exception/macros.h>

enum 
{
    METHOD_INTEGER_GET_ID,
    METHOD_INTEGER_SET_ID,
    
    METHOD_INTEGER_NUMBER
};

static method_description_t method_get_description =
{
/*    method_id_t id; */
    METHOD_INTEGER_GET_ID,
    
/*    wchar_t name[WSTRING_MAX_LENGTH]; */
    L"get",

/*    p_parameter_description_t return_type; */
    NULL,

/*    sequence_t parameter_descriptions; */
    { NULL, 0, 0 },

/*    sequence_t exceptions; */
    { NULL, 0, 0 },
};

static method_description_t method_set_description =
{
/*    method_id_t id; */
    METHOD_INTEGER_SET_ID,
    
/*    wchar_t name[WSTRING_MAX_LENGTH]; */
    L"set",

/*    p_parameter_description_t return_type; */
    NULL,

/*    sequence_t parameter_descriptions; */
    { NULL, 0, 0 },

/*    sequence_t exceptions; */
    { NULL, 0, 0 },
};

static method_reference_t methods[METHOD_INTEGER_NUMBER];

static interface_description_t interface_integer_description =
{
/*    interface_id_t id; */
    0x0002,
    
/*    wchar_t name[WSTRING_MAX_LENGTH]; */
    L"integer",
    
/*    uint32_t interface_type; */
    INTERFACE_TYPE_DYNAMIC,

/*    uint32_t number_of_references; */
    0
};

interface_reference_t integer_interface_register (
    p_integer_interface_table_t table)
{
    sequence_t seq = {(void *) methods, METHOD_INTEGER_NUMBER, 
        sizeof (method_reference_t) };
    
    methods[METHOD_INTEGER_GET_ID] = method_create (&method_get_description, 
        (p_method_function_t) table->get);
    methods[METHOD_INTEGER_SET_ID] = method_create (&method_set_description, 
        (p_method_function_t) table->set);
    
    return interface_create (&interface_integer_description, seq);
}

