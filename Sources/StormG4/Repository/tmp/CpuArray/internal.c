#include <enviroment.h>

#define MODULE_NAME "Repository"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include "../Include/cpu.h"
#include "../Include/cpu_array.h"

#include <debug/macros.h>
#include <exception/macros.h>

void cpu_array_schedule_internal (p_cpu_array_t cpu_array)
{
    uint32_t index;
    p_cpu_t cpu;

    for (index = 0; index < cpu_array->cpus.count; index++)
    {
        cpu = ((p_p_cpu_t) cpu_array->cpus.data)[index];
        
        cpu_schedule_internal (cpu);
    }
}

