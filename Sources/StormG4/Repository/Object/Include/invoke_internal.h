
#ifndef REPOSITORY_OBJECT_INVOKE_INTERNAL_H
#define REPOSITORY_OBJECT_INVOKE_INTERNAL_H

static inline void object_invoke_method_internal (p_object_t object, 
    p_handle_t handle, p_interface_t interface, method_id_t method_id, 
    p_computer_t computer, uint64_t handle_data,
    reference_t reference_base, reference_t reference_new, 
    sequence_t parameters_in, sequence_t parameters_inout, 
    sequence_t parameters_out)
{
    context_t context;
/*
#if defined (COMPUTER_INVOKE_HISTORY_ENABLED)
    computer_current->invoke_stack[computer_current->invoke_top].object = object;
#else
    p_object_t current;
    p_object_t current_invoker;

    current = OBJECT_CURRENT;
    current_invoker = OBJECT_CURRENT_INVOKER;

    OBJECT_CURRENT_INVOKER = current;
    OBJECT_CURRENT = object;
#endif
*/
    context.handle_data = handle_data;   
    context.object_data = object->data;
    
    class_invoke_method_internal (object->class, handle, object, interface, 
        method_id, computer, context, reference_base, reference_new, 
        parameters_in, parameters_inout, parameters_out);
/*
#if defined (COMPUTER_INVOKE_HISTORY_ENABLED)
#else
    OBJECT_CURRENT = current;
    OBJECT_CURRENT_INVOKER = current_invoker;
#endif
*/
}

#endif /* !REPOSITORY_OBJECT_INVOKE_INTERNAL_H */

