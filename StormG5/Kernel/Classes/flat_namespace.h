
typedef struct
{
    HASH_ELEMENT_PART;
    
    wchar_t name[WSTRING_MAX_LENGTH];
    unsigned int type;
    
    reference_t reference;
} flat_name_t;

typedef flat_name_t * p_flat_name_t;

typedef struct
{
    hash_table_t *names_table;
} flat_namespace_t;    

typedef flat_namespace_t * p_flat_namespace_t;

extern flat_namespace_init (class_reference_t class_reference);
