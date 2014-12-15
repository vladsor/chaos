/**
 * @file                defines.h
 * @brief               Generic storm defines. 
 * @author              Per Lundberg <per@chaosdev.org>,
 *                      Henrik Hallin <hal@chaosdev.org>,
 *                      Vladimir Sorokin
 * @version             1.16
 * @date                1998-2002
 */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#ifndef __ENVIROMENT_DEFINES_H__
#define __ENVIROMENT_DEFINES_H__

#undef NULL
/**
 * @brief               A pointer to the lowest accessible memory address.
 *
 * This address is not mapped. Therefore, it may be used for
 * specifying an "empty pointer", pointing to nothing -- a very common
 * programming practice.
 */
#define NULL            ((void *) 0)

/**
 * @brief               A true boolean value.
 */
#define TRUE            (1 == 1)

/**
 * @brief               A false boolean value.
 */
#define FALSE           (!TRUE)

/**
 * @brief               The minimum of the two values.
 */
#define MIN(a,b)        ((a) < (b) ? (a) : (b))

/**
 * @brief               The maximum of the two values.
 */
#define MAX(a,b)        ((a) > (b) ? (a) : (b))

/**
 * @brief               A kibibyte.
 */
#define KIB             (1024U)

/**
 * @brief               A mibibyte.
 */
#define MIB             (1024U * KIB)

/**
 * @brief               A gibibyte.
 */
#define GIB             (1024U * MIB)

/**
 * @brief               Use this define to attribute that the function
 *                      will not ever return. 
 */
#define NORETURN        __attribute__ ((noreturn))

/**
 * @brief               Use this define to tell the compiler that an
 *                      argument or variable is not used. 
 */
#define UNUSED          __attribute__ ((unused))

/**
 * @brief               Use this define to mark a function as deprecated.
 */
#define DEPRECATED      __attribute__ ((deprecated))

/**
 * @brief               Use this define to tell the compiler that a
 *                      structure should be packed.
 * 
 * A packed structure uses no padding, which may otherwise be put in
 * by the compiler to get a certain alignment on the data. For some
 * structures that are locked to a specific format (for example a
 * binary file format), such practices are directly harmful and you
 * need to mark such structures as PACKED for the code to work
 * properly..
 */
#define PACKED          __attribute__ ((packed))

#define ALIGNED(x)		__attribute__ ((aligned (x)))

/**
 *  @brief              Get absolute value of the number.
 */
#define ABS(a)          ((a) >= 0 ? (a) : (-(a)))

/**
 *  @brief              Round to the closest lower number.
 */
#define ROUND_DOWN(N, S)((N) - ((N) % (S)))

/**
 *  @brief              Round to the closest higher number.
 */
#define ROUND_UP(N, S)  ((((N) + (S) - 1) / (S)) * (S))

/**
 * @brief               Convert a number to the closest aligned address above x.
 */
#define ALIGN(x,align)  ((x) % (align) == 0 ? \
                         (x) : \
                         (x) + ((align) - \
                               ((x) % (align))))

#undef offset_of
#define offset_of(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

#endif /* !__ENVIROMENT_DEFINES_H__ */
