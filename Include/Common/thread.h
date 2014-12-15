#ifndef __COMMON_THREAD_H__
#define __COMMON_THREAD_H__

#include <list.h>
#include "irq.h"
#include "process.h"

typedef struct
{
    uint16_t ss;
    uint16_t ds;
    uint16_t es;
    uint16_t fs;
    uint16_t gs;

    irq_cpu_registers_t irq_cpu_registers;

} cpu_state_t;

typedef struct
{
    LIST_NODE_PART;
    
    uint8_t name[STRING_MAX_LENGTH];
    uint32_t state;
    uint32_t priority;
    uint64_t timeslices;
    process_t *process;

    cpu_state_t cpu_state;
    uint8_t *stack;
    uint8_t *stack_pointer;

    uint8_t *user_stack;
    uint8_t *user_stack_pointer;
    
    list_t context_list;    

} thread_t;

typedef return_t (thread_function_t) (p_void_t parameter);
typedef thread_function_t * p_thread_function_t;

#endif /* !__COMMON_THREAD_H__ */

