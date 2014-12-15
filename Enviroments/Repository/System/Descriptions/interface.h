enum interface_type_t
{
    INTERFACE_TYPE_DYNAMIC,
    INTERFACE_TYPE_STATIC,

	INTERFACE_TYPE_OBJECT_FACTORY,
	INTERFACE_TYPE_HANDLE_FACTORY,

	INTERFACE_TYPE_EVENT_SUPPLIER_FACTORY,
	INTERFACE_TYPE_EVENT_CONSUMER_FACTORY,
};

typedef struct
{
    description_reference_struct_t header;

    wchar_t name[WSTRING_MAX_LENGTH];
    uint32_t type;
    sequence_t method_descriptions;

} interface_description_t;

typedef interface_description_t * p_interface_description_t;

// Static
extern 
    interface_description_reference_t 
        interface_description_register_static 
        (
            p_interface_description_t interface_description
        );
    
extern 
    void 
        interface_description_unregister_static 
        (
            interface_description_reference_t description_reference
        );

// Dynamic
extern 
    interface_description_reference_t 
        interface_description_register 
        (
            p_interface_description_t interface_description
        );

extern 
    void 
        interface_description_unregister 
        (
            interface_description_reference_t description_reference
        );

