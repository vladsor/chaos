#include <enviroment.h>

#define MODULE_NAME "Repository"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>
#include <exception/macros.h>


#if defined (SECURITY_ENABLED)

void class_create_check_security (void)
{
    p_security_t security;

    security = (p_security_t) security_current;
    
    if (security->is_absolute)
    {
        return;
    }
    
    if (security->generic_acl.class_create)
    {
        return;
    }

#   if defined (SECURITY_GENERATE_ACCESS_DENIED)
    THROW_SYSTEM (EXCEPTION_ACCESS_DENIED);
#   else
    THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
#   endif /* defined (SECURITY_GENERATE_ACCESS_DENIED) */
}

void class_destroy_check_security (class_reference_t class)
{
    p_security_t security;
    uint32_t index;
    p_class_acl_t class_acl;

    security = current_security;
    
    if (security->is_absolute)
    {
        return;
    }
    
    if (object_current == class->owner)
    {
        return;
    }
    
    if (!security->generic_acl.class_destroy)
    {
#   if defined (SECURITY_GENERATE_ACCESS_DENIED)
        THROW_SYSTEM (EXCEPTION_ACCESS_DENIED);
#   else
        THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
#   endif /* defined (SECURITY_GENERATE_ACCESS_DENIED) */
    }

    for (index = 0; index < security->class_acls.count; index++)
    {
        class_acl = (p_class_acl_t) class_acls.data + index;
        
        if (class_acl.reference == class)
        {
            if (class_acl.destroy)
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

void class_set_interfaces_check_security (class_reference_t class)
{
    p_security_t security;

    security = (p_security_t) object_reference_current->security_reference;
    
    if (!security->is_absolute && !security->generic_acl.class_set_interfaces)
    {
#   if defined (SECURITY_GENERATE_ACCESS_DENIED)
        THROW_SYSTEM (EXCEPTION_ACCESS_DENIED);
#   else
        THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
#   endif /* defined (SECURITY_GENERATE_ACCESS_DENIED) */
    }
}

void class_get_interfaces_check_security (class_reference_t class)
{
    p_security_t security;

    security = (p_security_t) object_reference_current->security_reference;
    
    if (!security->is_absolute && !security->generic_acl.class_get_interfaces)
    {
#   if defined (SECURITY_GENERATE_ACCESS_DENIED)
        THROW_SYSTEM (EXCEPTION_ACCESS_DENIED);
#   else
        THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
#   endif /* defined (SECURITY_GENERATE_ACCESS_DENIED) */
    }
}

void class_get_interface_check_security (class_reference_t class)
{
    p_security_t security;

    security = (p_security_t) object_reference_current->security_reference;
    
    if (!security->is_absolute && !security->generic_acl.class_get_interface)
    {
#   if defined (SECURITY_GENERATE_ACCESS_DENIED)
        THROW_SYSTEM (EXCEPTION_ACCESS_DENIED);
#   else
        THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
#   endif /* defined (SECURITY_GENERATE_ACCESS_DENIED) */
    }
}

#endif /* defined (SECURITY_ENABLED) */

