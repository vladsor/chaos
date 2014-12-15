#ifndef __INTERFACE_TIMER_H__
#define __INTERFACE_TIMER_H__

#define IID_TIMER 0x00000701

enum
{
    MID_TIMER_SLEEP_MILLI,
    MID_TIMER_SLEEP_MICRO,
    MID_TIMER_READ,
    MID_TIMER_WRITE,
};

typedef return_t (timer_sleep_milli_function_t) (unsigned int time);
typedef return_t (timer_sleep_micro_function_t) (unsigned int time);
typedef return_t (timer_read_function_t) (uint64_t *value);
typedef return_t (timer_write_function_t) (uint64_t value);

typedef struct
{
    timer_sleep_milli_function_t *sleep_milli;
    timer_sleep_micro_function_t *sleep_micro;
    timer_read_function_t *read;
    timer_write_function_t *write;
} timer_interface_t;

#define timer$sleep_milli(handle,time) \
    ((timer_interface_t *) ((handle)->functions))->sleep_milli ( \
        (time))

#define timer$sleep_micro(handle,time) \
    ((timer_interface_t *) ((handle)->functions))->sleep_micro ( \
        (time))

#define timer$read(handle,value) \
    ((timer_interface_t *) ((handle)->functions))->read ( \
        (value))

#define timer$write(handle,value) \
    ((timer_interface_t *) ((handle)->functions))->write ( \
        (value))

#endif /* !__INTERFACE_TIMER_H__ */

