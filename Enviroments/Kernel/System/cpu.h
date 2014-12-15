/* Author: Vladimir Sorokin. */

/* Copyright 2004 chaos development. */

#ifndef __STORM_CPU_H__
#define __STORM_CPU_H__

extern cpu_info_t cpu_info_global;

static inline void feature_set (
    cpu_info_t *current_cpu_info, unsigned int feature, bool value)
{
  current_cpu_info->features[feature] = value;
}

static inline bool feature_get (
    cpu_info_t *current_cpu_info, unsigned int feature)
{
    return current_cpu_info->features[feature];
}

extern return_t cpu_init (int argc, char *argv[], char **envp);
extern return_t cpu_halt (enum halt_t type);
extern return_t cpu_lock (void);
extern return_t cpu_unlock (void);
extern return_t cpu_get_info (cpu_info_t *cpu_info);										

#endif /* !__STORM_CPU_H__ */
