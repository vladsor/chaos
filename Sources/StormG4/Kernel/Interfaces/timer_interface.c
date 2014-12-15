#include <enviroment.h>

#include <Interfaces/timer.h>
#include "timer_interface.h"

#define DEBUG_MODULE_NAME "Kernel{Timer}"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>
#include <exception/macros.h>

static void read_milli_wrapper (uint64_t function, context_t context, 
    sequence_t parameters_in UNUSED, sequence_t parameters_inout UNUSED, 
    sequence_t parameters_out)
{
    uint32_t milli;
    p_timer_read_milli_t read_milli;
    
    read_milli = (p_timer_read_milli_t) (address_t) function;
    
    milli = read_milli (context);
    
    ((p_uint32_t) parameters_out.data)[0] = milli;
}

static description_reference_t method_description_read_milli;

static method_reference_t methods[METHOD_TIMER_NUMBER];
static sequence_t method_seq = {data: methods, count: METHOD_TIMER_NUMBER};

static description_reference_t interface_description;

interface_reference_t timer_interface_register (
    p_timer_interface_table_t table)
{
    sequence_t empty_seq = {data: NULL, count: 0};
    interface_reference_t interface;
    
    method_description_read_milli = method_description_register (
        METHOD_TIMER_READ_MILLI_ID,
        L"read_milli",
        METHOD_TYPE_DYNAMIC,
        NULL,
        empty_seq,
        empty_seq);

    methods[METHOD_TIMER_READ_MILLI_ID] = method_create_dynamic (
        method_description_read_milli, REFERENCE_NULL, MEMORY_CURRENT, 
        &read_milli_wrapper, (address_t) table->read_milli, 0);

    interface_description = interface_description_register (
        INTERFACE_TIMER_ID,
        L"timer",
        INTERFACE_TYPE_DYNAMIC,
        empty_seq);
    
    interface = interface_create (interface_description, method_seq, 
        REFERENCE_NULL, 0);
    
    return interface;
}

