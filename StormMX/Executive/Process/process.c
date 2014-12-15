#include <enviroment.h>
#include <memory_inlines.h>
#include <list.h>

#include "../Include/process.h"
#include "../Include/spinlock.h"

#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>


process_t process_kernel;

list_t processes = LIST_EMPTY;

spinlock_t processes_lock = SPIN_UNLOCKED;

/*
thread_t *thread_get_current (void)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
         "%s::%s Current thread: %p [%p, %p]\n",
        __FILE__, __FUNCTION__, current_thread, 
        current_thread->previous, current_thread->next);
        
    return (thread_t *) current_thread;
}
*/

/*
return_t thread_create (thread_t *thread, thread_function_t *thread_function)
{
    return_t return_value;
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
         "%s::%s (%p, %p)\n",
        __FILE__, __FUNCTION__, thread, thread_function);

    memory_set_uint8 ((uint8_t *) thread, 0, sizeof (thread_t));
    thread->priority = THREAD_NEW_PRIORITY;
    thread->timeslices = 0;

    return_value = memory_allocate ((void **) &thread->stack, 
        THREAD_STACK_SIZE);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
         "%s::%s Stack: %p-%p\n",
        __FILE__, __FUNCTION__, 
        thread->stack, thread->stack + THREAD_STACK_SIZE - 1);
    
    thread->stack_pointer =thread->stack + THREAD_STACK_SIZE;
    
    default_state.esp = (uint32_t) thread->stack_pointer - 12;
    default_state.eip = (uint32_t) thread_function;
    thread->stack_pointer -= sizeof (default_state);

    memory_copy (thread->stack_pointer, &default_state, sizeof (default_state));

    spin_lock (&threads_lock);
            
    list_node_insert (&running_threads, (list_node_t *) thread, 
        LIST_OPTION_LAST);

    spin_unlock (&threads_lock);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
         "%s::%s Done: %p.\n",
        __FILE__, __FUNCTION__, thread->next);

    return 0;
}
*/
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

return_t process_init (int argc UNUSED, char *argv[] UNUSED)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
         "%s::%s (%i, %p)\n",
        __FILE__, __FUNCTION__, argc, argv);

    list_create (&processes);

    process_kernel.page_directory = global_page_directory;
    
    list_create (&process_kernel.threads_list);
    process_name_set (&process_kernel, "kernel");
    
    list_node_insert (&processes, (list_node_t *) &process_kernel, 
        LIST_OPTION_FIRST);

    return 0;
}
