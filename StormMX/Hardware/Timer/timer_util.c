#include <enviroment.h>
#include <string.h>

#include "Include/pit.h"
#include "Include/timer.h"

//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

timer_t sleep_timer;

static volatile bool locked = FALSE;

static void timer_sleep_unlock (void)
{
    locked = FALSE;
}

/* Sleep the given amount of milliseconds (by looping). */
return_t timer_sleep_milli (unsigned int time)
{
    timer_set_period (&sleep_timer, time);
    timer_start (&sleep_timer);
    locked = TRUE;

    while (locked)
    {
        cpu_no_operation ();
    }

    return STORM_RETURN_SUCCESS;
}

return_t timer_sleep_micro (unsigned int time)
{

    return STORM_RETURN_SUCCESS;
}

/*
return_t timer_sleep_nano (void *data UNUSED, unsigned int time)
{
    uint64_t count, wait_count;

    rdrsc (count);
    wait_count = count + ((uint64_t) time * cpu_frequency / 1000 000 000);
}
*/

return_t timer_sleep_init (void)
{
    timer_create (&sleep_timer, 0, TIMER_ONE_SHOT, &timer_sleep_unlock);
    
    return STORM_RETURN_SUCCESS;
}

timer_t system_timer;

return_t timer_system_read (uint32_t *value)
{
    return timer_read (&system_timer, value);
}

return_t timer_system_init (void)
{
    timer_create (&system_timer, 1000 / hz, TIMER_PERIODIC, NULL);
    timer_start (&system_timer);
    
    return STORM_RETURN_SUCCESS;
}

