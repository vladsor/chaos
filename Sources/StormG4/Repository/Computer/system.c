#include <enviroment.h>
#include <list.h>

#define DEBUG_MODULE_NAME "Repository"

//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE 
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE1 
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include "../Include/internal.h"

#include <debug/macros.h>

#ifndef GDB
static bool lock = TRUE;
#endif

computer_t computer_kernel =
{
    cpu: CPU_KERNEL,
    memory: MEMORY_GLOBAL,
    
    task_state: &task_state_kernel,

    stack: kernel_stack,  
    user_stack_virtual: NULL,
    user_stack_physical: NULL,
    
    security: SECURITY_ABSOLUTE,
    
    state: COMPUTER_STATE_RUNNING,
    
    node:
    {
        node: LIST_NODE_INIT,
        computer: &computer_kernel,
    },
    
    invoke_stack:
    {
      { NULL, NULL, NULL, NULL, NULL, {NULL,0}, {NULL,0}, {NULL,0} },
    },
    
    invoke_top: 0,

    exception_context_stack: LIST_INIT,
    exception_top: 0,
    
    upper: NULL,
    nested: NULL,
    
    upper_is_sync: FALSE,
    nested_is_sync: FALSE,
};

volatile p_computer_t computer_current = &computer_kernel;

computer_reference_t computer_create (
    cpu_reference_t cpu,
    memory_reference_t memory_reference,
    security_reference_t security)
{
    return_t return_value;
    
    p_computer_t computer;
    p_memory_t memory = (p_memory_t) memory_reference;
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p, %p, %p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        cpu, memory, security);
    
    memory_allocate ((void **) &computer, sizeof (computer_t));
    computer->node.computer = computer;    
    
    computer->cpu = cpu;
    computer->memory = memory;
    computer->security = security;
    
    computer->invoke_top = 0;
    
    computer->state = COMPUTER_STATE_STOPPED;
    
    memory_allocate ((void **) &computer->stack, PAGE_SIZE);

//    memory_allocate ((void **) &computer->user_stack, PAGE_SIZE);
    if (memory->virtual_memory->level == LEVEL_USER)
    {
        page_number_t vp, pp;
        
        return_value = virtual_memory_allocate (memory->virtual_memory, &vp, 1, &pp, 0);
        computer->user_stack_virtual = (p_uint8_t) PAGE_ADDRESS (vp);
        computer->user_stack_physical = (p_uint8_t) PAGE_ADDRESS (pp);
    }    
      
    memory_allocate ((void **) &computer->task_state, sizeof (task_state_t));

    task_state_create (computer->task_state, computer->memory->virtual_memory, 
        &computer_begin, computer->stack + PAGE_SIZE, 
        computer->stack + PAGE_SIZE);

    list_create (&computer->exception_context_stack);
    
    return (computer_reference_t) computer;
}    
    
void computer_destroy (computer_reference_t computer_reference)
{
    p_computer_t computer;
    
    computer = (p_computer_t) computer_reference;
    
    memory_deallocate (computer);
}    

void computer_reset (computer_reference_t computer_reference)
{
    p_computer_t computer;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        computer_reference);
    
    computer = (p_computer_t) computer_reference;
    
    computer->invoke_top = 0;
    task_state_create (computer->task_state, computer->memory->virtual_memory, 
        &computer_begin, computer->stack + PAGE_SIZE, 
        computer->stack + PAGE_SIZE); 
}    

computer_reference_t computer_get_current (void)
{
	return COMPUTER_CURRENT;
}

void computer_add_exception_context (
    computer_reference_t computer_reference, p_exception_context_t context)
{
    p_computer_t computer = computer_reference;
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p, %p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        computer_reference, context);

    context->catch_stack_pointer = (p_uint8_t) ((p_uint32_t) &computer_reference);
    context->catch_point = (p_void_t) ((p_uint32_t) &computer_reference - 1)[0];
    context->is_raised = FALSE;
    context->invoke_stack_pointer = computer->invoke_top;
    cpu_flags_save (context->eflags);
/*
    asm  \
    ( \
        "movl %%edi, %0\n" \
        "movl %%esi, %1\n" \
        "movl %%ebp, %2\n" \
        "movl %%ebx, %3\n" \
        "movl %%edx, %4\n" \
        "movl %%ecx, %5\n" \
        "movl %%eax, %6\n" \
            :   "=m" (__context__.edi), \
                "=m" (__context__.esi), \
                "=m" (__context__.ebp), \
                "=m" (__context__.ebx), \
                "=m" (__context__.edx), \
                "=m" (__context__.ecx), \
                "=m" (__context__.eax) \
    ); \
*/
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1, 
        "%s: IP: %p, SP: %p, ISP: %u, PS: %X\n",
        DEBUG_MODULE_NAME, 
        (void *) context->catch_point,
        (void *) context->catch_stack_pointer,
        context->invoke_stack_pointer,
        context->eflags);
    
    list_node_insert (&computer->exception_context_stack, 
        (list_node_t *) context, LIST_OPTION_LAST);
        
    return;
}    

