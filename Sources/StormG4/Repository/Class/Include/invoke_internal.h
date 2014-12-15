
#ifndef REPOSITORY_CLASS_INVOKE_INTERNAL_H
#define REPOSITORY_CLASS_INVOKE_INTERNAL_H

static inline void class_invoke_method_internal (p_class_t class, 
    p_handle_t handle, p_object_t object, p_interface_t interface, 
    method_id_t method_id, p_computer_t computer, context_t context,
    reference_t reference_base, reference_t reference_new, 
    sequence_t parameters_in, sequence_t parameters_inout, 
    sequence_t parameters_out)
{
/*    
#if defined (COMPUTER_INVOKE_HISTORY_ENABLED)
    computer_current->invoke_stack[computer_current->invoke_top].class = class;
#else
    p_class_t current;
    p_class_t current_invoker;

    current = computer_current->class;
    current_invoker = computer_current->class_invoker;

    computer_current->class_invoker = computer_current->class;
    computer_current->class = class;
#endif
*/
//    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1, 
//        "%s: %s (%p, %u, {%p, %u}, {%p, %u})\n",
//        DEBUG_MODULE_NAME, __FUNCTION__,
//        class, method_id, 
//        return_value.data, return_value.count,
//        parameters.data, parameters.count);
    
//    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE2, 
//        L"%s: class: %p, name: %S\n",
//        DEBUG_MODULE_NAME,
//        class, class->description->name);

    interface_invoke_method_internal (interface, handle, object, class, 
        method_id, computer, context, reference_base, reference_new, 
        parameters_in, parameters_inout, parameters_out);

/*
#if defined (COMPUTER_INVOKE_HISTORY_ENABLED)
#else
    computer_current->class = current;
    computer_current->class_invoker = current_invoker;
#endif
*/
}

#endif /* !REPOSITORY_CLASS_INVOKE_INTERNAL_H */

