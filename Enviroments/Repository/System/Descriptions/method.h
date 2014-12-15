enum method_type_t
{
    METHOD_TYPE_DYNAMIC,
    METHOD_TYPE_STATIC,
    
    METHOD_TYPE_DYNAMIC_ONEWAY,
    METHOD_TYPE_STATIC_ONEWAY,
};

typedef struct
{
    description_reference_struct_t header;
    
    wchar_t name[WSTRING_MAX_LENGTH];

    p_data_description_t return_type;

    sequence_t parameter_descriptions;

    sequence_t exception_descriptions;
    
} method_description_t;

typedef method_description_t * p_method_description_t;

// Static
extern 
    method_description_reference_t 
        method_description_register_static 
        (
            p_method_description_t method_description
        );
    
extern 
    void 
        method_description_unregister_static 
        (
            method_description_reference_t description_reference
        );

// Dynamic
extern 
    method_description_reference_t 
        method_description_register 
        (
            p_method_description_t method_description
        );

extern 
    void 
        method_description_unregister 
        (
            method_description_reference_t description_reference
        );

