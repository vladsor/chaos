#include <enviroment.h>

#define MODULE_NAME "Repository"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>
#include <exception/macros.h>

handle_reference_t handle_create_static_internal (p_handle_t handle)
{
    handle->object->number_of_references++;

#if defined (REPOSITORY_EXTERNAL)
    pool_of_integers_allocate (handle_ids_pool, &handle->id);
    hash_table_add_element (handles_table, (p_hash_element_t) handle);
#endif
    return class;
}

void handle_destroy_static_internal (handle_reference_t handle)
{
#if defined (REPOSITORY_EXTERNAL)
    hash_table_delete_element (handles_table, (p_hash_element_t) handle);
    pool_of_integers_deallocate (handle_ids_pool, handle->id);
#endif

    handle->object->number_of_references--;
}

void handle_clone_static_internal (handle_reference_t handle, 
    handle_reference_t new_handle, uint32_t options)
{
    handle->object->number_of_references++;

    new_handle->data = handle->data;
    new_handle->object = handle->object;
    new_handle->interface = handle->interface;

#if defined (REPOSITORY_EXTERNAL)
    pool_of_integers_allocate (handle_ids_pool, &new_handle->id);
    hash_table_add_element (handles_table, (p_hash_element_t) new_handle);
#endif
}


handle_reference_t handle_create_internal (object_reference_t object, 
    interface_id_t interface_id, sequence_t parameters, uint32_t options)
{
    handle_t handle;
    
    memory_allocate (&handle, sizeof (handle_t));

    handle->is_static = FALSE;
    
    handle->interface = object_get_interface (object, &handle->object, interface_id);

    handle->data = handle$open (handle_control, object->data, interface_id, 
        parameters, options);
    
    return handle_create_static_internal (handle);
}

void handle_destroy_internal (handle_reference_t handle)
{
    handle_destroy_static_internal (handle);
    
    handle$close (handle_control, object->data, handle->data);
    
    memory_deallocate (handle);
}

handle_reference_t handle_clone_internal (handle_reference_t handle, 
    uint32_t options)
{
    p_handle_t new_handle;

    memory_allocate (&new_handle, sizeof (handle_t));
    new_handle->is_static = FALSE;
    
    new_handle->data = handle$clone (handle_control, handle->object->data, 
        handle->data, options);
    
    handle_clone_static_internal (handle, new_handle, options);
    
    return new_handle;
}

void handle_invoke_method_internal (handle_t handle, method_id_t method_id, 
    sequence_t return_value, sequence_t parameters)
{
    p_method_t method;

    method = handle->interface->methods[method_id];
    
    if (handle->interface->description->type == INTERFACE_TYPE_STATIC)
    {
        method_invoke_static_lowlevel (method, handle->object->data, handle->data, 
            return_value.data, parameters.data, parameters.length);
    }
    else if (handle->interface->description->type == INTERFACE_TYPE_DYNAMIC)
    {
        method_invoke_dynamic_lowlevel (method, handle->object->data, handle->data, 
            return_value.data, parameters.data, parameters.length);
    }
}

