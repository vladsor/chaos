/**
 * @file                ia32/Segmentation/selector.h
 * @brief               Segment selector description.
 * @author              Vladimir Sorokin
 * @version             0.2
 * @date                2002-2004
 */

/** 
 * @addtogroup group_segmentation
 *
 * @{
 */

/** 
 * @defgroup group_segmentation_selectors Segment selectors
 *
 * @brief               Segment selectors in x86 architecture.
 *
 * @{
 */

#ifndef __SYSTEM_ENVIROMENT_IA32_SELECTOR_H__
#define __SYSTEM_ENVIROMENT_IA32_SELECTOR_H__

/**
 * @brief               A segment selector.
 *
 * A segment selector is a 16-bit identifier for a segment. It does not point
 * directly to the segment, but instead points to the segment descriptor that
 * defines the segment.
 */
typedef struct
{
    /**
     * @brief           Requested Privilege Level (RPL) (Bits 0 and 1). 
     *
     * Specifies the privilege level of the selector. The privilege level can 
     * range from 0 to 3, with 0 being the most privileged level. Refer to 
     * Section 4.5., "Privilege Levels" in Chapter 4, Protection for a 
     * description of the relationship of the RPL to the CPL of the executing 
     * program (or task) and the descriptor privilege level (DPL) of the
     * descriptor the segment selector points to.
     */
    uint16_t RPL   : 2;

    /**
     * @brief           TI (table indicator) flag (Bit 2).
     *
     * Specifies the descriptor table to use: clearing this flag selects the 
     * GDT; setting this flag selects the current LDT.
     */
    uint16_t TI    : 1;

    /**
     * @brief           Index (Bits 3 through 15). 
     *
     * Selects one of 8192 descriptors in the GDT or LDT. The processor 
     * multiplies the index value by 8 (the number of bytes in a segment 
     * descriptor) and adds the result to the base address of the GDT or LDT 
     * (from the GDTR or LDTR register, respectively).
     */
    uint16_t index : 13;
} selector_t PACKED;

/**
 * @brief               Segment selector.
 * @param index         Index in global table
 * @param ldt           Flag if using local table
 * @param rpl           Privilege level
 */
#define SELECTOR(index,ldt,rpl) \
                        (((index) << 3) | ((ldt) << 2) | (rpl))

#define SELECTOR_GET_DESCRIPTOR_INDEX(selector) ((selector) >> 3)

#endif /* !__SYSTEM_ENVIROMENT_IA32_SELECTOR_H__ */

/**
 * }@ // end of group group_segmentation_selectors
 */

/**
 * }@ // end of group group_segmentation
 */


