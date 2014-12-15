typedef struct
{
    reference_struct_t header;
    
    p_class_description_t description;
    sequence_t interfaces;
    
    sequence_t event_supplier_interfaces;
    sequence_t event_consumer_interfaces;
    
    handle_reference_t object_factory;
    handle_reference_t handle_factory;
    
    handle_reference_t state_monitor;
    handle_reference_t security_monitor;
    
    handle_reference_t quality_control;
    handle_reference_t transaction_control;

} class_t;

typedef class_t * p_class_t;
typedef p_class_t * p_p_class_t;

// Static
extern class_reference_t class_create_static (p_class_t class);

extern void class_destroy_static (class_reference_t class_reference);
