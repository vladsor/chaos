#include <enviroment.h>

#include <Interfaces/memory.h>

#include "../objects.h"

typedef struct
{
    memory_allocate_function_t *function;
    method_id_t method_id;
    uint32_t parameters_size;

    uint32_t number_of_parameters;

    parameter_t parameters[2];

} object_memory_allocate_method_t;

static object_memory_allocate_method_t object_memory_allocate_method =
{
    global_memory_allocate,
    MID_MEMORY_ALLOCATE,
    sizeof (void **) + sizeof (unsigned int),
    2,
    {
        {sizeof (enum halt_t)},
        {sizeof (unsigned int)}
    }
};

typedef struct
{
    memory_deallocate_function_t *function;
    method_id_t method_id;
    uint32_t parameters_size;

    uint32_t number_of_parameters;

    parameter_t parameters[1];

} object_memory_deallocate_method_t;

static object_memory_deallocate_method_t object_memory_deallocate_method =
{
    global_memory_deallocate,
    MID_MEMORY_DEALLOCATE,
    sizeof (void *),
    1,
    {
        {sizeof (void *)}
    }
};

static method_t *methods[] = 
{
    (method_t *) &object_memory_allocate_method,
    (method_t *) &object_memory_deallocate_method,
};
#define number_of_methods 2

memory_interface_t object_memory_interface = 
{
    &global_memory_allocate,
    &global_memory_deallocate,
};

return_t object_memory_init (interface_id_t *interface_id)
{
    register_interface_register (interface_id, IID_MEMORY, 
        INTERFACE_TYPE_STATIC, number_of_methods, methods, NULL);

    return STORM_RETURN_SUCCESS;
}


