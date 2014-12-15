#ifndef __STORM_PHYSICAL_MEMORY_H__
#define __STORM_PHYSICAL_MEMORY_H__

#include <ipool.h>
#include <rpool.h>

typedef struct
{
    pool_t block_pool;
    p_pool_of_integers_t node_allocator;
    p_range_node_t node_pool;
    raw_memory_t raw_memory;
    
} physical_memory_t;    

typedef physical_memory_t * p_physical_memory_t;

extern physical_memory_t physical_memory_global;

extern return_t physical_memory_init (int argc, char *argv[], char **envp);

/**
 * @brief               Reserve a pages.
 * @param pointer       A start page number.
 * @param pages         The number of pages to reserve.
 * @return              STORM_RETURN_SUCCESS if successful.
 */
extern return_t physical_memory_reserve (p_physical_memory_t memory,
    page_number_t start_page, unsigned int pages);

/**
 * @brief               Allocate a number of pages. 
 * @param start_page    A pointer to where the function will put start 
 *                      page number to the allocated memory.
 * @param pages         The number of pages to allocate.
 * @return              STORM_RETURN_SUCCESS if successful.
 */
extern return_t physical_memory_allocate (p_physical_memory_t memory,
    page_number_t *start_page, unsigned int pages);

/**
 * @brief               Deallocate a pages.
 * @param pointer       A start page number.
 * @param pages         The number of pages to deallocate.
 * @return              STORM_RETURN_SUCCESS if successful.
 */
extern return_t physical_memory_deallocate (p_physical_memory_t memory,
    page_number_t start_page, unsigned int pages);

/**
 * @brief               Reallocate a number of pages. 
 * @param start_page    A pointer to where the function will put start 
 *                      page number to the reallocated memory.
 * @param pages         The number of pages to allocate.
 * @return              STORM_RETURN_SUCCESS if successful.
 */
extern return_t physical_memory_reallocate (p_physical_memory_t memory,
    page_number_t *start_page, unsigned int pages);

extern return_t physical_memory_check (p_physical_memory_t memory,
    page_number_t start_page, unsigned int pages, unsigned int flags);

extern uint32_t physical_memory_get_total_pages (p_physical_memory_t memory);
extern uint32_t physical_memory_get_free_pages (p_physical_memory_t memory);

#endif /* !__STORM_PHYSICAL_MEMORY_H__ */

