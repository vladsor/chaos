/* $chaos: memory_physical.c,v 1.28 2002/10/20 19:30:33 per Exp $ */
/* Abstract: Physical memory allocation. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <enviroment.h>
#include <rpool.h>

#include "Include/internal.h"

#define DEBUG_MODULE_NAME "PhysicalMemory"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

physical_memory_t physical_memory_global = 
{
    block_pool: POOL_INIT,
    node_allocator: &node_allocator_global.pool,
    node_pool: node_pool_global,
    raw_memory: 
    {
        data: &physical_memory_global,
        allocate: &internal_memory_allocate,
        deallocate: &internal_memory_deallocate
    }    
};    

static void reserve_known_regions (void)
{
    uint32_t counter;
    
    /* If we have a Multiboot memory map, we can use it to avoid using
       any registered memory areas (used for hardware devices etc). */

    uint32_t index = 0;
    p_storm_memory_map_t map;

    for (index = 0; index < storm_info.number_of_memory_maps; index++)
    {
        map = storm_info.memory_map + index;
            
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1, 
            "%s: Map[%i]=%p,size=0x%04X,base_addr=%p,length=0x%08X,type=%u\n",
            DEBUG_MODULE_NAME, 
            index, map, map->size, map->base_address, map->length, map->type);

        if (map->type == MEMORY_MAP_TYPE_RAM)
        {
            uint32_t start_page = PAGE_NUMBER (map->base_address);
            uint32_t pages = SIZE_IN_PAGES (map->length);

            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1, "MM: %p-%p, %u-%u\n", 
                map->base_address, map->base_address + map->length, 
                start_page, pages);

            physical_memory_reserve (&physical_memory_global, start_page, 
                pages);
        }
    }

    for (counter = 0; counter < storm_info.number_of_modules; counter++)
    {
        page_number_t start_page;
        page_number_t end_page;
            
        start_page = PAGE_NUMBER (storm_info.module_info[counter].start);
        end_page = PAGE_NUMBER (storm_info.module_info[counter].end);

        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
            "%s: Module[%u]: %p - %p\n",
            DEBUG_MODULE_NAME, 
            counter, (void *) storm_info.module_info[counter].start,
            (void *) storm_info.module_info[counter].end);
		
        physical_memory_reserve (&physical_memory_global, start_page, 
            end_page - start_page + 1);
    }
}

uint32_t physical_memory_get_total_pages (p_physical_memory_t memory)
{
    return memory->block_pool.range.length;
}

uint32_t physical_memory_get_free_pages (p_physical_memory_t memory)
{
    return memory->block_pool.free_count;
}

/* Initialize physical memory allocation. */
return_t physical_memory_init (int argc UNUSED, char *argv[] UNUSED, 
    char **envp UNUSED) 
{
    range_t range;
    uint32_t free_pages;
    uint32_t physical_pages;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
         "%s: %s (%u, %p, %p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        argc, argv, envp);
    
    /* Store the number of physical pages (used later). */
    physical_pages = SIZE_IN_PAGES (storm_info.memory_size);
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s: Total memory: %u bytes, %u pages, %u KiB, %u MiB.\n", 
        DEBUG_MODULE_NAME, 
        storm_info.memory_size, physical_pages, 
        physical_pages * PAGE_SIZE / KIB, physical_pages * PAGE_SIZE / MIB);

    internal_memory_init (&physical_memory_global);
    
    range.start = 0;
    range.length = physical_pages;
    pool_init (&physical_memory_global.block_pool, range, 
        (p_raw_memory_t) &physical_memory_global.raw_memory);

    physical_memory_reserve (&physical_memory_global, 0, 
        SIZE_IN_PAGES (1 * MIB));    
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: Kernel: %p - %p\n", 
        DEBUG_MODULE_NAME, (void *) KERNEL_START, (void *) KERNEL_END);
    
    physical_memory_reserve (&physical_memory_global, 
        PAGE_NUMBER (KERNEL_START), SIZE_IN_PAGES (KERNEL_SIZE));

    reserve_known_regions ();

    free_pages = physical_memory_global.block_pool.free_count;
    
    /* Scanning done, over and out. */
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s: Free memory: %u bytes, %u pages, %u KiB, %u MiB.\n", 
        DEBUG_MODULE_NAME, 
        free_pages * PAGE_SIZE, free_pages, free_pages * PAGE_SIZE / KIB, 
        free_pages * PAGE_SIZE / MIB);
    
    return 0;
}

