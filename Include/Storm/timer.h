/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file timer.h
 * @brief Timer support.
 */

#ifndef __STORM_TIMER_H__
#define __STORM_TIMER_H__

extern return_t timer_init (int argc, char *argv[]);

extern return_t timer_sleep_milli (unsigned int time);
extern return_t timer_sleep_micro (unsigned int time);
//extern return_t timer_sleep_nano (unsigned int time);

typedef void (timer_handler_t) (void);

#include <list.h>

enum
{
    TIMER_ONE_SHOT,
    TIMER_PERIODIC,
};

enum
{
    TIMER_STATE_STOPED,
    TIMER_STATE_COUNTED,
};

typedef struct
{
    LIST_NODE_PART;
    
    uint32_t period;
    unsigned int type;
    timer_handler_t *handler;
    
    uint32_t start_tick;
    unsigned int state;
} timer_t;

extern return_t timer_create (timer_t *timer, uint32_t period, 
    unsigned int type, timer_handler_t *function);
extern return_t timer_destroy (timer_t *timer);
extern return_t timer_start (timer_t *timer);
extern return_t timer_stop (timer_t *timer);
extern return_t timer_set_period (timer_t *timer, uint32_t period);
extern return_t timer_read (timer_t *timer, uint32_t *value);
extern return_t timer_write (timer_t *timer, uint32_t value);

extern return_t timer_system_read (uint32_t *value);

extern uint32_t hz;

#endif /* !__STORM_TIMER_H__ */
