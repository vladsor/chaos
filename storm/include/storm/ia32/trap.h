/* $Id: trap.h,v 1.1.1.1 2000/09/26 19:08:18 plundis Exp $ */
/* Abstract: Exception stuff. */

/* Copyright 1999-2000 chaos development. */

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

#ifndef __STORM_IA32_TRAP_H__
#define __STORM_IA32_TRAP_H__

#include <storm/ia32/tss.h>
#include <storm/ia32/types.h>

typedef struct
{

  /* EXT External event (bit 0). When set, indicates that an event external to 
         the program caused the exception, such as a hardware interrupt. */
  int EXT : 1;

  /* IDT Descriptor location (bit 1). When set, indicates that the index portion
         of the error code refers to a gate descriptor in the IDT; when clear, 
         indicates that the index refers to a descriptor in the GDT or the 
         current LDT. */
  int IDT : 1; 

  /* TI GDT/LDT (bit 2). Only used when the IDT flag is clear. When set, the TI 
        flag indicates that the index portion of the error code refers to a 
        segment or gate descriptor in the LDT; when clear, it indicates that the 
        index refers to a descriptor in the current GDT. */
  int TI : 1;

  /* The segment selector index field provides an index into the IDT, GDT, or 
     current LDT to the segment or gate selector being referenced by the error 
     code. In some cases the error code is null (that is, all bits in the lower 
     word are clear). A null error code indicates that the error was not caused
     by a reference to a specific segment or that a null segment descriptor was 
     referenced in an operation. */
  int segment_selector_index : 13;

  int reserved : 16;
} __attribute__ ((packed)) segment_error_type;

typedef struct
{

  /* P 0 The fault was caused by a nonpresent page.
       1 The fault was caused by a page-level protection violation. */
  int P : 1;

  /* W/R 0 The access causing the fault was a read.
         1 The access causing the fault was a write. */
  int W_R : 1;

  /* U/S 0 The access causing the fault originated when the processor
           was executing in supervisor mode.
         1 The access causing the fault originated when the processor
           was executing in user mode. */
  int U_S : 1; 

  /* RSVD 0 The fault was not caused by a reserved bit violation.
          1 The page fault occured because a 1 was detected in one of the
            reserved bit positions of a page table entry or directory entry
            that was marked present. */
  int RSVD : 1;

  int reserved : 28;

} __attribute__ ((packed)) page_error_type;

enum
{
  HANDLER_TASK_GATE,
  HANDLER_INTERRUPT_GATE,
};

enum
{
  EXCEPTION_CODE_NONE,
  EXCEPTION_CODE_PAGE,
  EXCEPTION_CODE_SEGMENT,
};

/* Prototypes. */

extern void trap_init (void) INIT_CODE;
extern void trap0_handler(void);
extern void trap1_handler(void);
extern void trap2_handler(void);
extern void trap3_handler(void);
extern void trap4_handler(void);
extern void trap5_handler(void);
extern void trap6_handler(void);
extern void trap7_handler(void);
extern void trap8_handler(void);
extern void trap9_handler(void);
extern void trap10_handler(void);
extern void trap11_handler(void);
extern void trap12_handler(void);
extern void trap13_handler(void);
extern void trap14_handler(void);
extern void trap_reserved_handler(void);
/* External variables. */

extern tss_type *trap_tss;

#endif /* !__STORM_IA32_TRAP_H__ */
