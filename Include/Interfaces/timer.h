
#define INTERFACE_TIMER_ID 0x000A

enum
{
    METHOD_TIMER_READ_MILLI_ID,

    METHOD_TIMER_NUMBER
};

typedef uint32_t (timer_read_milli_t) (context_t context);
typedef timer_read_milli_t * p_timer_read_milli_t;
    
typedef struct
{
    p_timer_read_milli_t read_milli;
} timer_interface_table_t;

typedef timer_interface_table_t * p_timer_interface_table_t;

static inline handle_reference_t timer$handle$create (object_reference_t object)
{
    sequence_t seq_empty = {data: NULL, count: 0};

    return handle_create (object, INTERFACE_TIMER_ID, seq_empty, 0);
}    

static inline uint32_t timer$read_milli (handle_reference_t handle)
{
    sequence_t empty_seq = {data: NULL, count: 0};
    uint32_t ret = 0;
    sequence_t pars_out_seq = {data: &ret, count: 1};
    
    handle_invoke_method (handle, METHOD_TIMER_READ_MILLI_ID, REFERENCE_NULL,
        empty_seq, empty_seq, pars_out_seq, 0);
    
    return ret;
}

