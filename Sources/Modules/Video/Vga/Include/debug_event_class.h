#include <EventClasses/debug.h>

extern description_reference_t debug_description_register (void);

extern 
    event_supplier_interface_reference_t 
        debug_supplier_interface_register 
        (
            uint32_t type,
            p_debug_supplier_handler_t handler,
            cpu_reference_t cpu
        );

extern 
    event_consumer_interface_reference_t 
        debug_consumer_interface_register 
        (
            uint32_t type,
            p_debug_consumer_handler_t handler,
            cpu_reference_t cpu
        );

