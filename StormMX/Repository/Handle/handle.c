object_reference_t translate_object_reference (object_reference_t object)
{
    switch (object)    
    {
        case OBJECT_THIS:
        {
            return object_current;
        }
        
        case OBJECT_KERNEL:
        {
            return object_kernel;
        }
        
        case OBJECT_THIS_PROCESS:
        {
            return object_process_current;
        }
        
        case OBJECT_THIS_THREAD:
        {
            return object_thread_current;
        }
    };
    
    return object;
}

void handle_open (p_handle_reference_t p_handle, 
    object_reference_t object, interface_id_t interface_id,
    sequence_t parameters, uint32_t options)
{
    uint32_t i;
    p_class_t class;
    p_interface_t interface;
    handle_t repository;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p, %X)\n",
        __FILE__, __FUNCTION__, handle, interface_id);

    if (handle->object == NULL)
    {
        DEBUG_PRINT (DEBUG_LEVEL_WARNING,
            "%s::%s Empty handle: %p.\n",
            __FILE__, __FUNCTION__, handle);
        
        THROW (EXCEPTION_INVALID_PARAMETERS);
    }
    
    class = object->class;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
        "%s::%s Class: %p.\n",
        __FILE__, __FUNCTION__, class);

    for (i = 0; i < object->own_interfaces; i++)
    {
        interface = object->own_interfaces[i];
        
        if (interface->description.id == interface_id)
        {
            handle->current_object = object;
            handle->current_interface = interface;
            
            if (interface->type == INTERFACE_TYPE_DYNAMIC)
            {
                handle->data = handle$open (repository, object->data, interface_id, 
                    parameters, options);
            }
            
            return;
        }
    }
    
    for (i = 0; i < class->interfaces; i++)
    {
        interface = class->interfaces[i];
        if (interface->description.id == interfaces_id)
        {
            handle->current_object = object;
            handle->current_interface = interface;

            if (interface->type == INTERFACE_TYPE_DYNAMIC)
            {
                handle->data = handle$open (repository, object->data, interface_id, 
                    parameters, options);
            }
            
            return;
        }
    }
    
    for (j = object->joined_objects; j >= 0; j--)
    {
        class = object->joined_objects[j]->class;
        
        for (i = 0; i < class->interfaces; i++)
        {
            interface = class->interfaces[i];
            if (interface->description.id == interfaces_id)
            {
                handle->current_object = object->joined_objects[j];
                handle->current_interface = interface;

                if (interface->type == INTERFACE_TYPE_DYNAMIC)
                {
                    handle->data = handle$open (repository, 
                        handle->current_object->data, interface_id, 
                        parameters, options);
                }
            
                return;
            }
        }
    }
    

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s DONE\n",
        __FILE__, __FUNCTION__);
    
    THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
}

void handle_close (handle_reference_t handle_reference)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);

    if (handle->current_interface == NULL || handle->current_object == NULL)
    {
        DEBUG_PRINT (DEBUG_LEVEL_WARNING,
            "%s::%s Not opened handle: %p.\n",
            __FILE__, __FUNCTION__, handle);
        
        THROW (EXCEPTION_INVALID_PARAMETERS);
    }
                 
    handle$close (repository, handle->data);    

    object->number_of_references--;
/*    
    if (object->number_of_handles == 0)
    {
        repository_object_destroy (handle);
    }
*/    
    handle->current_interface = NULL;
    handle->current_object = NULL;
}

void handle_invoke_method (handle_reference_t handle, 
    method_id_t method_id, sequence_t parameters, sequence_t return_value)
{
    p_method_t current_method;

    if (handle->current_interface == NULL || handle->current_object == NULL)
    {
        DEBUG_PRINT (DEBUG_LEVEL_WARNING,
            "%s::%s Not opened handle: %p.\n",
            __FILE__, __FUNCTION__, handle);
        
        THROW (EXCEPTION_INVALID_PARAMETERS);
    }
    
    current_method = handle->current_interface->methods[method_id];
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s Invoke ((%s) %s)->%s ()\n",
        __FILE__, __FUNCTION__,
        handle->current_interface->name,
        handle->current_object->name,
        handle->current_interface->method_descriptions[method_id]->name);
    
    if (handle->current_interface->type == INTERFACE_TYPE_STATIC)
    {
        asm (
            "addl %2, %%esp\n"
            "movsb %1, %%esp"
            "call %0"
            :
            :
                "g" (current_method),
                "m" (parameters.data),
                "g" (parameters.length));
    }
    else if (handle->current_interface->type == INTERFACE_TYPE_DYNAMIC)
    {
        context_t context;
        
        context.object_data = handle->current_object->data;
        context.handle_data = handle->current_interface_data;

        asm (
            "addl %2, %%esp\n"
            "movsb %1, %%esp\n"
            "addl %4, %%esp\n"
            "movsb %3, %%esp\n"
            "call %0"
            :
            :
                "g" (current_method),
                "m" (parameters.data),
                "g" (parameters.length),
                "m" (&context),
                "ig" (sizeof (context)));
    }
}
