#include <enviroment.h>
#include <unicode.h>

#include <EventClasses/mouse.h>

#include "Include/mouse_event_class.h"

#define DEBUG_MODULE_NAME "MouseEventClass"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL 11
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

static description_reference_t mouse_description = REFERENCE_NULL;

description_reference_t mouse_description_register (void)
{
    mouse_description = event_description_register (
        EVENT_CLASS_MOUSE_ID, 
        L"mouse",
        sizeof (uint32_t) + sizeof (uint32_t) + sizeof (uint32_t));

    return mouse_description;
}

static bool supplier_handler_wrapper (uint64_t function, context_t context, 
    sequence_t parameters_out)
{
    p_mouse_supplier_handler_t handler;
    p_uint32_t p_x;
    p_uint32_t p_y;
    p_uint32_t p_button;
    bool fired;
    
    handler = (p_mouse_supplier_handler_t) (address_t) function;
    
    p_x = (p_uint32_t) ((p_uint32_t) parameters_out.data)[0];
    p_y = (p_uint32_t) ((p_uint32_t) parameters_out.data)[1];
    p_button = (p_uint32_t) ((p_uint32_t) parameters_out.data)[2];
    
    fired = handler (context, p_x, p_y, p_button);
    
//    ((p_uint32_t) return_value.data)[0] = fired;
    return fired;
}

event_supplier_interface_reference_t mouse_supplier_interface_register (
    uint32_t type, p_mouse_supplier_handler_t handler, cpu_reference_t cpu,
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
            L"mouse_supplier_handler",
            METHOD_TYPE_DYNAMIC,
            NULL,
            empty_seq,
            empty_seq);
        
        method = method_create_event_supplier_handler (
            method_description, computer, MEMORY_CURRENT, 
            &supplier_handler_wrapper, (address_t) handler, 0);
    }
    
    if (mouse_description == REFERENCE_NULL)
    {
        mouse_description_register ();
    }
        
    supplier_interface = event_supplier_interface_create (mouse_description,
        type, method, 0);

    event_supplier_interface_set_factory (supplier_interface, factory);
    
    return supplier_interface;
}

static void consumer_handler_wrapper (uint64_t function, context_t context, 
    sequence_t parameters_in)
{
    p_mouse_consumer_handler_t handler;
    uint32_t x;
    uint32_t y;
    uint32_t button;
    
    handler = (p_mouse_consumer_handler_t) (address_t) function;
    
    x = ((p_uint32_t) parameters_in.data)[0];
    y = ((p_uint32_t) parameters_in.data)[1];
    button = ((p_uint32_t) parameters_in.data)[2];
    
    handler (context, x, y, button);
}

event_consumer_interface_reference_t mouse_consumer_interface_register (
    uint32_t type, p_mouse_consumer_handler_t handler, cpu_reference_t cpu,
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
            L"mouse_consumer_handler",
            METHOD_TYPE_DYNAMIC,
            NULL,
            empty_seq,
            empty_seq);
        
        method = method_create_event_consumer_handler (
            method_description, computer, MEMORY_CURRENT, 
            &consumer_handler_wrapper, (address_t) handler, 0);
    }
    
    if (mouse_description == REFERENCE_NULL)
    {
        mouse_description_register ();
    }
        
    consumer_interface = event_consumer_interface_create (mouse_description,
        type, method, 0);

    event_consumer_interface_set_factory (consumer_interface, factory);
    
    return consumer_interface;
}


