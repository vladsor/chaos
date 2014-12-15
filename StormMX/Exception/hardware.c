/* $chaos: exception.c,v 1.21 2002/10/23 21:24:22 per Exp $ */
/* Abstract: Exception handling. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 *
 */

#include <enviroment.h>

#include "Include/exception.h"
#include "Include/hardware-exception.h"

#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#include <debug/macros.h>

/* Exception handlers. */
exception_hardware_description_t exception_hardware_descriptions[] =
{
    {
        &EXCEPTION_HANDLER_DIVIDE_ERROR_LOWLEVEL,
        EXCEPTION_CLASS_FAULT, "Divide Error", 
        "DIV and IDIV instructions.", 
        EXCEPTION_CODE_NONE,
    },

    {
        &EXCEPTION_HANDLER_DEBUG_LOWLEVEL,
        EXCEPTION_CLASS_TRAP, "Debug",
        "Any code or data reference or the INT 1 instruction.",
        EXCEPTION_CODE_NONE,
    },

    {
        &EXCEPTION_HANDLER_NONMASKABLE_INTERRUPT_LOWLEVEL,
        EXCEPTION_CLASS_INTERRUPT, "NMI Interrupt",
        "Nonmaskable external interrupt.", 
        EXCEPTION_CODE_NONE,
    },

    {
        &EXCEPTION_HANDLER_BREAKPOINT_LOWLEVEL,
        EXCEPTION_CLASS_TRAP, "Breakpoint", 
        "INT 3 instruction.",
        EXCEPTION_CODE_NONE,
    },


    {
        &EXCEPTION_HANDLER_OVERFLOW_LOWLEVEL,
        EXCEPTION_CLASS_TRAP, "Overflow",
        "INTO instruction.",
        EXCEPTION_CODE_NONE,
    },

    {
        &EXCEPTION_HANDLER_BOUND_RANGE_EXCEEDED_LOWLEVEL,
        EXCEPTION_CLASS_FAULT, "BOUND Range Exceeded",
        "BOUND instruction.", 
        EXCEPTION_CODE_NONE,
    },

    {
        &EXCEPTION_HANDLER_INVALID_OPCODE_LOWLEVEL,
        EXCEPTION_CLASS_FAULT, "Invalid Opcode (Undefined Opcode)",
        "UD2 instruction or reserved opcode.", 
        EXCEPTION_CODE_NONE,
    },

    {
        &EXCEPTION_HANDLER_DEVICE_NOT_AVAILABLE_LOWLEVEL,
        EXCEPTION_CLASS_FAULT, "Device Not Available (No Math Coprocessor)",
        "Floating-point or WAIT/FWAIT instruction.", 
        EXCEPTION_CODE_NONE,
    },

    {
        &EXCEPTION_HANDLER_DOUBLE_FAULT_LOWLEVEL,
        EXCEPTION_CLASS_ABORT, "Double Fault", 
        "Any instruction that can generate an exception, an NMI,"
        " or an INTR (probably due to a kernel bug).",
        EXCEPTION_CODE_NONE,
    },

    {
        &EXCEPTION_HANDLER_COPROCESSOR_SEGMENT_OVERRUN_LOWLEVEL,
        EXCEPTION_CLASS_FAULT, "Coprocessor Segment Overrun",
        "Floating-point instruction.", 
        EXCEPTION_CODE_NONE,
    },

    {
        &EXCEPTION_HANDLER_INVALID_TSS_LOWLEVEL,
        EXCEPTION_CLASS_FAULT, "Invalid TSS",
        "Task switch or TSS access.", 
        EXCEPTION_CODE_SEGMENT,
    },

    {
        &EXCEPTION_HANDLER_SEGMENT_NOT_PRESENT_LOWLEVEL,
        EXCEPTION_CLASS_FAULT, "Segment Not Present",
        "Loading segment registers or accessing system segments.",
        EXCEPTION_CODE_SEGMENT,
    },

    {
        &EXCEPTION_HANDLER_STACK_FAULT_LOWLEVEL,
        EXCEPTION_CLASS_FAULT, "Stack-Segment Fault",
        "Stack operations and SS register loads.", 
        EXCEPTION_CODE_SEGMENT,
    },

    {
        &EXCEPTION_HANDLER_GENERAL_PROTECTION_LOWLEVEL,
        EXCEPTION_CLASS_FAULT, "General Protection",
        "Any memory reference and other protection checks.", 
        EXCEPTION_CODE_SEGMENT,
    },

    {
        &EXCEPTION_HANDLER_PAGE_FAULT_LOWLEVEL,
        EXCEPTION_CLASS_FAULT, "Page Fault",
        "Any memory reference.",
        EXCEPTION_CODE_PAGE,
    },

    {
        &EXCEPTION_HANDLER_DUMMY_LOWLEVEL,
        EXCEPTION_CLASS_NONE, "(Intel Reserved)", 
        "Buggy CPU non-fault",
        EXCEPTION_CODE_NONE,
    },

    {
        &EXCEPTION_HANDLER_FLOATING_POINT_ERROR_LOWLEVEL,
        EXCEPTION_CLASS_FAULT, "Floating-Point Error (Math Fault)",
        "Floating-point or WAIT/FWAIT instruction.", 
        EXCEPTION_CODE_NONE,
    },

    {
        &EXCEPTION_HANDLER_ALIGNMENT_CHECK_LOWLEVEL,
        EXCEPTION_CLASS_FAULT, "Alignment Check",
        "Any data reference in memory.",
        EXCEPTION_CODE_NONE,
    },

    {
        &EXCEPTION_HANDLER_MACHINE_CHECK_LOWLEVEL,
        EXCEPTION_CLASS_ABORT, "Machine Check",
        "Error codes (if any) and source are model dependent.", 
        EXCEPTION_CODE_NONE,
    },

    {
        &EXCEPTION_HANDLER_STREAMING_SIMD_EXTENSIONS_LOWLEVEL,
        EXCEPTION_CLASS_FAULT, "Streaming SIMD Extensions",
        "SIMD floating-point instructions.", 
        EXCEPTION_CODE_NONE,
    },
    
    { NULL, EXCEPTION_CLASS_NONE, NULL, NULL, EXCEPTION_CODE_NONE, }
};

