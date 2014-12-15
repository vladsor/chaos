
#ifndef REPOSITORY_EVENT_CONSUMER_INTERFACE_INTERNAL_H
#define REPOSITORY_EVENT_CONSUMER_INTERFACE_INTERNAL_H

static inline p_event_consumer_interface_t 
    event_consumer_interface_create_static_internal (
        p_event_consumer_interface_t event_consumer_interface)
{
    if (event_consumer_interface->handle != NULL)
    {
        reference_acquire_internal (event_consumer_interface->handle);
    }    

    if (event_consumer_interface->factory != NULL)
    {
        reference_acquire_internal (event_consumer_interface->factory);
    }    

    reference_create_internal (&event_consumer_interface->header, 
        REFERENCE_TYPE_EVENT_CONSUMER_INTERFACE);
    
    return event_consumer_interface;
}

static inline void event_consumer_interface_destroy_static_internal (
    p_event_consumer_interface_t event_consumer_interface)
{
    reference_destroy_internal (event_consumer_interface);

    if (event_consumer_interface->handle != NULL)
    {
        reference_release_internal (event_consumer_interface->handle);
    }    

    if (event_consumer_interface->handle != NULL)
    {
        reference_release_internal (event_consumer_interface->handle);
    }
}

static inline p_event_consumer_interface_t 
    event_consumer_interface_create_internal 
    (
        p_event_description_t event_description, 
        int type, 
        method_reference_t handle,
        reference_t event_consumer_factory,
        uint32_t options UNUSED
    )
{
    p_event_consumer_interface_t event_consumer_interface;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s: %s (%p, %X, %p, %p, %X)\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        event_description, type, handle, event_consumer_factory, options);
    
    memory_allocate ((void **) &event_consumer_interface, 
        sizeof (event_consumer_interface_t));

    event_consumer_interface->event_description = event_description;
    event_consumer_interface->type = type;
    event_consumer_interface->handle = handle;
    event_consumer_interface->factory = event_consumer_factory;
    
    return event_consumer_interface_create_static_internal (
        event_consumer_interface);
}

static inline void event_consumer_interface_destroy_internal (
    p_event_consumer_interface_t event_consumer_interface)
{
    event_consumer_interface_destroy_static_internal (event_consumer_interface);
    
    memory_deallocate (event_consumer_interface);
}

static inline id_t event_consumer_interface_get_id_internal (
    p_event_consumer_interface_t interface)
{
    return description_reference_get_id_internal (interface->event_description);
}

static inline void event_consumer_interface_set_factory_internal (
    p_event_consumer_interface_t event_consumer_interface, 
    reference_t event_consumer_factory)
{
    event_consumer_interface->factory = event_consumer_factory;
}    

static inline void event_consumer_interface_create_event_consumer_internal (
    p_event_consumer_interface_t interface, p_object_t object,
    event_consumer_reference_t event_consumer, sequence_t parameters)
{
    if (interface->factory == REFERENCE_NULL)
    {
        return;
    }
    
    if (reference_get_type_internal (interface->factory) 
        == REFERENCE_TYPE_HANDLE)
    {
        p_handle_t factory;
        sequence_t empty_seq = {data: NULL, count: 0};
        factory = (p_handle_t) interface->factory;
        
        handle_invoke_method_internal (factory, 
            METHOD_EVENT_CONSUMER_FACTORY_CREATE_ID, NULL, 
            object, event_consumer, parameters, empty_seq, empty_seq);
    }
    else if (reference_get_type_internal (interface->factory) 
        == REFERENCE_TYPE_INTERFACE)
    {
        p_interface_t factory;
        sequence_t empty_seq = {data: NULL, count: 0};
        context_t context = {0,0};

        factory = (p_interface_t) interface->factory;
    
        interface_invoke_method_internal (factory, NULL, NULL, NULL,
            METHOD_EVENT_CONSUMER_FACTORY_CREATE_ID, NULL, context,
            object, event_consumer, parameters, empty_seq, empty_seq);
    }    
}    

static inline void event_consumer_interface_fire_async_internal (
    p_event_consumer_interface_t interface, 
    sequence_t event_data)
{
    if (interface->handle == NULL)
    {
        return;
    }
    else
    {
        sequence_t empty_seq = {data: NULL, count: 0};
        
        method_invoke_async_internal (interface->handle, NULL, NULL, NULL, NULL, 
            NULL, NULL, NULL, event_data, empty_seq);
    }    
}

static inline void event_consumer_interface_fire_sync_internal (
    p_event_consumer_interface_t interface, 
    sequence_t event_data)
{
    if (interface->handle == NULL)
    {
        return;
    }
    else
    {
        sequence_t empty_seq = {data: NULL, count: 0};
        context_t context = {0,0};
        
        method_invoke_internal (interface->handle, NULL, NULL, NULL, NULL, 
            NULL, context, NULL, NULL, event_data, empty_seq, empty_seq);
    }    
}

#endif /* !REPOSITORY_EVENT_CONSUMER_INTERFACE_INTERNAL_H */

