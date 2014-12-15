#include <enviroment.h>
#include <ipool.h>
#include <rpool.h>

#include "Include/page.h"

#define DEBUG_MODULE_NAME "VirtualMemory"

//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include <debug/macros.h>

return_t virtual_memory_destroy (p_virtual_memory_t virtual_memory)
{
    page_number_t page;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p)\n", 
        DEBUG_MODULE_NAME, __FUNCTION__, 
        virtual_memory);
    
    page = PAGE_NUMBER (virtual_memory->page_directory);
    physical_memory_deallocate (&physical_memory_global, page, 1);
    
    return STORM_RETURN_SUCCESS;
}

