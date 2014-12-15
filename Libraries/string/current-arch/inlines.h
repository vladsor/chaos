/* Copyright 2000 chaos development. */

/**
 * @file                 inlines.h
 * @brief                IA-32 specefic inlines functions.
 * @author               Vladimir Sorokin
 * @version              1.0
 * @date                 2000-2003
 */

#ifndef __LIBRARY_STRING_IA32_INLINES_H__
#define __LIBRARY_STRING_IA32_INLINES_H__

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
#include <string/current-arch/inlines-486.h>
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
 *              NO Copyright (C) 1991, 1992 Linus Torvalds,
 *              consider these trivial functions to be PD.
 */

#define HAVE_ARCHITECTURE_STRING_COPY

/**
 * @brief                Copy a string.
 * @param destination    Destination string
 * @param source         Source string
 * @return               Pointer to destination string
 */
static inline char * string_copy (char *destination, const char *source)
{
  int source_counter;
  int destination_counter;
  int test_value;

  asm volatile ("cld\n"
                "1: lodsb\n"
                "stosb\n"
                "testb %%al, %%al\n"
                "jne 1b"
                : 
		"=&S" (source_counter), 
		"=&D" (destination_counter), 
		"=&a" (test_value)
                : 
		"0" (source), 
		"1" (destination) 
                : 
		"memory");

  return destination;
}

#define HAVE_ARCHITECTURE_STRING_COPY_MAX

/**
 * @brief                Copy a string, but no more than 'count' bytes. 
 * @param destination    Destination string
 * @param source         Source string
 * @param count          Max copied characters
 * @return               Pointer to destination string
 */
static inline char * string_copy_max (char *destination, const char *source,
  unsigned int count)
{
  int source_counter;
  int destination_counter;
  int test_value;
  int length_counter;

  asm volatile ("cld\n"
                "1: decl %2\n"
                "js 2f\n"
                "lodsb\n"
                "stosb\n"
                "testb %%al, %%al\n"
                "jne 1b\n"
//    "rep\n"
//    "stosb\n"
                "2:"
                : 
		"=&S" (source_counter), 
		"=&D" (destination_counter), 
                "=&c" (length_counter), 
		"=&a" (test_value)
                : 
		"0" (source), 
		"1" (destination), 
		"2" (count) 
                : 
		"memory");

  return destination;
}

#define HAVE_ARCHITECTURE_STRING_APPEND

/**
 * @brief                Append a 'source' string to 'destination' string. 
 * @param destination    Destination string
 * @param source         Source string
 * @return               Pointer to destination string
 */
static inline char * string_append (char *destination, const char *source)
{
  int source_counter;
  int destination_counter;
  int test_value;
  int length_counter;

  asm volatile ("cld\n"
                "repne\n"
		"scasb\n"
	        "decl %1\n"
		"1: lodsb\n"
	        "stosb\n"
	        "testb %%al, %%al\n"
	        "jne 1b"
	        : 
		"=&S" (source_counter), 
		"=&D" (destination_counter), 
		"=&a" (test_value),
	        "=&c" (length_counter)
		: 
		"0" (source), 
		"1" (destination), 
		"2" (0), 
		"3" (0xFFFFFFFF)
	        : 
		"memory");

  return destination;
}

#define HAVE_ARCHITECTURE_STRING_APPEND_MAX

/**
 * @brief                Append a 'source' string to 'destination' string, but no more than 'count' bytes.  
 * @param destination    Destination string
 * @param source         Source string
 * @param count          Max appended characters
 * @return               Pointer to destination string
 */
static inline char * string_append_max (char *destination, const char *source,
  unsigned int count)
{
  int source_counter;
  int destination_counter;
  int test_value;
  int length_counter;

  asm volatile ("cld\n"
	        "repne\n"
		"scasb\n"
		"decl %1\n"
		"movl %8, %3\n"
		"1: decl %3\n"
		"js 2f\n"
	        "lodsb\n"
	        "stosb\n"
	        "testb %%al, %%al\n"
		"jne 1b\n"
		"2: xorl %2, %2\n"
	        "stosb"
	        : 
		"=&S" (source_counter), 
		"=&D" (destination_counter), 
		"=&a" (test_value), 
	        "=&c" (length_counter)
		: 
		"0" (source), 
		"1" (destination), 
		"2" (0), 
		"3" (0xFFFFFFFF), 
		"g" (count)
		: 
		"memory");

  return destination;
}

#define HAVE_ARCHITECTURE_STRING_COMPARE

/**
 * @brief                Compare two strings. Returns 0 if equal. 
 * @param string1        First string
 * @param string2        Second string
 * @return               Zero if equal, non zero otherwise.   
 */
static inline int string_compare (const char *string1, const char *string2)
{
  int string1_counter;
  int string2_counter;
  register int result;
  
  asm volatile ("cld\n"
		"1: lodsb\n"
		"scasb\n"
		"jne 2f\n"
		"testb %%al, %%al\n"
		"jne 1b\n"
		"xorl %%eax, %%eax\n"
	        "jmp 3f\n"
		"2: sbbl %%eax, %%eax\n"
		"orb $1, %%al\n"
		"3:"
		: 
		"=a" (result), 
		"=&S" (string1_counter), 
		"=&D" (string2_counter)
		: 
		"1" (string1), 
		"2" (string2));

  return result;
}

#define HAVE_ARCHITECTURE_STRING_COMPARE_MAX

/**
 * @brief                Compare two strings, but no more than 'count' bytes. 
 * @param string1        First string
 * @param string2        Second string
 * @param count          Max compared characters
 * @return               Zero if equal, non zero otherwise.
 */
