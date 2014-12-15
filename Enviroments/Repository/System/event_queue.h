typedef struct
{
    reference_struct_t header;
    
    p_event_description_t event_class;
    uint32_t type;
    uint32_t capacity;
    
    p_event_supplier_interface_t supplier;
    p_event_consumer_interface_t consumer;
    
    uint32_t buffer_head;
    uint32_t buffer_tail;
    
    countlock_t buffer_count;
    
    uint32_t number_of_losted_events;
    uint32_t last_lost_event_time;

    uint32_t last_fired_event_time;
    
} event_queue_t;

typedef event_queue_t * p_event_queue_t;

