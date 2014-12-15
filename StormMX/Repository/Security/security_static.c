#include <enviroment.h>

#define MODULE_NAME "Repository"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>
#include <exception/macros.h>

security_reference_t interface_create_static (p_security_t security)
{
#if defined (SECURITY_ENABLED)
    security_create_security_check ();
#endif
    
    security->is_static = TRUE;
    
    return security_create_static_internal (security);
}

void security_destroy_static (security_reference_t security)
{
#if defined (SECURITY_ENABLED)
    security_destroy_security_check ();
#endif
    
    security_destroy_static_internal (security);
}


