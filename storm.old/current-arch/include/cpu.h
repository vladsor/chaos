/* $Id: cpu.h,v 1.3 2000/10/15 11:17:51 plundis Exp $ */
/* Abstract: CPU detection and some lowlevel routines. */

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
   USA */

#ifndef __STORM_IA32_CPU_H__
#define __STORM_IA32_CPU_H__

#include <storm/generic/bit.h>
#include <storm/generic/defines.h>
#include <storm/generic/debug.h>
#include <storm/generic/memory.h>
#include <storm/ia32/idt.h>

/* External variables. */

extern void cpu_structaddr;
extern long no_idt[2];

/* Inlines. */

static inline void cpu_push_all (void)
{
  asm ("pusha");
}

static inline void cpu_pop_all (void)
{
 asm ("popa");
}

static inline void cpu_interrupt_return (void)
{
  asm ("iret");
}

static inline void cpu_interrupts_disable (void)
{
  asm ("cli");
}

static inline void cpu_interrupts_enable (void)
{
  asm ("sti");
}

static inline void cpu_halt (void)
{
  cpu_interrupts_disable ();
  while (TRUE);
}

static inline void cpu_no_operation (void)
{
  asm ("nop");
}

/* Inlines. */

static inline u32 cpu_get_esp (void)
{
  u32 return_value;

  asm volatile ("movl %%esp, %0"
		: "=a" (return_value)
		:);

  return return_value;
}

static inline u32 cpu_get_eflags (void)
{
  u32 return_value;

  asm volatile 
  ("\
    pushf
    popl %0"
   : "=a" (return_value));

  return return_value;
}

static inline u32 cpu_get_cs (void)
{
  u32 return_value;

  asm volatile ("movl %%cs, %0"
                : "=a" (return_value));
  return return_value;
}

static inline u32 cpu_get_cr0 (void)
{
  u32 return_value;
  asm volatile ("movl %%cr0, %0"
		: "=a" (return_value) 
		:);
  return return_value;
}

static inline void cpu_set_cr0 (u32 new_cr0)
{
  asm volatile ("movl %0, %%cr0"
		:
		: "r" (new_cr0));
}

static inline u32 cpu_get_cr2 (void)
{			   
  u32 return_value;
  asm volatile ("movl %%cr2, %0"
		: "=a" (return_value) 
		:);
  return return_value;
}

static inline void cpu_set_cr3 (u32 new_cr3)
{
  asm volatile ("movl %0, %%cr3"
		:
		: "r" (new_cr3));
}

static inline void cpu_set_cr4 (u32 new_cr4)
{
  asm volatile ("movl %0, %%cr4"
		:
		: "r" (new_cr4));
}

static inline u16 cpu_get_tr (void)
{
  u16 return_value;
  asm volatile ("str %0"
		: "=a" (return_value)
		:);
  return return_value;
}

static inline void cpu_set_tr (u16 new_tr)
{
  asm volatile ("ltr %0"
		:
		: "r" (new_tr));
}

static inline void cpu_reset (void)
{
  /* Force a triple fault.. */

  asm ("cli");
  memory_set_u8 ((u8 *) idt, 0, SIZE_IDT);

  /* Tribute to the good old DOS coding days... ;-) Completely
     non-serious... Can you tell I'm writing this at 3AM? */

  asm ("movb $0x13, %al");
  asm ("int $0x10");

  /* This code will not be reached. */

  while (TRUE);
}

/*
static inline void cpuid (u32 command, u32 *eax, u32 *ebx, u32 *ecx, u32 *edx)
{
  asm volatile ("cpuid"
       : "=a" (*eax), "=b" (*ebx), "=c" (*ecx), "=d" (*edx)
       : "a" (command)
       : "cc");
}
*/

#define cpuid(command,val1,val2,val3,val4) \
       __asm__ __volatile__("cpuid" \
			    : "=a" (val1), "=b" (val2),\
			      "=c" (val3),  "=d" (val4) \
			    : "a" (command)\
			    : "cc");

/*
 * Access to machine-specific registers (available on 586 and better only)
 * Note: the rd* operations modify the parameters directly (without using
 * pointer indirection), this allows gcc to optimize better
 */

#define rdmsr(msr,val1,val2) \
       __asm__ __volatile__("rdmsr" \
			    : "=a" (val1), "=d" (val2) \
			    : "c" (msr))

#define wrmsr(msr,val1,val2) \
     __asm__ __volatile__("wrmsr" \
			  : /* no outputs */ \
			  : "c" (msr), "a" (val1), "d" (val2))

#define rdtsc(low,high) \
     __asm__ __volatile__("rdtsc" : "=a" (low), "=d" (high))

#define rdtscl(low) \
     __asm__ __volatile__ ("rdtsc" : "=a" (low) : : "edx")

#define rdtscll(val) \
     __asm__ __volatile__ ("rdtsc" : "=A" (val))

#define write_tsc(val1,val2) wrmsr(0x10, val1, val2)

#define rdpmc(counter,low,high) \
     __asm__ __volatile__("rdpmc" \
			  : "=a" (low), "=d" (high) \
			  : "c" (counter))


/* CR0 bits. */
/* Paging enabled. */

#define CPU_CR0_PG (BIT_VALUE (31))

/* Protected mode flag. */

#define CPU_CR0_PE (BIT_VALUE (0))

/* Extension type. */

#define CPU_CR0_ET (BIT_VALUE (4))

/* Write protect (486+). */

#define CPU_CR0_WP (BIT_VALUE (16))

/* CR4 bits. */
/* Enable global page directory entries. */

#define CPU_CR4_PGE (BIT_VALUE (7))

#endif /* !__STORM_IA32_CPU_H__ */
