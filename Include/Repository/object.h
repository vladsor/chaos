enum
{
    OBJECT_NONE,
    OBJECT_THIS,
    OBJECT_KERNEL,
    OBJECT_THIS_PROCESS,
    OBJECT_THIS_THREAD,
    OBJECT_THIS_REPOSITORY
};

#define HANDLE_NULL         {NULL, NULL}
#define HANDLE_THIS         {(uint32_t *) OBJECT_THIS, NULL}
#define HANDLE_KERNEL       {(uint32_t *) OBJECT_KERNEL, NULL}
#define HANDLE_THIS_PROCESS {(uint32_t *) OBJECT_THIS_PROCESS, NULL}
#define HANDLE_THIS_THREAD  {(uint32_t *) OBJECT_THIS_THREAD, NULL}

typedef struct
{
    p_void_t object_data;
    p_void_t handle_data;
    security_reference_t security_reference;
    object_reference_t invoker;
} context_t;

typedef context_t * p_context_t;

typedef struct
{
    HASH_ELEMENT_PART;

    object_id_t id;
    
    char name[STRING_MAX_LENGTH];

    p_void_t data;

    p_class_t class;
    uint32_t number_of_references;
    security_reference_t security;
    
    sequence_t joined_objects;
    
    sequence_t own_interfaces;
} object_t;

typedef object_t * p_object_t;

typedef struct
{
    HASH_ELEMENT_PART;

    handle_id_t id;
    
    char name[STRING_MAX_LENGTH];

    p_void_t data;
    p_object_t object;
    
    p_object_t current_object;

    p_interface_t current_interface;
} handle_t;

typedef handle_t * p_handle_t;

#if defined (__STORM_KERNEL__) || defined (__STORM_KERNEL_MODULE__)
typedef p_handle_t handle_reference_t;
#elif defined (__STORM_PROGRAM__)
typedef handle_id_t handle_reference_t;
#else
#error "Unknown target of object file"
#endif

typedef handle_reference_t * p_handle_reference_t;

extern object_reference_t object_reference_current;

extern void object_create (p_object_reference_t object_reference,
    class_reference_t class_reference, 
    sequence_t own_interfaces, sequence_t joined_objects, 
    sequence_t parameters, uint32_t options)

extern void object_destroy (object_reference_t object_reference);

extern class_reference_t object_get_class (
    object_reference_t object_reference);
    
extern interface_reference_t object_get_interface (
    object_reference_t object_reference, interface_id_t interface_id);

extern security_reference_t object_get_security (
    object_reference_t object_reference);

extern void object_set_security (security_reference_t security_reference);

/*    
void object_add_joined_objects (handle_t handle, 
    uint32_t number_of_joined, handle_t joined_objects[])
void object_add_interfaces (handle_t handle, 
    uint32_t number_of_interfaces, interface_t interfaces[])
*/
void handle_open (p_handle_reference_t handle_reference, 
    object_reference_t object_reference, interface_id_t interface_id,
    sequence_t parameters, uint32_t options)

void handle_close (handle_reference_t handle_reference)

void handle_clone (p_handle_reference_t handle_reference,
    handle_reference_t handle_reference, uint32_t options);

extern void object_invoke_method (handle_t handle, interface_id_t interface_id, 
    method_id_t method_id, sequence_t parameters);


