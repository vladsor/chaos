/* $chaos: memory_physical.c,v 1.28 2002/10/20 19:30:33 per Exp $ */
/* Abstract: Physical memory allocation. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <enviroment.h>

#define DEBUG_MODULE_NAME "PhysicalMemory"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE1
#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include <debug/macros.h>

/* Allocate a number of pages. */
return_t physical_memory_allocate (p_physical_memory_t memory, 
    p_page_number_t pointer, unsigned int pages)
{
    return_t return_value;
    range_t range;
    
    range.start = 0;
    range.length = pages;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (Pointer: %p, Pages: %u, Range: %p).\n", 
        DEBUG_MODULE_NAME, __FUNCTION__, 
        pointer, pages, &range);
	
    return_value = pool_allocate (&memory->block_pool, &range);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1, 
        "%s: %s Range[%u] is %u-%u {%u, %u}.\n", 
        DEBUG_MODULE_NAME, __FUNCTION__, 
        return_value, range.start, range.start + range.length - 1, 
        memory->block_pool.free_count, memory->node_allocator->used_blocks);

    (*pointer) = range.start;
    
    if (range.start == 0)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
            "%s: %s: Failed. rv: %u, [%u], %u\n",
            DEBUG_MODULE_NAME, __FUNCTION__, 
            return_value, memory->block_pool.free_count, 
            memory->node_allocator->used_blocks);

        (* (p_uint32_t) NULL) = 1;
        	
        return STORM_RETURN_OUT_OF_MEMORY;
    }

    return STORM_RETURN_SUCCESS;
}

