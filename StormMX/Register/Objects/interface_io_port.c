#include <enviroment.h>

#include <Interfaces/io_port.h>

#include "../objects.h"

typedef struct
{
    io_port_aregister_function_t *function;
    method_id_t method_id;
    uint32_t parameters_size;

    uint32_t number_of_parameters;

    parameter_t parameters[3];

} object_io_port_aregister_method_t;

static object_io_port_aregister_method_t object_io_port_aregister_method =
{
    io_port_register,
    MID_IO_PORT_AREGISTER,
    sizeof (unsigned int) + sizeof (size_t) + sizeof (char *),
    3,
    {
        {sizeof (unsigned int)},
        {sizeof (size_t)},
        {sizeof (char *)}
    }
};

typedef struct
{
    io_port_unregister_function_t *function;
    method_id_t method_id;
    uint32_t parameters_size;

    uint32_t number_of_parameters;

    parameter_t parameters[1];

} object_io_port_unregister_method_t;

static object_io_port_unregister_method_t object_io_port_unregister_method =
{
    io_port_unregister,
    MID_IO_PORT_UNREGISTER,
    sizeof (unsigned int),
    1,
    {{sizeof (unsigned int)}}
};

static method_t *methods[] = 
{
    (method_t *) &object_io_port_aregister_method,
    (method_t *) &object_io_port_unregister_method,
};
#define number_of_methods 2

io_port_interface_t object_io_port_interface = 
{
    &io_port_register,
    &io_port_unregister,
};

return_t object_io_port_init (interface_id_t *interface_id)
{
    register_interface_register (interface_id, IID_IO_PORT, 
        INTERFACE_TYPE_STATIC, number_of_methods, methods, NULL);

    return STORM_RETURN_SUCCESS;
}


