/* $Id: memory.h,v 1.2 2001/02/10 21:26:30 jojo Exp $ */
/* Abstract: Functions for memory operations. */
/* Author: Per Lundberg <plundis@chaosdev.org> */

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

#ifndef __STORM_IA32_MEMORY_H__
#define __STORM_IA32_MEMORY_H__

#include <storm/generic/types.h>

/* Inlines. */

#ifdef MMX

/* MMX optimized functions. Will not work on non-MMX systems. */
/* FIXME: Doesn't seem to work 100%... */

static inline void *memory_copy (void *to, const void *from, int n)
{
  u32 ebx, ecx, edi, esi;

  asm volatile
  ("\
    testl       %%ecx, %%ecx
    jz          2f
1:  movq        (%%esi), %%mm0
    movq        %%mm0, (%%edi)
    addl        $8, %%esi
    addl        $8, %%edi
    loop        1b

2:  movl        %%ebx, %%ecx
    cld
    rep         movsb		/* Move 1 byte slack. */
  "
   : "=&b" (ebx), "=&c" (ecx), "=&D" (edi), "=&S" (esi)
   : "0" (n % 8), "1" (n / 8), "2" (to), "3" (from)
   : "memory");

  return to;
}

#if FALSE
static inline void memory_set_u8 (u8 *address, u8 c, unsigned int length)
{
  int ebx, ecx, edi;

  asm volatile
  ("\
    testl       %%ecx, %%ecx
    jz          2f
    movd        %%eax, %%mm0
1:  movq        %%mm0, (%%edi)
    addl        $8, %%edi
    loop        1b

    movl        %%ebx, %%ecx
2:  cld
    rep         stosb           /* Copy 1 byte slack. */
   "
   : "=&b" (ebx), "=&c" (ecx), "=&D" (edi)
   : "a" (c), "0" (length % 8), "1" (length / 8), "2" (address)
   : "memory");
}
#endif

#else

static inline void *memory_copy (void *to, const void *from, int n)
{
  int ecx, edi, esi;

  asm volatile 
  ("\
    cld
    rep ; movsl
    testb $2, %b4
    je 1f
    movsw
 1: testb $1, %b4
    je 2f
    movsb
 2:
   "
   : "=&c" (ecx), "=&D" (edi), "=&S" (esi)
   :"0" (n / 4), "q" (n),"1" ((long) to),"2" ((long) from)
   : "memory");

  return (to);
}

#endif

static inline void memory_set_u8 (u8 *address, u8 c, unsigned int size)
{
  int ecx, edi;

  asm volatile
  ("\
    cld
    rep
    stosb
   "
   : "=&c" (ecx), "=&D" (edi)
   : "a" (c), "1" (address), "0" (size)
   : "memory");
}

static inline void memory_set_u16 (u16 *addr, u16 c, unsigned int size)
{
  int d0, d1;
  asm volatile
  ("\
    cld
    rep
    stosw
"
   : "=&c" (d0), "=&D" (d1)
   : "a" (c), "1" (addr), "0" (size)
   : "memory");
}

#endif /* !__STORM_IA32_MEMORY_H__ */
