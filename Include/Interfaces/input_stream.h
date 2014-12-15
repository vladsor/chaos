#ifndef __INTERFACE_INPUT_STREAM_H__
#define __INTERFACE_INPUT_STREAM_H__

#define IID_INPUT_STREAM 0x00000A02

enum
{
    MID_INPUT_STREAM_READ,
    
    NUMBER_OF_INPUT_STREAM_METHODS,
};

typedef return_t (input_stream_read_function_t) (context_t *context, 
    uint8_t *data, uint32_t count);
    
typedef struct
{
    input_stream_read_function_t *read;
} input_stream_interface_t;

typedef struct
{
    input_stream_read_function_t *function;
    method_id_t method_id;
    uint32_t parameters_size;

    uint32_t number_of_parameters;

    parameter_t parameters[2];

} input_stream_read_method_t;

typedef struct
{
    uint8_t *data;
    uint32_t count;
} input_stream_read_parameters_t;

#define INPUT_STREAM_READ_METHOD(function) \
    (&(function)), \
    (MID_INPUT_STREAM_READ), \
    (sizeof (input_stream_read_parameters_t)), \
    (2), \
    { \
        {sizeof (uint8_t *)}, \
        {sizeof (uint32_t)}, \
    }
    
#define input_stream$read(handle,data,count) \
    ((input_stream_interface_t *) ((handle)->functions))->read ( \
        &((handle)->context), \
        (data), (count))

#endif /* !__INTERFACE_INPUT_STREAM_H__ */
