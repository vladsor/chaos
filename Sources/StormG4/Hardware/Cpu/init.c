/* Abstract: CPU identification. */
/* Author: Vladimir Sorokin. */

/* Copyright 1999-2001 chaos development. */

#include <enviroment.h>

#define DEBUG_MODULE_NAME "Cpu"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#include <debug/macros.h>

#include "Include/cpu_id.h"
#include "Include/bugs.h"
#include "Include/speed.h"

cpu_info_t cpu_info_global;

/* The number of CPUs in the system. When we write SMP support, this
   variable might be something else. */
//static unsigned int cpus = 1;

return_t cpu_get_info (cpu_info_t *cpu_info)
{
    memory_copy (cpu_info, &cpu_info_global, sizeof (cpu_info_t));
    
    return STORM_RETURN_SUCCESS;
}

return_t cpu_init (int argc UNUSED, char *argv[] UNUSED, char **envp UNUSED)
{
    /* Make sure we clear this structure. */
    memory_clear (&cpu_info_global, sizeof (cpu_info_t));
    
    cpu_id_detect (&cpu_info_global);

    if (feature_get (&cpu_info_global, CPU_FEATURE_TSC))
    {
        cpu_info_global.frequency = (uint64_t) cpu_speed_get ();
    }
    
    cpu_bugs_search (&cpu_info_global);

#ifdef FPU_ENABLED
    fpu_enable ();
    fpu_init ();

    cpu_cr0_disable (CPU_CR0_TS);
#endif
    
    return STORM_RETURN_SUCCESS;
}

