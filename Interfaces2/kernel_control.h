
#define INTERFACE_KERNEL_CONTROL_ID 0x0001

enum 
{
    METHOD_KERNEL_CONTROL_INIT_ID,
    METHOD_KERNEL_CONTROL_START_ID,
    METHOD_KERNEL_CONTROL_STOP_ID,

    METHOD_KERNEL_CONTROL_NUMBER
};

typedef void (kernel_control_invoker_init) (role_reference_t role)
typedef void (kernel_control_invoker_start) (role_reference_t role)
typedef void (kernel_control_invoker_stop) (role_reference_t role)

typedef void (kernel_control_init_invoked_t) (context_t context);
typedef void (kernel_control_start_invoked_t) (context_t context);
typedef void (kernel_control_stop_invoked_t) (context_t context);

typedef kernel_control_init_invoked_t * p_kernel_control_init_invoked_t;
typedef kernel_control_start_invoked_t * p_kernel_control_start_invoked_t;
typedef kernel_control_stop_invoked_t * p_kernel_control_stop_invoked_t;

typedef struct
{
    p_kernel_control_init_invoked_t init;
    p_kernel_control_start_invoked_t start;
    p_kernel_control_stop_invoked_t stop;

} kernel_control_invoked_interface_table_t;

typedef kernel_control_interface_table_t * p_kernel_control_interface_table_t;


static inline 
    role_reference_t 
        kernel_control$invoker$create 
        (
            object_reference_t object
        )
{
    scene_reference_t scene;
    role_reference_t role_master;
    role_reference_t role_slave;
    
    scene = scene_create (SCENE_TYPE_SYNC_INVOKE);
    role_master = role_create (scene, OBJECT_CURRENT, 
        INTERFACE_KERNEL_CONTROL_ID, ROLE_TYPE_INVOKER, DATA_NULL, 0);
    role_slave = role_create (scene, object, 
        INTERFACE_KERNEL_CONTROL_ID, ROLE_TYPE_INVOKED, DATA_NULL, 0);
    
    return role_master;
}    

static inline 
    void 
        kernel_control$invoker$destroy 
        (
            role_reference_t role
        )
{
    scene_reference_t scene;
    
    scene = role_get_scene (role);
    scene_destroy (scene);
}

static inline void kernel_control$init (role_reference_t role)
{
    role_play (role, METHOD_KERNEL_CONTROL_INIT_ID, 0);
}

static inline void kernel_control$start (role_reference_t role)
{
    role_play (role, METHOD_KERNEL_CONTROL_START_ID, 0);
}

static inline void kernel_control$stop (role_reference_t role)
{
    role_play (role, METHOD_KERNEL_CONTROL_STOP_ID, 0);
}

