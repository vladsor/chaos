
enum
{
    INTERFACE_TYPE_DYNAMIC,
    INTERFACE_TYPE_STATIC,
};

typedef struct
{
    interface_id_t id;
    wchar_t name[WSTRING_MAX_LENGTH];
    uint32_t interface_type;
    sequence_t method_descriptions;
    
    uint32_t number_of_references;
} interface_description_t;

typedef interface_description_t * p_interface_description_t;

#include <hash_table.h>

typedef struct
{
#if defined (REPOSITOTY_EXTERNAL)
    HASH_ELEMENT_PART;
    interface_id_t id;
#endif

#if defined (TRANSACTION_ENABLED)
    transaction_reference_t transaction;
    uint32_t transaction_slot_index;
#endif    

    object_reference_t owner;

    uint32_t number_of_references;
    bool is_static;

    p_interface_description_t description; 
    sequence_t methods;

} interface_t;

typedef interface_t * p_interface_t;

extern interface_reference_t interface_create_static (p_interface_t interface);
extern void interface_destroy_static (
    interface_reference_t interface_reference);

extern interface_reference_t interface_create (
    p_interface_description_t interface_description, 
    sequence_t interface_methods);

extern void interface_destroy (interface_reference_t interface_reference);

/*
extern void interface_invoke_static_method (
    interface_reference_t interface_reference, 
    method_id_t method_id, sequence_t parameters, sequence_t return_value);

extern void interface_invoke_dynamic_method (
    interface_reference_t interface_reference,
    handle_reference_t handle_reference,
    method_id_t method_id, sequence_t parameters, sequence_t return_value);
*/
