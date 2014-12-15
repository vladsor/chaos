#include <enviroment.h>

#define MODULE_NAME "Repository"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>
#include <exception/macros.h>

object_reference_t interface_create_static (p_object_t object)
{
    object_reference_t object_reference;
    
#if defined (SECURITY_ENABLED)
    object_create_security_check ();
#endif
    
    object->is_static = TRUE;
    
    object_reference = object_create_static_internal (object);
    
#if defined (REPOSITORY_EXTERNAL)
    pool_of_integers_allocate (object_ids_pool, &object->id);
    hash_table_add_element (objectes_table, (p_hash_element_t) object);
#endif

#if defined (TRANSACTION_ENABLED)
    if (transaction_current != NULL)
    {
        object_reference->transaction = transaction_current;

        object_reference->transaction_slot_index = transaction_add_slot (
            transaction_current, object_reference, 
            OPERATION_OBJECT_CREATE_STATIC);
    }
#ndif

    return object_reference;    
}

void object_destroy_static (object_reference_t object)
{
#if defined (SECURITY_ENABLED)
    object_destroy_security_check ();
#endif

#if defined (TRANSACTION_ENABLED)
    if (object->transaction != NULL && object->transaction != transaction_current)
    {
        THROW_SYSTEM (EXCEPTION_IS_LOCKED);
    }
    
    if (transaction_current != NULL)
    {
        if (transaction_current != object_reference->transaction)
        {
#   if defined (REPOSITORY_EXTERNAL)
            hash_table_delete_element (objectes_table, 
                (p_hash_element_t) object);
#   endif
            transaction_add_slot (transaction_current, object,
                OPERATION_OBJECT_DESTROY_STATIC);
            return;
        }
        
        transaction_clear_slot (object->transaction, object->transaction_slot_index);
    }
#endif

#if defined (REPOSITORY_EXTERNAL)
    hash_table_delete_element (objectes_table, (p_hash_element_t) object);
    pool_of_integers_deallocate (class_ids_pool, object->id);
#endif
    
    object_destroy_static_internal (object);
}


