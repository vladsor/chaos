typedef uint32_t method_id_t;
typedef method_id_t * p_method_id_t;

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
    
    char name[STRING_MAX_LENGTH];

    parameter_description_t return_type;

    sequence_t parameter_descriptions;

    sequence_t exceptions;
} method_description_t;

typedef method_description_t * p_method_description_t;

typedef void (method_t) (void);

typedef method_t * p_method_t;

