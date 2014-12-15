/* Abstract: CPU identification. */
/* Author: Vladimir Sorokin. */

/* Copyright 1999-2001 chaos development. */

#include <enviroment.h>

#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#include <debug/macros.h>

#include "Include/cpu_id.h"
#include "Include/cpu_bugs.h"

static cpu_info_t global_cpu_info;

/* The number of CPUs in the system. When we write SMP support, this
   variable might be something else. */
//static unsigned int cpus = 1;

return_t cpu_get_info (cpu_info_t *cpu_info)
{
    memory_copy (cpu_info, &global_cpu_info, sizeof (cpu_info_t));
    
    return STORM_RETURN_SUCCESS;
}

return_t cpu_init (int argc UNUSED, char *argv[] UNUSED, char **envp UNUSED)
{
    /* Make sure we clear this structure. */
    memory_set_uint8 ((uint8_t *) &global_cpu_info, 0, sizeof (cpu_info_t));
    cpu_id_detect (&global_cpu_info);
    
    cpu_bugs_search (&global_cpu_info);

#ifdef FPU_ENABLED
    fpu_enable ();
    fpu_init ();

    cpu_cr0_disable (CPU_CR0_TS);
#endif
    
    return STORM_RETURN_SUCCESS;
}

