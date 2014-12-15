#include <enviroment.h>

#define DEBUG_MODULE_NAME "Repository"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include <debug/macros.h>
#include <exception/macros.h>

#include "../Include/internal.h"

handle_reference_t handle_create (object_reference_t object_reference, 
    interface_id_t interface_id, sequence_t parameters, uint32_t options)
{
    p_object_t object;
    p_handle_t handle;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p, %u, %p, %u)\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        object_reference, interface_id, parameters.data, options);
    
#if defined (SECURITY_ENABLED)
    handle_create_security_check ();
#endif

    object = object_translate_reference (object_reference);

#if defined (CHECK_PARAMETERS)
    handle_create_check_parameters (object, interface_id, parameters, options);
#endif
    
    handle = handle_create_internal (object, interface_id, parameters, 
        options);
    
    handle->header.is_static = FALSE;    

    return (handle_reference_t) handle;    
}

void handle_destroy (handle_reference_t handle_reference)
{
    p_handle_t handle;

#if defined (SECURITY_ENABLED)
    handle_destroy_security_check (handle);
#endif

    handle = handle_translate_reference (handle_reference);

#if defined (CHECK_PARAMETERS)
    handle_destroy_check_parameters (handle);
#endif

    handle_destroy_internal (handle);
}

handle_reference_t handle_clone (handle_reference_t handle_reference, 
    uint32_t options)
{
    p_handle_t handle;
    p_handle_t new_handle;

#if defined (SECURITY_ENABLED)
    handle_clone_security_check (handle);
#endif

    handle = handle_translate_reference (handle_reference);
    
#if defined (CHECK_PARAMETERS)
    handle_clone_check_parameters (handle, options);
#endif
    
    new_handle = handle_clone_internal (handle, options);
    
    new_handle->header.is_static = FALSE;    

    return (handle_reference_t) new_handle;    
}

void handle_invoke_method (handle_reference_t handle_reference, 
    method_id_t method_id, 
    computer_reference_t computer,
    sequence_t parameters_in, sequence_t parameters_inout, 
    sequence_t parameters_out,
    uint32_t options UNUSED)
{
    p_handle_t handle;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p, %u, %p, {%p, %u}, {%p, %u}, {%p, %u})\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        handle_reference, method_id, computer, 
        parameters_in.data, parameters_in.count,
        parameters_inout.data, parameters_inout.count,
        parameters_out.data, parameters_out.count);

#if defined (SECURITY_ENABLED)
    handle_invoke_method_security_check (handle);
#endif

    handle = handle_translate_reference (handle_reference);
    
#if defined (CHECK_PARAMETERS)
    handle_invoke_method_check_parameters (handle, method_id, return_value, 
        parameters);
#endif
    
    handle_invoke_method_internal (handle, method_id, computer, 
        REFERENCE_NULL, REFERENCE_NULL, parameters_in, parameters_inout,
        parameters_out);
}


