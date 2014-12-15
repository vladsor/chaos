#include <enviroment.h>

#include "../Include/init.h"

#define MODULE_NAME "Repository"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include <debug/macros.h>
#include <exception/macros.h>

cpu_t global_cpu =
{
/*    uint32_t perfromance; */
    0,
    
/*    resource_usage_t usage; */
    { 0, 0, 0, 0 },
    
/*    list_t virtuals; */
    LIST_INIT,
    
/*    p_virtual_cpu_t current_virtual; */
//    NULL
};    

void repository_cpu_init (void)
{
}
    
