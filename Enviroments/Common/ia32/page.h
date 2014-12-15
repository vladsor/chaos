/** 
 * @file                page.h
 * @brief               Page description and functions. 
 * @author              Per Lundberg <per@chaosdev.org>
 * @author              Henrik Hallin <hal@chaosdev.org>
 * @author              Vladimir Sorokin          
 * @version             1.0
 * @date                2002-2004
 */

#ifndef __ENVIROMENT_IA32_PAGE_H__
#define __ENVIROMENT_IA32_PAGE_H__

/**
 * @brief               The size of a physical page. 
 */
#define PAGE_SIZE       (0x1000U)

/** 
 * @brief Calculate the number of pages needed to hold this number of bytes. 
 */
#define SIZE_IN_PAGES(x)        (((x) % PAGE_SIZE) != 0 ? \
                                 ((x) / PAGE_SIZE) + 1 : \
                                 ((x) / PAGE_SIZE))

/**
 *  @brief Get page index of the address.
 */
#define GET_PAGE_NUMBER(x)              ((u32) (x) / PAGE_SIZE)

/**
 *  @brief Get offset in page of the address.
 */
#define GET_OFFSET_IN_PAGE(x)           ((u32) (x) % PAGE_SIZE)

#endif /* !__ENVIROMENT_I32_PAGE_H__ */
