/* $chaos: memory_virtual.c,v 1.12 2002/10/24 20:41:50 per Exp $ */
/* Abstract: Virtual memory routines. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <enviroment.h>

#include "../Include/page.h"

#define DEBUG_MODULE_NAME "VirtualMemory"

//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

/**
 * @brief               Flags used when creating new entries in the page
 *                      directory.
 *
 * We let the page table set everything, so we need to have this
 * all-privileged.
 */
#define PAGE_DIRECTORY_FLAGS \
                        (PAGE_PRESENT | PAGE_WRITABLE | PAGE_NON_PRIVILEGED)


/**
 * @brief               Pages owned by the kernel.
 *
 * Supervisor-only, read-only (since we don't set WP bit, it isn't
 * really read-only for the kernel..), and global. 
 */
#define PAGE_KERNEL     (PAGE_PRESENT)

/**
 * @brief               Pages owned by user processes.
 */
#define PAGE_USER       (PAGE_PRESENT | PAGE_NON_PRIVILEGED | PAGE_WRITABLE | \
                         PAGE_WRITE_THROUGH)

/* Find a mapping. */
return_t page_lookup (page_directory_t *page_directory, 
    page_number_t virtual_page, page_number_t *physical_page, 
    unsigned int *flags)
{
    unsigned int page_directory_index;
    unsigned int page_table_index;

    page_table_t *page_table;
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "%s: %s (%p %X %p %p)\n", 
        DEBUG_MODULE_NAME, __FUNCTION__, 
        page_directory, virtual_page, physical_page, flags);
    
    page_directory_index = PAGE_DIRECTORY_INDEX (virtual_page);
    page_table_index = PAGE_TABLE_INDEX (virtual_page);
    
    if (page_directory[page_directory_index].present == 0)
    {
        physical_page = NULL;
        flags = NULL;

        DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
            "%s: %s Page table [%u] not present.\n", 
            DEBUG_MODULE_NAME, __FUNCTION__, 
            page_directory_index);
            
        return STORM_RETURN_NOT_FOUND;
    }

    page_table = (page_table_t *) 
        PAGE_ADDRESS (page_directory[page_directory_index].page_table_base);

    if (page_table[page_table_index].present == 0)
    {
        physical_page = NULL;
        flags = NULL;

        DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
            "%s: %s Page [%u] not present.\n", 
            DEBUG_MODULE_NAME, __FUNCTION__, 
            page_table_index);

        return STORM_RETURN_NOT_FOUND;
    }

    (*flags) = page_table[page_table_index].flags;
    (*physical_page) = page_table[page_table_index].page_base;

    return STORM_RETURN_SUCCESS;
}

/* Map memory. */
return_t page_map (page_directory_t *page_directory,
    page_number_t virtual_page, page_number_t physical_page, unsigned int pages,
    unsigned int flags) 
{
    uint32_t counter;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "%s::%s (%p %X %X %u %X)\n", 
        DEBUG_MODULE_NAME, __FUNCTION__, 
        page_directory, virtual_page, physical_page, pages, flags);

    /* Main loop. */
    for (counter = 0; counter < pages; counter++) 
    {
        uint32_t page_directory_index = 
            PAGE_DIRECTORY_INDEX (virtual_page + counter);
        uint32_t page_table_index = PAGE_TABLE_INDEX (virtual_page + counter);
        page_table_t *page_table;

        if (page_directory[page_directory_index].present == 0) 
        {
            page_number_t page;

            /* We need to set up a page table. */
            if (physical_memory_allocate (&page, 1) != STORM_RETURN_SUCCESS)
            {
                DEBUG_HALT ("Failed to allocate a page for the page table.");
            }

            page_table = (page_table_t *) PAGE_ADDRESS (page);

            /* Make sure it is cleared out. */
            memory_clear_page (page_table);

            /* Set up the page directory entry, referring to this
               newly created page table. */
            page_directory_fill_entry (page_directory, page_directory_index,
                page, PAGE_DIRECTORY_FLAGS);
        }
        else 
        {
            page_table = (page_table_t *) PAGE_ADDRESS (
                page_directory[page_directory_index].page_table_base);
        }

        /* Now, we have a page table. Create an entry. */
        page_table_fill_entry (page_table, page_table_index, 
            physical_page + counter, flags);
    }

    return STORM_RETURN_SUCCESS;
}

/* Initialize the virtual memory system. */
void page_system_init (page_directory_t *page_directory)
{
    unsigned int physical_pages;
    
    physical_pages = physical_memory_get_total_pages ();
    
    /* Make sure it is cleared out. */
    memory_clear_page (page_directory);

    /* Map the physical memory. We skip the first page to trap NULL
       references. */
    page_map (page_directory, 1, 1, physical_pages - 1, PAGE_KERNEL);
}

void page_enable (page_directory_t *page_directory)
{    
    /* Specify page directory to use for the kernel. */
    cpu_cr3_load (page_directory); 
    
    /* Enable paging (virtual memory). */
    cpu_cr0_enable (CPU_CR0_PG);
}
