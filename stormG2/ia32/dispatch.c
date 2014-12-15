/* $Id: dispatch.c,v 1.1 2001/02/10 22:58:46 jojo Exp $ */
/* Abstract: Thread dispatcher. */

/* Author: Per Lundberg <plundis@chaosdev.org> */

/* Copyright 2000 chaos development. */

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

#include <storm/generic/dispatch.h>
#include <storm/generic/thread.h>

thread_type *current_thread;

/* Dispatch the next thread immediately (like yield () in UNIX
   systems). */

void dispatch_next (void)
{
  while (TRUE);
}