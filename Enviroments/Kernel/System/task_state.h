
typedef struct
{
    tss_t tss;

/*
    fpu_state_t fpu_state;
    
    uint32_t real_eip;
    uint32_t real_cs;
    uint32_t real_eflags;
*/    
} task_state_t;

typedef task_state_t * p_task_state_t;

extern task_state_t task_state_kernel;

typedef struct
{
    /**
     * @brief           The current (or next) instruction. 
     */
    uint32_t eip;

    /**
     * @brief           The code segment selector.
     */
    uint32_t cs;

    /* @brief           EFLAGS get pushed first. 
     */
    uint32_t eflags;
    
} iret_data_t;

typedef iret_data_t * p_iret_data_t;

#define TASK_STATE_INIT_FLAGS (0)
#define TASK_STATE_NEW_EFLAGS \
                        (CPU_FLAG_INTERRUPT_ENABLE | CPU_FLAG_ADJUST | \
                        CPU_FLAG_PARITY | CPU_FLAG_SET)

extern void task_state_create (p_task_state_t task_state, 
    p_virtual_memory_t virtual_memory, p_function_t instruction_pointer,
    p_uint8_t stack_pointer, p_uint8_t user_stack);

extern void task_state_destroy (p_task_state_t task_state);
    
extern void task_state_switch_prepare (p_task_state_t task_state);
extern void task_state_switch_finish (void);
extern void task_state_switch_finish2 (void);
extern void task_state_switch_finish_internal (irq_cpu_registers_t reg);

extern return_t task_state_init (int argc, char *argv[], char **envp);

