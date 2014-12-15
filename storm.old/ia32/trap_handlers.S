/* Author:*/
	
/* Copyright 2000 chaos development. */

/* This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
   USA. */
/* FIXME: write wrappers for all handlers */
.globl trap0_handler
.globl trap1_handler
.globl trap2_handler
.globl trap3_handler
.globl trap4_handler
.globl trap5_handler
.globl trap6_handler
.globl trap7_handler
.globl trap8_handler
.globl trap9_handler
.globl trap10_handler
.globl trap11_handler
.globl trap12_handler
.globl trap13_handler
.globl trap14_handler
.globl trap_reserved_handler

.extern trap_divide_error_fault
.extern trap_debug_trap
.extern trap_nmi
.extern trap_breakpoint_trap
.extern trap_overflow_trap
.extern trap_bound_range_exceeded_fault
.extern trap_invalid_opcode_fault
.extern trap_device_not_available_fault
.extern trap_double_fault
.extern trap_coprocessor_segment_overrun_abort
.extern trap_invalid_tss_fault
.extern trap_segment_not_present_fault
.extern trap_stack_fault
.extern trap_general_protection_fault
.extern trap_page_fault
.extern trap_reserved
.extern trap_floating_point_error_fault
.extern trap_alignment_check_fault
.extern trap_machine_check_abort
.extern trap_streaming_simd_extensions_fault

.extern ecode

trap0_handler:
   call trap_divide_error_fault
   iret

trap1_handler:
   pushal
   call trap_debug_trap
   popal
   iret
   
trap2_handler:
   call trap_nmi
   iret

trap3_handler:
   pushal
   call trap_breakpoint_trap
   popal
   iret

trap4_handler:
   call trap_overflow_trap
   iret

trap5_handler:
   call trap_bound_range_exceeded_fault
   iret

trap6_handler:
   call trap_invalid_opcode_fault
   iret

trap7_handler:
   call trap_device_not_available_fault
   iret

trap8_handler:
   pushl %eax
   movl 4(%esp), %eax
   movl %eax, ecode
   popl %eax
   addl $4, %esp
   call trap_double_fault
   iret

trap9_handler:
   call trap_coprocessor_segment_overrun_abort
   iret

trap10_handler:
   pushl %eax
   movl 4(%esp), %eax
   movl %eax, ecode
   popl %eax
   addl $4, %esp
   call trap_invalid_tss_fault
   iret

trap11_handler:
   pushl %eax
   movl 4(%esp), %eax
   movl %eax, ecode
   popl %eax
   addl $4, %esp
   call trap_segment_not_present_fault
   iret
  
trap12_handler:
   pushl %eax
   movl 4(%esp), %eax
   movl %eax, ecode
   popl %eax
   addl $4, %esp
   call trap_stack_fault
   iret

trap13_handler:
   pushl %eax
   movl 4(%esp), %eax
   movl %eax, ecode
   popl %eax
   addl $4, %esp
   call trap_general_protection_fault
   iret

trap14_handler:
   pushl %eax
   movl 4(%esp), %eax
   movl %eax, ecode
   popl %eax
   addl $4, %esp
   call trap_page_fault
   iret

trap_reserved_handler:
   call trap_reserved
   iret
