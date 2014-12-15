#include <enviroment.h>

#include <Interfaces/timer.h>

#include "../objects.h"

typedef struct
{
    timer_sleep_milli_function_t *function;
    method_id_t method_id;
    uint32_t parameters_size;

    uint32_t number_of_parameters;

    parameter_t parameters[1];

} object_timer_sleep_milli_method_t;

static object_timer_sleep_milli_method_t object_timer_sleep_milli_method =
{
    timer_sleep_milli,
    MID_TIMER_SLEEP_MILLI,
    sizeof (unsigned int),
    1,
    {{sizeof (unsigned int)}}
};

typedef struct
{
    timer_sleep_micro_function_t *function;
    method_id_t method_id;
    uint32_t parameters_size;

    uint32_t number_of_parameters;

    parameter_t parameters[1];

} object_timer_sleep_micro_method_t;

static object_timer_sleep_micro_method_t object_timer_sleep_micro_method =
{
    timer_sleep_micro,
    MID_TIMER_SLEEP_MICRO,
    sizeof (unsigned int),
    1,
    {{sizeof (unsigned int)}}
};

typedef struct
{
    timer_read_function_t *function;
    method_id_t method_id;
    uint32_t parameters_size;

    uint32_t number_of_parameters;

    parameter_t parameters[1];

} object_timer_read_method_t;

static object_timer_read_method_t object_timer_read_method =
{
    timer_system_read,
    MID_TIMER_READ,
    sizeof (uint64_t *),
    1,
    {{sizeof (uint64_t *)}}
};

typedef struct
{
    timer_write_function_t *function;
    method_id_t method_id;
    uint32_t parameters_size;

    uint32_t number_of_parameters;

    parameter_t parameters[1];

} object_timer_write_method_t;

static object_timer_write_method_t object_timer_write_method =
{
    NULL,
    MID_TIMER_WRITE,
    sizeof (uint64_t),
    1,
    {{sizeof (uint64_t)}}
};

static method_t *methods[] = 
{
    (method_t *) &object_timer_sleep_milli_method,
    (method_t *) &object_timer_sleep_micro_method,
    (method_t *) &object_timer_read_method,
    (method_t *) &object_timer_write_method,
};
#define number_of_methods 4

timer_interface_t object_timer_interface = 
{
    &timer_sleep_milli,
    &timer_sleep_micro,
    &timer_read,
    &timer_write
};

return_t object_timer_init (interface_id_t *interface_id)
{
    register_interface_register (interface_id, IID_TIMER, 
        INTERFACE_TYPE_STATIC, number_of_methods, methods, NULL);

    return STORM_RETURN_SUCCESS;
}

