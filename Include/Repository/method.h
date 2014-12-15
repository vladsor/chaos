
enum
{
    METHOD_NONE,
    METHOD_THIS,
    METHOD_INVOKER,
};

enum parameter_attribute_t
{
    PARAMETER_ATTRIBUTE_IN,
    PARAMETER_ATTRIBUTE_OUT,
    PARAMETER_ATTRIBUTE_INOUT,
};

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
    uint32_t attribute;
    uint32_t type;
    uint32_t size;
} parameter_description_t;

typedef parameter_description_t * p_parameter_description_t;

typedef struct
{
    method_id_t id;
    
    wchar_t name[WSTRING_MAX_LENGTH];

    parameter_description_t return_type;

    sequence_t parameter_descriptions;

    sequence_t exceptions;
} method_description_t;

typedef method_description_t * p_method_description_t;

typedef void (method_function_t) (void);
typedef method_function_t * p_method_function_t;

typedef struct
{
#if defined (REPOSITORY_EXTERNAL)
    HASH_ELEMENT_PART;

    method_id_t id;
#endif

#if defined (TRANSACTION_ENABLED)
    transaction_reference_t transaction;
    uint32_t transaction_slot_index;
#endif    

    uint32_t number_of_references;
    bool is_static;

    p_method_description_t description;

    p_method_function_t function;
} method_t;

typedef method_t * p_method_t;

extern method_reference_t method_create_static (p_method_t method);
extern void method_destroy_static (method_reference_t method_reference);

extern method_reference_t method_create (
    p_method_description_t method_description, 
    p_method_function_t method_function);
extern void method_destroy (method_reference_t method_reference);

extern void method_invoke (method_reference_t method, context_t context,
    sequence_t return_value, sequence_t parameters);

extern void method_invoke_static (method_reference_t method, 
    sequence_t return_value, sequence_t parameters);
    
