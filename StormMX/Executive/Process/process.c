#include <enviroment.h>

#include <list.h>

#include "../Include/process.h"
#include "../Include/elf.h"
#include "../../Init/Include/multiboot.h"

#define DEBUG_MODULE_NAME "Process"

#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

extern process_t process_kernel;

list_t processes = LIST_EMPTY;

spinlock_t processes_lock = SPIN_UNLOCKED;

volatile process_t *current_process = NULL;

process_t * process_get_current (void)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
         "%s: %s Current process: %p [%p, %p]\n",
        DEBUG_MODULE_NAME, __FUNCTION__, current_process, 
        current_process->previous, current_process->next);
        
    return (process_t *) current_process;
}

#define THREAD_STACK_SIZE PAGE_SIZE
#define THREAD_NEW_EFLAGS (CPU_FLAG_INTERRUPT_ENABLE | CPU_FLAG_ADJUST | \
                           CPU_FLAG_PARITY | CPU_FLAG_SET)

extern list_t running_threads;
extern list_t waiting_threads;
extern spinlock_t threads_lock;


static irq_cpu_registers_t default_state =
{
    /* edi = */ 0,
    /* esi = */ 0,
    /* ebp = */ 0,
    /* esp = */ 0,
    /* ebx = */ 0,
    /* edx = */ 0,
    /* ecx = */ 0,
    /* eax = */ 0,

    /* eip = */ (uint32_t) NULL,
    /* cs = */ SELECTOR_PROCESS_CODE,
    /* eflags = */ THREAD_NEW_EFLAGS

};

void dump_stack (uint32_t ss, uint32_t *esp)
{
    uint32_t cs;
    cpu_cs_save (cs);
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE2,
         "cs: %X, esp: %X:%p, %X %X %X %X %X %X %X %X %X %X %X %X %X\n",
        cs, ss, esp, esp[0], esp[1], esp[2], esp[3], esp[4], esp[5], esp[6], esp[7], esp[8], esp[9], esp[10], esp[11], esp[12]);
}

return_t process_thread_create (process_t *process,
    thread_t *thread, p_thread_function_t thread_function, p_void_t parameter)
{
    return_t return_value;
    page_number_t ph_page;
    page_number_t vt_page;
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
         "%s: %s (%p, %p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__, thread, thread_function);

    memory_set_uint8 ((uint8_t *) thread, 0, sizeof (thread_t));
    thread->priority = 0;
    thread->timeslices = 0;
    thread->process = process;

    return_value = memory_allocate ((void **) &thread->stack, 
        THREAD_STACK_SIZE);
    physical_memory_allocate (&ph_page, 1);
    virtual_memory_allocate (process, &vt_page, 1);
    virtual_memory_map (process->page_directory, vt_page, ph_page, 1, PAGE_USER);

    thread->user_stack = PAGE_ADDRESS (vt_page);
    thread->user_stack_pointer = thread->user_stack + THREAD_STACK_SIZE - 8;
    {
        uint32_t *tmp = PAGE_ADDRESS (ph_page) + THREAD_STACK_SIZE - 8;
        tmp[0] = thread->user_stack_pointer;
        tmp[1] = SELECTOR_PROCESS_DATA;
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
         "%s: %s Kernel stack: %p-%p.\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        thread->stack, thread->stack + THREAD_STACK_SIZE - 1);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
         "%s: %s User stack: %p-%p\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        thread->user_stack, thread->user_stack + THREAD_STACK_SIZE - 1);
    
    thread->stack_pointer = thread->stack + THREAD_STACK_SIZE - 8;

    ((uint32_t *) thread->stack_pointer)[0] = thread->user_stack_pointer;
    ((uint32_t *) thread->stack_pointer)[1] = SELECTOR_PROCESS_DATA;
//    memory_copy (thread->stack_pointer + 4, &data, sizeof (sequence_t));
//    thread->stack_pointer--;
    
    default_state.esp = (uint32_t) thread->stack_pointer - 12;
    default_state.eip = (uint32_t) thread_function;
    thread->stack_pointer -= sizeof (default_state);

    memory_copy (thread->stack_pointer, &default_state, sizeof (default_state));

    //cpu_interrupts_disable ();
    spin_lock (&threads_lock);
            
//    list_node_insert (&running_threads, (list_node_t *) thread, 
//        LIST_OPTION_LAST);
    list_node_insert (&waiting_threads, (list_node_t *) thread, 
        LIST_OPTION_LAST);

    spin_unlock (&threads_lock);
    //cpu_interrupts_enable ();

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE2,
         "%s: %s return.\n",
        DEBUG_MODULE_NAME, __FUNCTION__);

    return 0;
}

static tss_t test_tss;
static thread_t test_thread;
extern void process_load_state (void);
elf_parsed_program_t parsed;

return_t process_create (process_t *process, void *address)
{
    return_t return_value;
    thread_t *thread = &test_thread;
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
         "%s: %s (%p, %p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__, process, address);

    memory_set_uint8 ((uint8_t *) process, 0, sizeof (process_t));
    
    memory_set_uint8 ((uint8_t *) &parsed, 0, sizeof (parsed));
    virtual_memory_create (process);
    elf_parse_program ((elf_header_t *) address, &parsed);
    elf_load_program (&parsed, process);

    process_thread_create (process, thread, process->entry_point, NULL);
    string_copy (thread->name, "Process main test thread");
    tss_create (&test_tss, process->page_directory, NULL, 
        thread->stack_pointer);

    process->tss = &test_tss;

    thread_unlock (thread);
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE2,
         "%s::%s Done [%p].\n",
        DEBUG_MODULE_NAME, __FUNCTION__, process->entry_point);

    return 0;
}

return_t process_name_set (process_t *process, char *name)
{
    string_copy_max (process->name, name, STRING_MAX_LENGTH);
    
    return 0;
}

return_t process_name_get (process_t *process, char *name)
{
    string_copy_max (name, process->name, STRING_MAX_LENGTH);
    
    return 0;
}

void process_print_list (void)
{
    iterator_t *i;
    process_t *process;

    spin_lock (&processes_lock);

    for (i = (iterator_t *) list_get_iterator (&processes); 
        iterator$has_next (i); )
    {
        process = (process_t *) iterator$get_next (i);
        
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
            "Process: [%s][%u]\n",
            process->name, process->threads_list.number_of_nodes);
    }

    spin_unlock (&processes_lock);
}
static process_t process_test;
return_t process_init (int argc UNUSED, char *argv[] UNUSED)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
         "%s: %s (%i, %p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__, argc, argv);

    list_create (&processes);

    process_kernel.page_directory = global_page_directory;
    list_create (&process_kernel.threads_list);
    process_name_set (&process_kernel, "kernel");

    current_process = &process_kernel;

    list_node_insert (&processes, (list_node_t *) &process_kernel, 
        LIST_OPTION_FIRST);
/*
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
         "%s: %s Image: %p - %p\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        (void *) multiboot_module_info[0].start, 
        (void *) multiboot_module_info[0].end);

    process_create (&process_test, multiboot_module_info[0].start);
*/
    return 0;
}
