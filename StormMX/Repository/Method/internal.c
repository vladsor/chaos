#include <enviroment.h>

#include "Include/internal.h"
#include "Include/lowlevel.h"

#define MODULE_NAME "Repository"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>
#include <exception/macros.h>

method_reference_t method_create_static_internal (p_method_t method)
{
    method->owner = object_get_current ();

    return method;
}

void method_destroy_static_internal (method_reference_t method)
{
}

method_reference_t method_create_internal (
    p_method_description_t method_description)
{
    method_t method;
    
    memory_allocate (&method, sizeof (method_t));

    method->is_static = FALSE;
    method->number_of_references = 0;
    
    memory_allocate (&method->description, sizeof (method_description_t));
    memory_copy (method->description, method_description);

    return method_create_static_internal (method);
}

void method_destroy_internal (method_reference_t method)
{
    method_destroy_static_internal (method);
    
    memory_deallocate (method->description);
    memory_deallocate (method);
}

#if defined (METHOD_HISTORY_ENABLED)

#   define METHOD_HISTORY_DEPTH 100
method_reference_t method_history[METHOD_HISTORY_DEPTH];
uint32_t method_index = 0;

#else

method_reference_t method_current;
method_reference_t method_current_invoker;

#endif

void method_invoke_internal (method_reference_t method, context_t context,
    sequence_t return_value, sequence_t parameters)
{
#if defined (METHOD_HISTORY_ENABLED)
    if (method_index == METHOD_HISTORY_DEPTH - 1)
    {
        THROW_SYSTEM (EXCEPTION_INTERNAL);
    }
    
    method_history[method_index] = method;
    method_index++;
#else
    method_reference_t current;
    method_reference_t current_invoker;

    current = method_current;
    current_invoker = method_current_invoker;
    
    method_current_invoker = method_current;
    method_current = method;
#endif

    method_invoke_lowlevel (context, return_value.data, 
        parameters.data, parameters.count);
    
#if defined (METHOD_HISTORY_ENABLED)
    method_index--;
#else
    method_current = current;
    method_current_invoker = current_invoker;
#endif
}

void method_invoke_static_internal (method_reference_t method,
    sequence_t return_value, sequence_t parameters)
{
#if defined (METHOD_HISTORY_ENABLED)
    if (method_index == METHOD_HISTORY_DEPTH - 1)
    {
        THROW_SYSTEM (EXCEPTION_INTERNAL);
    }

    method_history[method_index] = method;
    method_index++;
#else
    method_reference_t current;
    method_reference_t current_invoker;

    current = method_current;
    current_invoker = method_current_invoker;
    
    method_current_invoker = method_current;
    method_current = method;
#endif

    method_invoke_static_lowlevel (return_value.data, parameters.data, 
        parameters.count);
    
#if defined (METHOD_HISTORY_ENABLED)
    method_index--;
#else
    method_current = current;
    method_current_invoker = current_invoker;
#endif
}

