#include <enviroment.h>

#include <Interfaces/thread.h>

#include "../objects.h"

typedef struct
{
    thread_create_function_t *function;
    method_id_t method_id;
    uint32_t parameters_size;

    uint32_t number_of_parameters;

    parameter_t parameters[2];

} thread_create_method_t;

static thread_create_method_t thread_create_method =
{
    thread_create,
    MID_THREAD_CREATE,
    sizeof (thread_t *) + sizeof (thread_function_t *),
    2,
    {
        {sizeof (thread_t *)},
        {sizeof (thread_function_t *)}
    }
};

static method_t *methods[] = 
{
    (method_t *) &thread_create_method,
};
#define number_of_methods 1

return_t object_thread_init (interface_id_t *interface_id)
{
    register_interface_register (interface_id, IID_THREAD, 
        INTERFACE_TYPE_STATIC, number_of_methods, methods, NULL);

    return STORM_RETURN_SUCCESS;
}