/* One function for each exception. */
void EXCEPTION_HANDLER_DIVIDE_ERROR (exception_hardware_info_t exception_info)
{
    exception_invoke_handler (thread_get_current (), (exception_info_t *) &exception_info);
}

void EXCEPTION_HANDLER_DEBUG (exception_hardware_info_t exception_info)
{
    exception_invoke_handler (thread_get_current (), (exception_info_t *) &exception_info);
}

void EXCEPTION_HANDLER_NONMASKABLE_INTERRUPT (
    exception_hardware_info_t exception_info)
{
    exception_invoke_handler (thread_get_current (), (exception_info_t *) &exception_info);
}

void EXCEPTION_HANDLER_BREAKPOINT (exception_hardware_info_t exception_info)
{
    exception_invoke_handler (thread_get_current (), (exception_info_t *) &exception_info);
}

void EXCEPTION_HANDLER_OVERFLOW (exception_hardware_info_t exception_info)
{
    exception_invoke_handler (thread_get_current (), (exception_info_t *) &exception_info);
}

void EXCEPTION_HANDLER_BOUND_RANGE_EXCEEDED (
    exception_hardware_info_t exception_info)
{
    exception_invoke_handler (thread_get_current (), (exception_info_t *) &exception_info);
}

void EXCEPTION_HANDLER_INVALID_OPCODE (
    exception_hardware_info_t exception_info)
{
    exception_invoke_handler (thread_get_current (), (exception_info_t *) &exception_info);
}

