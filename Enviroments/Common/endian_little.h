/* $Id: little_endian.h,v 1.1 2001/02/10 22:58:14 jojo Exp $ */
/* Abstract: Little endian functions. */
/* Author: Per Lundberg <plundis@chaosdev.org> */

/* Copyright 2000 chaos development. */

#ifndef __LIBRARY_SYSTEM_LITTLE_ENDIAN_H__
#define __LIBRARY_SYSTEM_LITTLE_ENDIAN_H__

#define SYSTEM_LITTLE_ENDIAN

#define little_endian_to_native_uint64(x) (x)
#define little_endian_to_native_uint32(x) (x)
#define little_endian_to_native_uint16(x) (x)

#define big_endian_to_native_uint64(x) (byte_swap_uint64 (x))
#define big_endian_to_native_uint32(x) (byte_swap_uint32 (x))
#define big_endian_to_native_uint16(x) (byte_swap_uint16 (x))

#define native_to_big_endian_uint64(x) (byte_swap_uint64 (x))
#define native_to_big_endian_uint32(x) (byte_swap_uint32 (x))
#define native_to_big_endian_uint16(x) (byte_swap_uint16 (x))

#define native_to_little_endian_uint64(x) (x)
#define native_to_little_endian_uint32(x) (x)
#define native_to_little_endian_uint16(x) (x)

#endif /* !__LIBRARY_SYSTEM_LITTLE_ENDIAN_H__ */
