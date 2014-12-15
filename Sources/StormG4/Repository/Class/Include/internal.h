
#ifndef REPOSITORY_CLASS_INTERNAL_H
#define REPOSITORY_CLASS_INTERNAL_H

static inline p_class_t class_create_static_internal (p_class_t class)
{
    uint32_t index;
    p_interface_t interface;
    p_event_supplier_interface_t supplier_interface;
    p_event_consumer_interface_t consumer_interface;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s: %s (%p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        class);

    description_reference_acquire_internal (class->description);
    
    for (index = 0; index < class->interfaces.count; index++)
    {
        interface = ((p_p_interface_t) class->interfaces.data)[index];

        reference_acquire_internal (interface);
    }

    for (index = 0; index < class->event_supplier_interfaces.count; index++)
    {
        supplier_interface = ((p_p_event_supplier_interface_t) 
            class->event_supplier_interfaces.data)[index];

        reference_acquire_internal (supplier_interface);
    }

    for (index = 0; index < class->event_consumer_interfaces.count; index++)
    {
        consumer_interface = ((p_p_event_consumer_interface_t) 
            class->event_consumer_interfaces.data)[index];

        reference_acquire_internal (consumer_interface);
    }

    if (class->object_factory != REFERENCE_NULL)
    {
        reference_acquire_internal (class->object_factory);
    }    
    
    if (class->handle_factory != REFERENCE_NULL)
    {
        reference_acquire_internal (class->handle_factory);
    }    

    reference_create_internal (&class->header, REFERENCE_TYPE_CLASS);

    return class;
}

static inline void class_destroy_static_internal (p_class_t class)
{
    uint32_t index;
    p_interface_t interface;
    p_event_supplier_interface_t supplier_interface;
    p_event_consumer_interface_t consumer_interface;

    reference_destroy_internal (class);

    for (index = 0; index < class->event_consumer_interfaces.count; index++)
    {
        consumer_interface = ((p_p_event_consumer_interface_t) 
            class->event_consumer_interfaces.data)[index];

        reference_release_internal (consumer_interface);
    }

    for (index = 0; index < class->event_supplier_interfaces.count; index++)
    {
        supplier_interface = ((p_p_event_supplier_interface_t) 
            class->event_supplier_interfaces.data)[index];

        reference_release_internal (supplier_interface);
    }

    for (index = 0; index < class->interfaces.count; index++)
    {
        interface = ((p_p_interface_t) class->interfaces.data)[index];
        
        reference_release_internal (interface);
    }

    if (class->handle_factory != REFERENCE_NULL)
    {
        reference_release_internal (class->handle_factory);
    }    

    if (class->object_factory != REFERENCE_NULL)
    {
        reference_release_internal (class->object_factory);
    }    
    
    description_reference_release_internal (class->description);
}

static inline p_class_t class_create_internal (
    p_class_description_t class_description, sequence_t class_interfaces, 
    sequence_t class_event_suppliers, sequence_t class_event_consumers, 
    handle_reference_t class_object_factory,
    handle_reference_t class_handle_factory,
    uint32_t options UNUSED)
{
    p_class_t class;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s: %s (%p, {%p, %u}, {%p, %u}, {%p. %u}, %p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        class_description, 
        class_interfaces.data, class_interfaces.count, 
        class_event_suppliers.data, class_event_suppliers.count,
        class_event_consumers.data, class_event_consumers.count,
        class_object_factory);
    
    memory_allocate ((void **) &class, sizeof (class_t));

    class->description = class_description;

    // Copyng info about interfaces
    class->interfaces.count = class_interfaces.count;
    class->interfaces.data = NULL;
    
    if (class->interfaces.count > 0)
    {
        memory_allocate ((void **) &class->interfaces.data, 
            sizeof (interface_reference_t) * class_interfaces.count);

        memory_copy (class->interfaces.data, class_interfaces.data, 
            sizeof (interface_reference_t) * class_interfaces.count);
    }    

    // Copyng info about event supplier interfaces
    class->event_supplier_interfaces.count = class_event_suppliers.count;
    class->event_supplier_interfaces.data = NULL;
    
    if (class->event_supplier_interfaces.count > 0)
    {
        memory_allocate ((void **) &class->event_supplier_interfaces.data, 
            sizeof (event_supplier_reference_t) * class_event_suppliers.count);

        memory_copy (class->event_supplier_interfaces.data, 
            class_event_suppliers.data, 
            sizeof (event_supplier_reference_t) * class_event_suppliers.count);
    }
    

    // Copyng info about event consumer interfaces
    class->event_consumer_interfaces.count = class_event_consumers.count;
    class->event_consumer_interfaces.data = NULL;
    
    if (class->event_consumer_interfaces.count > 0)
    {
        memory_allocate ((void **) &class->event_consumer_interfaces.data, 
            sizeof (event_consumer_reference_t) * class_event_consumers.count);

        memory_copy (class->event_consumer_interfaces.data, 
            class_event_consumers.data, 
            sizeof (event_consumer_reference_t) * class_event_consumers.count);
    }    

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
        "%s: %s: Class: %p, description: %p, interfaces: %p\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        class, class->description, class->interfaces.data);

    class->object_factory = class_object_factory;
    class->handle_factory = class_handle_factory;
    
    class->quality_control = REFERENCE_NULL;
    class->transaction_control = REFERENCE_NULL;
    
    return class_create_static_internal (class);
}

