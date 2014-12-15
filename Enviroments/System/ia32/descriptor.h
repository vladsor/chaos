/* $chaos: descriptor.h,v 1.6 2002/10/14 21:29:50 per Exp $ */

/**
 * @file                descriptor.h
 * @brief               The descriptor structure. 
 * @author              Per Lundberg <per@chaosdev.org>
 * @author              Vladimir Sorokin
 * @version             1.7
 * @date                1998-2004
 */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#ifndef __SYSTEM_ENVIROMENT_IA32__DESCRIPTOR_H__
#define __SYSTEM_ENVIROMENT_IA32__DESCRIPTOR_H__

/**
 * attributes of descriptors
 */
#define PRIVILEGE_LEVEL_SYSTEM    0
#define PRIVILEGE_LEVEL_USER      3
#define SEGMENT_PRESENT           0x80
#define SEGMENT_NOT_PRESENT       0
#define SEGMENT_SIZE_MAX          0xFFFFFF
#define SEGMENT_DIGIT_16          0
#define SEGMENT_DIGIT_32          0x40
#define SEGMENT_GRANULARITY_BYTE  0
#define SEGMENT_GRANULARITY_PAGE  0x80

/**
 * @brief               Descriptor types.
 */
enum descriptor_type
{
    /**
     * @brief           A 32-bit task gate.
     */
    DESCRIPTOR_TYPE_TASK_GATE_32 = 5,

    /**
     * @brief           A TSS gate.
     */
    DESCRIPTOR_TYPE_TSS = 9,

    /**
     * @brief           A call gate.
     */
    DESCRIPTOR_TYPE_CALL_GATE = 12,

    /**
     * @brief           A 32-bit interrupt gate.
     */
    DESCRIPTOR_TYPE_INTERRUPT_GATE_32 = 14,

    /**
     * @brief           A 32-bit trap gate. 
     */
    DESCRIPTOR_TYPE_TRAP_GATE_32 = 15,
};

/**
 * @brief               Empty descriptor
 */
#define DESCRIPTOR_NULL 0ULL

/**
 * @brief               Descriptor of code segment
 */
#define DESCRIPTOR_CODE(base,limit,granularity,dpl,present,digit) (            \
    (BITS_GET_LOW((limit),15)) |                                               \
    (((uint64_t)BITS_GET_LOW((base),23)) << 16) |                              \
    ((((uint64_t) ((present) | 0x18 | ((dpl) << 5)))) << 40) |                 \
    ((((uint64_t) (BITS_GET((limit),19,16) | (digit) | (granularity)))) << 48) | \
    ((((uint64_t) BITS_GET(base,31,24))) << 56))

#define DESCRIPTOR_DATA(base,limit,granularity,dpl,present,digit) (            \
    (BITS_GET_LOW((limit),15)) |                                               \
    (((uint64_t)BITS_GET_LOW((base),23)) << 16) |                              \
    ((((uint64_t) ((present) | 0x12 | ((dpl) << 5)))) << 40) |                 \
    ((((uint64_t) (BITS_GET((limit),19,16) | (digit) | (granularity)))) << 48) | \
    ((((uint64_t) BITS_GET(base,31,24))) << 56))

#define DESCRIPTOR_STACK(base,limit,granularity,dpl,present,digit) (           \
  (BITS_GET_LOW((limit),15)) |                                                 \
  (((uint64_t)BITS_GET_LOW((base),23)) << 16) |                                \
  ((((uint64_t) ((present) | 0x16 | ((dpl) << 5)))) << 40) |                   \
  ((((uint64_t) (BITS_GET((limit),19,16) | (digit) | (granularity)))) << 48) | \
  ((((uint64_t) BITS_GET(base,31,24))) << 56))

