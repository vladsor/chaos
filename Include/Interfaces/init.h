
#define INTERFACE_KERNEL_CONTROL_ID 0x0001

enum 
{
    METHOD_KERNEL_CONTROL_INIT_ID,
    METHOD_KERNEL_CONTROL_START_ID,
    METHOD_KERNEL_CONTROL_STOP_ID,

    METHOD_KERNEL_CONTROL_NUMBER
};

typedef void (kernel_control_init_t) (context_t context);
typedef kernel_control_init_t * p_kernel_control_init_t;

typedef void (kernel_control_start_t) (context_t context);
typedef kernel_control_start_t * p_kernel_control_start_t;

typedef void (kernel_control_stop_t) (context_t context);
typedef kernel_control_stop_t * p_kernel_control_stop_t;

typedef struct
{
    p_kernel_control_init_t init;
    p_kernel_control_start_t start;
    p_kernel_control_stop_t stop;

} kernel_control_interface_table_t;

typedef kernel_control_interface_table_t * p_kernel_control_interface_table_t;

static inline handle_reference_t kernel_control$handle$create (
    object_reference_t object)
{
    sequence_t empty_seq = {data: NULL, count: 0};

    return handle_create (object, INTERFACE_KERNEL_CONTROL_ID, empty_seq, 0);
}    

static inline void kernel_control$init (handle_reference_t handle)
{
    sequence_t empty_seq = {data: NULL, count: 0};

    handle_invoke_method (handle, METHOD_KERNEL_CONTROL_INIT_ID, REFERENCE_NULL,
        empty_seq, empty_seq, empty_seq, 0);
}

static inline void kernel_control$start (handle_reference_t handle)
{
    sequence_t empty_seq = {data: NULL, count: 0};

    handle_invoke_method (handle, METHOD_KERNEL_CONTROL_START_ID, REFERENCE_NULL,
        empty_seq, empty_seq, empty_seq, 0);
}

static inline void kernel_control$stop (handle_reference_t handle)
{
    sequence_t empty_seq = {data: NULL, count: 0};

    handle_invoke_method (handle, METHOD_KERNEL_CONTROL_STOP_ID, REFERENCE_NULL,
        empty_seq, empty_seq, empty_seq, 0);
}

