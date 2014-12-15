extern handle_t handle_timer;

static inline return_t timer_sleep_milli (unsigned int time)
{
    return timer$sleep_milli (&handle_timer, time);
}

static inline return_t timer_sleep_micro (unsigned int time)
{
    return timer$sleep_micro (&handle_timer, time);
}

static inline return_t timer_system_read (uint64_t *value)
{
    return timer$read (&handle_timer, value);
}

