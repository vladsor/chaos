
// Control
extern object_reference_t object_create (class_reference_t class_reference, 
    security_reference_t security_reference, sequence_t parameters, 
    uint32_t options);

extern void object_destroy (object_reference_t object_reference);

extern object_reference_t object_clone (object_reference_t object_reference,
    uint32_t options);

extern void object_invoke_method (object_reference_t object_reference,
    interface_reference_t interface_reference, method_id_t method_id, 
    uint64_t handle_data, 
    computer_reference_t computer,
    sequence_t return_value, sequence_t parameters);

extern void object_fire_event (object_reference_t object_reference,
    event_supplier_interface_reference_t interface_reference,
    uint64_t event_supplier_data, 
    event_queue_reference_t event_queue,
    sequence_t event_data);

extern void object_wait_event (object_reference_t object_reference,
    event_consumer_interface_reference_t interface_reference,
    uint64_t event_consumer_data, 
    event_queue_reference_t event_queue,
    sequence_t event_data);

// Util
extern object_reference_t object_get_current (void);
extern object_reference_t object_get_kernel (void);

// Get and set methods
extern uint64_t object_get_data (object_reference_t object_reference);

extern void object_set_data (object_reference_t object_reference, 
    uint64_t data);

extern class_reference_t object_get_class (
    object_reference_t object_reference);
    
extern interface_reference_t object_get_interface_by_id (
    object_reference_t object_reference, 
    interface_id_t interface_id);

extern interface_reference_t object_get_interface_by_index (
    object_reference_t object_reference, 
    uint32_t index);

extern 
    event_supplier_interface_reference_t 
        object_get_event_supplier_interface_by_id 
        (
            object_reference_t object_reference, 
            uint32_t event_class_id
        );
    
extern 
    event_consumer_interface_reference_t 
        object_get_event_consumer_interface_by_id 
        (
            object_reference_t object_reference, 
            uint32_t event_class_id
        );

extern security_reference_t object_get_security (
    object_reference_t object_reference);

extern void object_set_security (object_reference_t object_reference,
    security_reference_t security_reference);


/*
object_get_quality (object, interface_id, method_id);
*/


