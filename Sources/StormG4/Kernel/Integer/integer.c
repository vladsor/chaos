#include <enviroment.h>

#include "integer_value_class.h"
#include "integer_control_interface.h"

//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

typedef struct
{
    atomic_uint32_t value;
} integer_value_data_t;

typedef integer_value_data_t * p_integer_value_data_t;

static p_void_t integer_object_create (context_t context UNUSED, 
    uint32_t value)
{
    p_void_t object_data;
    p_integer_value_data_t object;

    memory_allocate (&object_data, sizeof (integer_value_data_t));
    object = (p_integer_value_data_t) object_data;
    
    atomic_uint32_set (&object->value, value);

    return object_data;
}

static void integer_object_destroy (context_t context UNUSED, 
    p_void_t object_data)
{
    p_integer_value_data_t object = (p_integer_value_data_t) object_data;

    memory_deallocate (object);
}

static integer_control_interface_table_t integer_control_table = 
{
    &integer_object_create,
    &integer_object_destroy
};

static void integer_get (context_t context,
    p_uint32_t value)
{
    p_integer_value_data_t this = (p_integer_value_data_t) context.object_data;
    
    (*value) = atomic_uint32_read (&this->value);
}

static void integer_set (context_t context,
    uint32_t value)
{
    p_integer_value_data_t this = (p_integer_value_data_t) context.object_data;
    
    atomic_uint32_set (&this->value, value);
}

static integer_interface_table_t integer_table = 
{
    &integer_get,
    &integer_set
};

/* Main function. */

void integer_value_init (void)
{
    interface_reference_t control_interface;
    class_reference_t integer_class;
    object_reference_t repository;

    control_interface = integer_control_interface_register (&integer_control_table);

    integer_class = integer_value_class_register (repository, &integer_table);

//    class = integer_value$create (integer_class);
//    global_namespace_bind ("/storm/classes/integer", integer_class);
}

