#include <enviroment.h>

#include <Interfaces/debug.h>

#include "../objects.h"

typedef struct
{
    debug_print_function_t *function;
    method_id_t method_id;
    uint32_t parameters_size;

    uint32_t number_of_parameters;

    parameter_t parameters[5];

} object_debug_print_method_t;

static object_debug_print_method_t object_debug_print_method =
{
    system_debug_print,
    MID_DEBUG_PRINT,
    sizeof (uint8_t) + sizeof (char *) + sizeof (char *) + sizeof (uint32_t) + 
        sizeof (char *),
    5,
    {
        {sizeof (uint8_t)},
        {sizeof (char *)},
        {sizeof (char *)},
        {sizeof (uint32_t)},
        {sizeof (char *)}
    }
};

static method_t *methods[] = 
{
    (method_t *) &object_debug_print_method,
};
#define number_of_methods 1

debug_interface_t object_debug_interface = 
{
    &system_debug_print,
};

return_t object_debug_init (interface_id_t *interface_id)
{
    register_interface_register (interface_id, IID_DEBUG, 
        INTERFACE_TYPE_STATIC, number_of_methods, methods, NULL);

    return STORM_RETURN_SUCCESS;
}

