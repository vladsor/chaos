
enum
{
    EVENT_QUEUE_TYPE_ASYNCHRONOUS,
    EVENT_QUEUE_TYPE_SYNCHRONOUS
};

extern event_queue_reference_t event_queue_create (
    description_reference_t event_description, uint32_t type, 
    uint32_t capacity);
    
extern void event_queue_destroy (event_queue_reference_t event_queue);

extern void event_queue_flush (event_queue_reference_t event_queue);

