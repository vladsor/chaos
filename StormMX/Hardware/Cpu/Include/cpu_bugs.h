extern void cpu_bugs_search (cpu_info_t *cpu_info);

static inline void bug_set (
    cpu_info_t *cpu_info, unsigned int bug, bool value)
{
    cpu_info->bugs[bug] = value;
}

static inline bool bug_get (
    cpu_info_t *cpu_info, unsigned int bug)
{
    return cpu_info->bugs[bug];
}
