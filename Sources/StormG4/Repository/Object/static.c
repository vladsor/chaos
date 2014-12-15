#include <enviroment.h>

#if defined (REPOSITORY_EXTERNAL)
#	include "Include/repository_external.h"
#endif

#define MODULE_NAME "Repository"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>
#include <exception/macros.h>

#include "../Include/internal.h"

object_reference_t object_create_static (p_object_t object,
    sequence_t parameters, uint32_t options)
{
    p_object_t object_reference;
    
#if defined (SECURITY_ENABLED)
    object_create_security_check ();
#endif
    
    object_reference = object_create_static_internal (object, parameters, 
        options);

    object->header.is_static = TRUE;
    
#if defined (REPOSITORY_EXTERNAL)
    pool_of_integers_allocate (object_ids_pool, &object->id);
    hash_table_add_element (objects_table, (p_hash_element_t) object);
#endif

#if defined (TRANSACTION_ENABLED)
    if (transaction_current != NULL)
    {
        object_reference->transaction = transaction_current;

        object_reference->transaction_slot_index = transaction_add_slot (
            transaction_current, object_reference, 
            OPERATION_OBJECT_CREATE_STATIC);
    }
#endif

    return (object_reference_t) object_reference;    
}

void object_destroy_static (object_reference_t object_reference)
{
    p_object_t object = (p_object_t) object_reference;

#if defined (SECURITY_ENABLED)
    object_destroy_security_check (object);
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
            hash_table_delete_element (objects_table, 
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
    hash_table_delete_element (objects_table, (p_hash_element_t) object);
    pool_of_integers_deallocate (object_ids_pool, object->id);
#endif
    
    object_destroy_static_internal (object);
}


