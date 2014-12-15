
#ifndef REPOSITORY_HANDLE_INTERNAL_H
#define REPOSITORY_HANDLE_INTERNAL_H

static inline p_handle_t handle_create_static_internal (p_handle_t handle, 
    sequence_t parameters, uint32_t options UNUSED)
{
    reference_acquire_internal (handle->object);
    reference_acquire_internal (handle->interface);

    reference_create_internal (&handle->header, REFERENCE_TYPE_HANDLE);
    
    object_create_handle_internal (handle->object, handle, parameters);

    return handle;
}

static inline void handle_destroy_static_internal (p_handle_t handle)
{
    object_destroy_handle_internal (handle->object, handle);

    reference_destroy_internal (handle);

    reference_release_internal (handle->interface);
    reference_release_internal (handle->object);
}

static inline void handle_clone_static_internal (p_handle_t handle, 
    p_handle_t new_handle, uint32_t options UNUSED)
{
/*    
    p_handle_t handle_control = (p_handle_t) handle->object->class->handle_control;

    if (handle_control != NULL)
    {
//        new_handle->data = handle$clone (handle_control, object->data, handle->data, options);
    }
    else
    {
        new_handle->data = handle->data;
    }
*/
    reference_acquire_internal (handle->object);
    reference_acquire_internal (handle->interface);

    new_handle->object = handle->object;
    new_handle->interface = handle->interface;
}


static inline p_handle_t handle_create_internal (p_object_t object, 
    interface_id_t interface_id, sequence_t parameters, uint32_t options)
{
    p_handle_t handle;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p, %u, %p, %u)\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        object, interface_id, parameters.data, options);
    
    memory_allocate ((void **) &handle, sizeof (handle_t));

    handle->object = object;
    handle->interface = object_get_interface_by_id_internal (object, 
        interface_id);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1, 
        "%s: %s Interface: %p\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        handle->interface);
    
    return handle_create_static_internal (handle, parameters, options);
}

static inline void handle_destroy_internal (p_handle_t handle)
{
    handle_destroy_static_internal (handle);
    
    memory_deallocate (handle);
}

static inline p_handle_t handle_clone_internal (p_handle_t handle, 
    uint32_t options)
{
    p_handle_t new_handle;

    memory_allocate ((void **) &new_handle, sizeof (handle_t));
    
    handle_clone_static_internal (handle, new_handle, options);
    
    return new_handle;
}

static inline uint64_t handle_get_data_internal (p_handle_t handle)
{
    return handle->data;
}


#endif /* !REPOSITORY_HANDLE_INTERNAL_H */

