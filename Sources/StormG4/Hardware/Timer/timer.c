/* Abstract: Timer support. */
/* Author: Vladimir Sorokin */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <enviroment.h>

#include "Include/pit.h"
#include "Include/timer.h"

#define DEBUG_MODULE_NAME "Timer"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE2
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include <debug/macros.h>

typedef struct
{
    p_timer_handler_t handler;
    p_void_t data;
    
    unsigned int state;
    uint64_t ticks;
    uint32_t period;
    unsigned mode;
} timer_t;

static timer_t timers[NUMBER_OF_TIMERS] =
{
    [TIMER_NUMBER_SYSTEM] = 
    {
        handler: NULL,
        data: NULL,
        state: TIMER_STATE_STOPED,
        ticks: 0,
        period: 0,
        mode: TIMER_MODE_PERIODIC,
    },
};    

static void timer_handler (unsigned int irq_number UNUSED, 
    p_void_t parameter UNUSED, irq_cpu_registers_t irq_cpu_registers UNUSED)
{
    unsigned int timer_number;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE2,
         "%s: %s ()\n",
        DEBUG_MODULE_NAME, __FUNCTION__);
        
    timer_number = 0;
    
    timers[timer_number].ticks++;

    if (timers[timer_number].handler != 0)
    {
        (*timers[timer_number].handler) (timer_number, 
                timers[timer_number].data, &irq_cpu_registers);
    }     
}

return_t timer_start (unsigned int timer_number)
{
    if (timers[timer_number].state != TIMER_STATE_STOPED)
    {
        return STORM_RETURN_INVALID_ARGUMENT;
    }
    
    timers[timer_number].state = TIMER_STATE_COUNTED;
    timers[timer_number].ticks = 0;
    
    return STORM_RETURN_SUCCESS;
}

return_t timer_stop (unsigned int timer_number)
{
    if (timers[timer_number].state != TIMER_STATE_COUNTED)
    {
        return STORM_RETURN_INVALID_ARGUMENT;
    }
    
    timers[timer_number].state = TIMER_STATE_STOPED;

    return STORM_RETURN_SUCCESS;
}

return_t timer_set_period (unsigned int timer_number, uint32_t period)
{
    timers[timer_number].period = period;

    pit_frequency_set (0, 1000000 / period);

    return STORM_RETURN_SUCCESS;
}

return_t timer_set_mode (unsigned int timer_number, unsigned int mode)
{
    timers[timer_number].mode = mode;

    pit_mode_set (0, 16, 0);    

    return STORM_RETURN_SUCCESS;
}    

return_t timer_read (unsigned int timer_number, uint32_t *value)
{
    (*value) = timers[timer_number].ticks;

    return STORM_RETURN_SUCCESS;
}

return_t timer_write (unsigned int timer_number, uint32_t value)
{
    timers[timer_number].ticks = value;
    
    return STORM_RETURN_SUCCESS;
}

return_t timer_register_handler (unsigned int timer_number, 
    p_timer_handler_t timer_handler, p_void_t parameter)
{
    timers[timer_number].handler = timer_handler;
    timers[timer_number].data = parameter;

    return STORM_RETURN_SUCCESS;
}

    
return_t timer_unregister_handler (unsigned int timer_number)
{
    timers[timer_number].handler = NULL;
    timers[timer_number].data = NULL;

    return STORM_RETURN_SUCCESS;
}    

return_t timer_init (int argc UNUSED, char *argv[] UNUSED, char **envp UNUSED)
{
    pit_init ();

    irq_register (TIMER_IRQ, timer_handler, NULL);
   
    return STORM_RETURN_SUCCESS;
}
    
