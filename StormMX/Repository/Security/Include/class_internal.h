
extern class_reference_t class_create_static_internal (p_class_t class);

extern void class_destroy_static_internal (class_reference_t class);

extern class_reference_t class_create_internal (p_class_description_t class_description,
    sequence_t class_interfaces, object_reference_t class_repository);
    
extern void class_destroy_internal (class_reference_t class);

extern void class_set_interfaces_internal (class_reference_t class, 
    sequence_t class_interfaces);
    
extern sequence_t class_get_interfaces_internal (class_reference_t class_reference);

extern interface_reference_t class_get_interface_internal (class_reference_t class_reference, 
    interface_id_t interface_id);

