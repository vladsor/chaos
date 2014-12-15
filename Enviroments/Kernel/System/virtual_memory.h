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

#include <ipool.h>
#include <rpool.h>

enum
{
    LEVEL_SYSTEM,
    LEVEL_USER
};

enum
{
//    VIRTUAL_MEMORY_OPTION_PHYSICAL_ALLOCATE = 0,
//    VIRTUAL_MEMORY_OPTION_PHYSICAL_RESERVE = 1,
//    VIRTUAL_MEMORY_OPTION_PHYSICAL_NOT_USE = 2,

    VIRTUAL_MEMORY_OPTION_ONLY_VIRTUAL = BIT_VALUE (1),
    
    VIRTUAL_MEMORY_OPTION_READONLY = BIT_VALUE (2),
    VIRTUAL_MEMORY_OPTION_NON_CACHABLE = BIT_VALUE (3),
};

typedef struct
{
    p_physical_memory_t physical_memory;
    
    unsigned int level;
    
    uint16_t code_selector;
    uint16_t data_selector;
    uint16_t stack_selector;
    p_page_directory_t page_directory;
    
    bool is_direct;
    
    p_pool_t block_pool;
    p_pool_of_integers_t node_allocator;
    p_range_node_t node_pool;
    raw_memory_t raw_memory;
    
} virtual_memory_t;    

typedef virtual_memory_t * p_virtual_memory_t;

extern virtual_memory_t virtual_memory_global;

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
extern return_t virtual_memory_init (int argc, char *argv[], char **envp);

extern return_t virtual_memory_create (p_virtual_memory_t virtual_memory, 
    p_physical_memory_t physical_memory, unsigned int level);

extern return_t virtual_memory_destroy (p_virtual_memory_t memory);

extern return_t virtual_memory_reserve (p_virtual_memory_t virtual_memory, 
    page_number_t start_virtual_page, uint32_t pages,
    p_page_number_t start_physical_page, unsigned int options);

extern return_t virtual_memory_allocate (p_virtual_memory_t virtual_memory, 
    p_page_number_t start_virtual_page, uint32_t pages,
    p_page_number_t start_physical_page, unsigned int options);
    
extern return_t virtual_memory_deallocate (p_virtual_memory_t memory, 
    page_number_t start_page, unsigned int pages);

//extern return_t virtual_memory_reallocate (p_virtual_memory_t memory,
//    p_page_number_t start_page, unsigned int pages);

extern return_t virtual_memory_check (p_virtual_memory_t memory,
    page_number_t start_page, unsigned int pages, unsigned int flags);
    
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
extern return_t virtual_memory_lookup (p_virtual_memory_t memory,
    page_number_t virtual_page, p_page_number_t physical_page, 
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
extern return_t virtual_memory_map (p_virtual_memory_t memory,
    page_number_t virtual_page, page_number_t physical_page, 
    unsigned int pages, unsigned int flags);

#endif /* !__STORM_IA32_MEMORY_VIRTUAL_H__ */

