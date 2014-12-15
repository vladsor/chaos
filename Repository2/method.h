extern 
    method_reference_t 
        method_create 
        (
            interface_reference_t inerface_reference,
            description_reference_t description, 
            computer_reference_t computer,
            p_method_function_t function, 
            data_t data,
            uint32_t options
        );

extern 
    void 
        method_destroy 
        (
            method_reference_t method_reference
        );
/*
extern void method_invoke (method_reference_t method, 
    computer_reference_t computer, 
    sequence_t parameters_in,
    sequence_t parameters_out, 
    uint32_t options);
*/
