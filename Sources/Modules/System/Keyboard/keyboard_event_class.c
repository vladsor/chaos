#include <enviroment.h>
#include <unicode.h>

#include <EventClasses/keyboard.h>

#include "Include/keyboard_event_class.h"

#define DEBUG_MODULE_NAME "KeyboardEventClass"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL 11
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

static description_reference_t keyboard_description = REFERENCE_NULL;

description_reference_t keyboard_description_register (void)
{
    keyboard_description = event_description_register (
        EVENT_CLASS_KEYBOARD_ID, 
        L"keyboard",
        sizeof (keyboard_event_data_t));

    return keyboard_description;
}

static bool supplier_handler_wrapper (uint64_t function, context_t context, 
    sequence_t parameters_out)
{
    p_keyboard_supplier_handler_t handler;
    p_keyboard_event_data_t event_data;
    bool fired;
    
    handler = (p_keyboard_supplier_handler_t) (address_t) function;
    
    event_data = (p_keyboard_event_data_t) 
        ((p_uint32_t) parameters_out.data)[0];
    
    fired = handler (context, event_data);
    
//    ((p_uint32_t) return_value.data)[0] = fired;
    return fired;
}

event_supplier_interface_reference_t keyboard_supplier_interface_register (
    uint32_t type, p_keyboard_supplier_handler_t handler, cpu_reference_t cpu,
    reference_t factory)
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
            L"keyboard_supplier_handler",
            METHOD_TYPE_DYNAMIC,
            NULL,
            empty_seq,
            empty_seq);
        
        method = method_create_event_supplier_handler (
            method_description, computer, MEMORY_CURRENT, 
            &supplier_handler_wrapper, (address_t) handler, 0);
    }
    
    if (keyboard_description == REFERENCE_NULL)
    {
        keyboard_description_register ();
    }
        
    supplier_interface = event_supplier_interface_create (keyboard_description,
        type, method, 0);
    
    event_supplier_interface_set_factory (supplier_interface, factory);
    
    return supplier_interface;
}

static void consumer_handler_wrapper (uint64_t function, context_t context, 
    sequence_t parameters_in)
{
    p_keyboard_consumer_handler_t handler;
    p_keyboard_event_data_t event_data;
    
    handler = (p_keyboard_consumer_handler_t) (address_t) function;
    
    event_data = (p_keyboard_event_data_t) ((p_uint32_t) parameters_in.data)[0];
    
    handler (context, event_data);
}

event_consumer_interface_reference_t keyboard_consumer_interface_register (
    uint32_t type, p_keyboard_consumer_handler_t handler, cpu_reference_t cpu,
    reference_t factory)
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
            L"keyboard_consumer_handler",
            METHOD_TYPE_DYNAMIC,
            NULL,
            empty_seq,
            empty_seq);
        
        method = method_create_event_consumer_handler (
            method_description, computer, MEMORY_CURRENT, 
            &consumer_handler_wrapper, (address_t) handler, 0);
    }
    
    if (keyboard_description == REFERENCE_NULL)
    {
        keyboard_description_register ();
    }
        
    consumer_interface = event_consumer_interface_create (keyboard_description,
        type, method, 0);

    event_consumer_interface_set_factory (consumer_interface, factory);
    
    return consumer_interface;
}