p_exception_context_t computer_remove_exception_context (
    computer_reference_t computer_reference)
{
    p_exception_context_t context;
    p_computer_t computer = computer_reference;
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        computer_reference);

    context = (p_exception_context_t) computer->exception_context_stack.last;
    list_node_remove_last (&computer->exception_context_stack);
        
    return context;
}    

typedef struct
{
    exception_hardware_page_info_t    header;

    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
    uint32_t esp;
    uint32_t ss;
} exception_hardware_page_user_info_t;


extern void jump_lowlevel (void *, uint32_t, uint32_t, void *, uint32_t, uint32_t, uint32_t,
    uint32_t, uint32_t, uint32_t, uint32_t);

void computer_fire_exception (computer_reference_t computer_reference UNUSED, 
    p_exception_info_t exception_info)
{
    p_computer_t computer = computer_reference;
    p_exception_context_t context = NULL;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p, %p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        computer_reference, exception_info);

//    context = (p_exception_context_t) computer->exception_context_stack.last;
    context = computer_remove_exception_context (computer_reference);
    
    if (context == NULL)
    {
        const char *name_type;
        
        switch (exception_info->type)
        {
            case EXCEPTION_TYPE_HARDWARE: name_type = "hardware"; break;
            case EXCEPTION_TYPE_SYSTEM: name_type = "system"; break;
            case EXCEPTION_TYPE_USER: name_type = "user"; break;
            default: name_type = "unknown";
        }
        
        DEBUG_PRINT (DEBUG_LEVEL_ERROR,
            "Uncatched %s exception %u in %p at %p\n", 
            (char *) name_type, exception_info->id, computer, 
            (void *) exception_info->pc);
    
        if (exception_info->type == EXCEPTION_TYPE_HARDWARE)
        {
            int index = exception_info->id;
            exception_hardware_page_user_info_t *info = 
                (exception_hardware_page_user_info_t *) exception_info;

            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
                "%s: cs: %x, eip: %p, eflags: %x, ss: %x, esp: %p\n",
                DEBUG_MODULE_NAME,
                info->cs, (p_void_t) info->eip, info->eflags, 
                info->ss, (p_void_t) info->esp);
            
            exception_print_screen (
                exception_hardware_descriptions[index].class_id,
                exception_hardware_descriptions[index].description, 
                exception_hardware_descriptions[index].reason,
                exception_hardware_descriptions[index].error_code_type, 
                (exception_hardware_info_t *) exception_info);
                
        }
    }

    else
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
            "Catched exception %u in %p at %p\n", 
            exception_info->id, computer, 
            (void *) exception_info->pc);
//        memory_copy (context->info, exception_info,
//            sizeof (exception_info_t));

        context->is_raised = TRUE;
        
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1, 
            "%s: Jumps to: %p (%p)(%u)\n",
            DEBUG_MODULE_NAME,
            (void *) context->catch_point,
            (void *) context->catch_stack_pointer,
            context->invoke_stack_pointer);

        computer->invoke_top = context->invoke_stack_pointer;
        
        jump_lowlevel (
            (void *) context->catch_stack_pointer, 
            context->eflags,
            computer->memory->virtual_memory->code_selector,
            (void *) context->catch_point, 
            context->edi,
            context->esi,
            context->ebp,
            context->ebx,
            context->edx,
            context->ecx,
            context->eax);
    }

#ifndef GDB
    while (lock);
#else
    (* (p_uint32_t) NULL) = 1;
#endif
}

static void exc_handler (p_void_t, exception_hardware_info_t) NORETURN;

static void exc_handler (p_void_t data UNUSED,
    exception_hardware_info_t exception_info)
{
    computer_fire_exception (computer_current, 
        (p_exception_info_t) &exception_info);

    while (1);    
}


void repository_computer_init (void) 
{
    int index;

    for (index = 0; index < NUMBER_OF_EXCEPTIONS; index++)
    {
        exception_register (index, &exc_handler, NULL);
    }    

    list_create (&computer_kernel.exception_context_stack);
    
    list_create ((list_t *) &computers);
    
//    computer_kernel.node.computer = &computer_kernel;
    list_node_insert ((list_t *) &computers, (list_node_t *) &computer_kernel.node, 
        LIST_OPTION_LAST);
//    computer_start (&computer_kernel);

    timer_register_handler (TIMER_NUMBER_SYSTEM, 
        (p_timer_handler_t) &computer_schedule_prepare, NULL);
}

