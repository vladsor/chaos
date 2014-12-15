
#ifndef REPOSITORY_OBJECT_INTERNAL_H
#define REPOSITORY_OBJECT_INTERNAL_H

static inline p_object_t object_create_static_internal (p_object_t object,
    sequence_t parameters, uint32_t options UNUSED)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p, %p, %u)\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        object, parameters.data, options);

    reference_acquire_internal (object->class);
    
    if (object->security != NULL)
    {
        reference_acquire_internal (object->security);
    }    

    reference_create_internal (&object->header, REFERENCE_TYPE_OBJECT);
    
    class_create_object_internal (object->class, object, parameters);

    return object;
}

static inline void object_destroy_static_internal (p_object_t object)
{
    class_destroy_object_internal (object->class, object);

    reference_destroy_internal (object);

    if (object->security != NULL)
    {
        reference_release_internal (object->security);
    }    
    
    reference_release_internal (object->class);
}

static inline p_object_t object_create_internal (p_class_t object_class, 
    p_security_t object_security, sequence_t parameters, uint32_t options)
{
    p_object_t object;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p, %p, %p, %u)\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        object_class, object_security, parameters.data, options);
    
    memory_allocate ((void **) &object, sizeof (object_t));

    object->class = object_class;
    object->security = object_security;
    
    return object_create_static_internal (object, parameters, options);
}

static inline void object_destroy_internal (p_object_t object)
{
    object_destroy_static_internal (object);

    memory_deallocate (object);
}

static inline uint64_t object_get_data_internal (p_object_t object)
{
    return object->data;
}    

static inline p_class_t object_get_class_internal (p_object_t object)
{
    return reference_acquire_internal (object->class);
}
    
static inline p_interface_t object_get_interface_by_id_internal (
    p_object_t object, interface_id_t interface_id)
{
    return class_get_interface_by_id_internal (object->class, 
        interface_id);
}

static inline p_event_supplier_interface_t 
    object_get_event_supplier_interface_by_id_internal (
        p_object_t object, id_t event_class_id)
{
    return class_get_event_supplier_interface_by_id_internal (object->class,
        event_class_id);
}                    

static inline p_event_consumer_interface_t 
    object_get_event_consumer_interface_by_id_internal (
        p_object_t object, id_t event_class_id)
{
    return class_get_event_consumer_interface_by_id_internal (object->class,
        event_class_id);
}                    

static inline p_security_t object_get_security_internal (p_object_t object)
{
    if (object->security == NULL)
    {
        return NULL;
    }
        
    return reference_acquire_internal (object->security);
}

static inline void object_set_security_internal (p_object_t object, 
    p_security_t security)
{
    if (object->security != NULL)
    {
        reference_release_internal (object->security);
    }    
    
    if (security != NULL)
    {
        object->security = reference_acquire_internal (security);
    }    
}


static inline void object_create_handle_internal (p_object_t object UNUSED, 
    handle_reference_t handle UNUSED, sequence_t parameters UNUSED)
{
//    class_create_handle_internal (object->class, object->data, handle,
//        parameters);
}    

static inline void object_destroy_handle_internal (p_object_t object UNUSED, 
    handle_reference_t handle UNUSED)
{
//    class_destroy_handle_internal (object->class, object->data, handle);
}


static inline void object_create_event_supplier_internal (p_object_t object,
    p_event_supplier_t event_supplier, sequence_t parameters)
{
    class_create_event_supplier_internal (object->class, object, event_supplier, 
        parameters);
}

static inline void object_destroy_event_supplier_internal (p_object_t object UNUSED, 
    event_supplier_reference_t event_supplier UNUSED)
{
}
    
static inline void object_create_event_consumer_internal (p_object_t object UNUSED, 
    p_event_consumer_t event_consumer UNUSED, sequence_t parameters UNUSED)
{
//    class_create_event_consumer_internal (object->class, event_consumer, 
//        parameters);
}

#endif /* !REPOSITORY_OBJECT_INTERNAL_H */

