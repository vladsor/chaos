#include <enviroment.h>

#define MODULE_NAME "Repository"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>
#include <exception/macros.h>

method_reference_t method_create (p_method_description_t method_description)
{
    method_reference_t method_reference;

#if defined (SECURITY_ENABLED)
    method_create_security_check ();
#endif

#if defined (CHECK_PARAMETERS)
    method_create_check_parameters (method_description);
#endif
    
    method_reference = method_create_internal (method_description);

#if defined (REPOSITORY_EXTERNAL)
    pool_of_integers_allocate (method_ids_pool, &method->id);
    hash_table_add_element (methods_table, (p_hash_element_t) method);
#endif

#if defined (TRANSACTION_ENABLED)
    if (transaction_current != NULL)
    {
        method_reference->transaction = transaction_current;

        method_reference->transaction_slot_index = transaction_add_slot (
            transaction_current, method_reference, OPERATION_METHOD_CREATE);
    }
#ndif

    return method_reference;
}

void method_destroy (method_reference_t method)
{
#if defined (SECURITY_ENABLED)
    method_destroy_security_check (method);
#endif
    
#if defined (CHECK_PARAMETERS)
    method_destroy_check_parameters (method);
#endif

#if defined (TRANSACTION_ENABLED)
    if (method->transaction != NULL && 
        method->transaction != transaction_current)
    {
        THROW_SYSTEM (method_IS_LOCKED);
    }

    if (transaction_current != NULL)
    {
        if (transaction_current != method_reference->transaction)
        {
#   if defined (REPOSITORY_EXTERNAL)
            hash_table_delete_element (methods_table, 
                (p_hash_element_t) method);
#   endif
            transaction_add_slot (transaction_current, method,
                OPERATION_METHOD_DESTROY);
            return;
        }
        
        transaction_clear_slot (method->transaction, method->transaction_slot_index);
    }
#endif
    
#if defined (REPOSITORY_EXTERNAL)
    hash_table_delete_element (methods_table, (p_hash_element_t) method);
    pool_of_integers_deallocate (class_ids_pool, method->id);
#endif

    method_destroy_internal (method);
}

void method_invoke (method_reference_t method, context_t context,
    sequence_t return_value, sequence_t parameters)
{
/*
#if defined (SECURITY_ENABLED)
    method_invoke_security_check (method);
#endif
    
#if defined (CHECK_PARAMETERS)
    method_invoke_check_parameters (method, context, return_value, parameters);
#endif


#if defined (TRANSACTION_ENABLED)
    if (method->transaction != NULL && 
        method->transaction != transaction_current)
    {
        THROW_SYSTEM (method_IS_LOCKED);
    }

    if (transaction_current != NULL)
    {
        transaction$add_operation (transaction_control, object, method_id);
    }
#endif
*/
    method_invoke_internal (method, context, return_value, parameters);
}

void method_invoke_static (method_reference_t method, 
    sequence_t return_value, sequence_t parameters)
{
/*
#if defined (SECURITY_ENABLED)
    method_invoke_static_security_check (method);
#endif
    
#if defined (CHECK_PARAMETERS)
    method_invoke_static_check_parameters (method, return_value, parameters);
#endif
*/

    method_invoke_internal (method, return_value, parameters);
}

