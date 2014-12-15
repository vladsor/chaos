/* $chaos: memory_physical.c,v 1.28 2002/10/20 19:30:33 per Exp $ */
/* Abstract: Physical memory allocation. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <enviroment.h>
#include <rpool.h>

//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

extern pool_t block_pool;

return_t physical_memory_deallocate (page_number_t start_page, 
    unsigned int pages) 
{
    return_t return_value;
    range_t range = {start_page, pages};

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "Physical Memory Deallocate: %u-%u\n", 
        start_page, start_page + pages - 1);

    return_value = pool_deallocate (&block_pool, range);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Result: %u {%u}.\n", 
        return_value, block_pool.free_count);
    
    return STORM_RETURN_SUCCESS;
}
