/* $Id: stdlib.h,v 1.1.1.1 2000/09/26 19:08:07 plundis Exp $ */
/* Copyright (C) 1991-1999, 2000 Free Software Foundation, Inc.
   Copyright 2000 chaos development. */

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

/*
 *	ISO C Standard: 4.10 GENERAL UTILITIES	<stdlib.h>
 */

#ifndef	_STDLIB_H

#include <features.h>

#define __need_size_t
#define __need_wchar_t
#define __need_NULL
/* Get size_t, wchar_t and NULL from <stddef.h>.  */
#include <stddef.h>

#define	_STDLIB_H	1

__BEGIN_DECLS

/* Returned by `div'.  */
typedef struct
  {
    int quot;			/* Quotient.  */
    int rem;			/* Remainder.  */
  } div_t;

/* Returned by `ldiv'.  */
#ifndef __ldiv_t_defined
typedef struct
  {
    long int quot;		/* Quotient.  */
    long int rem;		/* Remainder.  */
  } ldiv_t;
# define __ldiv_t_defined	1
#endif

#ifndef __lldiv_t_defined
/* Returned by `lldiv'.  */
__extension__ typedef struct
  {
    long long int quot;		/* Quotient.  */
    long long int rem;		/* Remainder.  */
  } lldiv_t;
# define __lldiv_t_defined	1
#endif


/* The largest number rand will return (same as INT_MAX).  */
#define	RAND_MAX	2147483647


/* We define these the same for all machines.
   Changes from this to the outside world should be done in `_exit'.  */
#define	EXIT_FAILURE	1	/* Failing exit status.  */
#define	EXIT_SUCCESS	0	/* Successful exit status.  */


/* Maximum length of a multibyte character in the current locale.  */
#define	MB_CUR_MAX	(__ctype_get_mb_cur_max ()
extern size_t __ctype_get_mb_cur_max (void);


/* Convert a string to a floating-point number.  */
extern double atof (__const char *__nptr);
/* Convert a string to an integer.  */
extern int atoi (__const char *__nptr);
/* Convert a string to a long integer.  */
extern long int atol (__const char *__nptr);

#if defined __USE_ISOC9X || (defined __GNUC__ && defined __USE_MISC)
/* These functions will part of the standard C library in ISO C 9X.  */
__extension__ extern long long int atoll (__const char *__nptr);
#endif

/* Convert a string to a floating-point number.  */
extern double strtod (__const char *__restrict __nptr,
			   char **__restrict __endptr);

/* Likewise for `float' and `long double' sizes of floating-point numbers.  */
extern float strtof (__const char *__restrict __nptr,
			  char **__restrict __endptr);

extern long double strtold (__const char *__restrict __nptr,
                            char **__restrict __endptr);

/* Convert a string to a long integer.  */
extern long int strtol (__const char *__restrict __nptr,
                        char **__restrict __endptr, int __base);
/* Convert a string to an unsigned long integer.  */
extern unsigned long int strtoul (__const char *__restrict __nptr,
				       char **__restrict __endptr,
				       int __base);

/* These functions will part of the standard C library in ISO C 9X.  */

/* Convert a string to a quadword integer.  */
__extension__
extern long long int strtoll (__const char *__restrict __nptr,
				   char **__restrict __endptr, int __base);
/* Convert a string to an unsigned quadword integer.  */
__extension__
extern unsigned long long int strtoull (__const char *__restrict __nptr,
					     char **__restrict __endptr,
					     int __base);

/* Return a random integer between 0 and RAND_MAX inclusive.  */
extern int rand (void);
/* Seed the random number generator with the given number.  */
extern void srand (unsigned int __seed);

/* Allocate SIZE bytes of memory.  */
extern void * malloc (size_t __size);
/* Allocate NMEMB elements of SIZE bytes each, all initialized to 0.  */
extern void * calloc (size_t __nmemb, size_t __size);

/* Re-allocate the previously allocated block
   in void *, making the new block SIZE bytes long.  */
extern void * realloc (void * __ptr, size_t __size);
/* Free a block allocated by `malloc', `realloc' or `calloc'.  */
extern void free (void * __ptr);

/* Abort execution and generate a core-dump.  */
extern void abort (void) __attribute__ ((noreturn));

/* Register a function to be called when `exit' is called.  */
extern int atexit (void (*__func) (void));

/* Call all functions registered with `atexit' and `on_exit',
   in the reverse of the order in which they were registered
   perform stdio cleanup, and terminate program execution with STATUS.  */
extern void exit (int __status) __attribute__ ((noreturn));

/* Terminate the program with STATUS without calling any of the
   functions registered with `atexit' or `on_exit'.  */
extern void _Exit (int __status) __attribute__ ((noreturn));

/* Return the value of envariable NAME, or NULL if it doesn't exist.  */
extern char *getenv (__const char *__name);

/* This function is similar to the above but returns NULL if the
   programs is running with SUID or SGID enabled.  */
extern char *__secure_getenv (__const char *__name);

/* Execute the given line as a shell command.  */
extern int system (__const char *__command);

/* Return the absolute value of X.  */
extern int abs (int __x) __attribute__ ((__const__));
extern long int labs (long int __x) __attribute__ ((__const__));
__extension__ extern long long int llabs (long long int __x)
     __attribute__ ((__const__));

/* Return the `div_t', `ldiv_t' or `lldiv_t' representation
   of the value of NUMER over DENOM. */
/* GCC may have built-ins for these someday.  */
extern div_t div (int __numer, int __denom) __attribute__ ((__const__));
extern ldiv_t ldiv (long int __numer, long int __denom)
     __attribute__ ((__const__));
__extension__ extern lldiv_t lldiv (long long int __numer,
					 long long int __denom)
     __attribute__ ((__const__));

/* Return the length of the multibyte character
   in S, which is no longer than N.  */
extern int mblen (__const char *__s, size_t __n);
/* Return the length of the given multibyte character,
   putting its `wchar_t' representation in *PWC.  */
extern int mbtowc (wchar_t *__restrict __pwc,
                   __const char *__restrict __s, size_t __n);
/* Put the multibyte character represented
   by WCHAR in S, returning its length.  */
extern int wctomb (char *__s, wchar_t __wchar);

/* Convert a multibyte string to a wide char string.  */
extern size_t mbstowcs (wchar_t *__restrict  __pwcs,
			     __const char *__restrict __s, size_t __n);
/* Convert a wide char string to multibyte string.  */
extern size_t wcstombs (char *__restrict __s,
			     __const wchar_t *__restrict __pwcs, size_t __n);

__END_DECLS

#endif /* !_STDLIB.H  */
