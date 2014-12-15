
extern interface_reference_t interface_create_static_internal (p_interface_t interface);

extern void interface_destroy_static_internal (interface_reference_t interface);

extern interface_reference_t interface_create_internal (
    p_interface_description_t interface_description, 
    sequence_t interface_methods);
    
extern void interface_destroy_internal (interface_reference_t interface);

