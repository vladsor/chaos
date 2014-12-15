
#ifndef REPOSITORY_INTERFACE_INTERNAL_H
#define REPOSITORY_INTERFACE_INTERNAL_H

static inline p_interface_t interface_create_static_internal (
    p_interface_t interface)
{
    uint32_t index;
    p_method_t method;

    description_reference_acquire_internal (interface->description);
    
    for (index = 0; index < interface->methods.count; index++)
    {
        method = ((p_p_method_t) interface->methods.data)[index];
        
        if (method != NULL)
        {
            reference_acquire_internal (method);
        }    
    }

    if (interface->factory != REFERENCE_NULL)
    {
        reference_acquire_internal (interface->factory);
    }    

    reference_create_internal (&interface->header, REFERENCE_TYPE_INTERFACE);
    
    return interface;
}

static inline void interface_destroy_static_internal (p_interface_t interface)
{
    uint32_t index;
    p_method_t method;

    reference_destroy_internal (interface);

    if (interface->factory != REFERENCE_NULL)
    {
        reference_release_internal (interface->factory);
    }    

    for (index = 0; index < interface->methods.count; index++)
    {
        method = ((p_p_method_t) interface->methods.data)[index];
        
        if (method != NULL)
        {
            reference_release_internal (method);
        }    
    }

    description_reference_release_internal (interface->description);
}

static inline p_interface_t interface_create_internal (
    p_interface_description_t interface_description, 
    sequence_t interface_methods,
    reference_t interface_factory, 
    uint32_t options UNUSED)
{
    p_interface_t interface;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s: %s (%p, %p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        interface_description, interface_methods.data);
    
    memory_allocate ((void **) &interface, sizeof (interface_t));

    interface->description = interface_description;
    
    interface->methods.count = interface_methods.count;
    interface->methods.data = NULL;
    
    if (interface->methods.count > 0)
    {
        memory_allocate ((void **) &interface->methods.data, 
            sizeof (p_method_t) * interface_methods.count);
        memory_copy (interface->methods.data, interface_methods.data,
            sizeof (p_method_t) * interface_methods.count);
    }
    
    interface->factory = interface_factory;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s: %s: Interface: %p, description: %p, methods: %p\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        interface, interface->description, interface->methods.data);
    
    return interface_create_static_internal (interface);
}

static inline void interface_destroy_internal (p_interface_t interface)
{
    interface_destroy_static_internal (interface);
    
    memory_deallocate (interface->methods.data);
    memory_deallocate (interface);
}

static inline id_t interface_get_id_internal (p_interface_t interface)
{
    return description_reference_get_id_internal (interface->description);
}    

#endif /* !REPOSITORY_INTERFACE_INTERNAL_H */

