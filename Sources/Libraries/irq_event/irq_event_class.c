#include <enviroment.h>

#include <EventClasses/irq.h>

#include "Include/irq_event_class.h"

#define DEBUG_MODULE_NAME L"IrqEventClass"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL 11
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include <debug/macros.h>
#include <exception/macros.h>

static description_reference_t irq_description = REFERENCE_NULL;

description_reference_t irq_description_register (void)
{
    irq_description = event_description_register (
        EVENT_CLASS_IRQ_ID, 
        L"irq",
        0);

    return irq_description;
}

static bool supplier_handler_wrapper (uint64_t function, context_t context, 
    sequence_t parameters_out UNUSED)
{
    p_irq_supplier_handler_t handler;
    bool fired;
    
    handler = (p_irq_supplier_handler_t) (address_t) function;
    
    fired = handler (context);
    
//    ((p_uint32_t) return_value.data)[0] = fired;
    return fired;
}

event_supplier_interface_reference_t irq_supplier_interface_register (
    uint32_t type, p_irq_supplier_handler_t handler, cpu_reference_t cpu)
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
            L"irq_supplier_handler",
            METHOD_TYPE_EVENT_SUPPLIER_HANDLER,
            NULL,
            empty_seq,
            empty_seq);
        
        method = method_create_event_supplier_handler (
            method_description, computer, MEMORY_CURRENT, 
            &supplier_handler_wrapper, (address_t) handler, 0);

        reference_release (computer);
    }
    
    if (irq_description == REFERENCE_NULL)
    {
        irq_description_register ();
    }
        
    supplier_interface = event_supplier_interface_create (irq_description, 
        type, method, 0);
    
    return supplier_interface;
}

static void consumer_handler_wrapper (uint64_t function, context_t context, 
    sequence_t parameters_in UNUSED)
{
    p_irq_consumer_handler_t handler;
    
    handler = (p_irq_consumer_handler_t) (address_t) function;
    
    handler (context);
}

event_consumer_interface_reference_t irq_consumer_interface_register (
    uint32_t type, p_irq_consumer_handler_t handler, cpu_reference_t cpu)
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
            L"irq_consumer_handler",
            METHOD_TYPE_EVENT_CONSUMER_HANDLER,
            NULL,
            empty_seq,
            empty_seq);
        
        method = method_create_event_consumer_handler (
            method_description, computer, MEMORY_CURRENT, 
            &consumer_handler_wrapper, (address_t) handler, 0);
    }
    
    if (irq_description == REFERENCE_NULL)
    {
        irq_description_register ();
    }
        
    consumer_interface = event_consumer_interface_create (irq_description,
        type, method, 0);
    
    return consumer_interface;
}


