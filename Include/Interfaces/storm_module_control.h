
#define INTERFACE_STORM_MODULE_CONTROL_ID (0x0011)

enum
{
    METHOD_STORM_MODULE_CONTROL_START_ID,
    METHOD_STORM_MODULE_CONTROL_STOP_ID,
    
    METHOD_STORM_MODULE_CONTROL_NUMBER
};

typedef return_t (storm_module_control_start_t) (context_t context, 
    uint32_t argc, char **argv, char **envp);
typedef storm_module_control_start_t * p_storm_module_control_start_t;
        
typedef return_t (storm_module_control_stop_t) (context_t context);
typedef storm_module_control_stop_t * p_storm_module_control_stop_t;

typedef struct
{
    p_storm_module_control_start_t start;
    p_storm_module_control_stop_t stop;

} storm_module_control_interface_table_t;

typedef storm_module_control_interface_table_t * 
    p_storm_module_control_interface_table_t;
    

static inline handle_reference_t storm_module_control$handle$create (
    object_reference_t object)
{
    sequence_t seq_empty = {data: NULL, count: 0};

    return handle_create (object, INTERFACE_STORM_MODULE_CONTROL_ID, 
        seq_empty, 0);
}    

static inline return_t storm_module_control$start (handle_reference_t handle, 
    uint32_t argc, char **argv, char **envp)
{
    uint32_t pars[3] = {(uint32_t) argc, (uint32_t) argv, (uint32_t) envp};
    sequence_t pars_in_seq = {data: pars, count: 3};
    
    sequence_t empty_seq = {data: NULL, count: 0};
    
    uint32_t ret = 0;
    sequence_t pars_out_seq = {data: &ret, count: 1};
    
    handle_invoke_method (handle, METHOD_STORM_MODULE_CONTROL_START_ID, 
        REFERENCE_NULL, pars_in_seq, empty_seq, pars_out_seq, 0);

    return ret;
}

static inline return_t storm_module_control$stop (handle_reference_t handle)
{
    sequence_t empty_seq = {data: NULL, count: 0};

    uint32_t ret = 0;
    sequence_t pars_out_seq = {data: &ret, count: 1};
    
    handle_invoke_method (handle, METHOD_STORM_MODULE_CONTROL_STOP_ID, 
        REFERENCE_NULL, empty_seq, empty_seq, pars_out_seq, 0);

    return ret;
}

