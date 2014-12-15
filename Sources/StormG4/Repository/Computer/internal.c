#include <enviroment.h>

#define DEBUG_MODULE_NAME "Repository"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include "../Include/internal.h"
#include "Include/scheduler.h"

#include <debug/macros.h>
#include <exception/macros.h>

volatile list_t computers;

void computer_start (p_computer_t computer)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p), %X,%X,%X,%X\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        computer, 
        ((p_uint32_t) computer->task_state->tss.esp)[0], 
        ((p_uint32_t) computer->task_state->tss.esp)[1],
        ((p_uint32_t) computer->task_state->tss.esp)[2],
        ((p_uint32_t) computer->task_state->tss.esp)[3]);

    computer->state = COMPUTER_STATE_RUNNING;
    
    list_node_insert ((list_t *) &computers, (list_node_t *) &computer->node, 
        LIST_OPTION_LAST);
}

void computer_stop (p_computer_t computer)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        computer);

    computer->state = COMPUTER_STATE_STOPPED;
    
    list_node_remove ((list_t *) &computers, (list_node_t *) &computer->node);
}

void computer_schedule_prepare (void)
{
    p_computer_t next;

    next = scheduler_get_next_computer ();    

    DEBUG_ASSERT (next != NULL, "Next not null.");

    if (next != computer_current)
    {        
        task_state_switch_prepare (next->task_state);
        irq_set_post_handler (IRQ_CHANNEL_TIMER, 
            (p_function_t) &task_state_switch_finish);
        computer_current = next;
    }    
}

static inline void iret_call (p_function_t function)
{
    asm volatile
    (
        "pushl %0\n"
        "pushl %1\n"
        "call *%2\n"
        :
        :
            "i" (0),
            "i" (SELECTOR_KERNEL_CODE),
            "r" (function)
    );
}    

void computer_invoke_internal (p_computer_t computer,
    p_handle_t handle, p_object_t object, p_class_t class, 
    p_interface_t interface, p_method_t method, context_t context,
    reference_t reference_base, reference_t reference_new,
    sequence_t parameters_in, sequence_t parameters_inout,
    sequence_t parameters_out)
{
    p_function_t function;
    uint32_t type;
    uint64_t data;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1, 
        "%s: %s (%p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        computer);

    if (computer == NULL)
    {
        computer = computer_current;
    }    

    if (computer != computer_current)
    {
        computer_reset (computer);
    }    

    computer->invoke_stack[computer->invoke_top].handle = handle;
    computer->invoke_stack[computer->invoke_top].object = object;
    computer->invoke_stack[computer->invoke_top].class = class;
    computer->invoke_stack[computer->invoke_top].interface = interface;
    computer->invoke_stack[computer->invoke_top].method = method;

    computer->invoke_stack[computer->invoke_top].parameters_in = parameters_in;
    computer->invoke_stack[computer->invoke_top].parameters_inout = 
        parameters_inout;
    computer->invoke_stack[computer->invoke_top].parameters_out = parameters_out;

    computer->invoke_top++;
    
    if (computer == computer_current)
    {
        function = method_get_function_internal (method);
        type = method_get_type_internal (method);
        data = method_get_data_internal (method);

        computer_call_function (function, type, data, context, reference_base, 
            reference_new, parameters_in, parameters_inout, parameters_out);

        computer->invoke_top--;
    }    
    else
    {
        p_computer_t next;
        
        cpu_interrupts_disable ();
        
        computer_current->nested = computer;
        computer_current->nested_is_sync = TRUE;

        computer->upper = computer_current;
        computer->upper_is_sync = TRUE;

        computer_start (computer);
        computer_stop (computer_current);

        next = scheduler_get_next_computer ();
    
        DEBUG_ASSERT (next != NULL, "Next not null.");
        DEBUG_ASSERT (next != computer_current, "Next not current.");
        
        task_state_switch_prepare (next->task_state);
        computer_current = next;
//        task_state_switch_finish ();
        iret_call (&task_state_switch_finish);

        computer_current->nested = NULL;
        computer_current->nested_is_sync = FALSE;

        cpu_interrupts_enable ();
    }    
}    

