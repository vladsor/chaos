enum parameter_attribute_t
{
    PARAMETER_ATTRIBUTE_IN,
    PARAMETER_ATTRIBUTE_OUT,
    PARAMETER_ATTRIBUTE_INOUT,
};

enum data_type_t
{
    DATA_TYPE_SHORT_INT,
    DATA_TYPE_LONG_INT,
    DATA_TYPE_LONG_LONG_INT,

    DATA_TYPE_SHORT_UINT,
    DATA_TYPE_LONG_UINT,
    DATA_TYPE_LONG_LONG_UINT,
    
    DATA_TYPE_CHAR,
    DATA_TYPE_WCHAR,
    
    DATA_TYPE_BOOLEAN,
    DATA_TYPE_OCTET,
    
    DATA_TYPE_FLOAT,
    DATA_TYPE_DOUBLE,

    DATA_TYPE_SEQUENCE,
    DATA_TYPE_STRING,
    DATA_TYPE_STRUCT,
    
    DATA_TYPE_ANY,
    DATA_TYPE_OBJECT,
    DATA_TYPE_INTERFACE,
};

typedef struct
{
    uint32_t max_count;
    uint32_t element_size;
} type_sequence_info_t;    

typedef struct
{
    uint32_t attribute;
    uint32_t type;
    uint32_t size;
} parameter_description_t;

typedef parameter_description_t * p_parameter_description_t;
