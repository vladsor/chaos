
#ifndef REPOSITORY_INTERFACE_INVOKE_INTERNAL_H
#define REPOSITORY_INTERFACE_INVOKE_INTERNAL_H

static inline void interface_invoke_method_internal (p_interface_t interface, 
    p_handle_t handle, p_object_t object, p_class_t class, 
    method_id_t method_id, p_computer_t computer, context_t context,
    reference_t reference_base, reference_t reference_new, 
    sequence_t parameters_in, sequence_t parameters_inout, 
    sequence_t parameters_out)
{
    p_method_t method;
/*
#if defined (COMPUTER_INVOKE_HISTORY_ENABLED)
    computer_current->invoke_stack[computer_current->invoke_top].interface = 
        interface;
#else
    p_interface_t current;
    p_interface_t current_invoker;

    current = computer_current->interface;
    current_invoker = computer_current->interface_invoker;
    
    computer_current->interface_invoker = computer_current->interface;
    computer_current->interface = interface;
#endif
*/
//    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1, 
//        "%s: %s (%p, %u, {%llX, %llX}, {%p, %u}, {%p, %u})\n",
//        DEBUG_MODULE_NAME, __FUNCTION__,
//        interface, method_id, 
//        context.object_data, context.handle_data,
//        return_value.data, return_value.count,
//        parameters.data, parameters.count);

    method = ((p_p_method_t) interface->methods.data)[method_id];

//    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE2, 
//        L"%s: interface: %p, name: %S\n",
//        DEBUG_MODULE_NAME,
//        interface, interface->description->name);
    
    method_invoke_internal (method, handle, object, class, interface, computer,
        context, reference_base, reference_new, parameters_in, parameters_inout,
        parameters_out);
/*    
#if defined (COMPUTER_INVOKE_HISTORY_ENABLED)
#else
    computer_current->interface = current;
    computer_current->interface_invoker = current_invoker;
#endif
*/
}

#endif /* !REPOSITORY_INTERFACE_INVOKE_INTERNAL_H */

