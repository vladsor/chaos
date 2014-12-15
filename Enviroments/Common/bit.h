/** 
 * @file                bit.h
 * @brief               Bit manipulation macros. 
 * @author              Per Lundberg <per@chaosdev.org>,
 *                      Henrik Hallin <hal@chaosdev.org>,
 *                      Vladimir Sorokin
 * @version             1.4
 * @date                1998-2004
 *
 * This file is endian-specific and needs to be rewritten for
 * big-endian when we port to such a CPU. It provides very convenient
 * functions for reading and writing bit values to a integers, as well
 * as reading the upper/lower half of a 32-bit and 16-bit integer.
 */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#ifndef __ENVIROMENT_IA32_BIT_H__
#define __ENVIROMENT_IA32_BIT_H__

/** 
 * @brief               Get the low 32 bits of a 64-bit integer variable. 
 */
#define LOW_32(x)       ((x) & 0xFFFFFFFFUL)

/** 
 * @brief               Get the high 32 bits of a 64-bit integer variable. 
 */
#define HIGH_32(x)      ((x) >> 32)

/** 
 * @brief               Get the low 16 bits of a 32-bit integer variable. 
 */
#define LOW_16(x)       ((x) & 0xFFFF)

/** 
 * @brief               Get the high 16 bits of a 32-bit integer variable. 
 */
#define HIGH_16(x)      (((x) >> 16) & 0xFFFF)

/**
 * @brief               Get the low 8 bits of a 16-bit integer variable. 
 */
#define LOW_8(x)        ((x) & 0xFF)

/**
 * @brief               Get the high 8 bits of a 16-bit integer variable. 
 */
#define HIGH_8(x)       (((x) >> 8) & 0xFF)

/**
 * @brief               Set bit b in a.
 */
#define BIT_SET(a,b)    ((a) |= (1ULL << (b)))

/**
 * @brief               Clear bit b in a.
 */
#define BIT_CLEAR(a,b)  ((a) &= ~(1ULL << (b)))

/**
 * @brief               Switch bit b in a.
 */
#define BIT_SWITCH(a,b) ((a) ^= (1ULL << (b)))

/**
 * @brief               Get bit b in a.
 */
#define BIT_GET(a,b)    ((a) & (1ULL << (b)) ? 1 : 0) 

/**
 * @brief               Calculate the number of bytes for a bits.
 */
#define BIT_IN_BYTES(a) ((a) & 0x7 != 0 ? (a) >> 3 + 1 : (a) >> 3)

/**
 * @brief               Get the numeric value for bit x. 
 */
#define BIT_VALUE(x)    (1ULL << (x))

/**
 * @brief               Select bits 31..low in x
 */
#define BITS_SELECT_HIGH(x,low) \
			(((x)) & ~((1ULL << (low)) - 1))

/**
 * @brief               Select bits high..0 in x
 */
#define BITS_SELECT_LOW(x,high) \
			(((x)) & ((1ULL << ((high) + 1)) - 1))

/**
 * @brief               Select bits high..low in x
 */
#define BITS_SELECT(x,high,low) \
			BITS_SELECT_HIGH(BITS_SELECT_LOW(x,high),low)

/**
 * @brief               Get bits 31..low from x
 */
#define BITS_GET_HIGH(x,low) \
			(BITS_SELECT_HIGH(x,low) >> low)

/**
 * @brief               Get bits high..0 from x
 */
#define BITS_GET_LOW(x,high) \
			(BITS_SELECT_LOW(x,high))

/**
 * @brief               Get bits high..low from x
 */
#define BITS_GET(x,high,low) \
			(BITS_SELECT(x,high,low) >> low)

/**
 * @brief               Set bits 31..low in x
 */
#define BITS_SET_HIGH(x,low) \
			((x) |= ~((1ULL << (low)) - 1))

/**
 * @brief               Set bits high..0 in x
 */
#define BITS_SET_LOW(x,high) \
			((x) |= ((1ULL << ((high) + 1)) - 1))

/**
 * @brief               Set bits high..low in x
 */
#define BITS_SET(x,high,low) \
			((x) |= ((~((1ULL << (low)) - 1)) & \
			((1ULL << ((high) + 1)) - 1)))

/**
 * @brief               Clear bits 31..low in x
 */
#define BITS_CLEAR_HIGH(x,low) \
			((x) &= ((1ULL << (low)) - 1))

/**
 * @brief               Clear bits high..0 in x
 */
#define BITS_CLEAR_LOW(x,high) \
			((x) &= ~((1ULL << ((high) + 1)) - 1))

/**
 * @brief               Clear bits hight..low in x
 */
#define BITS_CLEAR(x,high,low) \
			((x) &= ~((~((1ULL << (low)) - 1)) & \
			((1ULL << ((high) + 1)) - 1)))

/**
 * @brief               Switch bits 31..low in x
 */
#define BITS_SWITCH_HIGH(x,low) \
			((x) ^= ~((1ULL << (low)) - 1))

/**
 * @brief               Switch bits high..0 in x
 */
#define BITS_SWITCH_LOW(h,high) \
			((x) ^= ((1ULL << ((high) + 1)) - 1))

/**
 * @brief               Switch bits high..low in x
 */
#define BITS_SWITCH(x,high,low) \
			((x) |= ((~((1ULL << (low)) - 1)) & \
			((1ULL << ((high) + 1)) - 1)))


/**
 * @brief               Declare bit map.
 * @param name          Name of map
 * @param length        Capacity
 */
#define BIT_MAP_DECLARE(name,length) \
			uint32_t name[(length) & 0x1F != 0 ? \
			    (length) >> 5 + 1 : (length) >> 5]

/**
 * @brief               Set bit in map
 * @param name          Name of map
 * @param index         Bit number
 */
#define BIT_MAP_SET(name,index) \
			BIT_SET ((name)[(index) >> 5], (index) & 0x1F)

/**
 * @brief               Clear bit in map
 * @param name          Name of map
 * @param index         Bit number
 */
#define BIT_MAP_CLEAR(name,index) \
			BIT_CLEAR ((name)[(index) >> 5], (index) & 0x1F)

/**
 * @brief               Switch bit in map
 * @param name          Name of map
 * @param index         Bit number
 */
#define BIT_MAP_SWITCH(name,index) \
			BIT_SWITCH ((name)[(index) >> 5], (index) & 0x1F)

#endif /* !__ENVIROMENT_IA32_BIT_H__ */
