/**
 * @file                ia32/limits.h
 * @brief               Function prototypes for IDT functions. 
 * @author              Per Lundberg <per@chaosdev.org>
 * @author              Vladimir Sorokin
 * @version             1.0
 * @date                1998-2004
 */

#ifndef __SYSTEM_ENVIROMENT_IA32_LIMITS_H__
#define __SYSTEM_ENVIROMENT_IA32_LIMITS_H__

/**
 * @brief               The number of max entries in the GDT.
 */
#define GDT_ENTRIES     (256)

/**
 * @brief               The size of the GDT.
 */
#define GDT_SIZE        (GDT_ENTRIES * sizeof (descriptor_t))

/**
 * @brief               The number of entries in the IDT.
 */
#define IDT_ENTRIES     (256)

/**
 * @brief               The size of the IDT.
 */
#define IDT_SIZE        (IDT_ENTRIES * sizeof (descriptor_t))

#endif /* !__SYSTEM_ENVIROMENT_IA32_LIMITS_H__ */

