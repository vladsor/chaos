#include <enviroment.h>

#include "../kernel_interfaces.h"
#include "integer_control_interface.h"

//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

typedef struct
{
    atomic_uint32_t value;
} integer_value_data_t;

typedef integer_value_data_t * p_integer_value_data_t;

static p_void_t integer_value_create (context_t context UNUSED, 
    uint32_t value)
{
    p_void_t object_data;
    p_integer_value_data_t object;

    memory_allocate (&object_data, sizeof (integer_value_data_t));
    object = (p_integer_value_data_t) object_data;
    
    atomic_uint32_set (&object->value, value);

    return object_data;
}

static void integer_value_destroy (context_t context UNUSED, 
    p_void_t object_data)
{
    p_integer_value_data_t object = (p_integer_value_data_t) object_data;

    memory_deallocate (object);
}

static integer_control_interface_table_t integer_control_table = 
{
    &integer_value_create,
    &integer_value_destroy
};

/* Main function. */

interface_reference_t integer_value_init (void)
{
    return integer_control_interface_register (&integer_control_table);
}

