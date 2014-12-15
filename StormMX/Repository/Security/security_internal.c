#include <enviroment.h>

#define MODULE_NAME "Repository"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>
#include <exception/macros.h>

security_reference_t security_translate_reference (security_reference_t security)
{
    switch (security)    
    {
        case SECURITY_THIS:
        {
            return object_current->security;
        }
        
        case SECURITY_ABSOLUTE:
        {
            return &security_absolute;
        }
    };
    
    return security;
}


security_reference_t security_create_static_internal (p_security_t security)
{
#if defined (REPOSITORY_EXTERNAL)
    pool_of_integers_allocate (security_ids_pool, &security->id);
    hash_table_add_element (securities_table, (p_hash_element_t) security);
#endif
    return security;
}

void security_destroy_static_internal (security_reference_t security)
{
#if defined (REPOSITORY_EXTERNAL)
    hash_table_delete_element (securities_table, (p_hash_element_t) security);
    pool_of_integers_deallocate (class_ids_pool, security->id);
#endif
}

security_reference_t security_create_internal (bool security_is_absolute, 
    p_generic_acl_t generic_acl)
{
    security_t security;
    
    memory_allocate (&security, sizeof (security_t));

    security->is_static = FALSE;
    security->number_of_references = 0;
    
    security->is_absolute = security_is_absolute;
    security->generic_acl = generic_acl;

    return security_create_static_internal (security);
}

void security_destroy_internal (security_reference_t security)
{
    security_destroy_static_internal (security);

    memory_deallocate (security);
}

