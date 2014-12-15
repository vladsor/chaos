
extern description_reference_t keyboard_description_register (void);

extern 
    event_supplier_interface_reference_t 
        keyboard_supplier_interface_register 
        (
            uint32_t type,
            p_keyboard_supplier_handler_t handler,
            cpu_reference_t cpu,
            reference_t factory
        );

extern 
    event_consumer_interface_reference_t 
        keyboard_consumer_interface_register 
        (
            uint32_t type,
            p_keyboard_consumer_handler_t handler,
            cpu_reference_t cpu,
            reference_t factory
        );

