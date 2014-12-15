#include <enviroment.h>
#include <unicode.h>

#include <EventClasses/debug.h>

#include "Include/debug_event_class.h"

#define DEBUG_MODULE_NAME "DebugEventClass"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL 11
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

static description_reference_t debug_description = REFERENCE_NULL;

description_reference_t debug_description_register (void)
{
    debug_description = event_description_register (
        EVENT_CLASS_DEBUG_ID, 
        L"debug",
        sizeof (debug_event_data_t));

    return debug_description;
}

static bool supplier_handler_wrapper (uint64_t function, context_t context, 
    sequence_t parameters_out)
{
    p_debug_supplier_handler_t handler;
    
    p_uint32_t p_level;
    wchar_t *module_name;
    wchar_t *function_name;
    p_uint32_t p_line;
    wchar_t *message;
    bool fired;
    
    handler = (p_debug_supplier_handler_t) (address_t) function;
    
    p_level = (p_uint32_t) ((p_uint32_t) parameters_out.data)[0];
    module_name = (wchar_t *) ((p_uint32_t) parameters_out.data)[1];
    function_name = (wchar_t *) ((p_uint32_t) parameters_out.data)[2];
    p_line = (p_uint32_t) ((p_uint32_t) parameters_out.data)[3];
    message = (wchar_t *) ((p_uint32_t) parameters_out.data)[4];
    
    fired = handler (context, p_level, module_name, function_name, p_line, 
        message);
    
//    ((p_uint32_t) return_value.data)[0] = fired;
    return fired;
}

event_supplier_interface_reference_t debug_supplier_interface_register (
    uint32_t type, p_debug_supplier_handler_t handler, cpu_reference_t cpu)
{
    event_supplier_interface_reference_t supplier_interface;
    method_reference_t method = REFERENCE_NULL;
    
    if (handler != NULL)
    {
        computer_reference_t computer = REFERENCE_NULL;
        description_reference_t method_description;
        sequence_t empty_seq = {data: NULL, count: 0};

        if (cpu != REFERENCE_NULL)
        {
            computer = computer_create (cpu, MEMORY_CURRENT, SECURITY_CURRENT);
        }    
        
        method_description = method_description_register (
            METHOD_EVENT_SUPPLIER_HANDLER_ID,
            L"debug_supplier_handler",
            METHOD_TYPE_EVENT_SUPPLIER_HANDLER,
            NULL,
            empty_seq,
            empty_seq);
        
        method = method_create_event_supplier_handler (
            method_description, computer, MEMORY_CURRENT, 
            &supplier_handler_wrapper, (address_t) handler, 0);
    }
    
    if (debug_description == REFERENCE_NULL)
    {
        debug_description_register ();
    }
        
    supplier_interface = event_supplier_interface_create (debug_description,
        type, method, 0);
    
    return supplier_interface;
}

static void consumer_handler_wrapper (uint64_t function, context_t context, 
    sequence_t parameters_in)
{
    p_debug_consumer_handler_t handler;
    uint32_t level;
    wchar_t *module_name;
    wchar_t *function_name;
    uint32_t line;
    wchar_t *message;
    
    handler = (p_debug_consumer_handler_t) (address_t) function;
    
    level = (uint32_t) ((p_uint32_t) parameters_in.data)[0];
    module_name = (wchar_t *) ((p_uint32_t) parameters_in.data)[1];
    function_name = (wchar_t *) ((p_uint32_t) parameters_in.data)[2];
    line = (uint32_t) ((p_uint32_t) parameters_in.data)[3];
    message = (wchar_t *) ((p_uint32_t) parameters_in.data)[4];
    
    handler (context, level, module_name, function_name, line, message);
}

event_consumer_interface_reference_t debug_consumer_interface_register (
    uint32_t type, p_debug_consumer_handler_t handler, cpu_reference_t cpu)
{
    event_consumer_interface_reference_t consumer_interface;
    method_reference_t method = REFERENCE_NULL;
    
    if (handler != NULL)
    {
        computer_reference_t computer = REFERENCE_NULL;
        description_reference_t method_description;
        sequence_t empty_seq = {data: NULL, count: 0};

        if (cpu != REFERENCE_NULL)
        {
            computer = computer_create (cpu, MEMORY_CURRENT, SECURITY_CURRENT);
        }    
        
        method_description = method_description_register (
            METHOD_EVENT_CONSUMER_HANDLER_ID,
            L"debug_consumer_handler",
            METHOD_TYPE_EVENT_CONSUMER_HANDLER,
            NULL,
            empty_seq,
            empty_seq);
        
        method = method_create_event_consumer_handler (
            method_description, computer, MEMORY_CURRENT, 
            &consumer_handler_wrapper, (address_t) handler, 0);
    }
    
    if (debug_description == REFERENCE_NULL)
    {
        debug_description_register ();
    }
        
    consumer_interface = event_consumer_interface_create (debug_description,
        type, method, 0);
    
    return consumer_interface;
}


