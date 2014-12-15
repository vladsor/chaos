
#include <enviroment.h>

#define DEBUG_MODULE_NAME "Cpu"
#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

return_t cpu_lock (void)
{
    cpu_interrupts_disable ();

    return STORM_RETURN_SUCCESS;
}

return_t cpu_unlock (void)
{
    cpu_interrupts_enable ();

    return STORM_RETURN_SUCCESS;
}

