#ifndef __INTERFACE_OUTPUT_STREAM_H__
#define __INTERFACE_OUTPUT_STREAM_H__

#define IID_OUTPUT_STREAM 0x00000A03

enum
{
    MID_OUTPUT_STREAM_WRITE,

    NUMBER_OF_OUTPUT_STREAM_METHODS,
};

typedef return_t (output_stream_write_function_t) (context_t *context, 
    uint8_t *data, uint32_t count);
    
typedef struct
{
    output_stream_write_function_t *write;
} output_stream_interface_t;

typedef struct
{
    output_stream_write_function_t *function;
    method_id_t method_id;
    uint32_t parameters_size;

    uint32_t number_of_parameters;

    parameter_t parameters[2];

} output_stream_write_method_t;

typedef struct
{
    uint8_t *data;
    uint32_t count;
} output_stream_write_parameters_t;

#define OUTPUT_STREAM_WRITE_METHOD(function) \
    (&(function)), \
    (MID_OUTPUT_STREAM_WRITE), \
    (sizeof (output_stream_write_parameters_t)), \
    (2), \
    { \
        {sizeof (uint8_t *)}, \
        {sizeof (uint32_t)}, \
    }
    
#define output_stream$write(handle,data,count) \
    ((output_stream_interface_t *) ((handle)->functions))->write ( \
        &((handle)->context), \
        (data), (count))

#endif /* !__INTERFACE_OUTPUT_STREAM_H__ */

