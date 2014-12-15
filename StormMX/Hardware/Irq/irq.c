/**
 * @file                irq.c
 * @brief               IRQ handling.
 * @author              Per Lundberg <per@chaosdev.org>
 * @author              Vladimir Sorokin
 * @version             1.1
 * @date                2000-2004
 */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <enviroment.h>

#include "Include/pic.h"
#include "Include/irq.h"
#include "Include/irq_handlers.h"

//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

p_irq_handler_t irq_handlers[NUMBER_OF_IRQ_CHANNELS];
p_void_t irq_handlers_data[NUMBER_OF_IRQ_CHANNELS];

uint8_t *current_stack_pointer;

/* Initialize IRQ handling. */
return_t irq_init (int argc UNUSED, char *argv[] UNUSED, char **envp UNUSED)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Irq init.\n");

    memory_set_uint32 ((uint32_t *) irq_handlers, (uint32_t) NULL, 
        NUMBER_OF_IRQ_CHANNELS);
    
    pic_init ();

   /* Remap the IRQs to 20-2F. The defaults are Very Bad, since they
      overlap the exceptions... */
    pic_remap_irq (BASE_IRQ);

    /* Set up a handler for the timer. */

    idt_setup_interrupt_gate (IDT_ENTRY_FOR_IRQ ( 0), SELECTOR_KERNEL_CODE,
        (address_t) irq0_handler, 0);

    idt_setup_interrupt_gate (IDT_ENTRY_FOR_IRQ ( 1), SELECTOR_KERNEL_CODE,
        (address_t) irq1_handler, 0);

    /* IRQ 2 is used to connect the two interrupt controllers and can
       not be used as an ordinary IRQ. */

    idt_setup_interrupt_gate (IDT_ENTRY_FOR_IRQ ( 3), SELECTOR_KERNEL_CODE,
        (address_t) irq3_handler, 0);
    idt_setup_interrupt_gate (IDT_ENTRY_FOR_IRQ ( 4), SELECTOR_KERNEL_CODE,
        (address_t) irq4_handler, 0);   
    idt_setup_interrupt_gate (IDT_ENTRY_FOR_IRQ ( 5), SELECTOR_KERNEL_CODE,
        (address_t) irq5_handler, 0);
    idt_setup_interrupt_gate (IDT_ENTRY_FOR_IRQ ( 6), SELECTOR_KERNEL_CODE,
        (address_t) irq6_handler, 0);
    idt_setup_interrupt_gate (IDT_ENTRY_FOR_IRQ ( 7), SELECTOR_KERNEL_CODE,
        (address_t) irq7_handler, 0);
    idt_setup_interrupt_gate (IDT_ENTRY_FOR_IRQ ( 8), SELECTOR_KERNEL_CODE,
        (address_t) irq8_handler, 0);
    idt_setup_interrupt_gate (IDT_ENTRY_FOR_IRQ ( 9), SELECTOR_KERNEL_CODE,
        (address_t) irq9_handler, 0);
    idt_setup_interrupt_gate (IDT_ENTRY_FOR_IRQ (10), SELECTOR_KERNEL_CODE,
        (address_t) irq10_handler, 0);
    idt_setup_interrupt_gate (IDT_ENTRY_FOR_IRQ (11), SELECTOR_KERNEL_CODE,
        (address_t) irq11_handler, 0);
    idt_setup_interrupt_gate (IDT_ENTRY_FOR_IRQ (12), SELECTOR_KERNEL_CODE,
        (address_t) irq12_handler, 0);
    idt_setup_interrupt_gate (IDT_ENTRY_FOR_IRQ (13), SELECTOR_KERNEL_CODE,
        (address_t) irq13_handler, 0);
    idt_setup_interrupt_gate (IDT_ENTRY_FOR_IRQ (14), SELECTOR_KERNEL_CODE,
        (address_t) irq14_handler, 0);
    idt_setup_interrupt_gate (IDT_ENTRY_FOR_IRQ (15), SELECTOR_KERNEL_CODE,
        (address_t) irq15_handler, 0);

    pic_disable_all_irq ();
    
    pic_enable_irq (IRQ_CHANNEL_CASCADE);

    /* Enable interrupts. */
    cpu_interrupts_enable ();
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Irq init end.\n");
    
    return 0;
}

/* Register an IRQ for use by a module. */
return_t irq_register (unsigned int irq_number, p_irq_handler_t function,
    p_void_t parameter)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "Trying to register %i for %p...", irq_number, function);

    /* Make sure the input data is pure. */
    if ((irq_number >= NUMBER_OF_IRQ_CHANNELS) || 
        (irq_number == IRQ_CHANNEL_CASCADE))
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, "Invalid IRQ number.\n");
        
        return STORM_RETURN_INVALID_ARGUMENT;
    }
    
    if (function == NULL)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, "Invalid address of function.\n");
        
        return STORM_RETURN_INVALID_ARGUMENT;
    }
    
    /* Make sure the IRQ level is free. */
    if (irq_handlers[irq_number] != NULL)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, "IRQ%u already used.\n", irq_number);
        
        return STORM_RETURN_BUSY;
    }
    
    irq_handlers[irq_number] = function;
    irq_handlers_data[irq_number] = parameter;
    pic_enable_irq (irq_number);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Handler successfull registered.\n");

    return STORM_RETURN_SUCCESS;
}

return_t irq_unregister (unsigned int irq_number)
{
    if ((irq_number >= NUMBER_OF_IRQ_CHANNELS) && 
        (irq_number == IRQ_CHANNEL_CASCADE))
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, "Invalid IRQ number.\n");
        
        return STORM_RETURN_INVALID_ARGUMENT;
    }

    pic_disable_irq (irq_number);
    irq_handlers[irq_number] = NULL;
    
    return STORM_RETURN_SUCCESS;
}

