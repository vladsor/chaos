#include <enviroment.h>

#define MODULE_NAME "Repository"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>
#include <exception/macros.h>

object_reference_t object_create (class_reference_t class, 
    sequence_t object_own_interfaces, sequence_t joined_objects, 
    security_reference_t security, sequence_t parameters, 
    uint32_t options)
{
    object_reference_t object_reference;

#if defined (SECURITY_ENABLED)
    object_create_security_check (object);
#endif

#if defined (CHECK_PARAMETERS)
    object_create_check_parameters (class, object_own_interfaces, 
        joined_objects, security, parameters, options);
#endif
    
    object_reference = object_create_internal (class, object_own_interfaces, 
        joined_objects, security, parameters, options);

#if defined (REPOSITORY_EXTERNAL)
    pool_of_integers_allocate (object_ids_pool, &object->id);
    hash_table_add_element (objectes_table, (p_hash_element_t) object);
#endif

#if defined (TRANSACTION_ENABLED)
    if (transaction_current != NULL)
    {
        object_reference->transaction = transaction_current;

        object_reference->transaction_slot_index = transaction_add_slot (
            transaction_current, object_reference, OPERATION_OBJECT_CREATE);
    }
#ndif

    return object_reference;
}

void object_destroy (object_reference_t object)
{
#if defined (SECURITY_ENABLED)
    object_destroy_security_check (object);
#endif
    
#if defined (CHECK_PARAMETERS)
    object_destroy_check_parameters (object);
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
                OPERATION_OBJECT_DESTROY);
            return;
        }
        
        transaction_clear_slot (object->transaction, object->transaction_slot_index);
    }
#endif
    
#if defined (REPOSITORY_EXTERNAL)
    hash_table_delete_element (objectes_table, (p_hash_element_t) object);
    pool_of_integers_deallocate (class_ids_pool, object->id);
#endif

    object_destroy_internal (object);
}

class_reference_t object_get_class (object_reference_t object)
{
    return object_get_class_internal (object);
}
    
interface_reference_t object_get_interface (
    object_reference_t object, interface_id_t interface_id)
{
    return object_get_interface_internal (object, interface_id);
}

security_reference_t object_get_security (
    object_reference_t object)
{
    return object_get_security_internal (object);
}

void object_set_security (object_reference_t object,
    security_reference_t security)
{
    object_set_security_internal (object, security);
}

