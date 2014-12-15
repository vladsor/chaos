#include <enviroment.h>

#include "Include/internal.h"

#define MODULE_NAME "Repository"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>
#include <exception/macros.h>

interface_reference_t interface_current = REFERENCE_NULL;

interface_reference_t interface_create_static_internal (p_interface_t interface)
{
    interface->owner = object_current;
    
    return class;
}

void interface_destroy_static_internal (interface_reference_t interface)
{
}

interface_reference_t interface_create_internal (
    p_interface_description_t interface_description, 
    sequence_t interface_methods)
{
    interface_t interface;
    
    memory_allocate (&interface, sizeof (interface_t));

    interface->is_static = FALSE;
    interface->number_of_references = 0;

//  TODO: move next to interface_description.c
    memory_allocate (&interface->description, 
        sizeof (interface_description_t));
    memory_copy (interface->description, interface_description,
        sizeof (interface_description_t));
    
    interface->methods.count = interface_methods.count;
    memory_allocate (&interface->methods.data, 
        sizeof (method_function_t) * interface_methods.count);
    memory_copy (interface->methods.data, interface_methods.data,
        sizeof (method_function_t) * interface_methods.count);
    
    return interface_create_static_internal (interface);
}

void interface_destroy_internal (interface_reference_t interface)
{
    interface_destroy_static_internal (interface);
    
    memory_deallocate (interface->methods.data);
    memory_deallocate (interface->description);
    memory_deallocate (interface);
}

/*
interface_reference_t interface_history[];
uint32_t interface_index;

extern void interface_invoke (interface, object_data, handle_data, method_id_t method_id, 
    sequence_t return_value, sequence_t parameters)
{
    interface_history[interface_index] = interface;
    interface_index++;
    
    method_invoke ();
    
    interface_index--;
}
*/

