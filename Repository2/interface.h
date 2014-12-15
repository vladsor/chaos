// Control
extern 
    interface_reference_t 
        interface_create 
        (
            class_reference_t class_reference,
            description_reference_t interface_description, 
            sequence_t interface_methods, 
            reference_t interface_factory,
            uint32_t options
        );

extern 
    void 
        interface_destroy 
        (
            interface_reference_t interface_reference
        );

extern 
    void 
        interface_invoke_method 
        (
            interface_reference_t interface_reference, 
            method_id_t method_id, 
            context_t context, 
            computer_reference_t computer,
            sequence_t parameters_in, 
            sequence_t parameters_out
        );

// Get and set methods
extern 
    method_reference_t 
        interface_get_method 
        (
            interface_reference_t interface_reference,
            method_id_t method_id
        );


