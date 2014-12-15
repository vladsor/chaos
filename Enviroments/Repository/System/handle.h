

typedef struct
{
    reference_struct_t header;

    uint64_t data;
    
    p_object_t object;
    p_interface_t interface;
    
} handle_t;

typedef handle_t * p_handle_t;
typedef p_handle_t * p_p_handle_t;

// Static
extern handle_reference_t handle_create_static (p_handle_t handle, 
     sequence_t parameters, uint32_t options);
     
extern void handle_destroy_static (handle_reference_t handle_reference);

extern handle_reference_t handle_clone_static (
    handle_reference_t handle_refernce, p_handle_t new_handle_reference, 
    uint32_t options);


