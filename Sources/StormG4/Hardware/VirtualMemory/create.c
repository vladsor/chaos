#include <enviroment.h>
#include <ipool.h>
#include <rpool.h>

#include "Include/page.h"
#include "Include/internal.h"

#define DEBUG_MODULE_NAME "VirtualMemory"

//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include <debug/macros.h>

return_t virtual_memory_create (p_virtual_memory_t virtual_memory, 
    p_physical_memory_t physical_memory, unsigned int level)
{
    page_number_t page;
    range_t range;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 

        "%s: %s (%p)\n", 
        DEBUG_MODULE_NAME, __FUNCTION__, 
        virtual_memory);

    virtual_memory->is_direct = FALSE;
    virtual_memory->physical_memory = physical_memory;
    virtual_memory->level = level;
    
    if (level == LEVEL_SYSTEM)
    {
        virtual_memory->code_selector = SELECTOR_KERNEL_CODE;
        virtual_memory->data_selector = SELECTOR_KERNEL_DATA;
        virtual_memory->stack_selector = SELECTOR_KERNEL_DATA;
    }
    else if (level == LEVEL_USER)
    {
        virtual_memory->code_selector = SELECTOR_PROCESS_CODE;
        virtual_memory->data_selector = SELECTOR_PROCESS_DATA;
        virtual_memory->stack_selector = SELECTOR_PROCESS_DATA;
    }
    else
    {
        DEBUG_HALT ("level != LEVEL_SYSTEM && level != LEVEL_USER");
    }        

    /* Allocate a page for the page directory. */
    if (physical_memory_allocate (&physical_memory_global, &page, 1) 
        != STORM_RETURN_SUCCESS)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR,
            "Failed to allocate a page for the process page directory.");

        return -1;
    }
    
    virtual_memory->page_directory = (p_page_directory_t) (PAGE_ADDRESS (page));

    /* Make sure it is cleared out. */
    memory_clear_page (virtual_memory->page_directory);

    physical_memory_allocate (&physical_memory_global, &page, 1);
    virtual_memory->node_allocator = (p_pool_of_integers_t) (PAGE_ADDRESS (page));

    physical_memory_allocate (&physical_memory_global, &page, 1);
    virtual_memory->node_pool = (p_range_node_t) (PAGE_ADDRESS (page));

// allocate virtual_memory->node_allocator
    pool_of_integers_init (virtual_memory->node_allocator, 100);

    internal_memory_init2 (virtual_memory);

    physical_memory_allocate (&physical_memory_global, &page, 1);
    virtual_memory->block_pool = (p_pool_t) (p_range_node_t) (PAGE_ADDRESS (page));

// allocate 
    range.start = USER_MEMORY_START;
    range.length = USER_MEMORY_SIZE;
    pool_init (virtual_memory->block_pool, range, 
        (p_raw_memory_t) &virtual_memory->raw_memory);

//    virtual_memory_reserve (virtual_memory, 0,
//        SIZE_IN_PAGES (GLOBAL_MEMORY_SIZE));
        
//    page_map (virtual_memory->page_directory, GLOBAL_MEMORY_START, 
//        GLOBAL_MEMORY_START), SIZE_IN_PAGES (GLOBAL_MEMORY_SIZE), 
//        PAGE_KERNEL);
    memory_copy (virtual_memory->page_directory, 
        virtual_memory_global.page_directory, PAGE_SIZE / 2);
    
    return STORM_RETURN_SUCCESS;
}

