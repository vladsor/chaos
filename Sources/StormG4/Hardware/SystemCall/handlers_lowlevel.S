/* $chaos: system_call_lowlevel.S,v 1.3 2002/10/24 22:14:06 per Exp $ */
/* Abstract: Low-level system call. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

.globl system_call_lowlevel

/* This function is called whenever a system call is being done. */
system_call_lowlevel:
        /* Preserve the registers. */
        pushal 

        /* Get the address of the caller's stack. */
        pushl   32 + 12(%esp)
        pushl   36 + 16(%esp)        

        call system_call
        addl    $8, %esp
        
        popl    %edi
        popl    %esi
        popl    %ebp

        /* %esp can't be popped for obvious reasons. */
        addl    $4, %esp

        popl    %ebx
        popl    %edx
        popl    %ecx

        /* Preserve %eax; gcc uses it for return values. */
        addl    $4, %esp
        iret
