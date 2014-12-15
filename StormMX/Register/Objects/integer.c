#include <enviroment.h>

#include <Classes/integer.h>

#include "../objects.h"

//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

static return_t integer_create (context_t *context, 
    void *parameter)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p, %p)\n",
        __FILE__, __FUNCTION__, context, parameter);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s Parameter: %u\n",
        __FILE__, __FUNCTION__, (*(uint32_t *) parameter));

    memory_allocate ((void **) &context->object_data, sizeof (uint32_t));
    (*((uint32_t *) context->object_data)) = (*(uint32_t *) parameter);
    
    return 0;
}

object_create_method_t integer_create_method =
{
    &integer_create,
    MID_OBJECT_CREATE,
    sizeof (void *),
    1,
    {
        {sizeof (void *)}
    }
};

static return_t integer_destroy (context_t *context)
{
    memory_deallocate (context->object_data);
    
    return 0;
}

object_destroy_method_t integer_destroy_method =
{
    &integer_destroy,
    MID_OBJECT_DESTROY,
    0,
    0,
};

static method_t *control_methods[] = 
{
    (method_t *) &integer_create_method,
    (method_t *) &integer_destroy_method,
};

#define number_of_control_methods 2

static return_t integer_get (
    context_t *context,
    uint32_t *value)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p, %p)\n",
        __FILE__, __FUNCTION__, context, value);
        
    (*value) = (*((uint32_t *) context->object_data));

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s Value = %u\n",
        __FILE__, __FUNCTION__, (*value));
    
    return 0;
}

static return_t integer_set (
    context_t *context,
    uint32_t value)
{
    (*((uint32_t *) context->object_data)) = value;

    return 0;
}

static integer_get_method_t integer_get_method =
{
    INTEGER_GET_METHOD (integer_get)
};

static integer_set_method_t integer_set_method =
{
    INTEGER_SET_METHOD (integer_set)
};

static method_t *methods[] = 
{
    (method_t *) &integer_get_method,
    (method_t *) &integer_set_method,
};

#define number_of_methods 2

static interface_id_t integer_control_id;
static interface_id_t integer_interface_id;
class_id_t integer_class_id;
static handle_t class;

/* Main function. */

return_t integer_init (void)
{
    return_t return_value;

    return_value = register_interface_register (&integer_control_id, 
        IID_INTEGER_CONTROL, INTERFACE_TYPE_CONTROL, number_of_control_methods, 
        control_methods, NULL);

    register_interface_register (&integer_interface_id, IID_INTEGER, 
        INTERFACE_TYPE_DYNAMIC, number_of_methods, methods, NULL);

    register_class_register (&integer_class_id, CID_INTEGER, CLASS_TYPE_DYNAMIC,
        1, &integer_interface_id, integer_control_id);

    register_object_create (&class, integer_class_id, &integer_class_id);
    global_namespace_bind ("/storm/classes/integer", &class);

    return 0;
}
