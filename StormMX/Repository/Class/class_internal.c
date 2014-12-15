#include <enviroment.h>

#include "Include/internal.h"

#define MODULE_NAME "Repository"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>
#include <exception/macros.h>

class_reference_t class_current = REFERENCE_NULL;

class_reference_t class_create_static_internal (p_class_t class)
{
    uint32_t index;
    p_interface_t interface;

    class->owner = object_current;

    for (index = 0; index < class->interfaces.count; index++)
    {
        interface = ((p_interface_t) class->interfaces.data) + index;
        
        interface->number_of_references++;
    }

    return class;
}

void class_destroy_static_internal (class_reference_t class)
{
    uint32_t index;
    p_interface_t interface;

    for (index = 0; index < class->interfaces.count; index++)
    {
        interface = ((p_interface_t) class->interfaces.data) + index;
        
        interface->number_of_references--;
    }
}

class_reference_t class_create_internal (p_class_description_t class_description,
    sequence_t class_interfaces, object_reference_t class_repository)
{
    class_t class;
    
    memory_allocate (&class, sizeof (class_t));

    class->is_static = FALSE;
    class->number_of_references = 0;
    
    memory_allocate (&class->description, sizeof (class_description_t));
    memory_copy (class->description, class_description, 
        sizeof (class_description_t));

    class->interfaces.count = class_interfaces.count;
    memory_allocate (&class->interfaces.data, sizeof (interface_reference_t) *
        class_interfaces.count);
    memory_copy (class->interfaces.data, class_interfaces.data, 
        sizeof (interface_reference_t) * class_interfaces.count);

    class->repository = repository;
    
    class->object_control = REFERENCE_NULL;
    class->handle_control = REFERENCE_NULL;
    class->quality_control = REFERENCE_NULL;
    class->transaction_control = REFERENCE_NULL;
    
    return class_create_static_internal (class);
}

void class_destroy_internal (class_reference_t class)
{
    class_destroy_static_internal (class);
    
    memory_deallocate (class->interfaces.data);
    memory_deallocate (class->description);
    memory_deallocate (class);
}

void class_set_interfaces_internal (class_reference_t class, 
    sequence_t class_interfaces)
{
    p_class_t class;
    uint32_t i;
    p_interface_t interface;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p, {%p, %u})\n",
        __FILE__, __FUNCTION__, class,
        class_interfaces.data, class_interfaces.length);

    for (i = 0; i < class->interfaces.length; i++)
    {
        interface = ((p_interface_t) class->interfaces.data) + i;
        
        interface->number_of_references--;
    }

    class->interfaces = class_interfaces;

    for (i = 0; i < class_interfaces.length; i++)
    {
        interface = ((p_interface_t) class_interfaces.data) + i;
            
        interface->number_of_references++;
    }
}

sequence_t class_get_interfaces_internal (class_reference_t class)
{
    return class->interfaces;
}

interface_reference_t class_get_interface_internal (class_reference_t class, 
    interface_id_t interface_id)
{
    uint32_t index;
    p_interface_t interface;

    for (index = 0; index < class->interfaces.length; index++)
    {
        interface = (p_interface_t) class->interfaces.data + index;
        
        if (interface->id == interface_id)
        {
            return (interface_reference_t) interface;
        }
    }
    
    return REFERENCE_NULL;
}

/*
class_reference_t class_history[];
uint32_t class_index;

extern void class_invoke (class, context, interface_id_t interface, method_id_t method_id, 
    sequence_t return_value, sequence_t parameters)
{
    class_history[class_index] = class;
    class_index++;
    
    interface_invoke_method ();
    
    class_index--;
}
*/

