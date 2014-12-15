/* $chaos: memory_virtual.c,v 1.12 2002/10/24 20:41:50 per Exp $ */
/* Abstract: Virtual memory routines. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <enviroment.h>
#include <ipool.h>
#include <rpool.h>

#include "../Include/page.h"

#define DEBUG_MODULE_NAME "VirtualMemory"

//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

page_directory_t *global_page_directory;
static uint32_t last_address;
#define GLOBAL_MEMORY_START (0 + PAGE_SIZE)
#define GLOBAL_MEMORY_END     (last_address)
#define GLOBAL_MEMORY_SIZE (GLOBAL_MEMORY_END - GLOBAL_MEMORY_START)

#if defined (SUBSYSTEM_PROCESS)
static range_node_t temp_buffer[1000];
STATIC_POOL (pool, 1000);


static void * internal_memory_allocate (void)
{
    uint32_t index;
    return_t return_value;
    void *pointer;

    return_value = pool_of_integers_allocate (pool, &index);
   
    pointer = (void *) ((uint32_t) temp_buffer + 
        (index * sizeof (range_node_t)));
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1, 
        "Internal Allocate: %u, %p\n", 
        index, pointer);
    
    return pointer;
}

static void internal_memory_deallocate (void *pointer)
{
    uint32_t index;
    
    index = ((int32_t) pointer - (uint32_t) temp_buffer) / 
        (sizeof (range_node_t));

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1, 
        "Internal Dellocate: %u, %p\n", 
        index, pointer);
    
    pool_of_integers_deallocate (pool, index);
}

raw_memory_interface_t rmi = 
{ 
    internal_memory_allocate, 
    internal_memory_deallocate
};

return_t virtual_memory_create (process_t *process)
{
    page_directory_t *page_directory;
    page_number_t page;
    range_t range;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p)\n", 
        DEBUG_MODULE_NAME, __FUNCTION__, process);

    /* Allocate a page for the kernel page directory. */
    if (physical_memory_allocate (&page, 1) != STORM_RETURN_SUCCESS)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR,
            "Failed to allocate a page for the process page directory.");

        return -1;
    }
    
    page_directory = (page_directory_t *) (PAGE_ADDRESS (page));

    /* Make sure it is cleared out. */
    memory_clear_page (page_directory);

    process->page_directory = page_directory;

    pool_of_integers_init (pool, 1000);

    range.start = PAGE_NUMBER (GLOBAL_MEMORY_END);
    range.length = PAGE_NUMBER (UINT32_MAX - 1);
    pool_init (&process->memory_pool, range, rmi);

    virtual_memory_reserve (process, 0,
        SIZE_IN_PAGES (GLOBAL_MEMORY_SIZE));
    page_map (page_directory, PAGE_NUMBER (GLOBAL_MEMORY_START), 
        PAGE_NUMBER (GLOBAL_MEMORY_START), SIZE_IN_PAGES (GLOBAL_MEMORY_SIZE), 
        PAGE_KERNEL);
    
    return 0;
}

return_t virtual_memory_destroy (process_t *process)
{
    page_number_t page;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s::%s (%p)\n", 
        DEBUG_MODULE_NAME, __FUNCTION__, process);
    
    page = PAGE_NUMBER (process->page_directory);
    physical_memory_deallocate (page, 1);
    
    return 0;
}

return_t virtual_memory_allocate (process_t *process, 
    page_number_t *virtual_page, unsigned int pages)
{
    return_t rv;
    range_t range;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p, %p, %u)\n", 
        DEBUG_MODULE_NAME, __FUNCTION__, 
        process, virtual_page, pages);

    range.start = 0;
    range.length = pages;

    rv = pool_allocate (&process->memory_pool, &range);
    (*virtual_page) = range.start;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s Allocated: %X (rv: %u).\n", 
        DEBUG_MODULE_NAME, __FUNCTION__, range.start, rv);

    return rv;
}

return_t virtual_memory_deallocate (process_t *process, 
    page_number_t virtual_page, unsigned int pages)
{
    range_t range;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p)\n", 
        DEBUG_MODULE_NAME, __FUNCTION__, process);

    range.start = virtual_page;
    range.length = pages;

    pool_deallocate (&process->memory_pool, range);

    return 0;
}

return_t virtual_memory_reserve (process_t *process, 
    page_number_t virtual_page, unsigned int pages)
{
    range_t range;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s::%s (%p)\n", 
        DEBUG_MODULE_NAME, __FUNCTION__, process);

    range.start = virtual_page;
    range.length = pages;
    pool_reserve (&process->memory_pool, range);

    return 0;
}
#endif

/* Map memory. */
return_t virtual_memory_map (page_directory_t *page_directory, 
    page_number_t virtual_page, page_number_t physical_page, 
    unsigned int pages, unsigned int flags) 
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s::%s (%p, %8.8X, %8.8X, %u, %X)\n", 
        DEBUG_MODULE_NAME, __FUNCTION__, 
        page_directory, virtual_page, physical_page, pages, flags);

    page_map (page_directory, virtual_page, physical_page, pages, flags);

    return STORM_RETURN_SUCCESS;
}

return_t virtual_memory_lookup (page_directory_t *page_directory, 
    page_number_t virtual_page, page_number_t *physical_page, 
    unsigned int *flags)
{
    return_t return_value;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s::%s (%p, %u, %p, %p)\n", 
        DEBUG_MODULE_NAME, __FUNCTION__, 
        page_directory, virtual_page, physical_page, flags);

    return_value = page_lookup (page_directory, virtual_page, physical_page, 
        flags);
        
    return return_value;
}

extern tss_t tss_kernel;

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

    {    
    unsigned int physical_pages;
    physical_pages = physical_memory_get_total_pages ();
    last_address = MIN (0x80000000, PAGE_ADDRESS (physical_pages));

    gdt_setup_tss_descriptor (DESCRIPTOR_INDEX_TSS1, &tss_kernel, 
                    0, sizeof (tss_t));
    cpu_tr_load (SELECTOR_TSS1);
    }
    
    return 0;
}
