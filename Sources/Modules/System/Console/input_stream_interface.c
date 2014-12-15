#include <enviroment.h>

#include <Interfaces/input_stream.h>
#include "Include/input_stream_interface.h"

#define DEBUG_MODULE_NAME "InputStream"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include <debug/macros.h>
#include <exception/macros.h>

static void read_wrapper (uint64_t function, context_t context, 
    sequence_t parameters_in UNUSED, sequence_t parameters_inout UNUSED, 
    sequence_t parameters_out)
{
    p_input_stream_read_t read;
    sequence_t block;
    uint32_t count;

    read = (p_input_stream_read_t) (address_t) function;
    
    block.data = (p_void_t) ((p_uint32_t) (parameters_in.data))[1];
    block.count = ((p_uint32_t) (parameters_in.data))[2];

    count = read (context, block);
    
    ((p_uint32_t) (parameters_out.data))[0] = count;
}

static description_reference_t method_description_read;

static method_reference_t methods[METHOD_INPUT_STREAM_NUMBER];
static sequence_t method_seq = {data: methods, 
    count: METHOD_INPUT_STREAM_NUMBER};

static description_reference_t interface_description;

interface_reference_t input_stream_interface_register (
    p_input_stream_interface_table_t table)
{
    sequence_t empty_seq = {data: NULL, count: 0};
    interface_reference_t interface;

    method_description_read = method_description_register (
        METHOD_INPUT_STREAM_READ_ID,
        L"read",
        METHOD_TYPE_DYNAMIC,
        NULL,
        empty_seq,
        empty_seq);
    
    methods[METHOD_INPUT_STREAM_READ_ID] = method_create_dynamic (
        method_description_read, REFERENCE_NULL, MEMORY_CURRENT,
        &read_wrapper, (address_t) table->read, 0);

    interface_description = interface_description_register (
        INTERFACE_INPUT_STREAM_ID,
        L"input_stream",
        INTERFACE_TYPE_DYNAMIC,
        empty_seq);

    interface = interface_create (interface_description, method_seq, 
        REFERENCE_NULL, 0);
    
    return interface;
}