static inline void class_destroy_internal (p_class_t class)
{
    class_destroy_static_internal (class);
    
    memory_deallocate (class->event_consumer_interfaces.data);
    memory_deallocate (class->event_supplier_interfaces.data);
    memory_deallocate (class->interfaces.data);
    memory_deallocate (class);
}

static inline void class_set_interfaces_internal (p_class_t class UNUSED, 
    sequence_t class_interfaces UNUSED)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s: %s (%p, {%p, %u})\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        class, class->interfaces.data, class->interfaces.count);
}

static inline void class_get_interfaces_internal (p_class_t class UNUSED, 
    sequence_t class_interfaces UNUSED)
{
}

static inline p_interface_t class_get_interface_by_id_internal (p_class_t class, 
    interface_id_t interface_id)
{
    uint32_t index;
    p_interface_t interface;

    for (index = 0; index < class->interfaces.count; index++)
    {
        interface = ((p_p_interface_t) class->interfaces.data)[index];

        if (interface_get_id_internal (interface) == interface_id)
        {
            return reference_acquire_internal (interface);
        }
    }
    
    return NULL;
}

static inline p_event_supplier_interface_t 
    class_get_event_supplier_interface_by_id_internal (p_class_t class, 
        id_t event_id)
{
    uint32_t index;
    p_event_supplier_interface_t supplier_interface;

    for (index = 0; index < class->event_supplier_interfaces.count; index++)
    {
        supplier_interface = ((p_p_event_supplier_interface_t) 
            class->event_supplier_interfaces.data)[index];
        
        if (event_supplier_interface_get_id_internal (supplier_interface) 
            == event_id)
        {
            return reference_acquire_internal (supplier_interface);
        }
    }
    
    return NULL;
}

static inline p_event_consumer_interface_t 
    class_get_event_consumer_interface_by_id_internal (p_class_t class, 
        id_t event_id)
{
    uint32_t index;
    p_event_consumer_interface_t consumer_interface;

    for (index = 0; index < class->event_consumer_interfaces.count; index++)
    {
        consumer_interface = ((p_p_event_consumer_interface_t) 
            class->event_consumer_interfaces.data)[index];
        
        if (event_consumer_interface_get_id_internal (consumer_interface) 
            == event_id)
        {
            return reference_acquire_internal (consumer_interface);
        }
    }
    
    return NULL;
}

static inline void class_create_object_internal (p_class_t class, 
    object_reference_t object, sequence_t parameters)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p, {%p, %u})\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        class, parameters.data, parameters.count);

    if (class->object_factory == REFERENCE_NULL)
    {
        return;
    }    

    if (reference_get_type_internal (class->object_factory) 
        == REFERENCE_TYPE_HANDLE)
    {
        p_handle_t handle;
        sequence_t empty_seq = {data: NULL, count: 0};
        handle = (p_handle_t) class->object_factory;
        
        handle_invoke_method_internal (handle, 
            METHOD_OBJECT_FACTORY_CREATE_ID, NULL, 
            class, object, parameters, empty_seq, empty_seq);
    }
    else if (reference_get_type_internal (class->object_factory) 
        == REFERENCE_TYPE_INTERFACE)
    {
        p_interface_t interface;
        sequence_t empty_seq = {data: NULL, count: 0};
        context_t context = {0,0};

        interface = (p_interface_t) class->object_factory;
    
        interface_invoke_method_internal (interface, NULL, NULL, NULL,
            METHOD_OBJECT_FACTORY_CREATE_ID, NULL, context,
            class, object, parameters, empty_seq, empty_seq);
    }    
}    

static inline void class_destroy_object_internal (p_class_t class UNUSED, 
    object_reference_t object UNUSED)
{
/*    
    p_handle_t handle = (p_handle_t) class->object_factory;

    if (handle != NULL)
    {
        sequence_t empty_seq = { data: NULL, count: 0 };
        
        handle_invoke_method_internal (handle, METHOD_OBJECT_FACTORY_DESTROY_ID, 
            NULL, object, empty_seq, empty_seq);
    }
*/
}
/*    
static inline uint64_t class_create_handle_internal (p_class_t class, 
    uint64_t object_data UNUSED, sequence_t parameters)
{
}
    
static inline void class_destroy_handle_internal (p_class_t class, 
    uint64_t object_data UNUSED, uint64_t handle_data)
{
} 
*/   

static inline void class_create_event_supplier_internal (p_class_t class UNUSED,
    p_object_t object, p_event_supplier_t event_supplier, sequence_t parameters)
{
    event_supplier_interface_create_event_supplier_internal (
        event_supplier->interface, object, event_supplier, parameters);
}
/*
static inline void class_create_event_consumer_internal (p_class_t class, 
    p_object_t object, p_event_consumer_t event_consumer, sequence_t parameters)
{
    event_consumer_interface_create_event_consumer_internal (
        event_consumer->interface, event_consumer, parameters);
}
*/
#endif /* !REPOSITORY_CLASS_INTERNAL_H */

