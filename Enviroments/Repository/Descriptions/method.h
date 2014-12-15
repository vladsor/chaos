
enum method_type_t
{
    METHOD_TYPE_DYNAMIC,
    METHOD_TYPE_STATIC,
    
    METHOD_TYPE_DYNAMIC_ONEWAY,
    METHOD_TYPE_STATIC_ONEWAY,

    METHOD_TYPE_OBJECT_CREATE,
    METHOD_TYPE_OBJECT_DESTROY,
    
    METHOD_TYPE_HANDLE_CREATE,
    METHOD_TYPE_HANDLE_DESTROY,
    
    METHOD_TYPE_EVENT_SUPPLIER_CREATE,
    METHOD_TYPE_EVENT_SUPPLIER_DESTROY,
    
    METHOD_TYPE_EVENT_CONSUMER_CREATE,
    METHOD_TYPE_EVENT_CONSUMER_DESTROY,

    METHOD_TYPE_EVENT_SUPPLIER_HANDLER,

    METHOD_TYPE_EVENT_CONSUMER_HANDLER,    
};

typedef id_t method_id_t;
typedef method_id_t * p_method_id_t;

typedef struct
{
    description_reference_struct_t header;
    
    wchar_t name[WSTRING_MAX_LENGTH];

    uint32_t type;

    p_void_t return_type;

    sequence_t parameter_descriptions;

    sequence_t exception_descriptions;
    
} method_description_t;

typedef method_description_t * p_method_description_t;

// Static
extern 
    description_reference_t 
        method_description_register_static 
        (
            p_method_description_t method_description
        );
    
extern 
    void 
        method_description_unregister_static 
        (
            description_reference_t description_reference
        );

// Dynamic
extern 
    description_reference_t 
        method_description_register 
        (
            id_t id,
            const wchar_t *name,
            uint32_t type,
            p_void_t return_type,
            sequence_t parameter_descriptions,
            sequence_t exception_descriptions
        );

extern 
    void 
        method_description_unregister 
        (
            description_reference_t description_reference
        );


