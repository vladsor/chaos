enum
{
    METHOD_OBJECT_FACTORY_CREATE_ID,
    METHOD_OBJECT_FACTORY_DESTROY_ID,
    METHOD_OBJECT_FACTORY_CLONE_ID,
    
    METHOD_OBJECT_FACTORY_NUMBER,
};    

typedef uint64_t (object_factory_create_t) (context_t context);
typedef object_factory_create_t * p_object_factory_create_t;
        
typedef void (object_factory_destroy_t) (context_t context, 
    uint64_t object_data);
typedef object_factory_destroy_t * p_object_factory_destroy_t;

typedef uint64_t (object_factory_clone_t) (context_t context, 
    uint64_t object_data);
typedef object_factory_clone_t * p_object_factory_clone_t;

typedef struct
{
    p_object_factory_create_t create;
    p_object_factory_destroy_t destroy;
    p_object_factory_clone_t clone;
} object_factory_interface_table_t;   

static inline void object$create (object_reference_t object)
{
    object_destroy (object);
}

static inline object_reference_t object$clone (object_reference_t object)
{
    return object_clone (object, 0);
}

 
