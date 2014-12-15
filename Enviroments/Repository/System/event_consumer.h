typedef struct
{
    reference_struct_t header;

    uint64_t data;
    p_object_t object;
    p_event_consumer_interface_t interface;
    p_event_queue_t queue;
    
} event_consumer_t;

typedef event_consumer_t * p_event_consumer_t;
typedef p_event_consumer_t * p_p_event_consumer_t;

