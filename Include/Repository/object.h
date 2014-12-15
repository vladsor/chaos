
enum
{
    OBJECT_NONE,
    OBJECT_THIS,
    OBJECT_INVOKER,
    OBJECT_KERNEL,
    OBJECT_THIS_PROCESS,
    OBJECT_THIS_THREAD,
    OBJECT_THIS_REPOSITORY
};

#include <hash_table.h>

typedef struct
{
#if defined (REPOSITORY_EXTERNAL)
    HASH_ELEMENT_PART;

    object_id_t id;
#endif

#if defined (TRANSACTION_ENABLED)
    transaction_reference_t transaction;
    uint32_t transaction_slot_index;
#endif    

    uint32_t number_of_references;
    bool is_static;

    p_void_t data;

    class_reference_t class;

    sequence_t own_interfaces;

    sequence_t joined_objects;

    security_reference_t security;
    
} object_t;

typedef object_t * p_object_t;

extern object_reference_t object_create_static (p_object_t object);
extern void object_destroy_static (object_reference_t object_reference);

extern object_reference_t object_create (class_reference_t class_reference, 
    sequence_t own_interfaces, sequence_t joined_objects, 
    security_reference_t security_reference, sequence_t parameters, 
    uint32_t options);

extern void object_destroy (object_reference_t object_reference);

extern class_reference_t object_get_class (
    object_reference_t object_reference);
    
extern interface_reference_t object_get_interface (
    object_reference_t object_reference, interface_id_t interface_id);

extern security_reference_t object_get_security (
    object_reference_t object_reference);

extern void object_set_security (object_reference_t object_reference,
    security_reference_t security_reference);

extern object_reference_t object_reference object_get_current (void);
/*
object_get_quality (object, interface_id, method_id);
*/

/*    
void object_add_joined_objects (handle_t handle, 
    uint32_t number_of_joined, handle_t joined_objects[])
void object_add_interfaces (handle_t handle, 
    uint32_t number_of_interfaces, interface_t interfaces[])
*/

