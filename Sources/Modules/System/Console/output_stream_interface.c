#include <enviroment.h>

#include <Interfaces/output_stream.h>
#include "Include/output_stream_interface.h"

#define DEBUG_MODULE_NAME "OutputStream"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include <debug/macros.h>
#include <exception/macros.h>

static void write_wrapper (uint64_t function, context_t context, 
    sequence_t parameters_in, sequence_t parameters_inout UNUSED, 
    sequence_t parameters_out)
{
    p_output_stream_write_t write;
    sequence_t block;
    uint32_t count;

    write = (p_output_stream_write_t) (address_t) function;
    
    block.data = (p_void_t) ((p_uint32_t) (parameters_in.data))[0];
    block.count = ((p_uint32_t) (parameters_in.data))[1];

    count = write (context, block);
    
    ((p_uint32_t) (parameters_out.data))[0] = count;
}

static description_reference_t method_description_write;

static method_reference_t methods[METHOD_OUTPUT_STREAM_NUMBER];
static sequence_t method_seq = {data: methods, 
    count: METHOD_OUTPUT_STREAM_NUMBER};

static description_reference_t interface_description;

interface_reference_t output_stream_interface_register (
    p_output_stream_interface_table_t table)
{
    sequence_t empty_seq = {data: NULL, count: 0};
    interface_reference_t interface;

    method_description_write = method_description_register (
        METHOD_OUTPUT_STREAM_WRITE_ID,
        L"write",
        METHOD_TYPE_DYNAMIC,
        NULL,
        empty_seq,
        empty_seq);
    
    methods[METHOD_OUTPUT_STREAM_WRITE_ID] = method_create_dynamic (
        method_description_write, REFERENCE_NULL, MEMORY_CURRENT,
        &write_wrapper, (address_t) table->write, 0);

    interface_description = interface_description_register (
        INTERFACE_OUTPUT_STREAM_ID,
        L"output_stream",
        INTERFACE_TYPE_DYNAMIC,
        empty_seq);

    interface = interface_create (interface_description, method_seq, 
        REFERENCE_NULL, 0);
    
    return interface;
}

