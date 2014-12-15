#include <enviroment.h>

#define DEBUG_MODULE_NAME "PhysicalMemory"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include <debug/macros.h>

return_t physical_memory_check (p_physical_memory_t memory UNUSED,
    page_number_t start_page UNUSED, unsigned int pages UNUSED, unsigned int flags UNUSED)
{
    return STORM_RETURN_SUCCESS;
}

