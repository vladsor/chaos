/* $chaos: memory_virtual.c,v 1.12 2002/10/24 20:41:50 per Exp $ */
/* Abstract: Virtual memory routines. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <enviroment.h>

#include "Include/page.h"
#include "Include/internal.h"

#define DEBUG_MODULE_NAME "VirtualMemory"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include <debug/macros.h>

//uint32_t last_address;
//static range_node_t temp_buffer[1000];
//STATIC_POOL (pool, 1000);

virtual_memory_t virtual_memory_global =
{
    physical_memory: &physical_memory_global,
    level: LEVEL_SYSTEM,

    code_selector: SELECTOR_KERNEL_CODE,
    data_selector: SELECTOR_KERNEL_DATA,
    stack_selector: SELECTOR_KERNEL_DATA,
    
    page_directory: page_directory_global,

    is_direct: TRUE,

    block_pool: NULL,
    node_allocator: NULL,
    node_pool: NULL,
    raw_memory: INTERNAL_MEMORY_INIT (NULL),
};

/* Map memory. */

return_t virtual_memory_map (p_virtual_memory_t memory, 
    page_number_t virtual_page, page_number_t physical_page, 
    unsigned int pages, unsigned int flags) 
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p, %8.8X, %8.8X, %u, %X)\n", 
        DEBUG_MODULE_NAME, __FUNCTION__, 
        memory, virtual_page, physical_page, pages, flags);

    page_map (memory->page_directory, virtual_page, physical_page, pages, flags);

    return STORM_RETURN_SUCCESS;
}

return_t virtual_memory_lookup (p_virtual_memory_t memory, 
    page_number_t virtual_page, page_number_t *physical_page, 
    unsigned int *flags)
{
    return_t return_value;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p, %u, %p, %p)\n", 
        DEBUG_MODULE_NAME, __FUNCTION__, 
        memory, virtual_page, physical_page, flags);

    return_value = page_lookup (memory->page_directory, virtual_page, physical_page, 
        flags);
        
    return return_value;
}

/* Initialize the virtual memory system. */
return_t virtual_memory_init (int argc UNUSED, char *argv[] UNUSED, 
    char **envp UNUSED)
{
    page_init ();

//    virtual_memory_global.page_directory = page_directory_global;

//    last_address = MIN (0x80000000, 
//        PAGE_ADDRESS (physical_memory_get_total_pages (&physical_memory_global)));
    
    return 0;
}


