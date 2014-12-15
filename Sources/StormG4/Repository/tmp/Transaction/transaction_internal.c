#include <enviroment.h>

#define MODULE_NAME "Repository"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>
#include <exception/macros.h>

transaction_reference_t transaction_create_static_internal (p_transaction_t transaction)
{
#if defined (REPOSITORY_EXTERNAL)
    pool_of_integers_allocate (transaction_ids_pool, &transaction->id);
    hash_table_add_element (transactiones_table, (p_hash_element_t) transaction);
#endif
    return transaction;
}

void transaction_destroy_static_internal (transaction_reference_t transaction)
{
#if defined (REPOSITORY_EXTERNAL)
    hash_table_delete_element (transactiones_table, (p_hash_element_t) transaction);
    pool_of_integers_deallocate (transaction_ids_pool, transaction->id);
#endif
}

transaction_reference_t transaction_create_internal (sequence_t filtered_objects, 
    sequence_t ignored_objects, uint32_t history_depth, uint32_t options)
{
    transaction_t transaction;
    
    memory_allocate (&transaction, sizeof (transaction_t));

    transaction->is_static = FALSE;
    transaction->number_of_references = 0;

    transaction->is_active = FALSE;
    transaction->slot = 0;

    transaction->history = memory_allocate (history_depth, sizeof (operation_t));
    
    transaction->filtered_objects = filtered_objects;
    
    for (filtered_objects)
    {
        if (class is new)
        {
        transaction_controls[i].handle = filtered_objects->class->transaction_control;
        transaction_controls[i].data = transaction$create (transaction_controls[i].handle);
        }
    }
    
    transaction->ignored_objects = ignored_objects;
    
    return transaction_create_static_internal (transaction);
}

void transaction_destroy_internal (transaction_reference_t transaction)
{
    transaction_destroy_static_internal (transaction);
    
    for (filtered_objects)
    {
        transaction$destroy (ctrl->handle, ctrl->data);
    }
    
    memory_deallocate (transaction->history);
    memory_deallocate (transaction);
}

void transaction_begin_internal (transaction_reference_t transaction)
{
    transaction->slot = 0;
    transaction->is_active = TRUE;

    for (index = 0; index < transaction->filtered_objects; index++)
    {
        transaction$begin (ctrl->handle, ctrl->data);
    }    
}

void transaction_commit_internal (transaction_reference_t transaction)
{
    for (filtered_objects)
    {
        ctrl = transaction->object_history + index;
  
        transaction$commit (ctrl->handle, ctrl->data);
    }

    transaction->slot = 0;
    transaction->is_active = FALSE;
}

void transaction_rollback_internal (transaction_reference_t transaction)
{
    uint32_t index;
    p_operation_t operation;
    p_handle_t transaction_control;

    for (filtered_objects)
    {
        ctrl = transaction->object_history + index;
  
        transaction$rollback (ctrl->handle, ctrl->data);
    }

    transaction->slot = 0;
    transaction->is_active = FALSE;
}

void transaction_add_operation_internal (transaction_reference_t transaction,
    handle_reference_t handle, method_id_t method_id)
{
    uint32_t index;

    for (ignored_objects)
    {
        if (==)
        {
            return;
        }
    }

    for (index = 0; index < transaction->filtered_objects; index++)
    {
        if (==)
        {
            transaction$add_operation (ctrl->handle, ctrl->data, 
                handle->object->data, handle->data, method_id);
            return;
        }
    }
    
//    transaction->object_slot++;
//    transaction$begin (
}

add_operation ()
{
    history[slot].operation = operation;
    history[slot].reference = reference;
    slot++;
}

rollback ()
{
    for ()
    {
    }
}

operations:
INTERFACE_CREATE
INTERFACE_DESTROY
OBJECT_CREATE
OBJECT_DESTROY
HANDLE_CREATE
HANDLE_DESTROY
SECURITY_CREATE
SECURITY_DESTROY
TRANSACTION_CREATE
TRANSACTION_DESTROY
//QUALITY_CREATE
//QUALITY_DESTROY

enum
{
    OPERATION_NULL,

    OPERATION_CLASS_CREATE_STATIC,
    OPERATION_CLASS_CREATE,
    OPERATION_CLASS_DESTROY_STATIC,
    OPERATION_CLASS_DESTROY,
    
    OPERATION_OBJECT_CREATE_STATIC,
    OPERATION_OBJECT_CREATE,
    OPERATION_OBJECT_DESTROY_STATIC,
    OPERATION_OBJECT_DESTROY,
};

uint32_t transaction_add_slot (transaction_reference_t transaction, 
    reference_t reference, uint32_t operation)
{
    uint32_t slot_index = slot;
    
    slots[slot].reference = reference;
    slots[slot].operation = operation;
    slot++;
    
    return slot_index;
}

transaction_clear_slot (transaction_reference_t transaction, 
    uint32_t slot_index)
{
    slots[slot_index].object = NULL;
    slots[slot_index].operation = OPEREATION_NULL;
}

