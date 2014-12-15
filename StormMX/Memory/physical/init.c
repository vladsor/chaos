/* $chaos: memory_physical.c,v 1.28 2002/10/20 19:30:33 per Exp $ */
/* Abstract: Physical memory allocation. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <enviroment.h>
#include <rpool.h>

#include "../../Init/Include/multiboot.h"

#include "internal_memory.h"

#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#include <debug/macros.h>

pool_t block_pool;

static void reserve_known_regions (void)
{
    uint32_t start_end;
    uint32_t counter;

    /* If we have a Multiboot memory map, we can use it to avoid using
       any registered memory areas (used for hardware devices etc). */
    if (multiboot_info.has_memory_map == 1)
    {
        int index = 0;
        multiboot_memory_map_t *mmap;

        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "We are having memory map!\n");

        for (mmap = (multiboot_memory_map_t *) multiboot_memory_map;
            (uint32_t) mmap < (uint32_t) multiboot_memory_map + 
            multiboot_info.memory_map_length; 
            mmap = (multiboot_memory_map_t *) ((uint32_t) mmap + mmap->size + 
            sizeof (mmap->size)), index++)
//        for (index = 0; index < (multiboot_info.memory_map_length / 
//	    sizeof (multiboot_memory_map_t)); index++)
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1, 
                "Map[%i] size = 0x%04X, base_addr = %X,"
                " length = 0x%08X, type = 0x%04X\n",
                index,
                (unsigned) mmap->size,
                (unsigned) mmap->base_address,
                (unsigned) mmap->length,
                (unsigned) mmap->type);

            if (multiboot_memory_map[index].type == 1) /* RAM. */
            {
//		uint32_t base = multiboot_memory_map[index].base_address;
//		uint32_t length = multiboot_memory_map[index].length;
//                uint32_t start_page = (base >> 12);
//                uint32_t pages = (length >> 12);

//                DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "MM: %u-%u, %u-%u\n", 
//                  base, length, start_page, pages);

//		physical_memory_reserve (start_page, pages);
            }
        }
    }
    else /* Nope, no memory map. But we still have some great help
            from our Multiboot loader. */
    {
        uint32_t page;
        
        /* Map the low pages we have into our slab structure. We don't
           care about getting this from the memory map; we blindly
           presume there ise 640KiB lower memory. I have personally a
           machine that reports 639 KiB, but I believe it is simply
           lying. */
        for (page = 0; page < (multiboot_info.memory_lower * KIB) / 
                 PAGE_SIZE; page++) 
        {
    physical_memory_reserve (page, 1);
//            check_and_add_page (page);
        }

        /* Now, take care of the high pages, starting with the page right
           after _end. */
        start_end = ((uint32_t) &_end) / PAGE_SIZE + 1;
        for (page = start_end; 
             page < (1 * MIB + multiboot_info.memory_upper * KIB) / PAGE_SIZE;
             page++) 
        {
    physical_memory_reserve (page, 1);
//            check_and_add_page (page);
        }
    }   

    if (multiboot_info.has_module_info == 1)
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "We are having module info!\n");
	
        for (counter = 0; counter < multiboot_info.number_of_modules; counter++)
        {
            page_number_t start_page;
            page_number_t end_page;
            
            start_page = PAGE_NUMBER (multiboot_module_info[counter].start);
            end_page = PAGE_NUMBER (multiboot_module_info[counter].end);

            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
                "Module[%u]: %p - %p\n",
                counter, (void *) multiboot_module_info[counter].start,
                (void *) multiboot_module_info[counter].end);
		
            physical_memory_reserve (start_page, end_page - start_page + 1);
        }
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1 ,
        "memory_lower: %X, memory_upper: %X, module_base: %X\n",
        multiboot_info.memory_lower,
        multiboot_info.memory_upper,
        multiboot_info.module_base);
}

uint32_t physical_memory_get_total_pages (void)
{
    return block_pool.range.length;
}

uint32_t physical_memory_get_free_pages (void)
{
    return block_pool.free_count;
}

/* Initialize physical memory allocation. */
return_t physical_memory_init (int argc UNUSED, char *argv[] UNUSED) 
{
    range_t range;
    uint32_t free_pages;
    uint32_t physical_pages;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
         "%s::%s (%i, %p)\n",
        __FILE__, __FUNCTION__, argc, argv);
    
    /* Store the number of physical pages (used later). */
    physical_pages = (1024 + multiboot_info.memory_upper) / 4;
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Total pages: %u.\n", physical_pages);

    /* We only support 2 GiB of physical memory because of the way our
       virtual memroy map is laid out. (all physical memory is mapped
       everywhere) This may be a bit bad, but it makes everything
       EXTREMELY simplified. */
    if (physical_pages > SIZE_IN_PAGES (MAX_MEMORY))
    {
        physical_pages = SIZE_IN_PAGES (MAX_MEMORY);
    }
    
    internal_memory_init ();
    
    range.start = 0;
    range.length = physical_pages;
    pool_init (&block_pool, range, imemory);

    physical_memory_reserve (0, SIZE_IN_PAGES (1 * MIB));    
    
    reserve_known_regions ();

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "Kernel: %p - %p\n", (void *) KERNEL_START, (void *) KERNEL_END);
    
    physical_memory_reserve (PAGE_NUMBER (KERNEL_START), 
        SIZE_IN_PAGES (KERNEL_SIZE));

    free_pages = block_pool.free_count;
    
    /* Scanning done, over and out. */
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "Free memory: %u pages, %u KiB, %u MiB.\n", 
        free_pages, free_pages * PAGE_SIZE / KIB, free_pages * PAGE_SIZE / MIB);
    
    return 0;
}

