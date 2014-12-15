#include <enviroment.h>

#include <list.h>

#include "../Include/thread.h"
#include "../Include/process.h"

#define DEBUG_MODULE_NAME "Thread"

//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE1
#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>


#define THREAD_STACK_SIZE PAGE_SIZE
#define THREAD_NEW_EFLAGS (CPU_FLAG_INTERRUPT_ENABLE | CPU_FLAG_ADJUST | \
                           CPU_FLAG_PARITY | CPU_FLAG_SET)
#define THREAD_NEW_PRIORITY 0

process_t process_kernel;
tss_t tss_kernel;

thread_t thread_main;

volatile thread_t *current_thread = &thread_main;
list_t running_threads = LIST_EMPTY;
list_t waiting_threads = LIST_EMPTY;
timer_t thread_timer;
spinlock_t threads_lock = SPIN_UNLOCKED;

thread_t *thread_get_current (void)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE2,
        "%s: %s Current thread: %p [%p, %p]\n",
        DEBUG_MODULE_NAME, __FUNCTION__, current_thread, 
        current_thread->previous, current_thread->next);
        
    return (thread_t *) current_thread;
}

return_t thread_lock (thread_t *thread)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s: %s (%p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__, thread);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
        "%s: %s (%p; %p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__, thread->previous, thread->next);

//    cpu_interrupts_disable ();
    spin_lock (&threads_lock);

    list_node_remove (&running_threads, (list_node_t *) thread);
    list_node_insert (&waiting_threads, (list_node_t *) thread, 
        LIST_OPTION_LAST);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
         "%s::%s Call thread_yield.\n",
        __FILE__, __FUNCTION__);
        
    if (thread == current_thread)
    {
        cpu_interrupts_disable ();
        spin_unlock (&threads_lock);

        thread_yield ();
        
        cpu_interrupts_enable ();
    }
    
//    cpu_interrupts_enable ();
    spin_unlock (&threads_lock);

    return 0;
}

return_t thread_unlock (thread_t *thread)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s: %s (%p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__, thread);

//    cpu_interrupts_disable ();
    spin_lock (&threads_lock);

    list_node_remove (&waiting_threads, (list_node_t *) thread);
    list_node_insert (&running_threads, (list_node_t *) thread, 
        LIST_OPTION_LAST);

    spin_unlock (&threads_lock);

//    cpu_interrupts_enable ();

    return 0;
}

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
    /* cs = */ SELECTOR_KERNEL_CODE,
    /* eflags = */ THREAD_NEW_EFLAGS

};

return_t thread_create (thread_t *thread, p_thread_function_t thread_function, 
    p_void_t parameter)
{
    return_t return_value;
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
         "%s::%s (%p, %p)\n",
        __FILE__, __FUNCTION__, thread, thread_function);

    memory_set_uint8 ((uint8_t *) thread, 0, sizeof (thread_t));
    thread->priority = THREAD_NEW_PRIORITY;
    thread->timeslices = 0;
    thread->process = &process_kernel;

    return_value = memory_allocate ((void **) &thread->stack, 
        THREAD_STACK_SIZE);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
         "%s::%s Stack: %p-%p\n",
        __FILE__, __FUNCTION__, 
        thread->stack, thread->stack + THREAD_STACK_SIZE - 1);
    
    thread->stack_pointer = thread->stack + THREAD_STACK_SIZE - 4 - 
        sizeof (p_void_t);
    ((uint32_t *) thread->stack_pointer)[0] = (uint32_t) &thread_exit_lowlevel;
    ((uint32_t *) thread->stack_pointer)[1] = (uint32_t) parameter;
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
         "%s::%s Done: %p.\n",
        __FILE__, __FUNCTION__, thread->next);

    return 0;
}

return_t thread_destroy (thread_t *thread)
{
    thread_lock (thread);
    return 0;
}

void thread_exit (int32_t exit_code)
{
    thread_t *thread;
    
    thread = thread_get_current ();
    thread_destroy (thread);
}

return_t thread_name_set (thread_t *thread, char *name)
{
    string_copy_max (thread->name, name, STRING_MAX_LENGTH);
    
    return 0;
}

return_t thread_name_get (thread_t *thread, char *name)
{
    string_copy_max (name, thread->name, STRING_MAX_LENGTH);
    
    return 0;
}

