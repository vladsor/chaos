#include <enviroment.h>

#define DEBUG_MODULE_NAME "Repository"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include "../Include/internal.h"

#include <debug/macros.h>
#include <exception/macros.h>

handle_reference_t handle_create_static (p_handle_t handle, 
     sequence_t parameters, uint32_t options)
{
    p_handle_t handle_reference;
    
#if defined (SECURITY_ENABLED)
    handle_create_security_check ();
#endif
    
    handle_reference = handle_create_static_internal (handle, parameters, 
        options);

    handle->header.is_static = TRUE;    

#if defined (TRANSACTION_ENABLED)
    if (transaction_current != NULL)
    {
        object_reference->transaction = transaction_current;

        object_reference->transaction_slot_index = transaction_add_slot (
            transaction_current, object_reference, 
            OPERATION_HANDLE_CREATE_STATIC);
    }
#endif

    return (handle_reference_t) handle_reference;    
}

void handle_destroy_static (handle_reference_t handle_reference)
{
    p_handle_t handle = (p_handle_t) handle_reference;

#if defined (SECURITY_ENABLED)
    handle_destroy_security_check (handle);
#endif

#if defined (TRANSACTION_ENABLED)
    if (handle->transaction != NULL && handle->transaction != transaction_current)
    {
        THROW_SYSTEM (EXCEPTION_IS_LOCKED);
    }
    
    if (transaction_current != NULL)
    {
        if (transaction_current != handle->transaction)
        {
#   if defined (REPOSITORY_EXTERNAL)
            hash_table_delete_element (handles_table, 
                (p_hash_element_t) handle);
#   endif
            transaction_add_slot (transaction_current, handle,
                OPERATION_HANDLE_DESTROY_STATIC);
            return;
        }
        
        transaction_clear_slot (object->transaction, object->transaction_slot_index);
    }
#endif
  
    handle_destroy_static_internal (handle);
}

handle_reference_t handle_clone_static (handle_reference_t handle_reference, 
    p_handle_t new_handle, uint32_t options)
{
    p_handle_t handle = (p_handle_t) handle_reference;
    
#if defined (SECURITY_ENABLED)
    handle_clone_security_check (handle);
#endif
    
    handle_clone_static_internal (handle, new_handle, options);
    
    handle->header.is_static = TRUE;    

#if defined (TRANSACTION_ENABLED)
    if (transaction_current != NULL)
    {
        new_handle->transaction = transaction_current;

        new_handle->transaction_slot_index = transaction_add_slot (
            transaction_current, new_handle, 
            OPERATION_HANDLE_CLONE_STATIC);
    }
#endif

    return (handle_reference_t) new_handle;    
}


