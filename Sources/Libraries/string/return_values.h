/* $Id: return_values.h,v 1.2 2001/02/10 21:23:14 jojo Exp $ */
/* Abstract: String library return values. */
/* Author: Per Lundberg <plundis@chaosdev.org> */

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

#ifndef __LIBRARY_STRING_RETURN_VALUES_H__
#define __LIBRARY_STRING_RETURN_VALUES_H__

enum
{
  /* The function completed successfully. */

  STRING_RETURN_SUCCESS,
  
  /* One or more of the arguments to a function was invalid. */

  STRING_RETURN_INVALID_ARGUMENT,
};

#endif /* !__LIBRARY_STRING_RETURN_VALUES_H__ */
