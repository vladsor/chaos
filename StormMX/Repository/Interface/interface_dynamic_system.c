#include <enviroment.h>

#define MODULE_NAME "Repository"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>
#include <exception/macros.h>

interface_reference_t interface_create (
    p_interface_description_t interface_description, 
    sequence_t interface_methods)
{
    interface_reference_t interface_reference;

#if defined (SECURITY_ENABLED)
    interface_create_security_check ();
#endif

#if defined (CHECK_PARAMETERS)
    interface_create_check_parameters (interface_description, 
        interface_methods);
#endif
    
    interface_reference = interface_create_internal (interface_description, 
        interface_methods);

#if defined (REPOSITORY_EXTERNAL)
    pool_of_integers_allocate (interface_ids_pool, &interface->id);
    hash_table_add_element (interfaces_table, (p_hash_element_t) interface);
#endif

#if defined (TRANSACTION_ENABLED)
    if (transaction_current != NULL)
    {
        interface->transaction = transaction_current;

        interface->transaction_slot_index = transaction_add_slot (
            transaction_current, interface_reference, 
            OPERATION_INTERFACE_CREATE);
    }
#ndif

    return interface_reference;    
}

void interface_destroy (interface_reference_t interface)
{
#if defined (SECURITY_ENABLED)
    interface_destroy_security_check (interface);
#endif
    
#if defined (CHECK_PARAMETERS)
    interface_destroy_check_parameters (interface);
#endif

#if defined (TRANSACTION_ENABLED)
    if ((interface->transaction != NULL) && 
        (interface->transaction != transaction_current))
    {
        THROW_SYSTEM (EXCEPTION_IS_LOCKED);
    }
    
    if (transaction_current != NULL)
    {
        if (interface->transaction == NULL)
        {
#   if defined (REPOSITORY_EXTERNAL)
            hash_table_delete_element (interfaces_table, 
                (p_hash_element_t) interface);
#   endif
            transaction_add_slot (transaction_current, interface,
                OPERATION_INTERFACE_DESTROY);
            return;
        }
        
        transaction_clear_slot (interface->transaction, 
            interface->transaction_slot_index);
    }
#endif

#if defined (REPOSITORY_EXTERNAL)
    hash_table_delete_element (interfaces_table, (p_hash_element_t) interface);
    pool_of_integers_deallocate (interface_ids_pool, interface->id);
#endif
    
    interface_destroy_internal (interface);
}

