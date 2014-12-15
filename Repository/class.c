

void class_register (p_class_id_t real_class_id, 
    class_id_t class_id, uint32_t class_type, uint32_t number_of_interfaces, 
    interface_id_t interface_ids[], handle_t repository)
{
    p_class_t class;
    uint32_t i, j;
    p_interface_t interface;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (cid: %X, type: %u, noi: %u, ids: %p, ciid: %X)\n",
        __FILE__, __FUNCTION__, class_id, class_type, number_of_interfaces,
        interface_ids, class_control_id);

    if (class_type == CLASS_TYPE_DYNAMIC)
    {
        pool_of_integers_allocate (class_ids_pool, real_class_id);
        
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
            "%s::%s rcid = %u\n",
            __FILE__, __FUNCTION__, (*real_class_id));
    }

    TRY
    {
        memory_allocate ((void **) &class, sizeof (class_t) + 
            sizeof (p_interface_t) * number_of_interfaces);
    }
    CATCH_ALL (e)
    {
        THROW (e);
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
        "%s::%s Class = %p\n",
        __FILE__, __FUNCTION__, class);

    class->real_cid = (*real_class_id);
    class->cid = class_id;
    class->number_of_objects = 0;
    class->type = class_type;

    if (class_control_id != IID_NONE)
    {
        interface = (p_interface_t) hash_table_search_element (
            interfaces_table, &class_control_id);
        
        if ((interface == NULL) || (interface->type != INTERFACE_TYPE_CONTROL))
        {
            THROW (EXCEPTION_INVALID_PARAMETERS);
        }
        
        class->control_interface = interface;
        interface->number_of_classes++;
    }
    else
    {
        class->control_interface = NULL;            
    }
    
    class->number_of_interfaces = number_of_interfaces;

    for (i = 0; i < number_of_interfaces; i++)
    {
        interface = (p_interface_t) hash_table_search_element (
            interfaces_table, &interface_ids[i]);
            
        if ((interface == NULL) || 
            ((interface->type != INTERFACE_TYPE_STATIC) &&
            (interface->type != INTERFACE_TYPE_DYNAMIC)))
        {
            DEBUG_PRINT (DEBUG_LEVEL_WARNING,
                "%s::%s Unknown interface: %X {%u}\n",
                __FILE__, __FUNCTION__, interface_ids[i], i);
                
            THROW (EXCEPTION_INVALID_PARAMETERS);
        }
        
        for (j = 0; j < i; j++)
        {
            if (class->interfaces[j]->iid == interface->iid)
            {
                THROW (EXCEPTION_INVALID_PARAMETERS);
            }
        }

        interface->number_of_classes++;
        class->interfaces[i] = interface;
    }

    hash_table_add_element (classes_table, (p_hash_element_t) class);
}

void class_unregister (class_id_t real_class_id)
{
    p_class_t class;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);

    class = (p_class_t) hash_table_search_element (classes_table, 
        &real_class_id);
        
    if (class == NULL)
    {
        THROW (EXCEPTION_INVALID_PARAMETERS);
    }
    
     if (class->number_of_objects > 0)
    {
        THROW (EXCEPTION_IN_USE);
    }

    hash_table_delete_element (classes_table, &real_class_id);
    pool_of_integers_deallocate (class_ids_pool, real_class_id);

    for (i = 0; i < class->number_of_interfaces; i++)
    {
        class->interfaces[i]->number_of_classes--;
    }
    
    if (class->control_interface != NULL)
    {
        class->control_interface->number_of_classes--;
    }

    memory_deallocate (class);
}

void class_add_interfaces (class_id_t real_class_id, 
    uint32_t number_of_interfaces, interface_id_t interface_ids[])
{
    p_class_t old_class, new_class;
    uint32_t i, j;
    p_interface_t interface;

    old_class = (p_class_t) hash_table_search_element (classes_table, 
        &real_class_id);
    
    if ((old_class == NULL) || (old_class->number_of_objects > 0))
    {
        THROW (EXCEPTION_INVALID_PARAMETERS);
    }

    memory_allocate ((void **) &new_class, sizeof (class_t) + 
        sizeof (p_interface_t) * 
        (old_class->number_of_interfaces + number_of_interfaces));

    memory_copy (new_class, old_class, sizeof (class_t) + 
        sizeof (p_interface_t) * old_class->number_of_interfaces);
    
    new_class->number_of_interfaces += number_of_interfaces;

    for (i = 0; i < number_of_interfaces; i++)
    {
        interface = (p_interface_t) hash_table_search_element (
            interfaces_table, &interface_ids[i]);
            
        if (interface == NULL)
        {
            DEBUG_PRINT (DEBUG_LEVEL_WARNING,
                "%s::%s Unknown interface: %X {%u}\n",
                __FILE__, __FUNCTION__, interface_ids[i], i);
                
            return -1;
        }
        
        for (j = 0; j < old_class->number_of_interfaces + i; j++)
        {
            if (new_class->interfaces[j]->iid == interface->iid)
            {
                THROW (EXCEPTION_INVALID_PARAMETERS);
            }
        }

        interface->number_of_classes++;
        new_class->interfaces[old_class->number_of_interfaces + i] = interface;
    }
    
    hash_table_delete_element (classes_table, &real_class_id);
    memory_deallocate (old_class);
    hash_table_add_element (classes_table, (p_hash_element_t) new_class);
}

void class_delete_interfaces (class_id_t real_class_id, 
    uint32_t number_of_interfaces, interface_id_t interface_ids[])
{
    p_class_t old_class, new_class;
    
    uint32_t i, j;
    p_interface_t interface;

    old_class = (p_class_t) hash_table_search_element (classes_table, 
        &real_class_id);

    for (i = 0; i < old_class->number_of_interfaces; i++)
    {
        for (j = 0; j < number_of_interfaces; j++)
        {
            if (old_class->interfaces[i]->iid == interface_ids[j])
            {
                break;
            }
        }
        
        if (j == number_of_interfaces)
        {
//            new_class->interfaces[] = old_class->interfaces[i];
        }
    }
}
