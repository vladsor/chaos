#include <enviroment.h>

#include "Include/page.h"

#define DEBUG_MODULE_NAME "VirtualMemory"

//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include <debug/macros.h>

return_t virtual_memory_deallocate (p_virtual_memory_t virtual_memory, 
    page_number_t start_page, unsigned int pages)
{
    return_t rv;
    range_t range;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p, %x, %u)\n", 
        DEBUG_MODULE_NAME, __FUNCTION__, 
        virtual_memory, start_page, pages);

    range.start = start_page;
    range.length = pages;

    rv = pool_deallocate (virtual_memory->block_pool, range);

    return rv;
}

