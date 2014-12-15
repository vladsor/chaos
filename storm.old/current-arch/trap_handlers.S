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

.globl trap1_handler
.globl trap3_handler
.globl trap14_handler

.extern trap_debug_trap
.extern trap_breakpoint_trap
.extern trap_page_fault
.extern ecode
/*
#define TRAP_HANDLER_WITH_ERROR_CODE(function) \
   pushl %eax
   movl 4(%esp), %eax
   movl %eax, ecode
   popl %eax
   addl $4, %esp
   pushal ;\
   call $function ;\
   popal ;\
   iret

#define TRAP_HANDLER_WITH_OUT_ERROR_CODE(function) \
   pushal ;\
   call $function ;\
   popal ;\
   iret
*/

trap1_handler:
   pushal ;\
   call trap_debug_trap ;\
   popal ;\
   iret

trap3_handler:
   pushal ;\
   call trap_breakpoint_trap ;\
   popal ;\
   iret

trap14_handler:
   pushl %eax
   movl 4(%esp), %eax
   movl %eax, ecode
   popl %eax
   addl $4, %esp
   pushal ;\
   call trap_page_fault ;\
   popal ;\
   iret

