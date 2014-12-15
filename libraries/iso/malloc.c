/* $Id: malloc.c,v 1.1.1.1 2000/09/26 19:08:07 plundis Exp $ */
/* Abstract: malloc() function. (Yuk! *spits on the floor*) */
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

#include <system/system.h>

#include "stdlib.h"

void *malloc (size_t size)
{
  void *pointer;

  system_call_memory_allocate (&pointer, SIZE_IN_PAGES (size));
  return pointer;
}

void free (void *pointer)
{
  system_call_memory_deallocate ((void **) &pointer);
}
