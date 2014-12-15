#include <enviroment.h>

#define MODULE_NAME "Repository"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>
#include <exception/macros.h>

interface_reference_t interface_create_static (p_interface_t interface)
{
    interface_reference_t interface_reference;
    
#if defined (SECURITY_ENABLED)
    interface_create_security_check ();
#endif
    
    interface->is_static = TRUE;
    
    interface_reference = interface_create_static_internal (interface);

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
            OPERATION_INTERFACE_CREATE_STATIC);
    }
#ndif

    return interface_reference;    
}

void interface_destroy_static (interface_reference_t interface)
{
#if defined (SECURITY_ENABLED)
    interface_destroy_security_check (interface);
#endif

#if defined (TRANSACTION_ENABLED)
    if ((interface>transaction != NULL) && 
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
                OPERATION_INTERFACE_DESTROY_STATIC);
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
    
    interface_destroy_static_internal (interface);
}

