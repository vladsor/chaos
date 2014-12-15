/* $chaos: system_call.c,v 1.7 2002/11/03 22:22:41 per Exp $ */
/* Abstract: System call implementation. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <enviroment.h>
#include "Include/system_call.h"

#define DEBUG_MODULE_NAME "SystemCall"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>

/* Set up the system call handler in the IDT. */
return_t system_call_init (void)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s ()\n",
        DEBUG_MODULE_NAME, __FUNCTION__);

    idt_setup_interrupt_gate (SYSTEM_CALL_IDT_ENTRY, SELECTOR_KERNEL_CODE, 
        system_call_lowlevel, 3);

    return 0;
}

/* The high-level system call handler, called from the low-level function. */
return_t system_call (uint32_t *stack)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__, stack);
        
    return 0;
}
