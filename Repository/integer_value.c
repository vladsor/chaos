#include <enviroment.h>

#include <Classes/integer.h>

#include "../objects.h"

//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

typedef struct
{
    atomic_uint32_t value;
} integer_value_t;

static sequence_t integer_value_create (context_t context UNUSED, 
    class_t class UNUSED, uint32_t options UNUSED, sequence_t parameters)
{
    sequeence_t object_data;
    p_integer_value_t object;
    context_t context = {NULL, NULL}

    object_data = memory_allocate (sizeof (integer_value_t));
    object = (p_integer_value_t) object_data.data;
    
    object->value = (*((uint32_t *) parameters->data));

    return object_data;
}

static void integer_value_destroy (context_t context UNUSED, 
    sequence_t object_data)
{
    p_integer_value_t object = (integer_value_t *) object_data.data;

    memory_deallocate (this);
}

static sequence_t integer_value_open (context_t context UNUSED,
    sequence_t object_data UNUSED, interface_t interface UNUSED)
{
    sequence_t handle;
    
    handle.data = NULL;
    handle.length = 0;
    
    return handle;
}

static void integer_value_close (context_t context UNUSED,
    sequence_t object_data UNUSED, sequence_t handle_data UNUSED)
{
}

static sequence_t integer_value_clone_handle (context_t UNUSED,
    sequence_t object_data UNUSED, sequence_t handle_data)
{
    return handle_data;
}

static bool integer_value_is_nil (context_t context UNUSED,
    sequence_t object_data)
{
    return object_data.data == NULL;
}

static interface_t integer_value_get_opened_interface (
    context_t context UNUSED,
    interface_t current_interface)
{
    return current_interface;
}

static void integer_get (p_context_t context,
    uint32_t *value)
{
    integer_value_t *this = (integer_value_t *) context.object_data;
    
    (*value) = atomic_uint32_read (this->value);
}

static void integer_set (p_context_t context,
    uint32_t value)
{
    integer_value_t *this = (integer_value_t *) context.object_data;
    
    atomic_uint32_set (this->value, value);
}

/* Main function. */

void integer_init (void)
{
    handle_t class;
    class_t integer_class;
    return_t return_value;
    integer_value_interfaces_t integer_value_interfaces;

    integer_value_repository_interface = interface_register ();
    integer_value_interfaces.integer = intger_interface_register ();

    integer_class = integer_value_class_register (integer_value_interfaces);

    class = integer_value$create (integer_class);
    global_namespace_bind ("/storm/classes/integer", class);
}

