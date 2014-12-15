
#ifndef __INTERFACE_INPUT_STREAM_H__
#define __INTERFACE_INPUT_STREAM_H__

#define INTERFACE_INPUT_STREAM_ID 0x00022

enum
{
    METHOD_INPUT_STREAM_READ_ID,
    
    METHOD_INPUT_STREAM_NUMBER,
};

typedef uint32_t (input_stream_read_t) (context_t context, 
    sequence_t block);
typedef input_stream_read_t * p_input_stream_read_t;
    
typedef struct
{
    p_input_stream_read_t read;
    
} input_stream_interface_table_t;

typedef input_stream_interface_table_t * p_input_stream_interface_table_t;

#endif /* !__INTERFACE_INPUT_STREAM_H__ */
