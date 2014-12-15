#include "Common/irq.h"

#define IID_IRQ 0x00000401

enum
{
    MID_IRQ_AREGISTER,
    MID_IRQ_UNREGISTER,
};

typedef return_t (irq_aregister_function_t) (unsigned int irq_number, 
    p_irq_handler_t function, p_void_t parameter);

typedef return_t (irq_unregister_function_t) (unsigned int irq_number);

typedef struct
{
    irq_aregister_function_t *aregister;
    irq_unregister_function_t *unregister;
} irq_interface_t;

#define irq$aregister(handle,irq_number,function, parameter) \
    ((irq_interface_t *) ((handle)->functions))->aregister ( \
        (irq_number), (function), (parameter))

#define irq$unregister(handle,irq_number) \
    ((irq_interface_t *) ((handle)->functions))->unregister ( \
        (irq_number))


