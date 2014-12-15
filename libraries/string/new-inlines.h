#ifndef _IA32_386_STRING_H_
#define _IA32_386_STRING_H_

/*
 * On a 486 or Pentium, we are better off not using the
 * byte string operations. But on a 386 or a PPro the
 * byte string ops are faster than doing it by hand
 * (MUCH faster on a Pentium).
 *
 * Also, the byte strings actually work correctly. Forget
 * the i486 routines for now as they may be broken..
 */

#if FIXED_486_STRING && defined(CONFIG_X86_USE_STRING_486)
#include <string/string-486.h>
#else

/*
 * This string-include defines all string functions as inline
 * functions. Use gcc. It also assumes ds=es=data space, this should be
 * normal. Most of the string-functions are rather heavily hand-optimized,
 * see especially strtok,strstr,str[c]spn. They should work, but are not
 * very easy to understand. Everything is done entirely within the register
 * set, making the functions fast and clean. String instructions have been
 * used through-out, making for "slightly" unclear code :-)
 *
 *		NO Copyright (C) 1991, 1992 Linus Torvalds,
 *		consider these trivial functions to be PD.
 */

#define HAVE_ARCHITECTURE_STRING_COPY
/* Copy a string. */
static inline char * string_copy (char *destination, const char *source)
{
  int source_counter;
  int destination_counter;
  int test_value;

  asm volatile 
  ("\
    cld
1:  lodsb
    stosb
    testb %%al, %%al
    jne 1b
  "
   : "=&S" (source_counter), "=&D" (destination_counter), "=&a" (test_value)
   : "0" (source), "1" (destination) 
   : "memory"
  );

  return destination;
}

#define HAVE_ARCHITECTURE_STRING_COPY_MAX
/* Copy a string, but no more than 'count' bytes. */
static inline char * string_copy_max (char *destination, const char *source,
  unsigned int count)
{
  int source_counter;
  int destination_counter;
  int test_value;
  int length_counter;

  asm volatile 
  ("\
    cld
1:  decl %2
    js 2f
    lodsb
    stosb
    testb %%al, %%al
    jne 1b
    rep
    stosb
2:
  "
   : "=&S" (source_counter), "=&D" (destination_counter), 
     "=&c" (length_counter), "=&a" (test_value)
   : "0" (source), "1" (destination), "2" (count) 
   : "memory"
  );

  return destination;
}

#define HAVE_ARCHITECTURE_STRING_APPEND
/* Append a 'source' string to 'destination' string. */
static inline char * string_append (char *destination, const char *source)
{
  int source_counter;
  int destination_counter;
  int test_value;

  asm volatile 
  ("\
    cld
    repne
    scasb
    decl %1
1:  lodsb
    stosb
    testb %%al, %%al
    jne 1b
  "
   : "=&S" (source_counter), "=&D" (destination_counter), "=&a" (test_value)
   : "0" (source), "1" (destination), "2" (0)
   : "memory");

  return destination;
}

#define HAVE_ARCHITECTURE_STRING_APPEND_MAX
/* Append a 'source' string to 'destination' string, but no more than 'count' 
   bytes.  */
static inline char * string_append_max (char *destination, const char *source,
  unsigned int count)
{
  int source_counter;
  int destination_counter;
  int test_value;
  int length_counter;

  asm volatile 
  ("\
    cld
    repne
    scasb
    decl %1
    movl %8, %3
1:  decl %3
    js 2f
    lodsb
    stosb
    testb %%al, %%al
    jne 1b
2:  xorl %2, %2
    stosb
  "
   : "=&S" (source_counter), "=&D" (destination_counter), "=&a" (test_value), 
     "=&c" (length_counter)
   : "0" (source), "1" (destination), "2" (0), "3" (0xFFFFFFFF), "g" (count)
   : "memory"
  );

  return destination;
}

#define HAVE_ARCHITECTURE_STRING_COMPARE
/* Compare two strings. Returns 0 if equal. */
static inline int string_compare (const char *string1, const char *string2)
{
  int string1_counter;
  int string2_counter;
  register int result;
  
  asm volatile 
  ("\
    cld
1:  lodsb
    scasb
    jne 2f
    testb %%al, %%al
    jne 1b
    xorl %%eax, %%eax
    jmp 3f
2:  sbbl %%eax, %%eax
    orb $1, %%al
3:
  "
   : "=a" (result), "=&S" (string1_counter), "=&D" (string2_counter)
   : "1" (string1), "2" (string2)
  );

  return result;
}

