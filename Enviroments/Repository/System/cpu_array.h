
typedef struct
{
    sequence_t cpus;
} cpu_array_t;

typedef cpu_array_t * p_cpu_array_t;

extern cpu_array_t global_cpu_array;
#define CPU_ARRAY_GLOBAL (&global_cpu_array)

extern void cpu_array_schedule (p_cpu_array_t cpu_array);


