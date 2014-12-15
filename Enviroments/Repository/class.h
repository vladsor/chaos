// Control
extern class_reference_t class_create (
    description_reference_t class_description,
    sequence_t class_interfaces, 
    sequence_t event_supplier_interfaces, 
    sequence_t event_consumer_interfaces, 
    handle_reference_t object_factory,
    uint32_t options);
    
extern void class_destroy (class_reference_t class_reference);

extern void class_invoke_method (class_reference_t class_reference,
    interface_reference_t interface_reference, method_id_t method_id, 
    context_t context,
    computer_reference_t computer,
    sequence_t parameters, sequence_t return_value);

extern void class_fire_event (class_reference_t class_reference,
    event_supplier_interface_reference_t interface_reference,
    context_t context, 
    event_queue_reference_t event_queue,
    sequence_t event_data);

extern void class_wait_event (class_reference_t class_reference,
    event_consumer_interface_reference_t interface_reference,
    context_t context, 
    event_queue_reference_t event_queue,
    sequence_t event_data);

// Get and set methods
extern sequence_t class_get_interfaces (class_reference_t class_reference);
    
extern void class_set_interfaces (class_reference_t class_reference, 
    sequence_t class_interfaces);

extern interface_reference_t class_get_interface_by_index (
    class_reference_t class_reference, uint32_t index);

extern interface_reference_t class_get_interface_by_id (
    class_reference_t class_reference, interface_id_t interface_id);


/*
    handle_reference_t object_factory;
    handle_reference_t handle_factory;
    
    handle_reference_t state_monitor;
    handle_reference_t security_monitor;
*/

