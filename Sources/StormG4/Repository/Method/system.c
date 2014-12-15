#include <enviroment.h>

#define DEBUG_MODULE_NAME "Repository"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include "../Include/internal.h"

#include <debug/macros.h>
#include <exception/macros.h>

method_reference_t method_create (
    description_reference_t method_description, 
    computer_reference_t method_computer,
    memory_reference_t method_memory,
    p_method_function_t method_function, uint64_t method_data,
    uint32_t options)
{
    p_method_t method;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p, %p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        method_description, method_function);

#if defined (SECURITY_ENABLED)
    method_create_security_check ();
#endif

#if defined (CHECK_PARAMETERS)
    method_create_check_parameters (method_description);
#endif
    
    method = method_create_internal (method_description, method_computer, 
        method_memory, method_function, method_data, options);

    method->header.is_static = FALSE;
    
    return (method_reference_t) method;
}

void method_destroy (method_reference_t method_reference)
{
    p_method_t method;

#if defined (SECURITY_ENABLED)
    method_destroy_security_check (method);
#endif
    
    method = method_translate_reference (method_reference);
    
#if defined (CHECK_PARAMETERS)
    method_destroy_check_parameters (method);
#endif

    method_destroy_internal (method);
}

void method_invoke (method_reference_t method_reference, 
    computer_reference_t computer, 
    sequence_t parameters_in, sequence_t parameters_inout, 
    sequence_t parameters_out, 
    uint32_t options UNUSED)
{
    p_method_t method;
    context_t context = {0,0};

#if defined (SECURITY_ENABLED)
    method_invoke_security_check (method);
#endif
    
#if defined (CHECK_PARAMETERS)
    method_invoke_check_parameters (method, context, return_value, parameters);
#endif

    method = method_translate_reference (method_reference);

    method_invoke_internal (method, NULL, NULL, NULL, NULL,
        computer, context, 
        REFERENCE_NULL, REFERENCE_NULL, 
        parameters_in, parameters_inout, parameters_out);
}

