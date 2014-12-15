/* Abstract: Exception handling. */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file		handlers.c
 * @author		Vladimir Sorokin
 */

#include <enviroment.h>

#include "Include/exception.h"
#include "Include/handlers.h"

//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>

/* Exception handlers. */
exception_hardware_description_t 
    exception_hardware_descriptions[NUMBER_OF_EXCEPTIONS] =
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
    }
};

