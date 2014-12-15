/* $chaos: memory_virtual.c,v 1.12 2002/10/24 20:41:50 per Exp $ */
/* Abstract: Virtual memory routines. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <enviroment.h>

#include "../Include/page.h"

#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#include <debug/macros.h>

page_directory_t *global_page_directory;

/*
pool_t block_pool;

create ()
{
    pool_init (0, UINT32_MAX);
    
    pool_reserve (GLOBAL_MEMORY_START, GLOBAL_MEMORY_SIZE);
    page_map (GLOBAL_MEMORY_START, GLOBAL_MEMORY_START, GLOBAL_MEMORY_SIZE);
    
    pool_reserve (PROGRAM_START, process->size);
    page_map (PROGRAM_START, process->base, process->size);
}

destroy ()
{
}

return_t virtual_memory_allocate (process_t *process, 
    page_number_t *virtual_page, unsigned int pages)
{
    range.start = 0;
    range.length = pages;

    rv = pool_allocate (&block_pool, &range);

    return STORM_RETURN_UNIMLPEMENTED;
}

return_t virtual_memory_deallocate (process_t *process, 
    page_number_t virtual_page, unsigned int pages)
{
    pool_deallocate (&block_pool, &range);

    return STORM_RETURN_UNIMPLEMENTED;
}
*/

/* Map memory. */
return_t virtual_memory_map (page_directory_t *page_directory, 
    page_number_t virtual_page, page_number_t physical_page, 
    unsigned int pages, unsigned int flags) 
{
    page_map (page_directory, virtual_page, physical_page, pages, flags);

    return STORM_RETURN_SUCCESS;
}

return_t virtual_memory_lookup (page_directory_t *page_directory, 
    page_number_t virtual_page, page_number_t *physical_page, 
    unsigned int *flags)
{
    return_t return_value;

    return_value = page_lookup (page_directory, virtual_page, physical_page, 
        flags);
        
    return return_value;
}

/* Initialize the virtual memory system. */
return_t virtual_memory_init (int argc UNUSED, char *argv[] UNUSED)
{
    page_number_t page;

    /* Allocate a page for the kernel page directory. */
    if (physical_memory_allocate (&page, 1) != STORM_RETURN_SUCCESS)
    {
        DEBUG_HALT ("Failed to allocate a page for the kernel page directory.");
    }
    
    global_page_directory = (page_directory_t *) (PAGE_ADDRESS (page));

    page_system_init (global_page_directory);

    page_enable (global_page_directory);

    return 0;
}
