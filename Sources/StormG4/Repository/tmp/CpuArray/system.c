#include <enviroment.h>

#define MODULE_NAME "Repository"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include "../Include/cpu_array.h"

#include <debug/macros.h>
#include <exception/macros.h>

void cpu_array_schedule (p_cpu_array_t cpu_array)
{
    cpu_array_schedule_internal (cpu_array);
}    
