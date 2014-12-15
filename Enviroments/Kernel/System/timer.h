/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file timer.h
 * @brief Timer support.
 */

#ifndef __STORM_TIMER_H__
#define __STORM_TIMER_H__

extern return_t timer_init (int argc, char *argv[], char **envp);

enum timer_mode_t
{
    TIMER_MODE_ONE_SHOT,
    TIMER_MODE_PERIODIC,
};

extern return_t timer_start (unsigned int timer_number);
extern return_t timer_stop (unsigned int timer_number);

extern return_t timer_set_period (unsigned int timer_number, uint32_t period);
extern return_t timer_set_mode (unsigned int timer_number, unsigned int mode);

extern return_t timer_read (unsigned int timer_number, uint32_t *value);
extern return_t timer_write (unsigned int timer_number, uint32_t value);

extern return_t timer_register_handler (unsigned int timer_number, 
    p_timer_handler_t timer_handler, p_void_t parameter);
extern return_t timer_unregister_handler (unsigned int timer_number);

#endif /* !__STORM_TIMER_H__ */
