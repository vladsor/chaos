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

/* Allocate a number of pages. */
return_t physical_memory_allocate (page_number_t *pointer, unsigned int pages)
{
    return_t rv;
    range_t range;
    
    range.start = 0;
    range.length = pages;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	"%s::%s Pointer: %p, Pages: %u, Range: %p.\n", 
	__FILE__, __FUNCTION__, pointer, pages, &range);
	
    rv = pool_allocate (&block_pool, &range);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Range[%u] is %u-%u {%u}.\n", 
        rv, range.start, range.start + range.length - 1, block_pool.free_count);

    (*pointer) = range.start;
    
    if (range.start == 0)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
            "%s : Failed.[%u]\n",
            __FUNCTION__, block_pool.free_count);
	
        return STORM_RETURN_OUT_OF_MEMORY;
    }

    return STORM_RETURN_SUCCESS;
}
