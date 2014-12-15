// Control
extern event_supplier_reference_t event_supplier_create (
    object_reference_t object_reference, 
    event_id_t event_class_id, 
    sequence_t parameters, 
    uint32_t options);
    
extern void event_supplier_destroy (
    event_supplier_reference_t event_supplier_reference);

extern void event_supplier_fire_event (
    event_supplier_reference_t event_supplier_reference, 
    sequence_t event_data, uint32_t options);

// Get and set methods
extern uint64_t event_supplier_get_data (
    event_supplier_reference_t event_supplier_reference);

extern void event_supplier_set_data (
    event_supplier_reference_t event_supplier_reference,
    uint64_t data);

extern void event_supplier_set_queue (
    event_supplier_reference_t event_supplier_reference,
    event_queue_reference_t event_queue_reference);


