
// Control
extern handle_reference_t handle_create (object_reference_t object_reference, 
    interface_id_t interface_id, 
    sequence_t parameters, 
    uint32_t options);

extern void handle_destroy (handle_reference_t handle_reference);

extern handle_reference_t handle_clone (handle_reference_t handle_reference, 
    uint32_t options);

extern void handle_invoke_method (handle_reference_t handle_reference, 
    method_id_t method_id, 
    computer_reference_t computer,
    sequence_t parameters_in, sequence_t parameters_inout, 
    sequence_t parameters_out, 
    uint32_t options);

// Get and set methods

extern uint64_t handle_get_data (handle_reference_t handle_reference);

extern object_reference_t handle_get_object (
    handle_reference_t handle_reference);

extern interface_reference_t handle_get_interface (
    handle_reference_t handle_reference);


