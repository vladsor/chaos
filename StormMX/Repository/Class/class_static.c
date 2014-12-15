#include <enviroment.h>

#define MODULE_NAME "Repository"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>
#include <exception/macros.h>

class_reference_t class_create_static (p_class_t class)
{
    class_reference_t class_reference;
    
#if defined (SECURITY_ENABLED)
    class_create_security_check ();
#endif
    
    class->is_static = TRUE;

    class_reference = class_create_static_internal (class);
    
#if defined (REPOSITORY_EXTERNAL)
    pool_of_integers_allocate (class_ids_pool, &class->id);
    hash_table_add_element (classes_table, (p_hash_element_t) class);
#endif

#if defined (TRANSACTION_ENABLED)
    if (transaction_current != NULL)
    {
        class->transaction = transaction_current;

        class->transaction_slot_index = transaction_add_slot (
            transaction_current, class_reference, 
            OPERATION_CLASS_CREATE_STATIC);
    }
#ndif

    return class_reference;    
}

void class_destroy_static (class_reference_t class)
{
#if defined (SECURITY_ENABLED)
    class_destroy_security_check (class);
#endif

#if defined (TRANSACTION_ENABLED)
    if ((class->transaction != NULL) && 
        (class->transaction != transaction_current))
    {
        THROW_SYSTEM (EXCEPTION_IS_LOCKED);
    }
    
    if (transaction_current != NULL)
    {
        if (class->transaction == NULL)
        {
#   if defined (REPOSITORY_EXTERNAL)
            hash_table_delete_element (classs_table, 
                (p_hash_element_t) class);
#   endif
            transaction_add_slot (transaction_current, class,
                OPERATION_CLASS_DESTROY_STATIC);
            return;
        }
        
        transaction_clear_slot (class->transaction, 
            class->transaction_slot_index);
    }
#endif

#if defined (REPOSITORY_EXTERNAL)
    hash_table_delete_element (classes_table, (p_hash_element_t) class);
    pool_of_integers_deallocate (class_ids_pool, class->id);
#endif
    
    class_destroy_static_internal (class);
}

