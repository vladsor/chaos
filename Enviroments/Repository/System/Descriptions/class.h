enum class_type_t
{
    CLASS_TYPE_STATIC,    
    CLASS_TYPE_DYNAMIC,
};

typedef struct
{
    description_reference_struct_t header;

    wchar_t name[WSTRING_MAX_LENGTH];

    uint32_t type;
    uint32_t number_of_interfaces;
} class_description_t;

typedef class_description_t * p_class_description_t;

extern description_reference_t class_description_register_static (
    p_class_description_t class_description);
    
extern void class_description_unregister_static (description_reference_t description);

extern description_reference_t class_description_register (
    p_class_description_t class_description);

extern void class_description_unregister (description_reference_t description);

