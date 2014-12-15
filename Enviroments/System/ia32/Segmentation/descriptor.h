/* $chaos: descriptor.h,v 1.6 2002/10/14 21:29:50 per Exp $ */

/**
 * @file                ia32/Segmentation/descriptor.h
 * @brief               The descriptor structure. 
 * @author              Per Lundberg <per@chaosdev.org>
 * @author              Vladimir Sorokin
 * @version             1.7
 * @date                1998-2004
 */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/** 
 * @addtogroup group_segmentation
 *
 * @{
 */

/** 
 * @defgroup group_segmentation_descriptors Segment descriptors
 *
 * @brief               Segment descriptors in x86 architecture.
 *
 * @{
 */

#ifndef __SYSTEM_ENVIROMENT_IA32__DESCRIPTOR_H__
#define __SYSTEM_ENVIROMENT_IA32__DESCRIPTOR_H__

/**
 * attributes of descriptors
 */
enum privilege_level_t
{ 
    PRIVILEGE_LEVEL_KERNEL,
    PRIVILEGE_LEVEL_SYSTEM1,
    PRIVILEGE_LEVEL_SYSTEM2,
    PRIVILEGE_LEVEL_USER,
};

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
enum descriptor_type_t
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
     *
     * Type field Indicates the segment or gate type and specifies the kinds
     * of access that can be made to the segment and the direction of growth.
     * The interpretation of this field depends on whether the descriptor type
     * flag specifies an application (code or data) descriptor or a system
     * descriptor. The encoding of the type field is different for code, data,
     * and system descriptors (refer to Figure 4-1 in Chapter 4, Protection).
     * Refer to Section 3.4.3.1., “Code- and Data-Segment Descriptor Types” for
     * a description of how this field is used to specify code and datasegment
     * types.     
     */
    uint8_t             type : 4;

    /**
     * @brief           S (descriptor type) flag
     *
     * Specifies whether the segment descriptor is for a system segment (S flag
     * is clear) or a code or data segment (S flag is set). 
     */
    uint8_t             descriptor_type : 1;

    /**
     * @brief           DPL (descriptor privilege level) field
     *
     * Specifies the privilege level of the segment. The privilege level can
     * range from 0 to 3, with 0 being the most privileged level. The DPL is
     * used to control access to the segment. Refer to Section 4.5., “Privilege
     * Levels” in Chapter 4, Protection for a description of the relationship
     * of the DPL to the CPL of the executing code segment and the RPL of a
     * segment selector.
     */
    uint8_t             dpl : 2;

    /**
     * @brief           P (segment-present) flag
     *
     * Indicates whether the segment is present in memory (set) or not present
     * (clear). If this flag is clear, the processor generates a
     * segment-not-present exception (#NP) when a segment selector that points
     * to the segment descriptor is loaded into a segment register. Memory
     * management software can use this flag to control which segments are
     * actually loaded into physical memory at a given time. It offers a control
     * in addition to paging for managing virtual memory.<BR>
     * When this flag is clear, the operating system or executive is free to use
     * the locations marked “Available” to store its own data, such as
     * information regarding the whereabouts of the missing segment.
     */
    uint8_t             segment_present : 1;

    /**
     * @brief           High four bits of segment limit. 
     */
    uint8_t             limit_hi : 4;

    /**
     * @brief           Available for system programmer's use.
     * 
     */
    uint8_t             available : 1;

    /**
     * @brief           Reserved (set to 0).
     */
    uint8_t             zero : 1;

    /**
     * @brief           D/B (default operation size/default stack pointer size
     *                  and/or upper bound) flag
     *
     * Performs different functions depending on whether the segment descriptor
     * is an executable code segment, an expand-down data segment, or a stack
     * segment. (This flag should always be set to 1 for 32-bit code and data
     * segments and to 0 for 16-bit code and data segments.)
     * <UL>
     *    <LI>     
     *        Executable code segment. The flag is called the D flag and it
     *        indicates the default length for effective addresses and operands
     *        referenced by instructions in the segment. If the flag is set,
     *        32-bit addresses and 32-bit or 8-bit operands are assumed; if it
     *        is clear, 16-bit addresses and 16-bit or 8-bit operands are
     *        assumed. The instruction prefix 66H can be used to select an
     *        operand size other than the default, and the prefix 67H can be
     *        used select an address size other than the default.
     *    </LI>
     *    <LI>
     *        Stack segment (data segment pointed to by the SS register). The
     *        flag is called the B (big) flag and it specifies the size of the
     *        stack pointer used for implicit stack operations (such as pushes,
     *        pops, and calls). If the flag is set, a 32-bit stack pointer is
     *        used, which is stored in the 32-bit ESP register; if the flag is
     *        clear, a 16-bit stack pointer is used, which is stored in the
     *        16-bit SP register. If the stack segment is set up to be an
     *        expand-down data segment (described in the next paragraph), the
     *        B flag also specifies the upper bound of the stack segment.
     *    </LI>
     *    <LI>
     *        Expand-down data segment. The flag is called the B flag and it
     *        specifies the upper bound of the segment. If the flag is set, the
     *        upper bound is FFFFFFFFH (4 GBytes); if the flag is clear, the
     *        upper bound is FFFFH (64 KBytes).
     *    </LI>
     * </UL>
     */     
    uint8_t             default_operation_size : 1;

    /**
     * @brief           G (granularity) flag
     *
     * Determines the scaling of the segment limit field. When the granularity
     * flag is clear, the segment limit is interpreted in byte units; when flag
     * is set, the segment limit is interpreted in 4-KByte units. (This flag
     * does not affect the granularity of the base address; it is always byte
     * granular.) When the granularity flag is set, the twelve least significant
     * bits of an offset are not tested when checking the offset against the
     * segment limit. For example, when the granularity flag is set, a limit of
     * 0 results in valid offsets from 0 to 4095.
     */
    uint8_t             granularity : 1;

    /**
     * @brief           Bits 24-31 of base address. 
     */
    uint8_t             base_hi2;
} descriptor_t PACKED;

/**
 * @brief               A gate descriptor. 
 */
typedef struct
{
    /**
     * @brief           Low 16 bits of offset. 
     */
    uint16_t            offset_lo;
    
    /**
     * @brief           Segment selector.
     */
    uint16_t            segment_selector;

    /**
     * @brief           Zero if not type == 12. 
     */
    uint8_t             params : 5;

    /*
     * @brief           Zero 
     */
    uint8_t             zero : 3;
    uint8_t             type : 5;                 

    /**
     * @brief           Descriptor privilege level. 
     */
    uint8_t             dpl : 2;

    /**
     * @brief           If zero, this descriptor isn't used. 
     */
    uint8_t             present : 1;

    /**
     * @brief           High 16 bits of offset. 
     */
    uint16_t            offset_hi;
} gate_descriptor_t PACKED;

#endif /* !__SYSTEM_ENVIROMENT_IA32__DESCRIPTOR_H__ */

/**
 * }@ // end of group group_segmentation_descriptors
 */

/**
 * }@ // end of group group_segmentation
 */


