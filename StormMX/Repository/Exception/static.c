#include <enviroment.h>

#define MODULE_NAME "Repository"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>
#include <exception/macros.h>

exception_reference_t interface_create_static (p_exception_t exception)
{
    exception_reference_t exception_reference;
    
#if defined (SECURITY_ENABLED)
    exception_create_security_check ();
#endif
    
    exception->is_static = TRUE;
    
    exception_reference = exception_create_static_internal (exception);
    
#if defined (REPOSITORY_EXTERNAL)
    pool_of_integers_allocate (exception_ids_pool, &exception->id);
    hash_table_add_element (exceptions_table, (p_hash_element_t) exception);
#endif

#if defined (TRANSACTION_ENABLED)
    if (transaction_current != NULL)
    {
        exception_reference->transaction = transaction_current;

        exception_reference->transaction_slot_index = transaction_add_slot (
            transaction_current, exception_reference, 
            OPERATION_EXCEPTION_CREATE_STATIC);
    }
#ndif

    return exception_reference;    
}

void exception_destroy_static (exception_reference_t exception)
{
#if defined (SECURITY_ENABLED)
    exception_destroy_security_check (exception);
#endif

#if defined (TRANSACTION_ENABLED)
    if ((exception->transaction != NULL) && 
        (exception->transaction != transaction_current))
    {
        THROW_SYSTEM (EXCEPTION_IS_LOCKED);
    }
    
    if (transaction_current != NULL)
    {
        if (exception->transaction == NULL)
        {
#   if defined (REPOSITORY_EXTERNAL)
            hash_table_delete_element (exceptions_table, 
                (p_hash_element_t) exception);
#   endif
            transaction_add_slot (transaction_current, exception,
                OPERATION_EXCEPTION_DESTROY_STATIC);
            return;
        }
        
        transaction_clear_slot (exception->transaction, exception->transaction_slot_index);
    }
#endif

#if defined (REPOSITORY_EXTERNAL)
    hash_table_delete_element (exceptions_table, (p_hash_element_t) exception);
    pool_of_integers_deallocate (exception_ids_pool, exception->id);
#endif
    
    exception_destroy_static_internal (exception);
}


