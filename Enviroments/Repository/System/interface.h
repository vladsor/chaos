typedef struct
{
    reference_struct_t header;

    p_interface_description_t description; 
    sequence_t methods;

    reference_t factory;
} interface_t;

typedef interface_t * p_interface_t;
typedef p_interface_t * p_p_interface_t;


// Static
extern interface_reference_t interface_create_static (p_interface_t interface);

extern void interface_destroy_static (
    interface_reference_t interface_reference);
