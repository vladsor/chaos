#ifndef __INTERFACE_OUTPUT_STREAM_H__
#define __INTERFACE_OUTPUT_STREAM_H__

#define INTERFACE_OUTPUT_STREAM_ID 0x00023

enum
{
    METHOD_OUTPUT_STREAM_WRITE_ID,

    METHOD_OUTPUT_STREAM_NUMBER,
};

typedef uint32_t (output_stream_write_t) (context_t context, 
    sequence_t block);
typedef output_stream_write_t * p_output_stream_write_t;
    
typedef struct
{
    p_output_stream_write_t write;
    
} output_stream_interface_table_t;

typedef output_stream_interface_table_t * p_output_stream_interface_table_t;

#endif /* !__INTERFACE_OUTPUT_STREAM_H__ */

