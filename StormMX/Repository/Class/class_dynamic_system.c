#include <enviroment.h>

#define MODULE_NAME "Repository"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>
#include <exception/macros.h>

class_reference_t class_create (p_class_description_t class_description,
    sequence_t class_interfaces, object_reference_t class_repository)
{
    class_reference_t class_reference;

#if defined (SECURITY_ENABLED)
    class_create_security_check ();
#endif

#if defined (CHECK_PARAMETERS)
    class_create_check_parameters (class_description, class_interfaces, 
        class_repository);
#endif
    
    class_reference = class_create_internal (class_description, class_interfaces, 
        class_repository);
        
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
            OPERATION_CLASS_CREATE);
    }
#ndif

    return class_reference;        
}

void class_destroy (class_reference_t class)
{
#if defined (SECURITY_ENABLED)
    class_destroy_security_check (class);
#endif
    
#if defined (CHECK_PARAMETERS)
    class_destroy_check_parameters (class);
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
                OPERATION_class_DESTROY);
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
    
    class_destroy_internal (class);
}

void class_set_interfaces (class_reference_t class, 
    sequence_t class_interfaces)
{
#if defined (SECURITY_ENABLED)
    class_set_interface_security_check (class);
#endif
    
#if defined (CHECK_PARAMETERS)
    class_set_interface_check_parameters (class);
#endif
    
    class_set_interface_internal (class, class_interfaces);
}

sequence_t class_get_interfaces (class_reference_t class)
{
#if defined (SECURITY_ENABLED)
    class_get_interfaces_security_check (class);
#endif
    
#if defined (CHECK_PARAMETERS)
    class_get_interfaces_check_parameters (class);
#endif
    
    return class_get_interfaces_internal (class);
}

interface_reference_t class_get_interface (
    class_reference_t class_reference, interface_id_t interface_id)
{
#if defined (SECURITY_ENABLED)
    class_get_interface_security_check (class);
#endif
    
#if defined (CHECK_PARAMETERS)
    class_get_interface_check_parameters (class);
#endif
    
    return class_get_interface_internal (class, interface_id);
}

