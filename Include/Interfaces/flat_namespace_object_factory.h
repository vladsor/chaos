
#define INTERFACE_FLAT_NAMESPACE_OBJECT_FACTORY_ID 0x0006

typedef uint64_t (flat_namespace_object_factory_create_t) (context_t context);
typedef flat_namespace_object_factory_create_t *
    p_flat_namespace_object_factory_create_t;
        
typedef struct
{
    p_flat_namespace_object_factory_create_t create;
        
    p_object_factory_destroy_t destroy;

} flat_namespace_object_factory_interface_table_t;

typedef flat_namespace_object_factory_interface_table_t * 
    p_flat_namespace_object_factory_interface_table_t;

static inline handle_reference_t flat_namespace_object_factory$handle$create (
    object_reference_t object)
{
    sequence_t seq_empty = {NULL, 0};

    return handle_create (object, INTERFACE_FLAT_NAMESPACE_OBJECT_FACTORY_ID, 
        seq_empty, 0);
}    

static inline object_reference_t flat_namespace$create (
    class_reference_t class)
{
    sequence_t seq_empty = {NULL, 0};
    
    return object_create (class, SECURITY_CURRENT, seq_empty, 0);
}


