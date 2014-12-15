#include <enviroment.h>

#define MODULE_NAME "Repository"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include "../Include/internal.h"

#include <debug/macros.h>
#include <exception/macros.h>

cpu_t cpu_kernel;

cpu_reference_t cpu_create (uint32_t performance)
{
    return (cpu_reference_t) cpu_create_internal (performance);
}    

/*
void cpu_schedule (p_cpu_t cpu)
{
    cpu_schedule_internal (cpu);
}
*/
