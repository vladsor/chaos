/* $chaos: inlines.h,v 1.1 2002/06/23 20:33:12 per Exp $ */
/* Abstract: Inlined functions. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2000-2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __LIBRARY_STRING_INLINES_H__
#define __LIBRARY_STRING_INLINES_H__

/* Inlined functions. */
/* Copy a string. */
static inline char *string_copy (char *destination, const char *source)
{
    int esi, edi, eax;
    
    asm volatile ("cld\n"
                  "1:  lodsb\n"
                  "stosb\n"
                  "testb %%al, %%al\n"
                  "jne 1b\n"
                  : "=&S" (esi), "=&D" (edi), "=&a" (eax)
                  : "0" (source), "1" (destination)
                  : "memory");
    
    return destination;
}

/* Copy a string, but no more than 'count' bytes. */
static inline char *string_copy_max (char *destination, const char *source,
                                     unsigned int count)
{
    int esi, edi, ecx, eax;

    asm volatile ("cld\n"
                  "1:  decl %2\n"
                  "js 2f\n"
                  "lodsb\n"
                  "stosb\n"
                  "testb %%al, %%al\n"
                  "jne 1b\n"
                  "rep\n"
                  "stosb\n"
                  "2:"
                  : "=&S" (esi), "=&D" (edi), "=&c" (ecx), "=&a" (eax)
                  : "0" (source), "1" (destination), "2" (count) 
                  : "memory");
  
  return destination;
}

/* Compare two strings. Returns 0 if equal. */
static inline int string_compare (const char *string1, const char *string2)
{
    int esi, edi;
    register int eax;

    asm volatile ("cld\n"
                  "1:  lodsb\n"
                  "scasb\n"
                  "jne 2f\n"
                  "testb %%al, %%al\n"
                  "jne 1b\n"
                  "xorl %%eax, %%eax\n"
                  "jmp 3f\n"
                  "2:  sbbl %%eax, %%eax\n"
                  "orb $1, %%al\n"
                  "3:"
                  : "=a" (eax), "=&S" (esi), "=&D" (edi)
                  : "1" (string1), "2" (string2));
    
    return eax;
}


/* Compare two strings, but no more than count characters. */
static inline int string_compare_max (const char *string1, const char *string2,
                                      unsigned int count)
{
    register int eax;
    int esi, edi, ecx;
    
    asm volatile ("cld\n"
                  "1:  decl %3\n"
                  "js 2f\n"
                  "lodsb\n"
                  "scasb\n"
                  "jne 3f\n"
                  "testb %%al, %%al\n"
                  "jne 1b\n"
                  "2:  xorl %%eax, %%eax\n"
                  "jmp 4f\n"
                  "3:  sbbl %%eax, %%eax\n"
                  "orb $1, %%al\n"
                  "4:"
                  : "=a" (eax), "=&S" (esi), "=&D" (edi), "=&c" (ecx)
                  : "1" (string1), "2" (string2), "3" (count));
    
    return eax;
}

/* Returns the string length. */
static inline size_t string_length (const char *string)
{
    int edi;
    register int ecx;
    
    asm volatile ("cld\n"
                  "repne\n"
                  "scasb\n"
                  "notl %0\n"
                  "decl %0"
                  : "=c" (ecx), "=&D" (edi)
                  : "1" (string), "a" (0), "0" (0xffffffff));
    return ecx;
}

/* Returns the string length, but only if it is less than size. */
static inline size_t string_length_max (const char *string, 
                                        unsigned int count)
{
    int d0;
    register int __res;
    
    asm volatile ("movl %2, %0\n"
                  "jmp 2f\n"
                  "1: cmpb $0, (%0)\n"
                  "je 3f\n"
                  "incl %0\n"
                  "2: decl %1\n"
                  "cmpl $-1, %1\n"
                  "jne 1b\n"
                  "3: subl %2, %0"
                  : "=a" (__res), "=&d" (d0)
                  :"c" (string),"1" (count));
    return __res;
}

/* Append one string to another. PLEASE NOTE that this function does
   not allocate more memory if needed! */
static inline void string_append (char *destination, char *source)
{
    string_copy (&destination[string_length (destination)], source);
}

#endif /* !__LIBRARY_STRING_INLINES_H__ */
