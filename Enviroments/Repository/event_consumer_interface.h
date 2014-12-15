
enum
{
    EVENT_CONSUMER_TYPE_NONE,
    EVENT_CONSUMER_TYPE_PUSH,
    EVENT_CONSUMER_TYPE_PULL,
};    

enum
{
	METHOD_EVENT_CONSUMER_HANDLER_ID,
};

// Static
extern event_consumer_interface_reference_t event_consumer_interface_create_static (
    p_event_consumer_interface_t event_consumer_interface);
     
extern void event_consumer_interface_destroy_static (
    event_consumer_interface_reference_t event_consumer_interface);

// Dynamic
extern 
    event_consumer_interface_reference_t 
        event_consumer_interface_create 
        (
//            uint32_t consumer_id,
            event_class_reference_t event_class, 
            int type, 
            method_reference_t handle,
//            reference_t event_consumer_factory,
            uint32_t options
        );

extern 
    void 
        event_consumer_interface_destroy 
        (
            event_consumer_interface_reference_t 
                event_consumer_interface_reference
        );

extern 
    void 
        event_consumer_interface_wait 
        (
            event_consumer_interface_reference_t 
                event_consumer_interface_reference, 
            context_t context, 
            event_queue_reference_t event_queue,
            sequence_t event_data
        );

extern 
    void 
        event_consumer_interface_set_factory 
        (
            event_consumer_interface_reference_t 
                event_consumer_interface_reference,
            reference_t factory
        );

