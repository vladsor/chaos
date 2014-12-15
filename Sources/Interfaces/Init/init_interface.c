#include <enviroment.h>

#include <Interfaces/init.h>
#include "init_interface.h"

#define DEBUG_MODULE_NAME "Repository"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>
#include <exception/macros.h>

static void init_wrapper (uint64_t function, context_t context, 
    sequence_t parameters_in UNUSED, sequence_t parameters_inout UNUSED, 
    sequence_t parameters_out UNUSED)
{
    p_kernel_control_init_t init;
    
    init = (p_kernel_control_init_t) (address_t) function;
    
    init (context);
}

static void start_wrapper (uint64_t function, context_t context,
    sequence_t parameters_in UNUSED, sequence_t parameters_inout UNUSED,
    sequence_t parameters_out UNUSED)
{
    p_kernel_control_start_t start;

    start = (p_kernel_control_start_t) (address_t) function;

    start (context);
}

static void stop_wrapper (uint64_t function, context_t context,
    sequence_t parameters_in UNUSED, sequence_t parameters_inout UNUSED,
    sequence_t parameters_out UNUSED)
{
    p_kernel_control_stop_t stop;

    stop = (p_kernel_control_stop_t) (address_t) function;

    stop (context);
}

static description_reference_t method_description_init;
static description_reference_t method_description_start;
static description_reference_t method_description_stop;

static method_reference_t methods[METHOD_KERNEL_CONTROL_NUMBER];
static sequence_t method_seq = {data: methods,
    count: METHOD_KERNEL_CONTROL_NUMBER};

static description_reference_t interface_description;

interface_reference_t kernel_control_interface_register (
    p_kernel_control_interface_table_t table)
{
    sequence_t empty_seq = {data: NULL, count: 0};
    interface_reference_t interface;
    
    method_description_init = method_description_register (
        METHOD_KERNEL_CONTROL_INIT_ID,
        L"init",
        METHOD_TYPE_DYNAMIC,
        NULL,
        empty_seq,
        empty_seq);

    methods[METHOD_KERNEL_CONTROL_INIT_ID] = method_create_dynamic (
        method_description_init, REFERENCE_NULL, MEMORY_CURRENT, 
        &init_wrapper, (address_t) table->init, 0);


    method_description_start = method_description_register (
        METHOD_KERNEL_CONTROL_START_ID,
        L"start",
        METHOD_TYPE_DYNAMIC,
        NULL,
        empty_seq,
        empty_seq);

    methods[METHOD_KERNEL_CONTROL_START_ID] = method_create_dynamic (
        method_description_start, REFERENCE_NULL, MEMORY_CURRENT,
        &start_wrapper, (address_t) table->start, 0);

    method_description_stop = method_description_register (
        METHOD_KERNEL_CONTROL_STOP_ID,
        L"stop",
        METHOD_TYPE_DYNAMIC,
        NULL,
        empty_seq,
        empty_seq);

    methods[METHOD_KERNEL_CONTROL_STOP_ID] = method_create_dynamic (
        method_description_stop, REFERENCE_NULL, MEMORY_CURRENT,
        &stop_wrapper, (address_t) table->stop, 0);

    interface_description = interface_description_register (
        INTERFACE_KERNEL_CONTROL_ID,
        L"kernel_control",
        INTERFACE_TYPE_DYNAMIC,
        empty_seq);
    
    interface = interface_create (interface_description, method_seq, 
        REFERENCE_NULL, 0);
    
    return interface;
}

