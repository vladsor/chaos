
enum
{
    CLASS_TYPE_STATIC,    
    CLASS_TYPE_DYNAMIC,
};

typedef struct
{
    class_id_t id;

    wchar_t name[WSTRING_MAX_LENGTH];

    uint32_t type;
    uint32_t number_of_interfaces;
} class_description_t;

typedef class_description_t * p_class_description_t;

#include <hash_table.h>

typedef struct
{
#if defined (REPOSITOTY_EXTERNAL)
    HASH_ELEMENT_PART;
    class_id_t id;
#endif

#if defined (TRANSACTION_ENABLED)
    transaction_reference_t transaction;
    uint32_t transaction_slot_index;
#endif    

    object_reference_t owner;

    uint32_t number_of_references;
    bool is_static;
    
    p_class_description_t description;
    sequence_t interfaces;
    
    object_reference_t repository;

    handle_reference_t object_control;
    handle_reference_t handle_control;
    handle_reference_t quality_control;
    handle_reference_t transaction_control;

} class_t;

typedef class_t * p_class_t;

extern class_reference_t class_create_static (p_class_t class);
extern void class_destroy_static (class_reference_t class_reference);

extern class_reference_t class_create (p_class_description_t class_description,
    sequence_t class_interfaces, object_reference_t class_repository);
extern void class_destroy (class_reference_t class_reference);
    
extern void class_set_interfaces (class_reference_t class_reference, 
    sequence_t class_interfaces);

extern sequence_t class_get_interfaces (class_reference_t class_reference);

extern interface_reference_t class_get_interface (
    class_reference_t class_reference, interface_id_t interface_id);

