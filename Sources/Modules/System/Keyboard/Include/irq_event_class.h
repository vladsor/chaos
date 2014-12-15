
extern description_reference_t irq_description_register (void);

extern 
    event_supplier_interface_reference_t 
        irq_supplier_interface_register 
        (
            uint32_t type,
            p_irq_supplier_handler_t handler,
            cpu_reference_t cpu
        );

extern 
    event_consumer_interface_reference_t 
        irq_consumer_interface_register 
        (
            uint32_t type,
            p_irq_consumer_handler_t handler,
            cpu_reference_t cpu
        );

