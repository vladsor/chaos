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

return_t physical_memory_reserve (page_number_t start_page, 
    unsigned int pages) 
{
    range_t range = {start_page, pages};
    return_t rv = 0;
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	"%s: %u-%u pages [%u].\n", 
	__FUNCTION__, start_page, start_page + pages - 1, 
	block_pool.free_count);
    
    rv = pool_reserve (&block_pool, range);    
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	"%s return value: %u [%u].\n", 
	__FUNCTION__, rv, block_pool.free_count);
    
    return STORM_RETURN_SUCCESS;
}
