
enum parameter_type_t
{
    PARAMETER_TYPE_BASE,
    PARAMETER_TYPE_SEQUENCE,
    PARAMETER_TYPE_STRUCT,
    PARAMETER_TYPE_OBJECT,
    PARAMETER_TYPE_INTERFACE,
};

typedef struct
{
    description_reference_struct_t header;

    uint32_t type;
    uint32_t size;
    
} data_description_t;

typedef data_description_t * p_data_description_t;


extern description_reference_t data_description_register_static (
    p_data_description_t data_description);
    
extern void data_description_unregister_static (
    description_reference_t description);

extern description_reference_t data_description_register (
    p_data_description_t data_description);

extern void data_description_unregister (description_reference_t description);

