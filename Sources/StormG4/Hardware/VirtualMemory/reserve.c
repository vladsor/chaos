#include <enviroment.h>

#include "Include/page.h"

#define DEBUG_MODULE_NAME "VirtualMemory"

#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include <debug/macros.h>

return_t virtual_memory_reserve (p_virtual_memory_t virtual_memory, 
    page_number_t start_virtual_page, uint32_t pages,
    p_page_number_t start_physical_page, unsigned int options)
{
    return_t rv;
    uint32_t physical_page = 0;
    range_t range;
    uint32_t flags = PAGE_USER;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p, %x, %u, %p, %X)\n", 
        DEBUG_MODULE_NAME, __FUNCTION__, 
        virtual_memory, start_virtual_page, pages, start_physical_page, 
        options);

    if (virtual_memory->is_direct)
    {
        rv = physical_memory_reserve (virtual_memory->physical_memory, 
            start_virtual_page, pages);

        if (rv != STORM_RETURN_SUCCESS || rv != STORM_RETURN_BUSY)
        {
            return STORM_RETURN_INTERNAL_DATA_ERROR;
        }
            
        if (start_physical_page != NULL)
        {
            (*start_physical_page) = physical_page;
        }    
        
        return STORM_RETURN_SUCCESS;
    }   

    range.start = start_virtual_page;
    range.length = pages;
    
    rv = pool_reserve (virtual_memory->block_pool, range);
        
    if (rv != STORM_RETURN_SUCCESS)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
            "%s: %s: Failed.\n",
            DEBUG_MODULE_NAME, __FUNCTION__);
            
        return STORM_RETURN_INTERNAL_DATA_ERROR;
    }

    if (options & VIRTUAL_MEMORY_OPTION_ONLY_VIRTUAL)
    {
        return STORM_RETURN_SUCCESS;
    }    

    rv = physical_memory_allocate (virtual_memory->physical_memory, 
        &physical_page, pages);

    if (rv != STORM_RETURN_SUCCESS)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
            "%s: %s: Failed.\n",
            DEBUG_MODULE_NAME, __FUNCTION__);

        return STORM_RETURN_INTERNAL_DATA_ERROR;
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s: Physical page: %x\n", 
        DEBUG_MODULE_NAME, __FUNCTION__, 
        physical_page);
            
    if (start_physical_page != NULL)
    {
        (*start_physical_page) = physical_page;
    }

    if (virtual_memory->level == LEVEL_SYSTEM)
    {
        flags = PAGE_KERNEL;
    }
    else if (virtual_memory->level == LEVEL_USER)
    {
        flags = PAGE_USER;
    }    
    
    rv = page_map (virtual_memory->page_directory, start_virtual_page, 
        physical_page, pages, flags);
                
    if (rv != STORM_RETURN_SUCCESS)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
            "%s: %s: Failed.\n",
            DEBUG_MODULE_NAME, __FUNCTION__);

        return STORM_RETURN_INTERNAL_DATA_ERROR;
    }

    return STORM_RETURN_SUCCESS;
}

