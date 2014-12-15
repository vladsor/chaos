#include <enviroment.h>

#define MODULE_NAME "Repository"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>
#include <exception/macros.h>

handle_reference_t handle_create_static (p_handle_t handle)
{
#if defined (SECURITY_ENABLED)
    handle_create_security_check (handle);
#endif
    
    handle->is_static = TRUE;
    
    return handle_create_static_internal (handle);
}

void handle_destroy_static (handle_reference_t handle)
{
#if defined (SECURITY_ENABLED)
    handle_destroy_security_check (handle);
#endif
    
    handle_destroy_static_internal (handle);
}

void handle_clone_static (handle_reference_t handle, handle_reference_t new_handle)
{
#if defined (SECURITY_ENABLED)
    handle_clone_security_check (handle);
#endif
    
    new_handle->is_static = TRUE;
    
    handle_clone_static_internal (handle, new_handle);
}


