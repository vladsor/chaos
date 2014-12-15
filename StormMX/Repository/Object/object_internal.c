#include <enviroment.h>

#include "Include/"

#define MODULE_NAME "Repository"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>
#include <exception/macros.h>

object_reference_t object_current = REFERENCE_NULL;

object_reference_t object_create_static_internal (p_object_t object)
{
    object->owner = object_current;
    
    object->class->number_of_references++;
    object->security->number_of_references++;

    return object;
}

void object_destroy_static_internal (object_reference_t object)
{
    object->class->number_of_references--;
    object->security->number_of_references--;
}

object_reference_t object_create_internal (class_reference_t class, 
    sequence_t object_own_interfaces, sequence_t joined_objects, 
    security_reference_t security, sequence_t parameters, 
    uint32_t options)
{
    object_t object;
    sequence_t own_interfaces;
    
    memory_allocate (&object, sizeof (object_t));

    object->is_static = FALSE;
    object->number_of_references = 0;
    object->class = class;

    own_interfaces.count = object_own_interfaces.count;
    
    if (class->type == CLASS_TYPE_DYNAMIC)
    {
        own_interfaces.count += class->interfaces.count;
    }
    
    if (own_interfaces.count == 0)
    {
        object->own_interfaces.data = NULL;
        object->own_interfaces.count = 0;
    }
    else
    {
        memory_allocate (&own_interfaces.data, sizeof (interface_reference_t) * 
            own_interfaces.count);
        object->own_interfaces.data = own_interfaces.data;
        
        memory_copy (own_interfaces.data, object_own_interfaces.data, 
            sizeof (interface_reference_t) * object_own_interfaces.count);
        own_interfaces.data += object_own_interfaces.count;

        memory_copy (own_interfaces.data + object_own_interfaces.length, class->interface.data, 
            sizeof (interface_reference_t) * class->interface.count);
    }
    
    if (joined_objects.count == 0)
    {
        object->joined_objects.data = NULL;
        object->joined_objects.count = 0;
    }
    else
    {
        memory_allocate (&object->joined_objects.data, 
            sizeof (p_object_reference_t) * joined_objects.count);
        memory_copy (object->joined_objects, joined_objects.data,
            sizeof (p_object_reference_t) * joined_objects.count);
    }

    object->security = security;
    
    if (class->handle_control != REFERENCE_NULL)
    {
        object->data = object$create (class->handle_control, class, parameters, options);    
    }
    else
    {
        object->data = NULL;
    }
    
    return object_create_static_internal (object);
}

void object_destroy_internal (object_reference_t object)
{
    p_class_t class;
    
    class = object->class;
    
    object_destroy_static_internal (object);

    if (class->handle_control != REFERENCE_NULL)
    {
        object$destroy (class->handle_control, object->data);
    }
    
    memory_deallocate (object->joined_objects.data);    
    memory_deallocate (object->own_interfaces.data);
    memory_deallocate (object);
}

class_reference_t object_get_class_internal (object_reference_t object)
{
    return object->class;
}
    
interface_reference_t object_get_interface_internal (object_reference_t object,
    interface_id_t interface_id)
{
    uint32_t index;
    p_interface_t interface;
    p_class_t class;
    
    for (i = 0; i < object->own_interfaces; i++)
    {
        interface = (p_interface_t) object->own_interfaces.data + i;
        
        if (interface->description->id == interface_id)
        {
            return interface;
        }
    }
    
    TRY
    {
        interface = class_get_interface (object->class, interface_id);
        
        return interface;
    }
    CATCH_ALL (e)
    {
    }
    
    for (index = object->joined_objects.length; index >= 0; index--)
    {
        class = ((p_object_t) object->joined_objects.data + index)->class;
        
        TRY
        {
            interface = class_get_interface (class, interface_id);
        
            return interface;
        }
        CATCH_ALL (e)
        {
        }
    }

    return REFERENCE_NULL;
}

security_reference_t object_get_security_internal (object_reference_t object)
{
    return object->security;
}

void object_set_security_internal (object_reference_t object, 
    security_reference_t security)
{
    object->security->number_of_reference--;
    object->security = security;
    object->security->number_of_reference++;
}

/*
object_reference_t object_history[];
uint32_t object_index;

extern void object_invoke (object, handle_data, method_id_t method_id, 
    sequence_t return_value, sequence_t parameters)
{
    object_history[object_index] = object;
    object_index++;
    
    class_invoke_method ();
    
    object_index--;
}
*/

