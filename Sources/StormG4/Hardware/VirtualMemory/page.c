/* $chaos: memory_virtual.c,v 1.12 2002/10/24 20:41:50 per Exp $ */
/* Abstract: Virtual memory routines. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <enviroment.h>

#include "Include/page.h"

#define DEBUG_MODULE_NAME "VirtualMemory"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include <debug/macros.h>

//p_page_directory_t page_directory_global;

page_directory_t page_directory_global[1024] ALIGNED (PAGE_SIZE) =
{
    {
        present: 0,
        read_write: 0,
        user_supervisor: 0,
        write_through: 0,
        cache_disable: 0,
        accessed: 0,
        zero: 0,
        page_size: 0,
        global: 0,
        available: 0,
        page_table_base: 0,
    },
};


/* Find a mapping. */
return_t page_lookup (p_page_directory_t page_directory, 
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

    (*flags) = ((p_uint32_t) page_table)[page_table_index] & 0x03FF;
    (*physical_page) = page_table[page_table_index].page_base;

    return STORM_RETURN_SUCCESS;
}

/* Map memory. */
return_t page_map (page_directory_t *page_directory,
    page_number_t virtual_page, page_number_t physical_page, unsigned int pages,
    unsigned int flags) 
{
    uint32_t counter;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "%s: %s (%p %X %X %u %X)\n", 
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
            if (physical_memory_allocate (&physical_memory_global, &page, 1) 
                != STORM_RETURN_SUCCESS)
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

return_t page_map_4mb (page_directory_t *page_directory,
    page_number_t virtual_page_4mb, page_number_t physical_page_4mb, 
    unsigned int pages_4mb, unsigned int flags)
{
    uint32_t counter;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "%s: %s (%p %X %X %u %X)\n", 
        DEBUG_MODULE_NAME, __FUNCTION__, 
        page_directory, virtual_page_4mb, physical_page_4mb, pages_4mb, flags);

    /* Main loop. */
    for (counter = 0; counter < pages_4mb; counter++) 
    {
        page_directory_fill_entry (page_directory, virtual_page_4mb + counter,
            (physical_page_4mb + counter) << 10, flags | PAGE_SIZE_4MB);
    }

    return STORM_RETURN_SUCCESS;
}

/* Initialize the virtual memory system. */
void page_init (void)
{
    unsigned int physical_pages;
    unsigned int flags;
//    page_number_t page;

    /* Allocate a page for the kernel page directory. */
//    if (physical_memory_allocate (&physical_memory_global, &page, 1)
//        != STORM_RETURN_SUCCESS)
//    {
//        DEBUG_HALT ("Failed to allocate a page for the kernel page directory.");
//    }
    
//    page_directory_global = (p_page_directory_t) (PAGE_ADDRESS (page));
    
    physical_pages = physical_memory_get_total_pages (&physical_memory_global);

    /* Make sure it is cleared out. */
//    memory_clear_page (page_directory_global);

    flags = PAGE_KERNEL;
    
    /* Map the physical memory. We skip the first page to trap NULL
       references. */
    if (feature_get (&cpu_info_global, CPU_FEATURE_PGE))
    {
        flags |= PAGE_GLOBAL;
    }

    if (feature_get (&cpu_info_global, CPU_FEATURE_PSE))
    {    
        page_map (page_directory_global, 1, 1, physical_pages - 1, flags);
    }
    else
    {
        unsigned int pages;
        unsigned int pages_4mb;

        pages = MIN (physical_pages - 1, (1 << 10) - 1);
        page_map (page_directory_global, 1, 1, pages, flags);

        pages_4mb = (physical_pages >> 10) - 1;

        if (pages_4mb > 0)
        {
            page_map_4mb (page_directory_global, 1, 1, pages_4mb, flags);
        }

        pages = physical_pages - ((pages_4mb + 1) << 10);

        if (pages > 0)
        {
            page_map (page_directory_global, (pages_4mb + 1) << 10,
                (pages_4mb + 1) << 10, pages, flags);
        }     
   }

    /* Specify page directory to use for the kernel. */
    cpu_cr3_load (page_directory_global);
    
    /* Enable paging (virtual memory). */
    cpu_cr0_enable (CPU_CR0_PG);
}



