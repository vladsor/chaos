
typedef struct
{
    uint32_t performance;
    resource_usage_t usage;
    
    list_t virtuals;
    
//    cpu_reference_t current_virtual;
} cpu_t;

typedef cpu_t * p_cpu_t;
typedef p_cpu_t * p_p_cpu_t;

#if defined (__STORM_KERNEL__)

extern cpu_t cpu_kernel;
#define CPU_KERNEL ((cpu_reference_t) &cpu_kernel)

#endif

extern cpu_reference_t cpu_create (uint32_t performance);
extern void cpu_destroy  (cpu_reference_t cpu_reference);

extern cpu_reference_t cpu_get_current (void);

extern void cpu_schedule (p_cpu_t cpu);
/*
cpu_save_state ()

cpu_load_state ()
*/
//extern virtual_cpu_reference_t cpu_get_least_virtual (p_cpu_t cpu);

extern void cpu_sleep_milli (cpu_reference_t cpu, uint32_t milli);

