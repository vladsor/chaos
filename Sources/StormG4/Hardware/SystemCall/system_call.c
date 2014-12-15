/* $chaos: system_call.c,v 1.7 2002/11/03 22:22:41 per Exp $ */
/* Abstract: System call implementation. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <enviroment.h>
#include "Include/system_call.h"

#define DEBUG_MODULE_NAME "SystemCall"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include <debug/macros.h>

/* Set up the system call handler in the IDT. */
return_t system_call_init (int argc UNUSED, char *argv[] UNUSED, 
    char **envp UNUSED)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s ()\n",
        DEBUG_MODULE_NAME, __FUNCTION__);

    idt_setup_interrupt_gate (SYSTEM_CALL_IDT_ENTRY, SELECTOR_KERNEL_CODE, 
        (address_t) system_call_lowlevel, PRIVILEGE_LEVEL_USER);

    return 0;
}

/* The high-level system call handler, called from the low-level function. */
return_t system_call (uint32_t ss, uint32_t *stack)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%x, %p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        ss, stack);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s: Stack %x,%x,%x,%x,%x,%x,%x,%x\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        stack[0], stack[1], stack[3], stack[4],
        stack[5], stack[6], stack[7], stack[8]);

    switch (stack[0])
    {
        case 0:
        {
            return_t return_value;
            
            return_value = system_debug_print ((uint8_t) stack[1], 
                (const char *) stack[2], (const char *) stack[3], 
                (uint32_t) stack[4], (const char *) stack[5]);
        
            return return_value;
        }
        
        case 1:
        {
            computer_return ();
        
            return STORM_RETURN_SUCCESS;
        }
    }
        
    return STORM_RETURN_SUCCESS;
}

