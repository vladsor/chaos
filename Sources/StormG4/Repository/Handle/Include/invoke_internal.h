
#ifndef REPOSITORY_HANDLE_INVOKE_INTERNAL_H
#define REPOSITORY_HANDLE_INVOKE_INTERNAL_H

static inline void handle_invoke_method_internal (p_handle_t handle, 
    method_id_t method_id, 
    p_computer_t computer, 
    reference_t reference_base, reference_t reference_new, 
    sequence_t parameters_in, sequence_t parameters_inout, 
    sequence_t parameters_out)
{
/*
#if defined (COMPUTER_INVOKE_HISTORY_ENABLED)
    computer_current->invoke_stack[computer_current->invoke_top].handle = 
        handle;
#else
    p_handle_t current;
    p_handle_t current_invoker;

    current = HANDLE_CURRENT;
    current_invoker = HANDLE_CURRENT_INVOKER;

    HANDLE_CURRENT_INVOKER = current;
    HANDLE_CURRENT = handle;
#endif
*/
//    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1, 
//        "%s: %s (%p, %u, {%p, %u}, {%p, %u})\n",
//        DEBUG_MODULE_NAME, __FUNCTION__,
//        handle, method_id, 
//        return_value.data, return_value.count, 
//        parameters.data, parameters.count);

    object_invoke_method_internal (handle->object, handle, handle->interface, 
        method_id, computer, handle->data, reference_base, reference_new, 
        parameters_in, parameters_inout, parameters_out);
/*
#if defined (COMPUTER_INVOKE_HISTORY_ENABLED)
#else
    HANDLE_CURRENT = current;
    HANDLE_CURRENT_INVOKER = current_invoker;
#endif
*/
}

#endif /* !REPOSITORY_HANDLE_INVOKE_INTERNAL_H */

