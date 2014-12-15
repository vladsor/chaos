/* $Id: byte_order.h,v 1.2 2001/02/10 21:23:15 jojo Exp $ */
/* Abstract: Inline functions for swapping byte order. */
/* Author: Per Lundberg <plundis@chaosdev.org> */

/* Copyright 1999-2000 chaos development. */

#ifndef __LIBRARY_SYSTEM_BYTE_ORDER_H__
#define __LIBRARY_SYSTEM_BYTE_ORDER_H__

/* 486 and above have the neat instruction 'bswap' which makes life a
   lot easier. */

#if CPU_FAMILY > 3

static inline uint32_t byte_swap_uint32 (uint32_t x)
{
    /* Swap the bytes. */

    asm (
      "bswap  %0"
      : "=r" (x)
      : "0" (x));
  
    return x;
}

#else

static inline uint32_t byte_swap_uint32 (uint32_t x)
{
    asm (
        /* Swap lower bytes. */
        "xchgb       %b0, %h0\n"

        /* Swap u16s. */
        "rorl        $16, %0\n"

        /* Swap higher bytes. */
        "xchgb       %b0, %h0\n"
    : "=q" (x)
    : "0" (x));

    return x;
}

#endif /* (!defined __i486__) && (!defined __i586__) && (!defined __i686) */

static inline uint16_t byte_swap_uint16 (uint16_t x)
{
    asm (
        "xchgb %b0, %h0"
    : "=q" (x) 
    : "0" (x));

    return x;
}

#endif /* !__LIBRARY_SYSTEM_BYTE_ORDER_H__ */
