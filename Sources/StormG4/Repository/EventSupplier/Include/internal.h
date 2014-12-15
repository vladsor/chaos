#ifndef REPOSITORY_EVENT_SUPPLIER_INTERNAL_H
#define REPOSITORY_EVENT_SUPPLIER_INTERNAL_H

static inline p_event_supplier_t event_supplier_create_static_internal (
    p_event_supplier_t event_supplier, 
    sequence_t parameters, uint32_t options UNUSED)
{
    reference_acquire_internal (event_supplier->object);
    reference_acquire_internal (event_supplier->interface);

    reference_create_internal (&event_supplier->header, 
        REFERENCE_TYPE_EVENT_SUPPLIER);
    
    object_create_event_supplier_internal (event_supplier->object, 
        event_supplier, parameters);

    return event_supplier;
}

static inline void event_supplier_destroy_static_internal (
    p_event_supplier_t event_supplier)
{
    object_destroy_event_supplier_internal (event_supplier->object, 
        event_supplier);

    reference_destroy_internal (event_supplier);

    reference_release_internal (event_supplier->interface);
    reference_release_internal (event_supplier->object);
}

static inline p_event_consumer_t event_consumer_create_static_internal (
    p_event_consumer_t event_consumer, 
    sequence_t parameters UNUSED, uint32_t options UNUSED)
{
    reference_acquire_internal (event_consumer->object);
    reference_acquire_internal (event_consumer->interface);

    reference_create_internal (&event_consumer->header, 
        REFERENCE_TYPE_EVENT_CONSUMER);
    
//    object_create_event_consumer_internal (event_supplier->object, 
//        event_consumer, parameters);

    return event_consumer;
}

#endif /* !REPOSITORY_EVENT_SUPPLIER_INTERNAL_H */

