#include <enviroment.h>

#include "../Include/init.h"

#define MODULE_NAME "Repository"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>
#include <exception/macros.h>

static void timer_handler (unsigned int timer_number UNUSED,
    p_void_t parameter UNUSED, p_irq_cpu_registers_t state UNUSED)
{
    cpu_array_schedule (CPU_ARRAY_GLOBAL);
}    

static p_cpu_t cpu_array[] =
{
    CPU_GLOBAL,
};

cpu_array_t global_cpu_array = 
{
    { &cpu_array, 1, 0 },
};

void repository_cpu_array_init (void)
{
    timer_set_mode (0, TIMER_MODE_PERIODIC);
    timer_set_period (0, 10000);
    timer_register_handler (0, &timer_handler, NULL);
    timer_start (0);
}
    
