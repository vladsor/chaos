// Control
extern 
    class_reference_t 
        class_create 
        (
            description_reference_t class_description,
            handle_reference_t object_factory,
            uint32_t options
        );
    
extern 
    void 
        class_destroy 
        (
            class_reference_t class_reference
        );

extern 
    void 
        class_invoke_method 
        (
            class_reference_t class_reference,
            interface_reference_t interface_reference, 
            method_id_t method_id, 
            context_t context,
            computer_reference_t computer,
            sequence_t parameters_in, 
            sequence_t parameters_out);

// Get and set methods
extern 
    interface_reference_t 
        class_get_interface 
        (
            class_reference_t class_reference, 
            interface_id_t interface_id
        );

