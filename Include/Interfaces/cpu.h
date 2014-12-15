#include "Common/cpu.h"

#define IID_CPU 0x00000101

enum
{
    MID_CPU_HALT,
    MID_CPU_LOCK,
    MID_CPU_UNLOCK,
    MID_CPU_GET_INFO,
};

typedef return_t (cpu_halt_function_t) (enum halt_t type);
typedef return_t (cpu_lock_function_t) (void);
typedef return_t (cpu_unlock_function_t) (void);
typedef return_t (cpu_get_info_function_t) (cpu_info_t *cpu_info);

typedef struct
{
    cpu_halt_function_t *halt;
    cpu_lock_function_t *lock;
    cpu_unlock_function_t *unlock;
    cpu_get_info_function_t *get_info;    
} cpu_interface_t;

#define cpu$halt(handle,type) \
    ((cpu_interface_t *) ((handle)->functions))->halt ( \
        (type))

#define cpu$lock(handle) \
    ((cpu_interface_t *) ((handle)->functions))->lock ()

#define cpu$unlock(handle) \
    ((cpu_interface_t *) ((handle)->functions))->unlock ()

#define cpu$get_info(handle,info) \
    ((cpu_interface_t *) ((handle)->functions))->get_info ( \
        (info))


