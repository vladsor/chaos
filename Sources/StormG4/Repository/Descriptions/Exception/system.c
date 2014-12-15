#include <enviroment.h>

#include "Include/internal.h"

#if defined (REPOSITORY_EXTERNAL)
#	include "Include/repository_external.h"
#endif

#define MODULE_NAME "Repository"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>
#include <exception/macros.h>

exception_reference_t exception_create (p_exception_description_t exception_description)
{
    p_exception_t exception;

#if defined (SECURITY_ENABLED)
    exception_create_security_check ();
#endif

#if defined (CHECK_PARAMETERS)
    exception_create_check_parameters (exception_description);
#endif
    
    exception = exception_create_internal (exception_description);

#if defined (REPOSITORY_EXTERNAL)
    pool_of_integers_allocate (exception_ids_pool, &exception->id);
    hash_table_add_element (exceptions_table, (p_hash_element_t) exception);
#endif

#if defined (TRANSACTION_ENABLED)
    if (transaction_current != NULL)
    {
        exception->transaction = transaction_current;

        exception->transaction_slot_index = transaction_add_slot (
            transaction_current, exception, OPERATION_EXCEPTION_CREATE);
    }
#endif

    return (exception_reference_t) exception;
}

void exception_destroy (exception_reference_t exception_reference)
{
    p_exception_t exception = (p_exception_t) exception_reference;

#if defined (SECURITY_ENABLED)
    exception_destroy_security_check (exception);
#endif
    
#if defined (CHECK_PARAMETERS)
    exception_destroy_check_parameters (exception);
#endif

#if defined (TRANSACTION_ENABLED)
    if (exception->transaction != NULL && exception->transaction != transaction_current)
    {
        THROW_SYSTEM (EXCEPTION_IS_LOCKED);
    }

    if (transaction_current != NULL)
    {
        if (transaction_current != exception->transaction)
        {
#   if defined (REPOSITORY_EXTERNAL)
            hash_table_delete_element (exceptiones_table, 
                (p_hash_element_t) exception);
#   endif
            transaction_add_slot (transaction_current, exception,
                OPERATION_EXCEPTION_DESTROY);
            return;
        }
        
        transaction_clear_slot (exception->transaction, exception->transaction_slot_index);
    }
#endif
    
#if defined (REPOSITORY_EXTERNAL)
    hash_table_delete_element (exceptions_table, (p_hash_element_t) exception);
    pool_of_integers_deallocate (exception_ids_pool, exception->id);
#endif

    exception_destroy_internal (exception);
}

