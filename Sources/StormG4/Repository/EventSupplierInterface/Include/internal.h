
#ifndef REPOSITORY_EVENT_SUPPLIER_INTERFACE_INTERNAL_H
#define REPOSITORY_EVENT_SUPPLIER_INTERFACE_INTERNAL_H

static inline p_event_supplier_interface_t 
    event_supplier_interface_create_static_internal (
        p_event_supplier_interface_t event_supplier_interface)
{
    if (event_supplier_interface->handle != NULL)
    {
        reference_acquire_internal (event_supplier_interface->handle);
    }    

    if (event_supplier_interface->factory != NULL)
    {
        reference_acquire_internal (event_supplier_interface->factory);
    }    

    reference_create_internal (&event_supplier_interface->header, 
        REFERENCE_TYPE_EVENT_SUPPLIER_INTERFACE);
    
    return event_supplier_interface;
}

static inline void event_supplier_interface_destroy_static_internal (
    p_event_supplier_interface_t event_supplier_interface)
{
    reference_destroy_internal (event_supplier_interface);

    if (event_supplier_interface->handle != NULL)
    {
        reference_release_internal (event_supplier_interface->handle);
    }    

    if (event_supplier_interface->handle != NULL)
    {
        reference_release_internal (event_supplier_interface->handle);
    }
}

static inline p_event_supplier_interface_t 
    event_supplier_interface_create_internal 
    (
        p_event_description_t event_description, 
        int type, 
        method_reference_t handle,
        uint32_t options UNUSED
    )
{
    p_event_supplier_interface_t event_supplier_interface;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s: %s (%p, %X, %p, %X)\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        event_description, type, handle, options);
    
    memory_allocate ((void **) &event_supplier_interface, 
        sizeof (event_supplier_interface_t));

    event_supplier_interface->event_description = event_description;
    event_supplier_interface->type = type;
    event_supplier_interface->handle = handle;
    
    return event_supplier_interface_create_static_internal (
        event_supplier_interface);
}

static inline void event_supplier_interface_destroy_internal (
    p_event_supplier_interface_t event_supplier_interface)
{
    event_supplier_interface_destroy_static_internal (event_supplier_interface);
    
    memory_deallocate (event_supplier_interface);
}

static inline id_t event_supplier_interface_get_id_internal (
    p_event_supplier_interface_t interface)
{
    return description_reference_get_id_internal (interface->event_description);
}

static inline void event_supplier_interface_set_factory_internal (
    p_event_supplier_interface_t event_supplier_interface, 
    reference_t event_supplier_factory)
{
    event_supplier_interface->factory = event_supplier_factory;
}    

static inline void event_supplier_interface_create_event_supplier_internal (
    p_event_supplier_interface_t interface, p_object_t object,
    event_supplier_reference_t event_supplier, sequence_t parameters)
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
            METHOD_EVENT_SUPPLIER_FACTORY_CREATE_ID, NULL, 
            object, event_supplier, parameters, empty_seq, empty_seq);
    }
    else if (reference_get_type_internal (interface->factory) 
        == REFERENCE_TYPE_INTERFACE)
    {
        p_interface_t factory;
        sequence_t empty_seq = {data: NULL, count: 0};
        context_t context = {0,0};

        factory = (p_interface_t) interface->factory;
    
        interface_invoke_method_internal (factory, NULL, NULL, NULL,
            METHOD_EVENT_SUPPLIER_FACTORY_CREATE_ID, NULL, context,
            object, event_supplier, parameters, empty_seq, empty_seq);
    }    
}    

static inline void event_supplier_interface_wait_internal (
    p_event_supplier_interface_t interface UNUSED, sequence_t event_data UNUSED)
{
}    

#endif /* !REPOSITORY_EVENT_SUPPLIER_INTERFACE_INTERNAL_H */

