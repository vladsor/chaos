/* Copyright (C) 1991, 92, 93, 94, 95, 96, 97 Free Software Foundation, Inc
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
 *	ISO C Standard: 4.1.3 Errors	<errno.h>
 */

#ifndef	_ERRNO_H

#define	_ERRNO_H	1
#include <features.h>

__BEGIN_DECLS

/* Declare the `errno' variable, unless it's defined as a macro by
   bits/errno.h.  This is the case in GNU, where it is a per-thread
   variable.  This redeclaration using the macro still works, but it
   will be a function declaration without a prototype and may trigger
   a -Wstrict-prototypes warning.  */
#ifndef	errno
extern int errno;
#endif

/* Some of those are not strictly ISO, but we define them anyway... I
   mean, who cares, really? ;-) */

enum
{
  ERANGE,
  EDOM,
  ENOMEM,
  EINVAL,
  EEXIST,
};

__END_DECLS

#endif /* _ERRNO_H */