#define DESCRIPTOR_TSS(address,size,granularity,dpl,present,digit) (           \
  (BITS_GET_LOW((size),15)) |                                                  \
  (((uint64_t)BITS_GET_LOW((address),23)) << 16) |                             \
  ((((uint64_t) ((present) | DESCRIPTOR_TYPE_TSS | ((dpl) << 5)))) << 40) |    \
  ((((uint64_t) (BITS_GET((size),19,16) | (digit) | (granularity)))) << 48) |  \
  ((((uint64_t) BITS_GET(address,31,24))) << 56))

#define DESCRIPTOR_CALL_GATE(selector,address,dpl,params,present) (            \
  (BITS_GET_LOW((address),15)) |                                               \
  (((uint64_t) (selector)) << 16) |                                            \
  (((uint64_t) (params)) << 32) |                                              \
  ((((uint64_t) ((present) | 12 | ((dpl) << 5)))) << 40) |                     \
  ((((uint64_t) BITS_GET(address,31,16))) << 48))

#define DESCRIPTOR_INTERRUPT_GATE(selector,address,dpl,present) (              \
  (BITS_GET_LOW((address),15)) |                                               \
  (((uint64_t) (selector)) << 16) |                                            \
  ((((uint64_t) ((present) | 14 | ((dpl) << 5)))) << 40) |                     \
  ((((uint64_t) BITS_GET(address,31,16))) << 48))

#define DESCRIPTOR_TRAP_GATE(selector,address,dpl,present) (                   \
  (BITS_GET_LOW((address),15)) |                                               \
  (((uint64_t) (selector)) << 16) |                                            \
  ((((uint64_t) ((present) | 15 | ((dpl) << 5)))) << 40) |                     \
  ((((uint64_t) BITS_GET(address,31,16))) << 48))

/** 
 * @brief               A descriptor. 
 */
typedef struct
{
    /**
     * @brief           Low 16 bits of segment limit. 
     */
    uint16_t limit_lo;

    /**
     * @brief           Low 16 bits of base address. 
     */
    uint16_t base_lo;

    /**
     * @brief           Bits 16-23 of base address. 
     */
    uint8_t base_hi;

    /**
     * @brief           Segment type. 
     */
    uint8_t type : 4;

    /**
     * @brief           0 = system, 1 = code or data. 
     */
    uint8_t descriptor_type : 1;

    /**
     * @brief           Descriptor privilege level. 
     */
    uint8_t dpl : 2;

    /**
     * @brief           Zero if segment isn't used. 
     */
    uint8_t segment_present : 1;

    /**
     * @brief           High four bits of segment limit. 
     */
    uint8_t limit_hi : 4;

    /* Unused. */
    uint8_t : 1;

    /**
     * @brief           Always zero! 
     */
    uint8_t zero : 1;

    /**
     * @brief           0 = 16-bit, 1 = 32-bit. 
     */
    uint8_t operation_size : 1;

    /**
     * @brief           If 1, segment limit is multiplied by 4096. 
     */
    uint8_t granularity : 1;

    /**
     * @brief           Bits 24-31 of base address. 
     */
    uint8_t base_hi2;
} descriptor_t PACKED;

/**
 * @brief               A gate descriptor. 
 */
typedef struct
{
    /**
     * @brief           Low 16 bits of offset. 
     */
    uint16_t offset_lo;
    uint16_t segment_selector;

    /**
     * @brief           Zero if not type == 12. 
     */
    uint8_t params : 5;

    /*
     * @brief           Zero 
     */
    uint8_t zero : 3;
    uint8_t type : 5;                 

    /**
     * @brief           Descriptor privilege level. 
     */
    uint8_t dpl : 2;

    /**
     * @brief           If zero, this descriptor isn't used. 
     */
    uint8_t present : 1;

    /**
     * @brief           High 16 bits of offset. 
     */
    uint16_t offset_hi;
} gate_descriptor_t PACKED;

#include "gdt.h"
#include "idt.h"

#endif /* !__SYSTEM_ENVIROMENT_IA32__DESCRIPTOR_H__ */

