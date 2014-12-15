#include <enviroment.h>

#define MODULE_NAME "Repository"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>
#include <exception/macros.h>

handle_reference_t handle_create (
    p_handle_description_t handle_description, 
    sequence_t handle_methods)
{
#if defined (SECURITY_ENABLED)
    handle_create_security_check ();
#endif

#if defined (CHECK_PARAMETERS)
    handle_create_check_parameters (handle_description, 
        handle_methods);
#endif
    
    return handle_create_internal (handle_description, 
        handle_methods);
}

void handle_destroy (handle_reference_t handle)
{
#if defined (SECURITY_ENABLED)
    handle_destroy_security_check ();
#endif
    
#if defined (CHECK_PARAMETERS)
    handle_destroy_check_parameters (handle);
#endif
    
    handle_destroy_internal (handle);
}

handle_reference_t handle_clone (handle_reference_t handle, 
    uint32_t options)
{
#if defined (SECURITY_ENABLED)
    handle_clone_security_check ();
#endif
    
#if defined (CHECK_PARAMETERS)
    handle_clone_check_parameters (handle, options);
#endif
    
    return handle_clone_internal (handle, options);
}

void handle_invoke_method (handle_t handle, method_id_t method_id, 
    sequence_t return_value, sequence_t parameters)
{
#if defined (SECURITY_ENABLED)
    handle_invoke_method_security_check ();
#endif
    
#if defined (CHECK_PARAMETERS)
    handle_invoke_method_check_parameters (handle, method_id, return_value, 
        parameters);
#endif
    
    handle_invoke_method_internal (handle, method_id, return_value, parameters);
}