void computer_invoke_async_internal (p_computer_t computer,
    p_handle_t handle, p_object_t object, p_class_t class, 
    p_interface_t interface, p_method_t method,
    reference_t reference_base UNUSED, reference_t reference_new UNUSED,
    sequence_t parameters_in, sequence_t parameters_inout)
{
    sequence_t empty_seq = {data: NULL, count: 0};
    p_computer_t next;
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        computer);

    if (computer == NULL)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
            "%s: %s: Not valid computer: %p\n",
            DEBUG_MODULE_NAME, __FUNCTION__,
            computer);
            
        return;
    }
    
    if (computer == computer_current)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
            "%s: %s: Not valid computer: %p, %u\n",
            DEBUG_MODULE_NAME, __FUNCTION__,
            computer, computer->state);
            
        return;
    }

    if (computer->state != COMPUTER_STATE_STOPPED)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
            "%s: %s: Not valid computer state: %p, %u\n",
            DEBUG_MODULE_NAME, __FUNCTION__,
            computer, computer->state);
            
        return;
    }

    computer_reset (computer);
    computer->invoke_stack[computer->invoke_top].handle = handle;
    computer->invoke_stack[computer->invoke_top].object = object;
    computer->invoke_stack[computer->invoke_top].class = class;
    computer->invoke_stack[computer->invoke_top].interface = interface;
    computer->invoke_stack[computer->invoke_top].method = method;
    
    computer->invoke_stack[computer->invoke_top].parameters_in = parameters_in;
    computer->invoke_stack[computer->invoke_top].parameters_inout = 
        parameters_inout;
    computer->invoke_stack[computer->invoke_top].parameters_out = empty_seq;

    computer->invoke_top++;

    cpu_interrupts_disable ();

    computer_start (computer);

    next = scheduler_get_next_computer ();
    
    if (computer_current != next)
    {
        task_state_switch_prepare (next->task_state);
        computer_current = next;
//        task_state_switch_finish ();
        iret_call (&task_state_switch_finish);
    }    
    
    cpu_interrupts_enable ();
}    

void computer_begin (void)
{
    p_computer_t next;
    
    p_method_t method;
    p_function_t function;
    uint32_t type;
    uint64_t data;
    context_t context = {0,0};

    reference_t reference_base = REFERENCE_NULL;
    reference_t reference_new = REFERENCE_NULL;
    sequence_t parameters_in;
    sequence_t parameters_inout;
    sequence_t parameters_out;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        computer_current);

    DEBUG_ASSERT (computer_current->invoke_top != 0, "Invoke stack not empty.");
/*
    {
        uint32_t eflags;
        
        cpu_flags_save (eflags);
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
            "%s: %s: Current eflags: %X\n",
            DEBUG_MODULE_NAME, __FUNCTION__,
            eflags);
    }
*/
    method = METHOD_CURRENT;
    //computer_current->invoke_stack[computer_current->invoke_top - 1].method;
    function = method_get_function_internal (method);
    type = method_get_type_internal (method);
    data = method_get_data_internal (method);

    if (OBJECT_CURRENT != REFERENCE_NULL)
    {
        context.object_data = object_get_data_internal (OBJECT_CURRENT);
    }
    
    if (HANDLE_CURRENT != REFERENCE_NULL)
    {
        context.handle_data = handle_get_data_internal (HANDLE_CURRENT);
    }    

    parameters_in = computer_current->invoke_stack[
        computer_current->invoke_top - 1].parameters_in;

    parameters_inout = computer_current->invoke_stack[
        computer_current->invoke_top - 1].parameters_inout;

    parameters_out = computer_current->invoke_stack[
        computer_current->invoke_top - 1].parameters_out;

//    ((p_function_event_consumer_handler_t) function) (
//        data, context, parameters_in);
    computer_call_function (function, type, data, context, reference_base, 
        reference_new, parameters_in, parameters_inout, parameters_out);
        
    computer_current->invoke_top--;

    cpu_interrupts_disable ();

    computer_stop (computer_current);
    
    if (computer_current->upper_is_sync)
    {
        computer_start ((p_computer_t) computer_current->upper);
    }
    
//    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
//        "%s: %s: Computer stopped: %p\n",
//        DEBUG_MODULE_NAME, __FUNCTION__,
//        computer_current);

    next = scheduler_get_next_computer ();

    DEBUG_ASSERT (next != NULL, "Next not null.");
    DEBUG_ASSERT (next != computer_current, "Next not current.");
        
    task_state_switch_prepare (next->task_state);
    computer_current = next;
    task_state_switch_finish ();
}

void computer_return (void)
{
    p_computer_t next;
    
    computer_current->invoke_top--;

    cpu_interrupts_disable ();
    computer_stop (computer_current);
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s: Computer stopped: %p\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        computer_current);

    if (computer_current->upper_is_sync)
    {
        p_computer_t upper = (p_computer_t) computer_current->upper;
        computer_current->upper_is_sync = FALSE;
        computer_current->upper = NULL;
        
        computer_start (upper);
        upper->nested_is_sync = FALSE;
        upper->nested = NULL;
    }

    next = scheduler_get_next_computer ();

    DEBUG_ASSERT (next != NULL, "Next not null.");
    DEBUG_ASSERT (next != computer_current, "Next not current.");
        
    task_state_switch_prepare (next->task_state);
    computer_current = next;
    task_state_switch_finish ();
}

