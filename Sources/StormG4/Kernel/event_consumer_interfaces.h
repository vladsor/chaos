
typedef event_consumer_reference_t 
    (kernel_event_consumer_init_function_t) (void);
typedef kernel_event_consumer_init_function_t * 
    p_kernel_event_consumer_init_function_t;

enum
{
    KERNEL_EVENT_CONSUMER_INTERFACE_DEBUG_INDEX,
};

typedef struct
{
    const wchar_t *name;
    p_kernel_event_consumer_init_function_t init;
    bool enabled;

} kernel_event_consumer_interface_info_t;

extern kernel_event_consumer_interface_info_t 
    kernel_event_consumers_interface_info[];

extern kernel_event_consumer_init_function_t debug_consumer_init;

