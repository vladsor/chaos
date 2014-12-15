#include <enviroment.h>

#define DEBUG_MODULE_NAME "Repository"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>
#include <exception/macros.h>

#if defined (SECURITY_ENABLED)

void object_create_check_security (void)
{
    p_security_t security;

    security = (p_security_t) object_reference_current->security_reference;
    
    if (!security->is_absolute && !security->generic_acl.object_create)
    {
#   if defined (SECURITY_GENERATE_ACCESS_DENIED)
        THROW_SYSTEM (EXCEPTION_ACCESS_DENIED);
#   else
        THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
#   endif /* defined (SECURITY_GENERATE_ACCESS_DENIED) */
    }
}

void object_destroy_check_security (void)
{
    p_security_t security;

    security = (p_security_t) object_reference_current->security_reference;
    
    if (!security->is_absolute && !security->generic_acl.object_destroy)
    {
#   if defined (SECURITY_GENERATE_ACCESS_DENIED)
        THROW_SYSTEM (EXCEPTION_ACCESS_DENIED);
#   else
        THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
#   endif /* defined (SECURITY_GENERATE_ACCESS_DENIED) */
    }
}

#endif /* defined (SECURITY_ENABLED) */

