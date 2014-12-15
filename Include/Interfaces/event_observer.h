
#ifndef __INTERFACE_EVENT_OBSERVER_H__
#define __INTERFACE_EVENT_OBSERVER_H__

#define IID_EVENT_OBSERVER 0x00000C02

enum
{
    MID_EVENT_OBSERVER_READ,
    MID_EVENT_OBSERVER_PEEK,
    MID_EVENT_OBSERVER_GET_NUMBER_OF_WAITING_EVENTS,
};

typedef return_t (event_observer_read_function_t) (context_t *context, 
    uint8_t *data);
typedef return_t (event_observer_peek_function_t) (context_t *context, 
    uint8_t *data);

typedef struct
{
    event_observer_read_function_t *read;
    event_observer_peek_function_t *peek;
/*    
    event_observer_get_number_of_waiting_events_function_t 
        *get_number_of_waiting_events;
*/    
} event_observer_interface_t;

typedef struct
{
    event_observer_read_function_t *function;
    method_id_t method_id;
    uint32_t parameters_size;

    uint32_t number_of_parameters;

    parameter_t parameters[1];

} event_observer_read_method_t;

typedef struct
{
    uint8_t *data;
} event_observer_read_parameters_t;

#define EVENT_OBSERVER_READ_METHOD(function) \
    (&(function)), \
    (MID_EVENT_OBSERVER_READ), \
    (sizeof (event_observer_read_parameters_t)), \
    (1), \
    { \
        {sizeof (uint8_t *)}, \
    }
    
typedef struct
{
    event_observer_read_function_t *function;
    method_id_t method_id;
    uint32_t parameters_size;

    uint32_t number_of_parameters;

    parameter_t parameters[1];

} event_observer_peek_method_t;

typedef struct
{
    uint8_t *data;
} event_observer_peek_parameters_t;

#define EVENT_OBSERVER_PEEK_METHOD(function) \
    (&(function)), \
    (MID_EVENT_OBSERVER_READ), \
    (sizeof (event_observer_peek_parameters_t)), \
    (1), \
    { \
        {sizeof (uint8_t *)}, \
    }
    

#define event_observer$read(handle,data) \
    ((event_observer_interface_t *) ((handle)->functions))->read ( \
        &((handle)->context), \
        (data))

#define event_observer$peek(handle,data) \
    ((event_observer_interface_t *) ((handle)->functions))->peek ( \
        &((handle)->context), \
        (data))

#endif /* !__INTERFACE_EVENT_OBSERVER_H__ */
