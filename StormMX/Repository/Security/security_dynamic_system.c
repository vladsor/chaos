#include <enviroment.h>

#define MODULE_NAME "Repository"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>
#include <exception/macros.h>

security_reference_t security_create (bool security_is_absolute, 
    p_generic_acl_t generic_acl)
{
#if defined (SECURITY_ENABLED)
    security_create_security_check ();
#endif

#if defined (CHECK_PARAMETERS)
    security_create_check_parameters (security_is_absolute, generic_acl);
#endif
    
    return security_create_internal (security_is_absolute, generic_acl);
}

void security_destroy (security_reference_t security)
{
#if defined (SECURITY_ENABLED)
    security_destroy_security_check ();
#endif
    
#if defined (CHECK_PARAMETERS)
    security_destroy_check_parameters (security);
#endif
    
    security_destroy_internal (security);
}

