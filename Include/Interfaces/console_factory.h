
#define INTERFACE_CONSOLE_FACTORY_ID 0x0020

typedef uint64_t (console_factory_create_t) (context_t context,
    uint32_t console_width, uint32_t console_height, uint32_t console_depth, 
    uint32_t console_mode_type);
    
typedef console_factory_create_t * p_console_factory_create_t;
        
typedef struct
{
    p_console_factory_create_t  create;    
    p_object_factory_destroy_t  destroy;
    p_object_factory_clone_t    clone;

} console_factory_interface_table_t;

typedef console_factory_interface_table_t * 
    p_console_factory_interface_table_t;

static inline handle_reference_t console_factory$handle$create (
    object_reference_t object)
{
    sequence_t seq_empty = {NULL, 0};

    return handle_create (object, INTERFACE_CONSOLE_FACTORY_ID, seq_empty, 0);
}    

static inline void console_factory$handle$destroy (
    handle_reference_t handle)
{
    handle_destroy (handle);
}

static inline object_reference_t console$object$create (
    class_reference_t class, 
    uint32_t console_width, uint32_t console_height, uint32_t console_depth, 
    uint32_t console_mode_type)
{
	uint32_t pars[] = {console_width, console_height, console_depth, 
        console_mode_type};
    sequence_t pars_seq = {data: pars, count: 4};
    
    return object_create (class, SECURITY_CURRENT, pars_seq, 0);
}


