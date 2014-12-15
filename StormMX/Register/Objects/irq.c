#include <enviroment.h>

#include <Interfaces/irq.h>

#include "../objects.h"

typedef struct
{
    irq_aregister_function_t *function;
    method_id_t method_id;
    uint32_t parameters_size;

    uint32_t number_of_parameters;

    parameter_t parameters[2];

} object_irq_aregister_method_t;

static object_irq_aregister_method_t object_irq_aregister_method =
{
    irq_register,
    MID_IRQ_AREGISTER,
    sizeof (unsigned int) + sizeof (irq_handler_t *),
    2,
    {
        {sizeof (unsigned int)},
        {sizeof (irq_handler_t *)}
    }
};

typedef struct
{
    irq_unregister_function_t *function;
    method_id_t method_id;
    uint32_t parameters_size;

    uint32_t number_of_parameters;

    parameter_t parameters[1];

} object_irq_unregister_method_t;

static object_irq_unregister_method_t object_irq_unregister_method =
{
    irq_unregister,
    MID_IRQ_UNREGISTER,
    sizeof (unsigned int),
    1,
    {{sizeof (unsigned int)}}
};

static method_t *methods[] = 
{
    (method_t *) &object_irq_aregister_method,
    (method_t *) &object_irq_unregister_method,
};
#define number_of_methods 2

irq_interface_t object_irq_interface = 
{
    &irq_register,
    &irq_unregister,
};

return_t object_irq_init (interface_id_t *interface_id)
{
    register_interface_register (interface_id, IID_IRQ, 
        INTERFACE_TYPE_STATIC, number_of_methods, methods, NULL);

    return STORM_RETURN_SUCCESS;
}


