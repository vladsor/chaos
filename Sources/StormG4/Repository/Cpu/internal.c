#include <enviroment.h>

#define DEBUG_MODULE_NAME "Repository"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include "../Include/internal.h"

#include <debug/macros.h>
#include <exception/macros.h>

p_cpu_t cpu_create_internal (uint32_t performance)
{
    p_cpu_t cpu;
    
    memory_allocate ((void **) &cpu, sizeof (cpu_t));
    
    cpu->performance = performance;
    
    cpu->usage.max = 0;
    cpu->usage.average = 0;
    cpu->usage.min = 0;
    cpu->usage.max_burst = 0;
    
//    cpu->current_virtual = NULL;
    
    return cpu;
}

void cpu_destroy_internal (p_cpu_t cpu)
{
    memory_deallocate (cpu);
}

/*
void cpu_idle ()
{
    asm (
        "1:\n"
        "jmp 1b"
    );
}    
*/
/*
void cpu_schedule_internal (p_cpu_t cpu)
{
    if (cpu->current_virtual != NULL)
    {
        if (((p_virtual_cpu_t) cpu->current_virtual)->next != NULL)
        {
            cpu->current_virtual = (virtual_cpu_reference_t) 
                ((p_virtual_cpu_t) cpu->current_virtual)->next;
        }
        else
        {
            cpu->current_virtual = (virtual_cpu_reference_t) cpu->virtuals.first;
        }
    }
    else
    {
        cpu->current_virtual = (p_virtual_cpu_t) cpu->virtuals.first;
    }
    
    if (cpu->current_virtual == NULL)
    {
//        cpu_sleep_internal (cpu);
    }    
}
*/
/*
cpu_save_state ()

cpu_load_state ()

p_vitrual_cpu_t cpu_get_least_virtual (p_cpu_t cpu)
{
}
*/

cpu_reference_t cpu_get_current (void)
{
	return CPU_CURRENT;
}

void cpu_sleep_milli (cpu_reference_t cpu UNUSED, uint32_t milli)
{
    uint32_t start;
    uint32_t current;
    uint32_t wait;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s: %s (%p, %u)\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        cpu, milli);

    {
    uint32_t eflags;

    cpu_flags_save (eflags);
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
        "%s: %s: %p, %x\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        COMPUTER_CURRENT, eflags);
    }

    wait = milli > 10 ? milli / 10 : 1;

    timer_read (0, &start);

    do
    {
        timer_read (0, &current);

	} while ((current - start) < wait);
}