extern void iret_to_func (p_function_t, uint32_t, /*uint32_t,*/ uint8_t *, uint32_t);

void computer_call_function (p_function_t function, uint32_t type, 
    uint64_t data, context_t context,
    reference_t reference_base, reference_t reference_new,
    sequence_t parameters_in, sequence_t parameters_inout,
    sequence_t parameters_out)
{
    if (computer_current->memory->virtual_memory->level == LEVEL_USER)
    {
        p_uint8_t user_stack = computer_current->user_stack_physical + PAGE_SIZE;
        uint32_t offset = PAGE_SIZE/* - (sizeof (parameters_out) + sizeof (parameters_inout) +
            sizeof (parameters_in) + sizeof (context) + sizeof (data) +
            sizeof (uint32_t) * 1)*/;

        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
            "%s: %s (%p, %p, %p)\n",
            DEBUG_MODULE_NAME, __FUNCTION__,
            function,
            computer_current->user_stack_physical,
            computer_current->user_stack_virtual);
/*
        user_stack -= sizeof (parameters_out);
        memory_copy (user_stack, &parameters_out, sizeof (parameters_out));
        
        user_stack -= sizeof (parameters_inout);
        memory_copy (user_stack, &parameters_inout, sizeof (parameters_inout));

        user_stack -= sizeof (parameters_in);
        memory_copy (user_stack, &parameters_in, sizeof (parameters_in));

        user_stack -= sizeof (context);
        memory_copy (user_stack, &context, sizeof (context));

        user_stack -= sizeof (data);
        memory_copy (user_stack, &data, sizeof (data));

        user_stack -= sizeof (uint32_t);
        ((p_uint32_t) user_stack)[0] = 0;
*/
/*
        user_stack -= sizeof (uint32_t);
        ((p_uint32_t) user_stack)[0] = SELECTOR_PROCESS_DATA;
        
        user_stack -= sizeof (uint32_t);
        ((p_uint32_t) user_stack)[0] = (uint32_t) computer_current->user_stack_virtual + offset;
*/
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
            "%s: %s (%p, %x, %p)\n",
            DEBUG_MODULE_NAME, __FUNCTION__,
            user_stack,
            offset,
            computer_current->user_stack_virtual + offset);

//        computer_current->user_stack_physical = user_stack;
/*
    asm volatile 
    (
    "pushl %3\n"
    "pushl %2\n"
    "pushl %1\n"
    "pushl %0\n"
    "xorl %%edi, %%edi\n"
    "xorl %%esi, %%esi\n"
    "xorl %%ebp, %%ebp\n"
    "xorl %%ebx, %%ebx\n"
    "xorl %%edx, %%edx\n"
    "xorl %%ecx, %%ecx\n"
    "xorl %%eax, %%eax\n"
//    "int $3\n"
    "lret\n"
    :
    :
        "g" (function), 
        "g" (SELECTOR_PROCESS_CODE),
        "g" (computer_current->user_stack_virtual + offset), 
        "g" (SELECTOR_PROCESS_DATA)
    );
*/
        iret_to_func (function, SELECTOR_PROCESS_CODE,
            computer_current->user_stack_virtual + offset, 
            SELECTOR_PROCESS_DATA);
        return;
    }

    switch (type)
    {
        case METHOD_TYPE_DYNAMIC:
        {
            ((p_function_dynamic_t) function) (data, context, 
                parameters_in, parameters_inout, parameters_out);
            
            break;
        }

        case METHOD_TYPE_STATIC:
        {
            ((p_function_static_t) function) (data, 
                parameters_in, parameters_inout, parameters_out);
            
            break;
        }
        
        case METHOD_TYPE_OBJECT_CREATE:
        {
            ((p_function_object_create_t) function) (data, context, 
                reference_base, reference_new, parameters_in);
            
            break;
        }
            
        case METHOD_TYPE_OBJECT_DESTROY:
        {
            ((p_function_object_destroy_t) function) (data, context, 
                reference_base, reference_new);
            
            break;
        }    

        case METHOD_TYPE_EVENT_SUPPLIER_CREATE:
        {
            ((p_function_event_supplier_create_t) function) (data, 
                context, reference_base, reference_new, parameters_in);
            
            break;
        }
            
        case METHOD_TYPE_EVENT_SUPPLIER_DESTROY:
        {
            ((p_function_event_supplier_destroy_t) function) (data, 
                context, reference_base, reference_new);
            
            break;
        }
        
        case METHOD_TYPE_EVENT_SUPPLIER_HANDLER:
        {
            bool fired;
            
            fired = ((p_function_event_supplier_handler_t) function) (
                data, context, parameters_out);
        }    

        case METHOD_TYPE_EVENT_CONSUMER_HANDLER:
        {
            ((p_function_event_consumer_handler_t) function) (data, 
                context, parameters_in);
        }    
    }    
}