static inline int string_compare_max (const char *string1, const char *string2, 
  unsigned int count)
{
  int string1_counter;
  int string2_counter;
  int length_counter;
  register int result;

  asm volatile ("cld\n"
		"1: decl %3\n"
		"js 2f\n"
		"lodsb\n"
		"scasb\n"
		"jne 3f\n"
		"testb %%al, %%al\n"
		"jne 1b\n"
		"2: xorl %%eax, %%eax\n"
		"jmp 4f\n"
		"3: sbbl %%eax, %%eax\n"
		"orb $1, %%al\n"
		"4:"
		: 
		"=a" (result), 
		"=&S" (string1_counter), 
		"=&D" (string2_counter), 
    		"=&c" (length_counter)
		: 
		"1" (string1), 
		"2" (string2), 
		"3" (count));
  
  return result;
}

#define HAVE_ARCHITECTURE_STRING_LENGTH

/**
 * @brief                Returns the string length. 
 * @param string         String
 * @return               Length of string
 */
static inline unsigned int string_length (const char *string)
{
  int test_character;
  register int result;

  asm volatile ("cld\n"
		"repne\n"
		"scasb\n"
		"notl %0\n"
		"decl %0"
		: 
		"=c" (result), 
		"=&D" (test_character) 
		: 
		"1" (string), 
		"a" (0), 
		"0" (0xFFFFFFFF));

  return result;
}

#define HAVE_ARCHITECTURE_STRING_LENGTH_MAX

/**
 * @brief                Returns the string length, but only if it is less than 'count'. 
 * @brief string         String
 * @brief count          Max analyzed characters
 * return                Minimum of  string's length or 'count'
 */
static inline unsigned int string_length_max (const char *string, 
  unsigned int count)
{
  int length_counter;
  register int result;

  asm volatile ("movl %2, %0\n"
		"jmp 2f\n"
		"1: cmpb $0, (%0)\n"
		"je 3f\n"
		"incl %0\n"
		"2: decl %1\n"
		"cmpl $-1, %1\n"
		"jne 1b\n"
		"3: subl %2, %0"
		: 
		"=a" (result), 
		"=&d" (length_counter)
		: 
		"c" (string), 
		"1" (count));

  return result;
}

#define HAVE_ARCHITECTURE_STRING_FIND_FIRST_CHAR

/**
 * @brief                Find the first occurrence of 'character' in 'string'.  
 * @param string         String
 * @param character      Character
 * @return               Pointer to character in string if found, pointer to '\0' otherwise.
 */
static inline char * string_find_first_char (const char *string, int character)
{
  int test_counter;
  register char *result;
  
  asm volatile ("cld\n"
		"movb %%al, %%ah\n"
		"1: lodsb\n"
		"cmpb %%ah, %%al\n"
		"je 2f\n"
		"testb %%al, %%al\n"
		"jne 1b\n"
		"movl $1, %1\n"
		"2: movl %1, %0\n"
		"decl %0"
		: 
		"=a" (result), 
		"=&S" (test_counter) 
		: 
		"1" (string), 
		"0" (character));

  return result;
}

#define HAVE_ARCHITECTURE_STRING_FIND_LAST_CHAR

/**
 * @brief                Find the last occurrence of 'character' in 'string'.  
 * @param string         String
 * @param character      Character
 * @return               Pointer to character in 'string'
 */
static inline char * string_find_last_char (const char *string, int character)
{
  int test_counter;
  int test_character;
  register char *result;

  asm volatile ("cld\n"
		"movb %%al, %%ah\n"
		"1: lodsb\n"
		"cmpb %%ah, %%al\n"
		"jne 2f\n"
		"leal -1(%%esi), %0\n"
		"2: testb %%al, %%al\n"
		"jne 1b" 
		: 
		"=g" (result), 
		"=&S" (test_counter), 
		"=&a" (test_character) 
		: 
		"0" (0), 
		"1" (string), 
		"2" (character));

  return result;
}

#define HAVE_ARCHITECTURE_STRING_FIND_SUBSTRING

/**
 * @brief                Find the first occurrence of 'substring' in 'string'.  
 * @param string         String
 * @param substring      Substring
 * @return               Pointer to 'substring' in 'string'.
 */
static inline char * string_find_substring (const char *string, 
  const char *substring)
{
  int string_counter;
  int d0; /* ? */
  register char *result;

  asm volatile ("movl %6, %%edi\n"
		"repne\n"
		"scasb\n"
		"notl %%ecx\n"
/* NOTE! This also sets Z if searchstring='' */
		"decl %%ecx\n"                   
		"movl %%ecx, %%edx\n"
		"1: movl %6, %%edi\n"
		"movl %%esi, %%eax\n"
		"movl %%edx, %%ecx\n"
		"repe\n"
		"cmpsb\n"
/* also works for empty string, see above */
		"je 2f\n"                           
		"xchgl %%eax, %%esi\n"
		"incl %%esi\n"
		"cmpb $0, -1(%%eax)\n"
		"jne 1b\n"
		"xorl %%eax, %%eax\n"
		"2:"
		: 
		"=a" (result), 
		"=&c" (d0), 
		"=&S" (string_counter)
		: 
		"0" (0), 
		"1" (0xFFFFFFFF), 
		"2" (string), 
		"g" (substring)
		: 
		"dx", 
		"di");

  return result;
}

#endif /* !(FIXED_486_STRING && defined(CONFIG_X86_USE_STRING_486)) */

#endif /* __LIBRARY_STRING_IA32_INLINES_H__ */
