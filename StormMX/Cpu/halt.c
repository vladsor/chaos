/* $chaos: halt.c,v 1.3 2002/10/23 07:22:38 per Exp $ */
/* Abstract: Functions for halting the machine. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <enviroment.h>

#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

/* Halt the computer. */
return_t cpu_halt (enum halt_t type)
{
    uint16_t idtr[3] = 
    {
        0x0000, 
        0x0000,
        0x0000
    };

    switch (type)
    {
        case HALT_REBOOT:
        {
            asm volatile ("lidt      (%0)\n"
                          "int       $0" 
                          : 
                          :
                          "g" (idtr));
            break;
        }
        case HALT_SHUTDOWN:
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
                "System has been shut down. You may power off.\n");

            cpu_interrupts_disable ();
            while (TRUE)
            {
                asm ("hlt");
            }
            break;
        }

        default:
        {
            return STORM_RETURN_INVALID_ARGUMENT;
        }
    }
            
    /* We should never get here. */
    return STORM_RETURN_SUCCESS;
}
