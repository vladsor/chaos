typedef struct
{
    reference_struct_t header;

    p_event_description_t event_description;
    unsigned int type;
    p_method_t handle;
    reference_t factory;
    unsigned int factory_type;

} event_supplier_interface_t;

typedef event_supplier_interface_t * p_event_supplier_interface_t;
typedef p_event_supplier_interface_t * p_p_event_supplier_interface_t;


