/* Abstract: Inlines functions for 486. */
/* Author: Vladimir Sorokin */

/* Copyright 2000 chaos development. */

/* This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public License
   as published by the Free Software Foundation; either version 2 of
   the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
   USA. */

#ifndef __LIBRARY_STRING_IA32_INLINES_486_H__
#define __LIBRARY_STRING_IA32_INLINES_486_H__

/*
 * This string-include defines all string functions as inline
 * functions. Use gcc. It also assumes ds=es=data space, this should be
 * normal. Most of the string-functions are rather heavily hand-optimized,
 * see especially strtok,strstr,str[c]spn. They should work, but are not
 * very easy to understand. Everything is done entirely within the register
 * set, making the functions fast and clean. 
 *
 *              Copyright (C) 1991, 1992 Linus Torvalds
 *              Revised and optimized for i486/pentium
 *              1994/03/15 by Alberto Vignani/Davide Parodi @crf.it
 *
 *      Split into 2 CPU specific files by Alan Cox to keep #ifdef noise down.
 *
 *      1999/10/5       Proper register args for newer GCCs and minor bugs
 *                      fixed - Petko Manolov (petkan@spct.net)
 *      1999/10/14      3DNow memscpy() added - Petkan
 *      2000/05/09      extern changed to static in function definitions
 *                      and a few cleanups - Petkan
 */

#define HAVE_ARCHITECTURE_STRING_COPY
static inline char * string_copy (char * dest, const char *src)
{
  register char *tmp = (char *) dest;
  register char dummy;
  asm volatile 
  ("\
1:  movb (%0), %2
    incl %0
    movb %2, (%1)
    incl %1
    testb %2, %2
    jne 1b
  "
   : "=r" (src), "=r" (tmp), "=q" (dummy)
   : "0" (src), "1" (tmp)
   : "memory"   
  );
  
  return dest;
}

#define HAVE_ARCHITECTURE_STRING_COPY_MAX
static inline char * string_copy_max (char * dest, const char *src, 
  unsigned int count)
{
  register char *tmp = (char *) dest;
  register char dummy;

  if (count == 0) 
  {
    return dest;
  }

  asm volatile 
  ("\
1:  movb (%0), %2
    incl %0
    movb %2, (%1)
    incl %1
    decl %3
    je 3f
    testb %2, %2
    jne 1b
2:  movb %2, (%1)
    incl %1
    decl %3
    jne 2b
3:
  "
   : "=r" (src), "=r" (tmp), "=q" (dummy), "=r" (count)
   : "0" (src), "1" (tmp), "3" (count)
   : "memory"
  );

  return dest;
}

#define HAVE_ARCHITECTURE_STRING_APPEND
static inline char * string_append (char *dest, const char *src)
{
  register char *tmp = (char *) (dest - 1);
  register char dummy;

  asm volatile 
  ("\
1:  incl %1
    cmpb $0, (%1)
    jne 1b
2:  movb (%2), %b0
    incl %2
    movb %b0, (%1)
    incl %1
    testb %b0, %b0
    jne 2b
  "
   : "=q" (dummy), "=r" (tmp), "=r" (src)
   : "1"  (tmp), "2"  (src)
   : "memory"
  );

  return dest;
}

#define HAVE_ARCHITECTURE_STRING_APPEND_MAX
static inline char * string_append_max (char *dest, const char *src, 
  unsigned int count)
{
  register char *tmp = (char *) (dest - 1);
  register char dummy;
  
  asm volatile
  ("\
1:  incl %1
    cmpb $0, (%1)
    jne 1b
2:  decl %3
    js 3f
    movb (%2), %b0
    incl %2
    movb %b0, (%1)
    incl %1
    testb %b0, %b0
    jne 2b
3:  xorb %0, %0
    movb %b0, (%1)
  "
   : "=q" (dummy), "=r" (tmp), "=r" (src), "=r" (count)
   : "1"  (tmp), "2"  (src), "3"  (count)
   : "memory"
  );
  
  return dest;
}

