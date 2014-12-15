
void repository_interface_register (p_interface_id_t real_interface_id,
    interface_id_t interface_id, uint32_t interface_type, handle_t *repository,
    uint32_t number_of_methods, p_method_t methods[])
{
    p_interface_t interface;
    uint32_t i;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (rid: %p, iid: %X, nom: %u, methods: %p, control: %p)\n",
        __FILE__, __FUNCTION__, real_interface_id, interface_id, 
        number_of_methods, methods, control);

    pool_of_integers_allocate (interface_ids_pool, real_interface_id);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
        "%s::%s riid = %u\n",
        __FILE__, __FUNCTION__, (*real_interface_id));

    TRY
    {
        memory_allocate ((void **) &interface, sizeof (interface_t) + 
            sizeof (p_method_t) * number_of_methods);
    }
    CATCH_ALL (e)
    {
        THROW (e);
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
        "%s::%s Interface = %p\n",
        __FILE__, __FUNCTION__, interface);

    interface->real_iid = (*real_interface_id);
    interface->iid = interface_id;
    interface->type = interface_type;
    interface->number_of_classes = 0;
    interface->control = control;
    
    interface->object_data = NULL;
    interface->handle_data = NULL;
    
    interface->number_of_methods = number_of_methods;

    for (i = 0; i < number_of_methods; i++)
    {
        if (method[i]->function == NULL)
        {
            DEBUG_PRINT (DEBUG_LEVEL_ERROR,
                "%s::%s Method[%u]->function is NULL.\n",
                __FILE__, __FUNCTION__, i);
            
            THROW (EXCEPTION_INVALID_PARAMETERS);
        }
        
        interface->methods[i] = methods[i];        
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
        "%s::%s Adding to storage: %p....\n",
        __FILE__, __FUNCTION__, interface);

    hash_table_add_element (interfaces_table, (hash_element_t *) interface);
}

void interface_unregister (interface_id_t real_interface_id)
{
    p_interface_t interface;
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%u)\n",
        __FILE__, __FUNCTION__, real_interface_id);

    interface = (p_interface_t) hash_table_search_element (&real_interface_id);
    
    if (interface == NULL)
    {
        THROW (EXCEPTION_INVALID_PARAMETERS);
    }
    
    if (interface->number_of_classes > 0)
    {
        THROW (EXCEPTION_IN_USE);
    }

    hash_table_delete_element (interfaces_table, &real_interface_id);
    pool_of_integers_deallocate (interface_ids_pool, real_interface_id);
    
    memory_deallocate (interface);
}

