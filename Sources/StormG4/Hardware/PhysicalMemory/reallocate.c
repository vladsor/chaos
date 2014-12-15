#include <enviroment.h>

#define DEBUG_MODULE_NAME "PhysicalMemory"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include <debug/macros.h>

return_t physical_memory_reallocate (p_physical_memory_t memory UNUSED,
    page_number_t *start_page UNUSED, unsigned int pages UNUSED)
{
    return 0;
}    

