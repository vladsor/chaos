
#ifndef REPOSITORY_METHOD_INVOKE_INTERNAL_H
#define REPOSITORY_METHOD_INVOKE_INTERNAL_H

static inline void method_invoke_internal (p_method_t method, 
    p_handle_t handle, p_object_t object, p_class_t class, 
    p_interface_t interface, p_computer_t computer, context_t context, 
    reference_t reference_base, reference_t reference_new, 
    sequence_t parameters_in, sequence_t parameters_inout, 
    sequence_t parameters_out)
{
    if (computer == NULL)
    {
        computer = method->computer;
    }

    computer_invoke_internal (computer,
        handle, object, class, interface, method, context,
        reference_base, reference_new, parameters_in, parameters_inout, 
        parameters_out);
/*
#if defined (COMPUTER_INVOKE_HISTORY_ENABLED)
    computer_current->invoke_stack[computer_current->invoke_top].method = 
        method;
    computer_current->invoke_top++;
#else
    p_method_t current;
    p_method_t current_invoker;

    current = computer_current->method;
    current_invoker = computer_current->method_invoker;
    
    computer_current->method_invoker = computer->method;
    computer_current->method = method;

#endif

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1, 
        "%s: %s (%p, {%llX, %llX}, {%p, %u}, {%p, %u})\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        method, 
        context.object_data, context.handle_data,
        return_value.data, return_value.count, 
        parameters.data, parameters.count);

//    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE2, 
//        L"%s: Description: %p, name: %S, type: %u, function: %p, data: %llX\n",
//        DEBUG_MODULE_NAME,
//        method->description, method->description->name,
//        method->description->type, method->function, method->data);

    if (computer == NULL)
    {
        if (method->computer != NULL)
        {
            computer = method->computer;
        }
        else
        {
            computer = COMPUTER_CURRENT;
        }    
    }
    
    if (computer != COMPUTER_CURRENT)
    {
        while (1);
    }    

    switch (method->description->type)
    {
        case METHOD_TYPE_DYNAMIC:
        {
            p_method_dynamic_t function;
            
            function = (p_method_dynamic_t) method->function;

            function (method->data, context, return_value, parameters);
            
            break;
        }

        case METHOD_TYPE_STATIC:
        {
            p_method_static_t function;
            
            function = (p_method_static_t) method->function;

            function (method->data, return_value, parameters);
            
            break;
        }
        
        case METHOD_TYPE_OBJECT_CREATE:
        {
            p_method_object_create_t function;

            function = (p_method_object_create_t) method->function;

            function (method->data, context, reference, parameters);
            
            break;
        }
            
        case METHOD_TYPE_OBJECT_DESTROY:
        {
            p_method_object_destroy_t function;
            
            function = (p_method_object_destroy_t) method->function;
            
            function (method->data, context, reference);
            
            break;
        }    
    }    
    
#if defined (COMPUTER_INVOKE_HISTORY_ENABLED)
    computer_current->invoke_top--;
#else    
    computer_current->method = current;
    computer_current->method_invoker = current_invoker;
#endif
*/
}

static inline void method_invoke_async_internal (p_method_t method, 
    p_handle_t handle, p_object_t object, p_class_t class, 
    p_interface_t interface, p_computer_t computer, 
    reference_t reference_base, reference_t reference_new, 
    sequence_t parameters_in, sequence_t parameters_inout)
{
    if (computer == NULL)
    {
        computer = method->computer;
    }

    computer_invoke_async_internal (computer, 
        handle, object, class, interface, method, 
        reference_base, reference_new, parameters_in, parameters_inout);
}

#endif /* !REPOSITORY_METHOD_INVOKE_INTERNAL_H */

