/* $chaos: memory_virtual.h,v 1.8 2002/10/23 07:26:51 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file                        memory_virtual.h
 * @brief                       Virtual memory prototypes and data structures. 
 */

#ifndef __STORM_IA32_MEMORY_VIRTUAL_H__
#define __STORM_IA32_MEMORY_VIRTUAL_H__

extern page_directory_t *global_page_directory;

/**
 * @brief               Flags used when creating new entries in the page
 *                      directory.
 *
 * We let the page table set everything, so we need to have this
 * all-privileged. 
 */

/** 
 * @brief Initialize the virtual memory system. 
 */
extern return_t virtual_memory_init (int argc, char *argv[]);

/**
 * @brief               Find the mapping that a page is mapped to.
 * @param page_directory
 *                      The page directory to inspect.
 * @param virtual_page  The virtual page to check.
 * @param physical_page Pointer to where the function will store the
 *                      physical page number (note: not address, but
 *                      page number).
 * @param flags         Pointer to the flags of this mapping.
 * @return              STORM_RETURN_SUCCESS if successful.
 */
extern return_t virtual_memory_lookup (page_directory_t *page_directory,
                                     page_number_t virtual_page,
                                     page_number_t *physical_page,
                                     unsigned int *flags);

/**
 * @brief               Map memory into the given page directory. 
 * @param page_directory
 *                      The page directory in which to map.
 * @param virtual_page  The virtual page base.
 * @param physical_page The physical page base.
 * @param pages         The number of pages to map.
 * @param flags         The page flags to use.
 * @return              STORM_RETURN_SUCCESS if successful.
 */
extern return_t virtual_memory_map (page_directory_t *page_directory,
                                    page_number_t virtual_page, 
                                    page_number_t physical_page,
                                    unsigned int pages,
                                    unsigned int flags);

#endif /* !__STORM_IA32_MEMORY_VIRTUAL_H__ */
