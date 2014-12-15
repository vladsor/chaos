/* $Id: alignment.h,v 1.1 2001/02/10 22:58:13 jojo Exp $ */
/* Abstract: Alignment functions. */
/* Author: Anders Ohrt <doa@chaosdev.org> */

/* Copyright 2000 chaos development. */


#ifndef __LIBRARY_SYSTEM_ALIGNMENT_H__
#define __LIBRARY_SYSTEM_ALIGNMENT_H__

#if defined __i386__

#define system_get_unaligned_u32(pointer) (*(u32 *) (pointer))
#define system_get_unaligned_u16(pointer) (*(u16 *) (pointer))
#define system_get_unaligned_u8(pointer) (*(u8 *) (pointer))

#define system_get_unaligned_s32(pointer) (*(s32 *) (pointer))
#define system_get_unaligned_s16(pointer) (*(s16 *) (pointer))
#define system_get_unaligned_s8(pointer) (*(s8 *) (pointer))

#endif

#endif /* !__LIBRARY_SYSTEM_ALIGNMENT_H__ */
