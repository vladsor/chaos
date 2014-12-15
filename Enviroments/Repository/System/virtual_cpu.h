
typedef struct
{
    LIST_NODE_PART;

    p_cpu_t cpu;
//    cpu_state_t state;
    
    uint32_t policy;
    resource_usage_t usage;
    
    uint64_t first_tick;
    uint64_t last_tick;
    /*
    handle_current;
    object_current;
    class_current;
    interface_current;
    method_current;
    */
} virtual_cpu_t;

typedef virtual_cpu_t * p_virtual_cpu_t;
typedef p_virtual_cpu_t * p_p_virtual_cpu_t;

#define VIRTUAL_CPU_CURRENT ((virtual_cpu_reference_t) NULL)

extern virtual_cpu_reference_t virtual_cpu_create (uint32_t cpu_policy, 
    resource_usage_t cpu_usage);

extern void virtual_cpu_destroy (virtual_cpu_reference_t virtual_cpu);
/*
calculate_next_ticks ();
*/

extern void virtual_cpu_sleep_milli (virtual_cpu_reference_t virtual_cpu, 
    uint32_t milliseconds);

extern void virtual_cpu_sleep_micro (virtual_cpu_reference_t virtual_cpu, 
    uint32_t microseconds);

extern uint32_t virtual_cpu_time_read_milli (
    virtual_cpu_reference_t virtual_cpu);