#define HAVE_ARCHITECTURE_STRING_COMPARE
static inline int string_compare (const char *cs, const char *ct)
{
  register int res;

  asm volatile
  ("\
1:  movb (%1), %b0
    incl %1
    cmpb %b0, (%2)
    jne 2f
    incl %2
    testb %b0, %b0
    jne 1b
    xorl %0, %0
    jmp 3f
2:  movl $1, %0
    jb 3f
    negl %0
3:
  "
   : "=q" (res), "=r" (cs), "=r" (ct)
   : "1" (cs), "2" (ct)
   : "memory" 
  );
  
  return res;
}

#define HAVE_ARCHITECTURE_STRING_COMPARE_MAX
static inline int string_compare_max (const char *cs, const char *ct, 
  unsigned int count)
{
  register int res;

  asm volatile
  ("\
1:  decl %3
    js 2f
    movb (%1), %b0
    incl %1
    cmpb %b0, (%2)
    jne 3f
    incl %2
    testb %b0, %b0
    jne 1b
2:  xorl %0, %0
    jmp 4f
3:  movl $1, %0
    jb 4f
    negl %0
4:
  "
   : "=q" (res), "=r" (cs), "=r" (ct), "=r" (count)
   : "1"  (cs), "2"  (ct), "3" (count)
  );

  return res;
}

#define HAVE_ARCHITECTURE_STRING_LENGTH
static inline unsigned int string_length (const char *s)
{
  /* slightly slower on a 486, but with better chances of register allocation */
  register char dummy, *tmp = (char *) s;

  asm volatile 
  ("\
1:  movb (%0), %1
    incl %0
    testb %1, %1
    jne 1b
  "
   : "=r" (tmp), "=q" (dummy)
   : "0" (s)
   : "memory" 
  );
  
  return (tmp - s - 1);
}

#define HAVE_ARCHITECTURE_STRING_LENGTH_MAX
static inline unsigned int string_length_max (const char * s, 
  unsigned int count)
{
  int d0;
  register int res;

  asm volatile
  ("\
    movl %3, %0
    jmp 2f
1:  cmpb $0, (%0)
    je 3f
    incl %0
2:  decl %2
    cmpl $-1, %2
    jne 1b
3:  subl %3, %0
  "
   : "=a" (res), "=&d" (d0)
   : "1" (count), "c" (s)
  );

  return res;
}

#define HAVE_ARCHITECTURE_STRING_CHR
static inline char * string_chr (const char *s, int c)
{
  register char *res;

  asm volatile
  ("\
    movb %%al, %%ah
1:  movb (%1), %%al
    cmpb %%ah, %%al
    je 2f
    incl %1
    testb %%al, %%al
    jne 1b
    xorl %1, %1
2:  movl %1, %0
  "
   : "=a" (res), "=r" (s)
   : "0" (c), "1"  (s)
  );
  
  return res;
}

#define HAVE_ARCHITECTURE_STRING_RCHR
static inline char * string_rchr (const char *s, int c)
{
  int d0, d1;
  register char *res;

  asm volatile
  ("\
    cld
    movb %%al, %%ah
1:  lodsb
    cmpb %%ah, %%al
    jne 2f
    leal -1(%%esi), %0
2:  testb %%al, %%al
    jne 1b
  "
   : "=d" (res), "=&S" (d0), "=&a" (d1)
   : "0" (0), "1" (s), "2" (c)
  );

  return res;
}

#define HAVE_ARCHITECTURE_STRING_CSPN
static inline unsigned int string_cspn (const char *cs, const char *ct)
{
  int d0, d1;
  register char *res;

  asm volatile 
  ("\
    cld
    movl %6, %%edi
    repne
    scasb
    notl %%ecx
    decl %%ecx
    movl %%ecx, %%edx
1:  lodsb
    testb %%al, %%al
    je 2f
    movl %6, %%edi
    movl %%edx, %%ecx
    repne
    scasb
    jne 1b
2:  decl %0
  "
   : "=S" (res), "=&a" (d0), "=&c" (d1)
   : "0" (cs), "1" (0), "2" (0xffffffff), "g" (ct)
   : "dx", "di"
  );

  return res - cs;
}

#endif /* __LIBRARY_STRING_IA32_INLINES_486_H__ */
