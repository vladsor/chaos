#include <enviroment.h>

#include "Include/security_check.h"

#define MODULE_NAME "Repository"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>
#include <exception/macros.h>

#if defined (SECURITY_ENABLED)

void interface_create_check_security (void)
{
    p_security_t security;

    security = current_security;
    
    if (security->is_absolute)
    {
        return;
    } 
    
    if (security->generic_acl.interface_create)
    {
        return;
    }

#   if defined (SECURITY_GENERATE_ACCESS_DENIED)
    THROW_SYSTEM (EXCEPTION_ACCESS_DENIED);
#   else
    THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
#   endif /* defined (SECURITY_GENERATE_ACCESS_DENIED) */
}

void interface_destroy_check_security (interface_reference_t interface)
{
    p_security_t security;
    uint32_t index;
    p_interface_acl_t interface_acl;

    security = current_security;
    
    if (security->is_absolute)
    {
        return;
    }
    
    if (object_current == interface->owner)
    {
        return;
    }
    
    if (!security->generic_acl.interface_destroy)
    {
#   if defined (SECURITY_GENERATE_ACCESS_DENIED)
        THROW_SYSTEM (EXCEPTION_ACCESS_DENIED);
#   else
        THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
#   endif /* defined (SECURITY_GENERATE_ACCESS_DENIED) */
    }

    for (index = 0; index < security->interface_acls.count; index++)
    {
        interface_acl = (p_interface_acl_t) interface_acls.data + index;
        
        if (interface_acl.reference == interface)
        {
            if (interface_acl.destroy)
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

