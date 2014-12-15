

handle_t repository_object_create (class_t class, uint32_t options,
    uint32_t number_of_joined_objects, handle_t joined_objects[], 
    sequence_t parameters)
{
    p_class_t class;
    uint32_t i;
    handle_t repository;
    p_object_t object;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p, %X, %p)\n",
        __FILE__, __FUNCTION__, handle, real_class_id, data);

    if ((handle->class != NULL) || (handle->context.object_data != NULL) || 
        (handle->context.handle_data != NULL) || (handle->functions != NULL))
    {
        DEBUG_PRINT (DEBUG_LEVEL_WARNING,
            "%s::%s Not empty handle: %p, %p, %p, %p, %p.\n",
            __FILE__, __FUNCTION__, handle, handle->class, 
            handle->context.object_data, handle->context.handle_data, 
            handle->functions);
        
        THROW (EXCEPTION_INVALID_PARAMETERS);
    }

    class = (p_class_t) hash_table_search_element (classes_table, 
        &real_class_id);
    
    if (class == NULL)
    {
        DEBUG_PRINT (DEBUG_LEVEL_WARNING,
            "%s::%s Unknown class: %X\n",
            __FILE__, __FUNCTION__, real_class_id);
            
        THROW (EXCEPTION_INVALID_PARAMETERS);
    }

    repository = class->repository;

    TRY
    {
        memory_allocate ((void **) &object, sizeof (object_t) + 
            sizeof (p_object_t) * number_of_joined_objects);
    }
    CATCH_ALL (e)
    {
        THROW (e);
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
        "%s::%s Object = %p\n",
        __FILE__, __FUNCTION__, object);
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
        "%s::%s Class: %p, cid: %X, type: %u\n",
        __FILE__, __FUNCTION__, class, class->cid, class->type);
    
    handle->class = class;
    class->number_of_references++;
    
    for (i = 0; i < number_of_joined_objects; i++)
    {
        object->joined_objects[i] = joined_objects[i].object;
    }
    
    if (class->type == CLASS_TYPE_DYNAMIC)
    {
        memory_allocate ();
        for (i=0;i<number_of_interfaces;i++)
        {
            object->own_interfaces[i] = class->interfaces[i];
            class->interfaces[i]->number_of_references++;
        }
    }

    handle->interface = NULL;
    handle->object = object;
    handle->context.object_data = NULL;
    handle->context.handle_data = NULL;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
        "%s::%s Parameters (%u:%p)\n",
            __FILE__, __FUNCTION__, 
            parameters.length, parameters.data);
            
    handle->context.object_data = repository$object_create (repository, 
        options, class, parameters);    

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s Return success.\n",
        __FILE__, __FUNCTION__);
}

void repository_object_add_joined_objects (handle_t handle, 
    uint32_t number_of_joined, handle_t joined_objects[])
{
    
}

void repository_object_delete_joined_objects (handle_t handle, 
    uint32_t number_of_joined, handle_t joined_objects[])
{
}

void repository_object_add_interfaces (handle_t handle, 
    uint32_t number_of_interfaces, interface_t interfaces[])
{
}

void repository_object_delete_interfaces (handle_t handle, 
    uint32_t number_of_interfaces, interface_t interfaces[])
{
}

void repository_object_destroy (handle_t handle)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p)\n",
        __FILE__, __FUNCTION__, handle);

    if (handle->interface != NULL)
    {
        DEBUG_PRINT (DEBUG_LEVEL_WARNING,
            "%s::%s Not closed handle: %p.\n",
            __FILE__, __FUNCTION__, handle);
        
        THROW (EXCEPTION_INVALID_PARAMETERS);
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1, 
        "%s::%s Calling user control function: %p.\n",
        __FILE__, __FUNCTION__, interface->control->close);
                    
    repository$object_destroy (repository, handle);    

    memory_deallocate (object);
    
    class->number_of_references--;
}

void repository_object_open (handle_t handle, interface_id_t interface_id,
    uint32_t options, sequence_t parameters)
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

    switch ((uint32_t) handle->class)    
    {
        case OBJECT_THIS:
        {
            class = NULL;
            break;
        }
        
        case OBJECT_KERNEL:
        {
            class = NULL;
            break;
        }
        
        case OBJECT_THIS_PROCESS:
        {
            class = NULL;
            break;
        }
        
        case OBJECT_THIS_THREAD:
        {
            class = NULL;
            break;
        }
        
        default:
        {
            class = handle->object->class;
        }
    };
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
        "%s::%s Class: %p.\n",
        __FILE__, __FUNCTION__, class);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
        "%s::%s Number of interfaces: %u.\n",
        __FILE__, __FUNCTION__, class->number_of_interfaces);

    for (i = 0; i < class->number_of_interfaces; i++)
    {
        interface = class->interfaces[i];

        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
            "%s::%s Interface: %p {%u}.\n",
            __FILE__, __FUNCTION__, interface, i);
            
        if (interface->iid == interface_id)
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
                "%s::%s Interface %X match.\n",
                __FILE__, __FUNCTION__, interface->real_iid);
                
            if (repository->interface != NULL)
            {
                DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
                    "%s::%s Calling user control function: %p.\n",
                    __FILE__, __FUNCTION__, interface->control->open);
                    
                repository$object_open (repository, handle, interface_id, 
                    options, parameters);
            }

            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
                "%s::%s Number of methods: %u.\n",
                __FILE__, __FUNCTION__, interface->number_of_methods);

            handle->interface = interface;
            
            break;
        }
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s DONE\n",
        __FILE__, __FUNCTION__);
}

void repository_object_close (handle_t handle)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);

    if (handle->interface == NULL)
    {
        DEBUG_PRINT (DEBUG_LEVEL_WARNING,
            "%s::%s Not opened handle: %p.\n",
            __FILE__, __FUNCTION__, handle);
        
        THROW (EXCEPTION_INVALID_PARAMETERS);
    }
                 
    repository$object_close (repository, handle);    

    handle->object->number_of_handles--;
    
    if (handle->object->number_of_handles == 0)
    {
        repository_object_destroy (handle);
    }
    
    handle->interface = NULL;
}

