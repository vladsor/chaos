#include <enviroment.h>

#include <Interfaces/dma.h>

#include "../objects.h"

typedef struct
{
    dma_aregister_function_t *function;
    method_id_t method_id;
    uint32_t parameters_size;

    uint32_t number_of_parameters;

    parameter_t parameters[2];

} object_dma_aregister_method_t;

static object_dma_aregister_method_t object_dma_aregister_method =
{
    dma_register,
    MID_DMA_AREGISTER,
    sizeof (int) + sizeof (void **),
    2,
    {
        {sizeof (int)},
        {sizeof (void **)}
    }
};

typedef struct
{
    dma_unregister_function_t *function;
    method_id_t method_id;
    uint32_t parameters_size;

    uint32_t number_of_parameters;

    parameter_t parameters[1];

} object_dma_unregister_method_t;

static object_dma_unregister_method_t object_dma_unregister_method =
{
    dma_unregister,
    MID_DMA_UNREGISTER,
    sizeof (int),
    1,
    {{sizeof (int)}}
};

typedef struct
{
    dma_transfer_function_t *function;
    method_id_t method_id;
    uint32_t parameters_size;

    uint32_t number_of_parameters;

    parameter_t parameters[5];

} object_dma_transfer_method_t;

static object_dma_transfer_method_t object_dma_transfer_method =
{
    dma_transfer,
    MID_DMA_TRANSFER,
    sizeof (unsigned int) + sizeof (unsigned int) + sizeof (unsigned int) + 
        sizeof (unsigned int) + sizeof (bool),
    5,
    {
        {sizeof (unsigned int)},
        {sizeof (unsigned int)},
        {sizeof (unsigned int)},
        {sizeof (unsigned int)},
        {sizeof (bool)},
    }
};

static method_t *methods[] = 
{
    (method_t *) &object_dma_aregister_method,
    (method_t *) &object_dma_unregister_method,
    (method_t *) &object_dma_transfer_method,
};
#define number_of_methods 3

dma_interface_t object_dma_interface = 
{
    &dma_register,
    &dma_unregister,
    &dma_transfer,
};

return_t object_dma_init (interface_id_t *interface_id)
{
    register_interface_register (interface_id, IID_DMA, 
        INTERFACE_TYPE_STATIC, number_of_methods, methods, NULL);

    return STORM_RETURN_SUCCESS;
}

