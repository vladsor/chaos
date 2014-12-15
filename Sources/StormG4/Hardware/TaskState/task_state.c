#include <enviroment.h>

#include "Include/tss.h"
#include "Include/task_state.h"

#define DEBUG_MODULE_NAME "TaskState"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include <debug/macros.h>

task_state_t task_state_kernel =
{
    tss: {
    previous_task_link: 0,
    u0: 0,
    esp0: 0,
    ss0: 0,
    u1: 0,
    esp1: 0,
    ss1: 0,
    u2: 0,
    esp2: 0,
    ss2: 0,
    u3: 0,
    cr3: 0,
    eip: 0,
    eflags: 0,
    eax: 0,
    ecx: 0,
    edx: 0,
    ebx: 0,
    esp: 0,
    ebp: 0,
    esi: 0,
    edi: 0,
    es: 0,
    u4: 0,
    cs: 0,
    u5: 0,
    ss: 0,
    u6: 0,
    ds: 0,
    u7: 0,
    fs: 0,
    u8: 0,
    gs: 0,
    u9: 0,
    ldt_selector: 0,
    u10: 0,
    t: 0,
    u11: 0,
    iomap_base: 0,
    iomap_size: 0,
    iomap: {},
    },
#ifdef FPU_ENABLED
    fpu_initialised: TRUE,
    fpu_state: FPU_STATE_INIT,
#endif
};

void task_state_create (p_task_state_t task_state, 
    p_virtual_memory_t virtual_memory, p_function_t instruction_pointer,
    p_uint8_t stack_pointer, p_uint8_t user_stack_pointer)
{
    p_iret_data_t iret;

    stack_pointer -= sizeof (iret_data_t);

    iret = (p_iret_data_t) stack_pointer;

    iret->eip = (uint32_t) instruction_pointer;
    iret->cs = SELECTOR_KERNEL_CODE;//virtual_memory->code_selector;
    iret->eflags = TASK_STATE_NEW_EFLAGS;

    tss_create (&task_state->tss, virtual_memory->page_directory,
        SELECTOR_KERNEL_CODE, /*SELECTOR_KERNEL_DATA, */
        virtual_memory->data_selector,
        (uint32_t) &task_state_switch_finish2, (uint32_t) stack_pointer, 
        (uint32_t) user_stack_pointer, 
        TASK_STATE_INIT_FLAGS);
}    

void task_state_destroy (p_task_state_t task_state UNUSED)
{
}
    
void task_state_switch_prepare (p_task_state_t task_state)
{
    tss_switch_prepare (&task_state->tss);
}

void task_state_switch_finish_internal (irq_cpu_registers_t reg UNUSED)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
         "%s: eip: %p, esp: %p, eflags: %X\n",
        DEBUG_MODULE_NAME, 
        (p_void_t) reg.eip, (p_void_t) reg.esp, reg.eflags);
}    

return_t task_state_init (int argc UNUSED, char *argv[] UNUSED, 
    char **envp UNUSED)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
         "%s: %s (%u, %p, %p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
	argc, argv, envp);

    task_state_kernel.tss.cr3 = 
        (uint32_t) virtual_memory_global.page_directory;
    
    gdt_setup_tss_descriptor (DESCRIPTOR_INDEX_TSS1, &task_state_kernel.tss,
        sizeof (tss_t), PRIVILEGE_LEVEL_KERNEL);

    cpu_tr_load (SELECTOR_TSS1);

    return STORM_RETURN_SUCCESS;
}

