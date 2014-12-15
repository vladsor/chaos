#include <hash_table.h>

typedef void * description_reference_t;

enum description_reference_type_t
{
    DESCRIPTION_REFERENCE_TYPE_DATA,
    DESCRIPTION_REFERENCE_TYPE_EXCEPTION,
    DESCRIPTION_REFERENCE_TYPE_METHOD,
    DESCRIPTION_REFERENCE_TYPE_INTERFACE,
    DESCRIPTION_REFERENCE_TYPE_CLASS,
};

typedef struct
{
    HASH_ELEMENT_PART;
    id_t id;
    
    uint32_t magic_number;

    uint32_t number_of_references;
    bool is_static;

} description_reference_struct_t;

typedef description_reference_struct_t * p_description_reference_struct_t;

