#include <enviroment.h>

#define DEBUG_MODULE_NAME "Repository"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include "../Include/internal.h"

#include <debug/macros.h>
#include <exception/macros.h>


p_security_t security_create_static_internal (p_security_t security)
{
    p_security_t security_reference;
    
    security_reference = (p_security_t) reference_create_internal (
        (p_reference_struct_t) security, REFERENCE_TYPE_SECURITY);
    
    return security_reference;
}

void security_destroy_static_internal (p_security_t security)
{
    reference_destroy_internal ((reference_t) security);
}

p_security_t security_create_internal (bool security_is_absolute, 
    p_generic_acl_t generic_acl)
{
    p_security_t security;
    
    memory_allocate ((void **) &security, sizeof (security_t));
    security->is_absolute = security_is_absolute;

    memory_allocate ((void **) &security->generic_acl, sizeof (generic_acl_t));
    memory_copy (security->generic_acl, generic_acl, sizeof (generic_acl_t));

    return security_create_static_internal (security);
}

void security_destroy_internal (p_security_t security)
{
    security_destroy_static_internal (security);

    memory_deallocate (security->generic_acl);
    memory_deallocate (security);
}

security_t security_absolute =
{
    header: 
    {
        node: LIST_NODE_INIT,  
        type: REFERENCE_TYPE_SECURITY,    
        magic_number: REFERENCE_MAGIC_NUMBER_SECURITY,
        owner: NULL,
        number_of_references: ATOMIC_UINT32_INIT (0),
        lock: SPIN_INIT,
        is_static: TRUE,
    },
    is_absolute: TRUE,
    generic_acl: NULL,
    exception_acls: { data: NULL, count: 0 },
    method_acls: { data: NULL, count: 0 },
    interface_acls: { data: NULL, count: 0 },
    class_acls: { data: NULL, count: 0 },
    object_acls: { data: NULL, count: 0 },
    handle_acls: { data: NULL, count: 0 },
    user_acls: { data: NULL, count: 0 },
};

