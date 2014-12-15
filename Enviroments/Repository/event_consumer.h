// Dynamic
extern event_consumer_reference_t event_consumer_create (
    object_reference_t object_reference, 
    event_id_t event_class_id, 
    sequence_t parameters, 
    uint32_t options);

extern void event_consumer_destroy (
    event_consumer_reference_t reference);

extern void event_consumer_wait_event (
    event_consumer_reference_t reference, 
    sequence_t event_data, uint32_t options);

extern void event_consumer_set_queue (
    event_consumer_reference_t event_consumer_reference,
    event_queue_reference_t event_queue_reference);

