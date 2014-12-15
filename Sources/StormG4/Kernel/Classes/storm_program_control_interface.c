#include <enviroment.h>

#include <Interfaces/storm_program_control.h>
#include "storm_program_control_interface.h"

#define DEBUG_MODULE_NAME "StormProgramControl"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>
#include <exception/macros.h>

static void main_wrapper (uint64_t function, context_t context, 
    sequence_t parameters_in, sequence_t parameters_inout UNUSED,
    sequence_t parameters_out)
{
    p_storm_program_control_main_t main_function;
    return_t return_value;
    uint32_t argc;
    char **argv;
    char **envp;
    
    main_function = (p_storm_program_control_main_t) (address_t) function;
    
    argc = (uint32_t) ((uint32_t *) parameters_in.data)[0];
    argv = (char **) ((uint32_t *) parameters_in.data)[1];
    envp = (char **) ((uint32_t *) parameters_in.data)[2];
        
    return_value = main_function (context, argc, argv, envp);
    
    (uint32_t) ((uint32_t *) parameters_out.data)[0] = return_value;
}

static description_reference_t method_description_main;

static method_reference_t methods[METHOD_STORM_PROGRAM_CONTROL_NUMBER];
static sequence_t method_seq = {data: methods, 
    count: METHOD_STORM_PROGRAM_CONTROL_NUMBER };

static description_reference_t interface_description;

interface_reference_t storm_program_control_interface_register (
    p_storm_program_control_interface_table_t table)
{
    sequence_t empty_seq = {data: NULL, count: 0};
    interface_reference_t interface;
    
    method_description_main = method_description_register (
        METHOD_STORM_PROGRAM_CONTROL_MAIN_ID,
        L"main",
        METHOD_TYPE_DYNAMIC,
        NULL,
        empty_seq,
        empty_seq);

    methods[METHOD_STORM_PROGRAM_CONTROL_MAIN_ID] = method_create_dynamic (
        method_description_main, REFERENCE_NULL, MEMORY_CURRENT, 
        &main_wrapper, (address_t) table->main, 0);

    interface_description = interface_description_register (
        INTERFACE_STORM_PROGRAM_CONTROL_ID,
        L"storm_program_control",
        INTERFACE_TYPE_DYNAMIC,
        empty_seq);
    
    interface = interface_create (interface_description, method_seq, 
        REFERENCE_NULL, 0);
    
    return interface;
}



