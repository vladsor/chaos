#include <enviroment.h>

#include <Interfaces/cpu.h>

#include "../objects.h"

typedef struct
{
    cpu_halt_function_t *function;
    method_id_t method_id;
    uint32_t parameters_size;

    uint32_t number_of_parameters;

    parameter_t parameters[1];

} object_cpu_halt_method_t;

static object_cpu_halt_method_t object_cpu_halt_method =
{
    cpu_halt,
    MID_CPU_HALT,
    sizeof (enum halt_t),
    1,
    {{sizeof (enum halt_t)}}
};

typedef struct
{
    cpu_lock_function_t *function;
    method_id_t method_id;
    uint32_t parameters_size;

    uint32_t number_of_parameters;

} object_cpu_lock_method_t;

static object_cpu_lock_method_t object_cpu_lock_method =
{
    cpu_lock,
    MID_CPU_LOCK,
    0,
    0,
};

typedef struct
{
    cpu_unlock_function_t *function;
    method_id_t method_id;
    uint32_t parameters_size;

    uint32_t number_of_parameters;

} object_cpu_unlock_method_t;

static object_cpu_unlock_method_t object_cpu_unlock_method =
{
    cpu_unlock,
    MID_CPU_UNLOCK,
    0,
    0,
};

typedef struct
{
    cpu_get_info_function_t *function;
    method_id_t method_id;
    uint32_t parameters_size;

    uint32_t number_of_parameters;

    parameter_t parameters[1];

} object_cpu_get_info_method_t;

static object_cpu_get_info_method_t object_cpu_get_info_method =
{
    cpu_get_info,
    MID_CPU_GET_INFO,
    sizeof (cpu_info_t *),
    1,
    {{sizeof (cpu_info_t *)}}
};

static method_t *methods[] = 
{
    (method_t *) &object_cpu_halt_method,
    (method_t *) &object_cpu_lock_method,
    (method_t *) &object_cpu_unlock_method,
    (method_t *) &object_cpu_get_info_method,
};
#define number_of_methods 4

cpu_interface_t object_cpu_interface = 
{
    &cpu_halt,
    &cpu_lock,
    &cpu_unlock,
    &cpu_get_info
};

return_t object_cpu_init (interface_id_t *interface_id)
{
    register_interface_register (interface_id, IID_CPU, 
        INTERFACE_TYPE_STATIC, number_of_methods, methods, NULL);

    return STORM_RETURN_SUCCESS;
}
