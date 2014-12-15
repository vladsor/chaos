#include <enviroment.h>

#include <Interfaces/block.h>
#include "Include/block_interface.h"

#define DEBUG_MODULE_NAME "Block"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include <debug/macros.h>
#include <exception/macros.h>

static void read_wrapper (uint64_t function, context_t context, 
    sequence_t parameters_in, sequence_t parameters_inout UNUSED, 
    sequence_t parameters_out)
{
    p_block_read_t read;
    sequence_t blocks;
    uint32_t start;
    uint32_t count;

    read = (p_block_read_t) (address_t) function;
    
    start = ((p_uint32_t) (parameters_in.data))[0];

    blocks.data = (p_void_t) ((p_uint32_t) (parameters_out.data))[1];
    blocks.count = ((p_uint32_t) (parameters_out.data))[2];
    
    count = read (context, blocks, start);
    
    ((p_uint32_t) (parameters_out.data))[0] = count;
}

static void write_wrapper (uint64_t function, context_t context, 
    sequence_t parameters_in, sequence_t parameters_inout UNUSED, 
    sequence_t parameters_out)
{
    p_block_write_t write;
    sequence_t blocks;
    uint32_t start;
    uint32_t count;

    write = (p_block_write_t) (address_t) function;
    
    blocks.data = (p_void_t) ((p_uint32_t) (parameters_in.data))[0];
    blocks.count = ((p_uint32_t) (parameters_in.data))[1];
    start = ((p_uint32_t) (parameters_in.data))[2];

    count = write (context, blocks, start);

    ((p_uint32_t) (parameters_out.data))[0] = count;
}

static description_reference_t method_description_read;
static description_reference_t method_description_write;

static method_reference_t methods[METHOD_BLOCK_NUMBER];
static sequence_t method_seq = {data: methods, count: METHOD_BLOCK_NUMBER};

static description_reference_t interface_description;

interface_reference_t block_interface_register (
    p_block_interface_table_t table)
{
    sequence_t empty_seq = {data: NULL, count: 0};
    interface_reference_t interface;

    method_description_read = method_description_register (
        METHOD_BLOCK_READ_ID,
        L"read",
        METHOD_TYPE_DYNAMIC,
        NULL,
        empty_seq,
        empty_seq);
    
    methods[METHOD_BLOCK_READ_ID] = method_create_dynamic (
        method_description_read, REFERENCE_NULL, MEMORY_CURRENT,
        &read_wrapper, (address_t) table->read, 0);

    method_description_write = method_description_register (
        METHOD_BLOCK_WRITE_ID,
        L"write",
        METHOD_TYPE_DYNAMIC,
        NULL,
        empty_seq,
        empty_seq);
    
    methods[METHOD_BLOCK_WRITE_ID] = method_create_dynamic (
        method_description_write, REFERENCE_NULL, MEMORY_CURRENT,
        &write_wrapper, (address_t) table->write, 0);

    interface_description = interface_description_register (
        INTERFACE_BLOCK_ID,
        L"block",
        INTERFACE_TYPE_DYNAMIC,
        empty_seq);

    interface = interface_create (interface_description, method_seq, 
        REFERENCE_NULL, 0);
    
    return interface;
}

