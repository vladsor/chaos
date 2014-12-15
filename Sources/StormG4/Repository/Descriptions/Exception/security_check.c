#include <enviroment.h>

#define MODULE_NAME "Repository"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>
#include <exception/macros.h>

#if defined (SECURITY_ENABLED)

void exception_create_check_security (void)
{
    p_security_t security;

    security = current_security;
    
    if (security->is_absolute)
    {
        return;
    } 
    
    if (security->generic_acl.exception_create)
    {
        return;
    }

#   if defined (SECURITY_GENERATE_ACCESS_DENIED)
    THROW_SYSTEM (EXCEPTION_ACCESS_DENIED);
#   else
    THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
#   endif /* defined (SECURITY_GENERATE_ACCESS_DENIED) */
}

void exception_destroy_check_security (exception_reference_t exception)
{
    p_security_t security;
    uint32_t index;
    p_exception_acl_t exception_acl;

    security = current_security;
    
    if (security->is_absolute)
    {
        return;
    }
    
    if (object_current == exception->owner)
    {
        return;
    }
    
    if (!security->generic_acl.exception_destroy)
    {
#   if defined (SECURITY_GENERATE_ACCESS_DENIED)
        THROW_SYSTEM (EXCEPTION_ACCESS_DENIED);
#   else
        THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
#   endif /* defined (SECURITY_GENERATE_ACCESS_DENIED) */
    }

    for (index = 0; index < security->exception_acls.count; index++)
    {
        exception_acl = (p_exception_acl_t) exception_acls.data + index;
        
        if (exception_acl.reference == exception)
        {
            if (exception_acl.destroy)
            {
                return;
            }
            
#   if defined (SECURITY_GENERATE_ACCESS_DENIED)
            THROW_SYSTEM (EXCEPTION_ACCESS_DENIED);
#   else
            THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
#   endif /* defined (SECURITY_GENERATE_ACCESS_DENIED) */
        }
    }
    
#   if defined (SECURITY_GENERATE_ACCESS_DENIED)
    THROW_SYSTEM (EXCEPTION_ACCESS_DENIED);
#   else
    THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
#   endif /* defined (SECURITY_GENERATE_ACCESS_DENIED) */
}

#endif /* defined (SECURITY_ENABLED) */

