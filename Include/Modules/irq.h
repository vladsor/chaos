extern handle_t handle_irq;

static inline return_t irq_register (unsigned int irq_number, 
    p_irq_handler_t function, p_void_t parameter)
{
    return irq$aregister (&handle_irq, irq_number, function, parameter);
}

static inline return_t irq_unregister (int irq_number)
{
    return irq$unregister (&handle_irq, irq_number);
}

