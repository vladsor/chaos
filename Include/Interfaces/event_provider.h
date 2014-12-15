
#ifndef __INTERFACE_EVENT_PROVIDER_H__
#define __INTERFACE_EVENT_PROVIDER_H__

#define IID_EVENT_PROVIDER 0x00000C03

enum
{
    MID_EVENT_PROVIDER_WRITE,
    MID_EVENT_PROVIDER_GET_NUMBER_OF_WAITING_EVENTS,
};

typedef return_t (event_provider_write_function_t) (context_t *context, 
    uint8_t *event_data);

typedef struct
{
    event_provider_write_function_t *write;
/*    
    event_provider_get_number_of_waiting_events_function_t 
        *get_number_of_waiting_events;
*/    
} event_provider_interface_t;

typedef struct
{
    event_provider_write_function_t *function;
    method_id_t method_id;
    uint32_t parameters_size;

    uint32_t number_of_parameters;

    parameter_t parameters[1];

} event_provider_write_method_t;

typedef struct
{
    uint8_t *data;
} event_provider_write_parameters_t;

#define EVENT_PROVIDER_WRITE_METHOD(function) \
    (&(function)), \
    (MID_EVENT_PROVIDER_WRITE), \
    (sizeof (event_provider_write_parameters_t)), \
    (1), \
    { \
        {sizeof (uint8_t *)}, \
    }


#define event_provider$write(handle,data) \
    ((event_provider_interface_t *) ((handle)->functions))->write ( \
        &((handle)->context), \
        (data))

#endif /* !__INTERFACE_EVENT_PROVIDER_H__ */
