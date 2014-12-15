/* $Id: log.h,v 1.2 2001/02/10 21:26:22 jojo Exp $ */
/* Abstract: Kernel logging functions. */
/* Author: Henrik Hallin <hal@chaosdev.org> */

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

#ifndef __STORM_GENERIC_LOG_H__
#define __STORM_GENERIC_LOG_H__

typedef struct
{
  char *string;
  struct log_list_type *next;
} log_list_type;

extern log_list_type *log_list;

extern void log_init (void);
extern void log_print (char *string);

#endif /* !__STORM_GENERIC_LOG_H__ */
