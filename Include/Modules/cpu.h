extern handle_t handle_cpu;

static inline return_t cpu_halt (enum halt_t type)
{
    return cpu$halt (&handle_cpu, type);
}

static inline return_t cpu_lock (void)
{
    return cpu$lock (&handle_cpu);
}

static inline return_t cpu_unlock (void)
{
    return cpu$unlock (&handle_cpu);
}

static inline return_t cpu_get_info (cpu_info_t *cpu_info)
{
    return cpu$get_info (&handle_cpu, cpu_info);
}
