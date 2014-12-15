/* $chaos: timer.c,v 1.3 2002/10/04 19:01:21 per Exp $ */
/* Abstract: Timer support. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <enviroment.h>
#include <string.h>

#include "Include/pit.h"
#include "Include/timer.h"

//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE2
#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

/* The timer frequency. */
uint32_t hz = 100;
volatile uint32_t ticks = 0;

list_t timers;

static char *screen = (char *)(0xB8000);
static char hex[] = "0123456789ABCDEF";

static void timer_handler (void)
{
    iterator_t *iterator;
    timer_t *timer;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE2,
         "%s::%s ()\n",
        __FILE__, __FUNCTION__);

    ticks++;
    
    screen[0] = hex[BITS_GET (ticks, 15, 12)];
    screen[2] = hex[BITS_GET (ticks, 11,  8)];
    screen[4] = hex[BITS_GET (ticks,  7,  4)];
    screen[6] = hex[BITS_GET (ticks,  3,  0)];

    for (iterator = (iterator_t *) list_get_iterator (&timers); 
        iterator$has_next (iterator); )
    {
        timer = (timer_t *) iterator$get_next (iterator);
        
        if ((ticks - timer->start_tick) % timer->period == 0)
        {
            if (timer->type == TIMER_ONE_SHOT)
            {
                timer_stop (timer);
            }
            
            if (timer->handler != NULL)
            {
                DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
                    "%s::%s Calling: %p\n",
                    __FILE__, __FUNCTION__, timer->handler);
                    
                timer->handler ();
            }
        }
    }
}

return_t timer_create (timer_t *timer, uint32_t period, unsigned int type, 
    timer_handler_t *function)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
         "%s::%s (%p, %u, %u, %p)\n",
        __FILE__, __FUNCTION__, timer, period, type, function);
        
    timer->period = (period >= (1000 / hz)) ? (period * hz / 1000) : 1;
    timer->type = type;
    timer->handler = function;
    timer->start_tick = 0;
    timer->state = TIMER_STATE_STOPED;

    return STORM_RETURN_SUCCESS;
}

return_t timer_destroy (timer_t *timer)
{
    if (timer->state == TIMER_STATE_COUNTED)
    {
        timer_stop (timer);
    }

    return STORM_RETURN_SUCCESS;
}

return_t timer_start (timer_t *timer)
{
    if (timer->state != TIMER_STATE_STOPED)
    {
        return -1;
    }
    
    timer->state = TIMER_STATE_COUNTED;
    timer->start_tick = ticks;
    
    list_node_insert (&timers, (list_node_t *) timer, LIST_OPTION_LAST);
    
    return STORM_RETURN_SUCCESS;
}

return_t timer_stop (timer_t *timer)
{
    if (timer->state != TIMER_STATE_COUNTED)
    {
        return -1;
    }
    
    timer->state = TIMER_STATE_STOPED;

    list_node_remove (&timers, (list_node_t *) timer);
    
    return STORM_RETURN_SUCCESS;
}

return_t timer_set_period (timer_t *timer, uint32_t period)
{
    if (timer->state != TIMER_STATE_STOPED)
    {
        return -1;
    }

    timer->period = (period >= (1000 / hz)) ? (period * hz / 1000) : 1;
    
    return STORM_RETURN_SUCCESS;
}

return_t timer_read (timer_t *timer, uint32_t *value)
{
    (*value) = (ticks - timer->start_tick) * 1000 / hz;

    return STORM_RETURN_SUCCESS;
}

return_t timer_write (timer_t *timer, uint32_t value)
{
    timer->start_tick = ticks - value * hz / 1000;
    
    return STORM_RETURN_SUCCESS;
}

return_t timer_init (int argc, char *argv[])
{
    int i;
    
    for (i = 1; i < argc; i++)
    {
        if ((string_compare (argv[i], "--hz") == 0) && (i + 1 < argc))
        {
            string_to_uint32 (argv[i + 1], &hz, 10, NULL);
            i++;
        }
    }

    list_create (&timers);
    
    pit_init ();
    
    timer_sleep_init ();
    timer_system_init ();

    irq_register (0, &timer_handler);
    
    return STORM_RETURN_SUCCESS;
}
    
