#include <enviroment.h>

#include <Interfaces/console_control.h>
#include "Include/console_control_interface.h"

#define DEBUG_MODULE_NAME "ConsoleControl"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>
#include <exception/macros.h>

static void output_wrapper (uint64_t function, context_t context, 
    sequence_t parameters_in, sequence_t parameters_inout UNUSED, 
    sequence_t parameters_out UNUSED)
{
    p_console_control_output_t output;

    wchar_t *text;
    
    output = (p_console_control_output_t) (address_t) function;
    
    text = (wchar_t *) ((uint32_t *) parameters_in.data)[0];
        
    output (context, (const wchar_t *) text);
}

static description_reference_t method_description_output;

static method_reference_t methods[METHOD_CONSOLE_CONTROL_NUMBER];
static sequence_t method_seq = {data: methods, 
    count: METHOD_CONSOLE_CONTROL_NUMBER};

static description_reference_t interface_description;

interface_reference_t console_control_interface_register (
    p_console_control_interface_table_t table UNUSED)
{
    sequence_t empty_seq = {data: NULL, count: 0};
    interface_reference_t interface;

    method_description_output = method_description_register (
        METHOD_CONSOLE_CONTROL_OUTPUT_ID,
        L"output",
        METHOD_TYPE_DYNAMIC,
        NULL,
        empty_seq,
        empty_seq);

    methods[METHOD_CONSOLE_CONTROL_OUTPUT_ID] = method_create_dynamic (
        method_description_output, REFERENCE_NULL, MEMORY_CURRENT,
        &output_wrapper, (address_t) table->output, 0);

    interface_description = interface_description_register (
        INTERFACE_CONSOLE_CONTROL_ID,
        L"console_control",
        INTERFACE_TYPE_DYNAMIC,
        empty_seq);

    interface = interface_create (interface_description, method_seq, 
        REFERENCE_NULL, 0);
    
    return interface;
}



