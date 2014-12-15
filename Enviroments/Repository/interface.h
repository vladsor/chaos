// Control
extern 
    interface_reference_t 
        interface_create 
        (
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
            sequence_t parameters, 
            sequence_t return_value
        );

// Get and set methods
extern method_reference_t interface_get_method_by_index (
    interface_reference_t interface_reference,
    uint32_t index);

extern method_reference_t interface_get_method_by_id (
    interface_reference_t interface_reference,
    method_id_t method_id);


