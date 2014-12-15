/* $chaos: gdt.h,v 1.10 2002/10/14 21:40:02 per Exp $ */

/**
 * @file                ia32/Segmentation/gdt.h 
 * @brief               GDT description and functions.
 * @author              Per Lundberg <per@chaosdev.org>
 * @author              Henrik Hallin <hal@chaosdev.org>
 * @author              Vladimir Sorokin
 * @version             1.12
 * @date                1998-2004
 */

/** 
 * @addtogroup group_segmentation
 *
 * @{
 */

/** 
 * @defgroup group_segmentation_gdt GDT
 *
 * @brief               Global Descriptors Table (GDT).
 *
 * @{
 */

#ifndef __SYSTEM_ENVIROMENT_IA32_GDT_H__
#define __SYSTEM_ENVIROMENT_IA32_GDT_H__

/**
 * @brief               The GDT (Global Descriptors Table).
 */
extern descriptor_t gdt[];

/**
 * @brief               Setup a TSS descriptor gate in the GDT.
 * @param entry         The entry in the GDT to set it at.
 * @param address       The address of the TSS.
 * @param tss_size      The sizeof TSS segment.
 * @param dpl           The DPL (Descriptor Privilege Level, see Intel
 *                      documentation)
 */
static inline void gdt_setup_tss_descriptor (uint16_t entry, tss_t *address,
	int tss_size, int dpl)
{
  ((uint64_t *) gdt)[entry] = DESCRIPTOR_TSS ((uint32_t) address, tss_size, 
      SEGMENT_GRANULARITY_BYTE, dpl, SEGMENT_PRESENT, SEGMENT_DIGIT_32);
}

/**
 * @brief               Setup a call gate descriptor in the GDT.
 * @param entry         The entry in the GDT to set it at.
 * @param selector      The selector of function's segment.
 * @param address       The address of the function.
 * @param dpl           The DPL (Descriptor Privilege Level, see Intel
 *                      documentation)
 * @param params        The number of function's pameters.
 */
static inline void gdt_setup_call_gate (uint16_t entry, uint16_t selector,
	address_t address, int dpl, uint8_t params)
{
  ((uint64_t *) gdt)[entry] = DESCRIPTOR_CALL_GATE (selector, 
      (uint32_t) address, dpl, params, SEGMENT_PRESENT);
}

#endif /* !__SYSTEM_ENVIROMENT_IA32_GDT_H__ */

/**
 * }@ // end of group group_segmentation_gdt
 */

/**
 * }@ // end of group group_segmentation
 */

