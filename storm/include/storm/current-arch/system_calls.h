/* $Id: system_calls.h,v 1.2 2001/02/10 21:26:31 jojo Exp $ */
/* Abstract: Function prototypes and structure definitions for system
   calls. */
/* Authors: Per Lundberg <plundis@chaosdev.org>
            Henrik Hallin <hal@chaosdev.org> */

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

#ifndef __STORM_IA32_SYSTEM_CALLS_H__
#define __STORM_IA32_SYSTEM_CALLS_H__

#include <storm/ia32/defines.h>
#include <storm/ia32/types.h>
#include <storm/system_calls.h>

/* Type definitions. */

typedef struct
{
  u32 number;
  function_type handler;
  u8 arguments;
} system_call_type;

/* External variables. */

extern const system_call_type system_call[];

/* Function prototypes. */

extern void system_calls_init (void) INIT_CODE;

#endif /* !__STORM_IA32_SYSTEM_CALLS_H__ */