void EXCEPTION_HANDLER_DEVICE_NOT_AVAILABLE (
    exception_hardware_info_t exception_info)
{
    exception_invoke_handler (thread_get_current (), (exception_info_t *) &exception_info);
}

void EXCEPTION_HANDLER_DOUBLE_FAULT (
    exception_hardware_with_error_code_info_t exception_info)
{
    exception_invoke_handler (thread_get_current (), (exception_info_t *) &exception_info);
}

void EXCEPTION_HANDLER_COPROCESSOR_SEGMENT_OVERRUN (
    exception_hardware_info_t exception_info)
{
    exception_invoke_handler (thread_get_current (), (exception_info_t *) &exception_info);
}

void EXCEPTION_HANDLER_INVALID_TSS (
    exception_hardware_segment_info_t exception_info)
{
    exception_invoke_handler (thread_get_current (), (exception_info_t *) &exception_info);
}

void EXCEPTION_HANDLER_SEGMENT_NOT_PRESENT (
    exception_hardware_segment_info_t exception_info)
{
    exception_invoke_handler (thread_get_current (), (exception_info_t *) &exception_info);
}

void EXCEPTION_HANDLER_STACK_FAULT (
    exception_hardware_segment_info_t exception_info)
{
    exception_invoke_handler (thread_get_current (), (exception_info_t *) &exception_info);
}

void EXCEPTION_HANDLER_GENERAL_PROTECTION (
    exception_hardware_segment_info_t exception_info)
{
    exception_invoke_handler (thread_get_current (), (exception_info_t *) &exception_info);
}

void EXCEPTION_HANDLER_PAGE_FAULT (
    exception_hardware_page_info_t exception_info)
{
    exception_invoke_handler (thread_get_current (), (exception_info_t *) &exception_info);
}  

void EXCEPTION_HANDLER_DUMMY (exception_hardware_info_t exception_info)
{
    exception_invoke_handler (thread_get_current (), (exception_info_t *) &exception_info);
}

void EXCEPTION_HANDLER_FLOATING_POINT_ERROR (
    exception_hardware_info_t exception_info)
{
    exception_invoke_handler (thread_get_current (), (exception_info_t *) &exception_info);
}

void EXCEPTION_HANDLER_ALIGNMENT_CHECK (
    exception_hardware_with_error_code_info_t exception_info)
{
    exception_invoke_handler (thread_get_current (), (exception_info_t *) &exception_info);
}

void EXCEPTION_HANDLER_MACHINE_CHECK (
    exception_hardware_info_t exception_info)
{
    exception_invoke_handler (thread_get_current (), (exception_info_t *) &exception_info);
}

void EXCEPTION_HANDLER_STREAMING_SIMD_EXTENSIONS (
    exception_hardware_info_t exception_info)
{
    exception_invoke_handler (thread_get_current (), (exception_info_t *) &exception_info);
}

static void exception_print_page_screen (
    exception_hardware_page_info_t *exception_info)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "    Error code: 0x%8.8X\n", 
        *((uint32_t *) &exception_info->page_error));

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "    Page error: ");

    if (exception_info->page_error.rsvd)
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "RSVD, ");
    }

    if (exception_info->page_error.u_s)
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Supervisor ");
    }
    else
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "User ");
    }
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Page, ");

    if (exception_info->page_error.w_r)
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Write ");
    }
    else
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Read ");
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Operation");

    if (exception_info->page_error.p)
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, ", Page Not Present");
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "\n");

    DEBUG_PRINT (DEBUG_LEVEL_ERROR, "  Page address: %p\n",
        (void *) exception_info->address);
}

static void exception_print_segment_screen (
    exception_hardware_segment_info_t *exception_info)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "    Segment Error: ");

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Selector Index: %u, ", 
        exception_info->segment_error.segment_selector_index);

    if (!exception_info->segment_error.idt)
    {               
        if (exception_info->segment_error.ti)
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "in LDT, ");
        }
        else
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "in GDT, ");
        }
    }
    else
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "in IDT, ");
    }
      
    if (exception_info->segment_error.ext)
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "External Event");
    }
    else
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Internal Event");
    }
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "\n");
}