static int dispatch_flag = 0;
uint32_t jump_data[2] = {0, 0};
extern void thread_load_state (void);
extern void thread_load_state2 (void);
void thread_switch_to_next (void)
{
    static thread_t *next_thread = NULL;
    
    current_thread->timeslices++;
    
    if (threads_lock == SPIN_LOCKED)
    {
        return;
    }

    if (current_thread->next != NULL)
    {
        next_thread = (thread_t *) current_thread->next;
    }
    else
    {
        next_thread = (thread_t *) running_threads.first;
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
         "%s: %s Current thread: %p, Next thread: %p, Stack pointer: %p.\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        current_thread, next_thread, current_stack_pointer);

    if (next_thread != current_thread)
    {
        if (next_thread->process == current_thread->process)
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
                "%s: %s Jump to %p [%s].\n",
                DEBUG_MODULE_NAME, __FUNCTION__, 
                NULL, next_thread->name);

            current_thread->stack_pointer = current_stack_pointer;
            
            current_thread = next_thread;
            current_stack_pointer = current_thread->stack_pointer;
                pic_acknowledge (0);
            goto *(&thread_load_state2);
        }
        else
        {
            tss_t *current_tss;
            tss_t *next_tss;
            int pr_level;
            
            current_tss = current_thread->process->tss;
            next_tss = next_thread->process->tss;

            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
                "%s: %s Current tss: %p, Next tss: %p.\n",
                DEBUG_MODULE_NAME, __FUNCTION__, 
                current_tss, next_tss);

            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
                "%s: %s Next tss: cr3: %08X, cs: %04X, eax: %X.\n",
                DEBUG_MODULE_NAME, __FUNCTION__, 
                next_tss->cr3, next_tss->cs, next_tss->eax);
            
            dispatch_flag ^= 1;
            
            if (dispatch_flag == 0)
            {
                gdt_setup_tss_descriptor (DESCRIPTOR_INDEX_TSS1, next_tss, 
                    PRIVILEGE_LEVEL_SYSTEM, sizeof (tss_t));
//                jump_data[1] = SELECTOR_TSS1;

                DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
                    "%s: %s Jump to %p [%s].\n",
                    DEBUG_MODULE_NAME, __FUNCTION__, 
                    next_tss->eip, next_thread->name);
//            while (1);
                current_thread->stack_pointer = current_stack_pointer;

                current_thread = next_thread;
                next_tss->eip = &thread_load_state;
                next_tss->esp = next_thread->stack_pointer;
                
                pic_acknowledge (0);
                asm ("ljmp %0, $0x0": : "n" SELECTOR_TSS1);
//            asm ("ljmp *jump_data");
            }
            else
            {
                gdt_setup_tss_descriptor (DESCRIPTOR_INDEX_TSS2, next_tss, 
                    PRIVILEGE_LEVEL_SYSTEM, sizeof (tss_t));
//                jump_data[1] = SELECTOR_TSS2;

                DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
                    "%s: %s Jump to %p [%s].\n",
                    DEBUG_MODULE_NAME, __FUNCTION__, 
                    next_tss->eip, next_thread->name);
                current_thread->stack_pointer = current_stack_pointer;

                current_thread = next_thread;
                next_tss->eip = &thread_load_state;
                next_tss->esp = next_thread->stack_pointer;

                pic_acknowledge (0);
                asm ("ljmp %0, $0x0": : "n" SELECTOR_TSS2);
//            asm ("ljmp *jump_data");
            }
            
//            asm ("ljmp *jump_data");
        }
    }

    return;
}

void thread_print_list (void)
{
    iterator_t *i;
    thread_t *thread;

    spin_lock (&threads_lock);

//    cpu_interrupts_disable ();

    for (i = (iterator_t *) list_get_iterator (&running_threads); 
        iterator$has_next (i); )
    {
        thread = (thread_t *) iterator$get_next (i);
        
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
            "Running: [%s][%llu]\n",
            thread->name, thread->timeslices);
    }

    for (i = (iterator_t *) list_get_iterator (&waiting_threads); 
        iterator$has_next (i); )
    {
        thread = (thread_t *) iterator$get_next (i);
        
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
            "Waiting: [%s][%llu]\n",
            thread->name, thread->timeslices);
    }

    spin_unlock (&threads_lock);
//    cpu_interrupts_enable ();
}


static thread_t thr;
static char *thread_screen = (char *)(0xB8000);

static return_t thread_test (p_void_t par UNUSED)
{
    while (TRUE)
    {
        thread_screen[159]++;
    }
}
extern page_directory_t *global_page_directory;

return_t thread_init (int argc UNUSED, char *argv[] UNUSED, char **envp UNUSED)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
         "%s::%s (%i, %p)\n",
        __FILE__, __FUNCTION__, argc, argv);

    list_create (&running_threads);
    list_create (&waiting_threads);    

    memory_clear (&tss_kernel, sizeof (tss_t));
    tss_kernel.cr3 = global_page_directory;
    process_kernel.tss = &tss_kernel;
    gdt_setup_tss_descriptor (DESCRIPTOR_INDEX_TSS1, &tss_kernel, 
        PRIVILEGE_LEVEL_SYSTEM, sizeof (tss_t));

    thread_main.process = NULL;
    thread_main.stack = NULL;
    list_create (&thread_main.context_list);
    thread_main.process = &process_kernel;
    
    list_node_insert (&running_threads, (list_node_t *) &thread_main, 
        LIST_OPTION_FIRST);
    
    thread_name_set (&thread_main, "init");

    thread_create (&thr, &thread_test, NULL);
    thread_name_set (&thr, "test");
    thread_unlock (&thr);

    timer_create (&thread_timer, 1000 / hz, TIMER_PERIODIC,
        &thread_switch_to_next);

    timer_start (&thread_timer);

    return 0;
}
