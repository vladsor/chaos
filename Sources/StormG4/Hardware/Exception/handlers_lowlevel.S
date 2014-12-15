/* $chaos: exception_lowlevel.S,v 1.5 2002/10/04 19:01:21 per Exp $ */
/* Abstract: Low-level exception handlers. Push registers etc. */

/**
 * @author Per Lundberg <per@chaosdev.org> 
 * @author Vladimir Sorokin
 */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#define _ASM
#include <System/ia32/Exceptions/codes.h>
#include <Kernel/Common/exception.h>

.extern exception_handlers
.extern exception_handlers_data

#define EXCEPTION_HANDLER_WITH_ERROR_CODE(NAME)           \
.globl EXCEPTION_HANDLER_ ## NAME ## _LOWLEVEL ;           \
EXCEPTION_HANDLER_ ## NAME ## _LOWLEVEL:                  \
    pusha ;                                                \
    movl  36(%esp), %eax ;   \
    movl  40(%esp), %ebx ;   \
    movl  44(%esp), %ecx ;   \
    pushl %ds ;   \
    pushl %es ;   \
    pushl %fs ;   \
    pushl %gs ;   \
    pushl %ss ;   \
    pushl %ebx ;   \
    pushl %ecx ;   \
    pushl $EXCEPTION_ ## NAME ;      \
    pushl $EXCEPTION_TYPE_HARDWARE ; \
    pushl %eax ;   \
    movl (exception_handlers + EXCEPTION_ ## NAME * 4), %eax ;\
    cmpl $0, %eax ;\
    je EXCEPTION_ ## NAME ## _END ;\
    movl (exception_handlers_data + EXCEPTION_ ## NAME * 4), %ebx ;\
    pushl %ebx ;\
    call *%eax ;\
    addl $4, %esp ;\
EXCEPTION_ ## NAME ## _END: \
    addl $18 * 4, %esp ;   \
    popa ;   \
    addl $4 * 4, %esp ;   \
    iret

#define EXCEPTION_HANDLER_WO_ERROR_CODE(NAME)    \
.globl EXCEPTION_HANDLER_ ## NAME ## _LOWLEVEL ;       \
EXCEPTION_HANDLER_ ## NAME ## _LOWLEVEL:      \
    pusha ;   \
    movl  32(%esp), %eax ;   \
    movl  36(%esp), %ebx ;   \
    movl  40(%esp), %ecx ;   \
    pushl %ds ;   \
    pushl %es ;   \
    pushl %fs ;   \
    pushl %gs ;   \
    pushl %ss ;   \
    pushl %ebx ;   \
    pushl %ecx ;   \
    pushl $EXCEPTION_ ## NAME ;   \
    pushl $EXCEPTION_TYPE_HARDWARE ;   \
    pushl %eax ;   \
    movl (exception_handlers + EXCEPTION_ ## NAME * 4), %eax ;\
    cmpl $0, %eax ;\
    je EXCEPTION_ ## NAME ## _END;\
    movl (exception_handlers_data + EXCEPTION_ ## NAME * 4), %ebx ;\
    pushl %ebx ;\
    call *%eax ;\
    addl $4, %esp ;\
EXCEPTION_ ## NAME ## _END: \
    addl $18 * 4, %esp ;   \
    popa ;   \
    addl $3 * 4, %esp ;   \
    iret

#define EXCEPTION_HANDLER_WITH_SEGMENT_ERROR_CODE(NAME) \
    EXCEPTION_HANDLER_WITH_ERROR_CODE(NAME)

#define EXCEPTION_HANDLER_WITH_PAGE_ERROR_CODE(NAME)    \
.globl EXCEPTION_HANDLER_ ## NAME ## _LOWLEVEL ;   \
EXCEPTION_HANDLER_ ## NAME ## _LOWLEVEL:      \
    pushl %eax ; \
    movl %cr2, %eax ; \
    xchg 4(%esp), %eax ; \
    xchg (%esp), %eax ; \
    pusha ;   \
    movl  40(%esp), %eax ;   \
    movl  44(%esp), %ebx ;   \
    movl  48(%esp), %ecx ;   \
    pushl %ds ;   \
    pushl %es ;   \
    pushl %fs ;   \
    pushl %gs ;   \
    pushl %ss ;   \
    pushl %ebx ;   \
    pushl %ecx ; \
    pushl $EXCEPTION_ ## NAME ;    \
    pushl $EXCEPTION_TYPE_HARDWARE ;   \
    pushl %eax ;   \
    movl (exception_handlers + EXCEPTION_ ## NAME * 4), %eax ;\
    cmpl $0, %eax ;\
    je EXCEPTION_ ## NAME ## _END ;\
    movl (exception_handlers_data + EXCEPTION_ ## NAME * 4), %ebx ;\
    pushl %ebx ;\
    call *%eax ;\
EXCEPTION_ ## NAME ## _END: \
    addl $18 * 4, %esp ;   \
    popa ;   \
    addl $5 * 4, %esp ;   \
    iret

EXCEPTION_HANDLER_WO_ERROR_CODE (DIVIDE_ERROR);
EXCEPTION_HANDLER_WO_ERROR_CODE (DEBUG);
EXCEPTION_HANDLER_WO_ERROR_CODE (NONMASKABLE_INTERRUPT);
EXCEPTION_HANDLER_WO_ERROR_CODE (BREAKPOINT);
EXCEPTION_HANDLER_WO_ERROR_CODE (OVERFLOW);
EXCEPTION_HANDLER_WO_ERROR_CODE (BOUND_RANGE_EXCEEDED);
EXCEPTION_HANDLER_WO_ERROR_CODE (INVALID_OPCODE);
EXCEPTION_HANDLER_WO_ERROR_CODE (DEVICE_NOT_AVAILABLE);
EXCEPTION_HANDLER_WITH_ERROR_CODE (DOUBLE_FAULT);
EXCEPTION_HANDLER_WO_ERROR_CODE (COPROCESSOR_SEGMENT_OVERRUN);
EXCEPTION_HANDLER_WITH_SEGMENT_ERROR_CODE (INVALID_TSS);
EXCEPTION_HANDLER_WITH_SEGMENT_ERROR_CODE (SEGMENT_NOT_PRESENT);
EXCEPTION_HANDLER_WITH_SEGMENT_ERROR_CODE (STACK_FAULT);
EXCEPTION_HANDLER_WITH_SEGMENT_ERROR_CODE (GENERAL_PROTECTION);
EXCEPTION_HANDLER_WITH_PAGE_ERROR_CODE (PAGE_FAULT);
EXCEPTION_HANDLER_WO_ERROR_CODE (DUMMY);
EXCEPTION_HANDLER_WO_ERROR_CODE (FLOATING_POINT_ERROR);
EXCEPTION_HANDLER_WITH_ERROR_CODE (ALIGNMENT_CHECK);
EXCEPTION_HANDLER_WO_ERROR_CODE (MACHINE_CHECK);
EXCEPTION_HANDLER_WO_ERROR_CODE (STREAMING_SIMD_EXTENSIONS);

