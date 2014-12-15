

typedef struct
{
    p_void_t object_data;
    p_void_t handle_data;
    p_void_t security_data;
} context_t;

typedef context_t * p_context_t;

typedef struct
{
#if defined (REPOSITOTY_EXTERNAL)
    HASH_ELEMENT_PART;
    handle_id_t id;
#endif
    
    bool is_static;

    p_void_t data;
    
    object_reference_t object;
    interface_reference_t interface;
} handle_t;

typedef handle_t * p_handle_t;

extern handle_reference_t handle_create_static (p_handle_t handle);
extern void handle_destroy_static (handle_reference_t handle);
extern void handle_clone_static (handle_reference_t handle, 
    handle_reference_t new_handle, uint32_t options);

extern handle_reference_t handle_create (object_reference_t object, 
    interface_id_t interface_id, sequence_t parameters, uint32_t options);

extern void handle_destroy (handle_reference_t handle);

extern handle_reference_t handle_clone (handle_reference_t handle, 
    uint32_t options);

extern void handle_invoke (handle_t handle, method_id_t method_id, 
    sequence_t return_value, sequence_t parameters);

