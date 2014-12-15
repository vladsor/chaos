#include <enviroment.h>

#define DEBUG_MODULE_NAME "Repository"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include "../Include/internal.h"

#include <debug/macros.h>
#include <exception/macros.h>

security_reference_t security_create (bool security_is_absolute, 
    p_generic_acl_t generic_acl)
{
    p_security_t security;

#if defined (SECURITY_ENABLED)
    security_create_security_check ();
#endif

#if defined (CHECK_PARAMETERS)
    security_create_check_parameters (security_is_absolute, generic_acl);
#endif
    
    security = security_create_internal (security_is_absolute, generic_acl);

    security->header.is_static = FALSE;

    return (security_reference_t) security;
}

void security_destroy (security_reference_t security_reference)
{
    p_security_t security;
    
#if defined (SECURITY_ENABLED)
    security_destroy_security_check ();
#endif

    security = security_translate_reference (security_reference);
    
#if defined (CHECK_PARAMETERS)
    security_destroy_check_parameters (security);
#endif
    
    security_destroy_internal (security);
}

security_reference_t security_get_current (void)
{
    return SECURITY_CURRENT;
}    
