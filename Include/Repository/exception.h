
#include <hash_table.h>

typedef struct
{
    exception_id_t id;

    wchar_t name[WSTRING_MAX_LENGTH];

    uint32_t length;

    uint32_t number_of_references;

} exception_description_t;

typedef exception_description_t * p_exception_description_t;

typedef struct
{
#if defined (REPOSITORY_EXTERNAL)
    HASH_ELEMENT_PART;
    exception_id_t id;
#endif

#if defined (TRANSACTION_ENABLED)
    transaction_reference_t transaction;
    uint32_t transaction_slot_index;
#endif    
//    char name[STRING_MAX_LENGTH];
    
    object_reference_t owner;
    uint32_t number_of_references;

    p_exception_description_t description; 

} exception_t;

typedef exception_t * p_exception_t;


extern exception_reference_t exception_create_static (p_exception_t exception);
extern void exception_destroy_static_internal (exception_reference_t exception);

extern exception_reference_t exception_create (
    p_exception_description_t exception_description);

extern void exception_destroy (exception_reference_t exception);

