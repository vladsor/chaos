#include <enviroment.h>

#include "Include/exception.h"

#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#include <debug/macros.h>

void exception_add_handler (thread_t *thread, 
    p_exception_context_t exception_context)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s::%s (%p, %p)\n",
        __FILE__, __FUNCTION__, thread, exception_context);
        
    list_node_insert (&thread->context_list, 
        (list_node_t *) exception_context, LIST_OPTION_LAST);
}

void exception_remove_handler (thread_t *thread)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s::%s (%p)\n",
        __FILE__, __FUNCTION__, thread);

    list_node_remove_last (&thread->context_list);
}

static uint32_t jump_data;
static uint32_t stack_data;
static void cpu_load_state (cpu_state_t *cpu_state)
{
    jump_data = cpu_state->irq_cpu_registers.eip;
    stack_data = cpu_state->irq_cpu_registers.esp;
    asm (
      "movl %1, %%esp; movl %0, %%eax; jmp *%%eax\n"
      :
      : "m" (jump_data),
        "m" (stack_data));
}

void exception_invoke_handler (thread_t *thread, 
    p_exception_info_t exception_info)
{
    p_exception_context_t context = NULL;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s::%s (%p, %p)\n",
        __FILE__, __FUNCTION__, thread, exception_info);

    context = (p_exception_context_t) thread->context_list.last;
    
    if (exception_info->type == EXCEPTION_TYPE_HARDWARE)
    {
        int index = exception_info->id;

        DEBUG_PRINT (DEBUG_LEVEL_ERROR,
            "Hardware exception %u in %s[%p] at %p\n", 
            exception_info->id, thread->name, thread, 
            (void *) exception_info->pc);
        
        exception_print_screen (exception_hardware_descriptions[index].class_id,
            exception_hardware_descriptions[index].description, 
            exception_hardware_descriptions[index].reason,
            exception_hardware_descriptions[index].error_code_type, 
            (exception_hardware_info_t *) exception_info, thread);
        
        while (TRUE);
    }
    
    if (context == NULL)
    {
        char *name_type;
        
        switch (exception_info->type)
        {
            case EXCEPTION_TYPE_HARDWARE: name_type = "hardware"; break;
            case EXCEPTION_TYPE_SYSTEM: name_type = "system"; break;
            case EXCEPTION_TYPE_USER: name_type = "user"; break;
            default: name_type = "unknown";
        }
        
        DEBUG_PRINT (DEBUG_LEVEL_ERROR,
            "Uncatched %s exception %u in %s[%p] at %p\n", 
            name_type, exception_info->id, thread->name, thread, 
            (void *) exception_info->pc);
    
        thread_lock (thread);  
    }
    else
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR,
            "Catched exception %u in %s[%p] at %p\n", 
            /*name_type,*/ exception_info->id, thread->name, thread, 
            (void *) exception_info->pc);
//        memory_copy (context->info, exception_info,
//            sizeof (exception_info_t));

        context->raised = TRUE;
        exception_remove_handler (thread);
        
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
            "%s::%s Jumps to: %p (%p)\n",
            __FILE__, __FUNCTION__, 
            (void *) context->state.irq_cpu_registers.eip,
            (void *) context->state.irq_cpu_registers.esp);

        cpu_load_state (&context->state);
    }
    
    while (TRUE);
}

return_t exception_software_init (int argc UNUSED, char *argv[] UNUSED) 
{
    return 0;
}

