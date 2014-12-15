enum class_type_t
{
    CLASS_TYPE_STATIC,    
    CLASS_TYPE_DYNAMIC,
};

typedef id_t class_id_t;
typedef class_id_t * p_class_id_t;

typedef struct
{
    description_reference_struct_t header;

    wchar_t name[WSTRING_MAX_LENGTH];

    uint32_t type;
    
    uint32_t number_of_interfaces;
    uint32_t number_of_event_suppliers;
    uint32_t number_of_event_consumers;
} class_description_t;

typedef class_description_t * p_class_description_t;

// Dynamic
extern 
    description_reference_t 
        class_description_register 
        (
            id_t id,
            const wchar_t *name,
            uint32_t type,
            uint32_t number_of_interfaces,
            uint32_t number_of_event_suppliers,
            uint32_t number_of_event_consumers
        );

extern 
    void 
        class_description_unregister 
        (
            description_reference_t description_reference
        );


