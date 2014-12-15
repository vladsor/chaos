#include <enviroment.h>

#define DEBUG_MODULE_NAME "Repository"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include "../Include/internal.h"

#include <debug/macros.h>
#include <exception/macros.h>

#ifdef REPOSITORY_NOT_INLINE

p_method_t method_create_static_internal (p_method_t method)
{
    reference_create_internal (&method->header, REFERENCE_TYPE_METHOD);

    return method;
}

void method_destroy_static_internal (p_method_t method)
{
    reference_destroy_internal (method);
}

p_method_t method_create_internal (
    p_method_description_t method_description,
    p_method_function_t method_function)
{
    p_method_t method;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p, %p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        method_description, method_function);
    
    memory_allocate ((void **) &method, sizeof (method_t));

    memory_allocate ((void **) &method->description, 
        sizeof (method_description_t));
    memory_copy (method->description, method_description, 
        sizeof (method_description_t));
    
    method->function = method_function;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s Method: %p, description: %p, function: %p\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        method, method->description, method->function);

    return method_create_static_internal (method);
}

void method_destroy_internal (p_method_t method)
{
    method_destroy_static_internal (method);
    
    memory_deallocate (method->description);
    memory_deallocate (method);
}

#if defined (METHOD_HISTORY_ENABLED)

#   define METHOD_HISTORY_DEPTH 100
method_t method_history[METHOD_HISTORY_DEPTH];
uint32_t method_index = 0;

#endif

p_method_t method_current = NULL;
p_method_t method_current_invoker = NULL;

void method_invoke_internal (p_method_t method, context_t context,
    sequence_t return_value, sequence_t parameters)
{
    p_method_t current;
    p_method_t current_invoker;
    uint32_t return_type;

#if defined (METHOD_HISTORY_ENABLED)
    if (method_index == METHOD_HISTORY_DEPTH - 1)
    {
        THROW_SYSTEM (EXCEPTION_INTERNAL);
    }
    
    method_history[method_index] = method;
    method_index++;
#endif

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p, %p, %p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        method, return_value.data, parameters.data);

    current = method_current;
    current_invoker = method_current_invoker;
    
    method_current_invoker = method_current;
    method_current = method;

    return_type = RETURN_TYPE_VOID;

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE, 
        L"%s: Description: %p, name: %S, type: %u, function: %p\n",
        DEBUG_MODULE_NAME,
        method->description, method->description->name,
        method->description->type, method->function);

    if (method->description->type == METHOD_TYPE_DYNAMIC)
    {
        method_invoke_lowlevel (method->function, context, return_type,
            return_value.data, parameters.data, parameters.count);
    }
    else if (method->description->type == METHOD_TYPE_STATIC)
    {
        method_invoke_static_lowlevel (method->function, return_type, 
            return_value.data, parameters.data, parameters.count);
    }
    
    method_current = current;
    method_current_invoker = current_invoker;

#if defined (METHOD_HISTORY_ENABLED)
    method_index--;
#endif
}

#endif /* REPOSITORY_NOT_INLINE */


