/* $Id: types.h,v 1.1.1.1 2000/09/26 19:08:17 plundis Exp $ */
/* Abstract: Standard types used in the chaos operating system. */

/* Copyright 1998-2000 chaos development. */

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

#ifndef __STORM_TYPES_H__
#define __STORM_TYPES_H__

/* General types. Those should only be used when a fixed size variable
   (for example in IP headers); for speed performances, use int or
   unsigned whenever a generic type is desired. But if you do,
   remember to not take for granted that the maximum value is 2^32 - 1
   etcetera. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

#ifndef __cplusplus
typedef int bool;
#endif

typedef unsigned long long u64;
typedef signed long long s64;

/* Specific types. */

typedef u8 utf8_type;
typedef u32 size_type;
typedef s32 return_type;
typedef u32 process_id_type;
typedef u32 cluster_id_type;
typedef u32 thread_id_type;
typedef u32 task_id_type;
typedef u32 user_id_type;
typedef u32 group_id_type;
typedef u64 time_type;
typedef u32 state_type;
typedef unsigned int mailbox_id_type;
typedef unsigned int mutex_id_type;
typedef volatile int spinlock_type;
typedef unsigned int limit_type;

#endif /* !__STORM_TYPES_H__ */
