#include <enviroment.h>

#include <Interfaces/storm_module_control.h>
#include "storm_module_control_interface.h"

#define DEBUG_MODULE_NAME "StormModuleControl"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>
#include <exception/macros.h>

static void start_wrapper (uint64_t function, context_t context, 
    sequence_t parameters_in, sequence_t parameters_inout UNUSED,
    sequence_t parameters_out)
{
    p_storm_module_control_start_t start;
    return_t return_value;
    uint32_t argc;
    char **argv;
    char **envp;
    
    start = (p_storm_module_control_start_t) (address_t) function;
    
    argc = (uint32_t) ((uint32_t *) parameters_in.data)[0];
    argv = (char **) ((uint32_t *) parameters_in.data)[1];
    envp = (char **) ((uint32_t *) parameters_in.data)[2];
        
    return_value = start (context, argc, argv, envp);
    
    (uint32_t) ((uint32_t *) parameters_out.data)[0] = return_value;
}

static void stop_wrapper (uint64_t function, context_t context, 
    sequence_t parameters_in UNUSED, sequence_t parameters_inout UNUSED,
    sequence_t parameters_out)
{
    p_storm_module_control_stop_t stop;
    return_t return_value;
    
    stop = (p_storm_module_control_stop_t) (address_t) function;
    
    return_value = stop (context);
    
    (uint32_t) ((uint32_t *) parameters_out.data)[0] = return_value;
}

static description_reference_t method_description_start;
static description_reference_t method_description_stop;

static method_reference_t methods[METHOD_STORM_MODULE_CONTROL_NUMBER];
static sequence_t method_seq = {data: methods, 
    count: METHOD_STORM_MODULE_CONTROL_NUMBER };

static description_reference_t interface_description;

interface_reference_t storm_module_control_interface_register (
    p_storm_module_control_interface_table_t table)
{
    sequence_t empty_seq = {data: NULL, count: 0};
    interface_reference_t interface;
    
    method_description_start = method_description_register (
        METHOD_STORM_MODULE_CONTROL_START_ID,
        L"start",
        METHOD_TYPE_DYNAMIC,
        NULL,
        empty_seq,
        empty_seq);

    methods[METHOD_STORM_MODULE_CONTROL_START_ID] = method_create_dynamic (
        method_description_start, REFERENCE_NULL, MEMORY_CURRENT, 
        &start_wrapper, (address_t) table->start, 0);

    method_description_stop = method_description_register (
        METHOD_STORM_MODULE_CONTROL_STOP_ID,
        L"stop",
        METHOD_TYPE_DYNAMIC,
        NULL,
        empty_seq,
        empty_seq);

    methods[METHOD_STORM_MODULE_CONTROL_STOP_ID] = method_create_dynamic (
        method_description_stop, REFERENCE_NULL, MEMORY_CURRENT, 
        &stop_wrapper, (address_t) table->stop, 0);

    interface_description = interface_description_register (
        INTERFACE_STORM_MODULE_CONTROL_ID,
        L"storm_module_control",
        INTERFACE_TYPE_DYNAMIC,
        empty_seq);
    
    interface = interface_create (interface_description, method_seq, 
        REFERENCE_NULL, 0);
    
    return interface;
}