static void dump_registers (exception_hardware_info_t *registers)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "  Registers:\n");
  
    DEBUG_PRINT (DEBUG_LEVEL_ERROR,
        "    CS: %04X EIP: %08X EFLAGS: %08X\n", 
        registers->cs, registers->header.pc, registers->eflags);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "  Segment registers:\n");

    DEBUG_PRINT (DEBUG_LEVEL_ERROR,
        "    CS: %04X DS: %04X SS: %04X ES: %04X FS: %04X GS: %04X\n",
        registers->cs, registers->ds, registers->ss, registers->es, 
        registers->fs, registers->gs);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "  General-purpose registers:\n");
  

    DEBUG_PRINT (DEBUG_LEVEL_ERROR,
        "    EAX: %08X EBX: %08X ECX: %08X EDX: %08X\n",
        registers->eax, registers->ebx, registers->ecx, registers->edx);

    DEBUG_PRINT (DEBUG_LEVEL_ERROR,
        "    ESI: %08X EDI: %08X EBP: %08X ESP: %08X\n",
        registers->esi, registers->edi, registers->ebp, registers->esp);
}

/* Display a exception screen. */

void exception_print_screen (uint32_t class_id, char *description, 
    char *reason, uint32_t error_code_type, 
    exception_hardware_info_t *exception_info, 
    volatile thread_t *dump_thread UNUSED)
{
/*
  debug_print ("Source: ");
   
  if (dump_thread->cpu_task->eip >= BASE_KERNEL && 
      dump_thread->cpu_task->eip < BASE_KERNEL + SIZE_KERNEL)
  {
    debug_print ("Kernel\n");
   
  }
  else
  {
    debug_print ("Unknown\n");
   
  }
*/

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "  Exception class: ");
    
    switch (class_id)
    {
        case EXCEPTION_CLASS_FAULT:
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Fault\n");
            break;
        }
        
        case EXCEPTION_CLASS_ABORT:
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Abort.\n");
            break;
        }
        
        case EXCEPTION_CLASS_INTERRUPT:
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Interrupt.\n");
            break;
        }
        
        default:
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Unknown.\n");
        }
    }
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "    Description: %s\n", 
        description);
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "    Possible reason: %s\n", 
        reason);
  
    switch (error_code_type)
    {
        case EXCEPTION_CODE_PAGE:
        {
            exception_print_page_screen (
                (exception_hardware_page_info_t *) exception_info);
            break;
        }
        
        case EXCEPTION_CODE_SEGMENT:
        {
            exception_print_segment_screen (
                (exception_hardware_segment_info_t *) exception_info);
            break;
        }
    }
/*
    debug_print ("Dispatch count: %u\n", dispatch_count);
    debug_print ("Causing process:\n");

    debug_print ("  Process: %s (PROCESS ID %u).\n",
               ((process_type *) dump_thread->owner)->name,
               ((process_type *) dump_thread->owner)->id);
    debug_print ("  Thread: %s (THREAD ID %u).\n",
               dump_thread->name, dump_thread->id);
    debug_print ("  Process was dispatched %u times.\n", dump_thread->timeslices);

    debug_print ("Registers:\n");
  
    debug_dump_registers (dump_thread);
*/    
    dump_registers (exception_info);
}

/* Initialize exceptions. */
return_t exception_hardware_init (int argc UNUSED, char *argv[] UNUSED) 
{
#ifndef GDB /* The GDB stuff provides its own exception handlers. */
    int index;
    /* Setup exception handlers for all exceptions. */
    for (index = 0; exception_hardware_descriptions[index].handler != NULL; 
        index++)
    {
        idt_setup_interrupt_gate (index, SELECTOR_KERNEL_CODE,
            (address_t) exception_hardware_descriptions[index].handler, 0);
    }
#endif

    return 0;
}