#define HAVE_ARCHITECTURE_STRING_COMPARE_MAX
/* Compare two strings, but no more than 'count' bytes. */
static inline int string_compare_max (const char *string1, const char *string2, 
  unsigned int count)
{
  int string1_counter;
  int string2_counter;
  int length_counter;
  register int result;

  asm volatile 
  ("\
    cld
1:  decl %3
    js 2f
    lodsb
    scasb
    jne 3f
    testb %%al, %%al
    jne 1b
2:  xorl %%eax, %%eax
    jmp 4f
3:  sbbl %%eax, %%eax
    orb $1, %%al
4:
  "
   : "=a" (result), "=&S" (string1_counter), "=&D" (string2_counter), 
     "=&c" (length_counter)
   : "1" (string1), "2" (string2), "3" (count)
  );
  
  return result;
}

#define HAVE_ARCHITECTURE_STRING_LENGTH
/* Returns the string length. */
static inline unsigned int string_length (const char *string)
{
  int test_character;
  register int result;

  asm volatile 
  ("\
    cld
    repne
    scasb
    notl %0
    decl %0
  "
   : "=c" (result), "=&D" (test_character) 
   : "1" (string), "a" (0), "0" (0xFFFFFFFF)
  );

  return result;
}

#define HAVE_ARCHITECTURE_STRING_LENGTH_MAX
/* Returns the string length, but only if it is less than 'count'. */
static inline unsigned int string_length_max (const char *string, 
  unsigned int count)
{
  int length_counter;
  register int result;

  asm volatile 
  ("\
    movl %2, %0
    jmp 2f
1:  cmpb $0, (%0)
    je 3f
    incl %0
2:  decl %1
    cmpl $-1, %1
    jne 1b
3:  subl %2, %0
  "
   : "=a" (result), "=&d" (length_counter)
   : "c" (string), "1" (count)
  );

  return result;
}

#define HAVE_ARCHITECTURE_STRING_FIND_FIRST_CHAR
/* Find the first occurrence of 'character' in 'string'.  */
static inline char * string_find_first_char (const char * string, int character)
{
  int test_counter;
  register char *result;
  
  asm volatile 
  ("\
    cld
    movb %%al, %%ah
1:  lodsb
    cmpb %%ah, %%al
    je 2f
    testb %%al, %%al
    jne 1b
    movl $1, %1
2:  movl %1, %0
    decl %0
  "
   : "=a" (result), "=&S" (test_counter) 
   : "1" (string), "0" (character)
  );

  return result;
}

#define HAVE_ARCHITECTURE_STRING_FIND_LAST_CHAR
/* Find the last occurrence of 'character' in 'string'.  */
static inline char * string_find_last_char (const char *string, int character)
{
  int test_counter;
  int test_character;
  register char *result;

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
   : "=g" (result), "=&S" (test_counter), "=&a" (test_character) 
   : "0" (0), "1" (string), "2" (character)
  );

  return result;
}

#define HAVE_ARCHITECTURE_STRING_FIND_SUBSTRING
/* Find the first occurrence of 'substring' in 'string'.  */
static inline char * string_find_substring (const char *string, 
  const char *substring)
{
  int string_counter;
  int d0; /* ? */
  register char *result;

  asm volatile 
  ("\
    movl %6, %%edi
    repne
    scasb
    notl %%ecx
    decl %%ecx                   /* NOTE! This also sets Z if searchstring='' */
    movl %%ecx, %%edx
1:  movl %6, %%edi
    movl %%esi, %%eax
    movl %%edx, %%ecx
    repe
    cmpsb
    je 2f                           /* also works for empty string, see above */
    xchgl %%eax, %%esi
    incl %%esi
    cmpb $0, -1(%%eax)
    jne 1b
    xorl %%eax, %%eax
2:
  "
   : "=a" (result), "=&c" (d0), "=&S" (string_counter)
   : "0" (0), "1" (0xFFFFFFFF), "2" (string), "g" (substring)
   : "dx", "di"
  );

  return result;
}

#endif /* !(FIXED_486_STRING && defined(CONFIG_X86_USE_STRING_486)) */

#endif /* _IA32_386_STRING_H_ */
