
#define INTERFACE_STORM_PROGRAM_CONTROL_ID (0x0012)

enum
{
    METHOD_STORM_PROGRAM_CONTROL_MAIN_ID,
    
    METHOD_STORM_PROGRAM_CONTROL_NUMBER
};

typedef return_t (storm_program_control_main_t) (context_t context, 
    uint32_t argc, char **argv, char **envp);
typedef storm_program_control_main_t * p_storm_program_control_main_t;
        
typedef struct
{
    p_storm_program_control_main_t main;

} storm_program_control_interface_table_t;

typedef storm_program_control_interface_table_t * 
    p_storm_program_control_interface_table_t;
    

static inline handle_reference_t storm_program_control$handle$create (
    object_reference_t object)
{
    sequence_t seq_empty = {data: NULL, count: 0};

    return handle_create (object, INTERFACE_STORM_PROGRAM_CONTROL_ID, 
        seq_empty, 0);
}    

static inline return_t storm_program_control$main (handle_reference_t handle, 
    uint32_t argc, char **argv, char **envp)
{
    uint32_t pars[3] = {(uint32_t) argc, (uint32_t) argv, (uint32_t) envp};
    sequence_t pars_in_seq = {data: pars, count: 3};
    
    sequence_t empty_seq = {data: NULL, count: 0};
    
    uint32_t ret = 0;
    sequence_t pars_out_seq = {data: &ret, count: 1};
    
    handle_invoke_method (handle, METHOD_STORM_PROGRAM_CONTROL_MAIN_ID, 
        REFERENCE_NULL, pars_in_seq, empty_seq, pars_out_seq, 0);

    return ret;
}


