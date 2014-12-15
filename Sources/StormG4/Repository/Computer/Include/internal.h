extern volatile list_t computers;

extern void computer_invoke_internal (p_computer_t computer,
    p_handle_t handle, p_object_t object, p_class_t class, 
    p_interface_t interface, p_method_t method, context_t context,
    reference_t base_reference, reference_t new_reference,
    sequence_t parameters_in, sequence_t parameters_inout,
    sequence_t parameters_out);

extern void computer_invoke_async_internal (p_computer_t computer,
    p_handle_t handle, p_object_t object, p_class_t class, 
    p_interface_t interface, p_method_t method, 
    reference_t reference_base, reference_t reference_new,
    sequence_t parameters_in, sequence_t parameters_inout);

extern void computer_call_function (p_function_t function, uint32_t type, 
    uint64_t data, context_t context,
    reference_t reference_base, reference_t reference_new,
    sequence_t parameters_in, sequence_t parameters_inout,
    sequence_t parameters_out);

extern void computer_start (p_computer_t computer);    
extern void computer_stop (p_computer_t computer);

extern void computer_schedule_prepare (void);
extern void computer_begin (void);

