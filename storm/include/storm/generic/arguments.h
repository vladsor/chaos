/* $Id: arguments.h,v 1.2 2001/02/10 21:26:14 jojo Exp $ */
/* Abstract: Function prototypes for command line argument parsing
   routines. */

/* Copyright 1999-2000 chaos development. */

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
   USA */

#ifndef __STORM_I386_ARGUMENTS_H__
#define __STORM_I386_ARGUMENTS_H__

#include <storm/types.h>

/* Function prototypes. */

extern u32 arguments_parse (char *source, char *destination, u32 delta);
extern char arguments_kernel[];

#endif /* !__STORM_I386_ARGUMENTS_H__ */
