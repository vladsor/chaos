enum interface_type_t
{
    INTERFACE_TYPE_DYNAMIC,
    INTERFACE_TYPE_STATIC,

	INTERFACE_TYPE_OBJECT_FACTORY,
	INTERFACE_TYPE_HANDLE_FACTORY,

	INTERFACE_TYPE_EVENT_SUPPLIER_FACTORY,
	INTERFACE_TYPE_EVENT_CONSUMER_FACTORY,
};

typedef id_t interface_id_t;
typedef interface_id_t * p_interface_id_t;

typedef struct
{
    description_reference_struct_t header;

    wchar_t name[WSTRING_MAX_LENGTH];
    uint32_t type;

    sequence_t method_descriptions;
    
} interface_description_t;

typedef interface_description_t * p_interface_description_t;

// Dynamic
extern 
    description_reference_t 
        interface_description_register 
        (
            id_t id,
            const wchar_t *name,
            uint32_t type,
            sequence_t method_descriptions
        );

extern 
    void 
        interface_description_unregister 
        (
            description_reference_t description_reference
        );


