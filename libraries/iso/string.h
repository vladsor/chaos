/* Copyright (C) 1991,92,93,95,96,97,98,99 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with the GNU C Library; see the file COPYING.LIB.  If not,
   write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/*
 *	ISO C Standard: 4.11 STRING HANDLING	<string.h>
 */

#ifndef	_STRING_H
#define	_STRING_H	1

#include <features.h>

__BEGIN_DECLS

/* Get size_t and NULL from <stddef.h>.  */
#define	__need_size_t
#define	__need_NULL
#include <stddef.h>

/* Copy N bytes of SRC to DEST.  */
extern void * memcpy (void * __restrict __dest,
                       __const void * __restrict __src, size_t __n);
/* Copy N bytes of SRC to DEST, guaranteeing
   correct behavior for overlapping strings.  */
extern void * memmove (void * __dest, __const void * __src,
                        size_t __n);

/* Set N bytes of S to C.  */
extern void * memset (void * __s, int __c, size_t __n);

/* Compare N bytes of S1 and S2.  */
extern int memcmp (__const void *__s1, __const void * __s2,
                   size_t __n);

/* Search N bytes of S for C.  */
extern void * memchr (__const void *__s, int __c, size_t __n);

/* Copy SRC to DEST.  */
extern char *strcpy (char *__restrict __dest,
                     __const char *__restrict __src);
/* Copy no more than N characters of SRC to DEST.  */
extern char *strncpy (char *__restrict __dest,
                      __const char *__restrict __src, size_t __n);

/* Append SRC onto DEST.  */
extern char *strcat (char *__restrict __dest, __const char *__restrict __src);

/* Append no more than N characters from SRC onto DEST.  */
extern char *strncat (char *__restrict __dest, __const char *__restrict __src,
                      size_t __n);

/* Compare S1 and S2.  */
extern int strcmp (__const char *__s1, __const char *__s2);
/* Compare N characters of S1 and S2.  */
extern int strncmp (__const char *__s1, __const char *__s2, size_t __n);

/* Compare the collated forms of S1 and S2.  */
extern int strcoll (__const char *__s1, __const char *__s2);

/* Put a transformation of SRC into no more than N bytes of DEST.  */
extern size_t strxfrm (char *__restrict __dest, __const char *__restrict __src,
                       size_t __n);
/* Find the first occurrence of C in S.  */
extern char *strchr (__const char *__s, int __c);
/* Find the last occurrence of C in S.  */
extern char *strrchr (__const char *__s, int __c);

/* Return the length of the initial segment of S which
   consists entirely of characters not in REJECT.  */
extern size_t strcspn (__const char *__s, __const char *__reject);
/* Return the length of the initial segment of S which
   consists entirely of characters in ACCEPT.  */
extern size_t strspn (__const char *__s, __const char *__accept);
/* Find the first occurrence in S of any character in ACCEPT.  */
extern char *strpbrk (__const char *__s, __const char *__accept);
/* Find the first occurrence of NEEDLE in HAYSTACK.  */
extern char *strstr (__const char *__haystack, __const char *__needle);

/* Divide S into tokens separated by characters in DELIM.  */
extern char *strtok (char *__restrict __s, const char *__restrict __delim);

/* Return the length of S.  */
extern size_t strlen (__const char *__s);

/* Return a string describing the meaning of the `errno' code in ERRNUM.  */
extern char *strerror (int __errnum);

__END_DECLS

#endif /* string.h  */
