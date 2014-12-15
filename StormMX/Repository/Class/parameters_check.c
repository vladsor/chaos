
void class_create_check_parameters (p_class_description_t class_description,
    sequence_t class_interfaces, object_reference_t class_repository)
{
    uint32_t index;
    p_interface_t interface;
    
    if (class_description == NULL || class_repository == NULL)
    {
        THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
    }
    // TODO: check repository: must be in same process
    
    for (index = 0; index < class_interfaces.length; index++)
    {
        interface = ((p_interface_t) class_interfaces.data) + index;
            
        if ((interface == NULL) || 
            ((interface->type != INTERFACE_TYPE_STATIC) &&
            (interface->type != INTERFACE_TYPE_DYNAMIC)))
        {
            THROW (EXCEPTION_INVALID_PARAMETERS);
        }
    }
}

void class_destroy_check_parameters (class_reference_t class)
{
    if (class == NULL)
    {
        THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
    }
    
    if (class->is_static)
    {
        THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
    }
    
    if (class->number_of_references > 0)
    {
        THROW_SYSTEM (EXCEPTION_IS_LOCKED);
    }
}

