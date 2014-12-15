/* $chaos: memory_physical.c,v 1.28 2002/10/20 19:30:33 per Exp $ */
/* Abstract: Physical memory allocation. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <enviroment.h>

#define DEBUG_MODULE_NAME "PhysicalMemory"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include <debug/macros.h>

return_t physical_memory_deallocate (p_physical_memory_t memory, 
    page_number_t start_page, unsigned int pages) 
{
    return_t return_value;
    range_t range = {start_page, pages};

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s: %u-%u\n", 
        DEBUG_MODULE_NAME, __FUNCTION__,
        start_page, start_page + pages - 1);

    return_value = pool_deallocate (&memory->block_pool, range);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Result: %u {%u}.\n", 
        return_value, memory->block_pool.free_count);
    
    return STORM_RETURN_SUCCESS;
}

