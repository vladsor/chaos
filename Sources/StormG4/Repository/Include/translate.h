
static inline p_method_t method_translate_reference (method_reference_t method)
{
    p_reference_struct_t header;
    
    if (method == REFERENCE_NULL)
    {
        return NULL;
    }
    
    header = &((p_method_t) method)->header;
    
    if (header->magic_number != REFERENCE_MAGIC_NUMBER_METHOD)
    {
        return NULL;
    }

    return (p_method_t) method;
}

static inline p_interface_t interface_translate_reference (
    interface_reference_t interface)
{
    p_reference_struct_t header;
    
    if (interface == REFERENCE_NULL)
    {
        return NULL;
    }
    
    header = &((p_interface_t) interface)->header;
    
    if (header->magic_number != REFERENCE_MAGIC_NUMBER_INTERFACE)
    {
        return NULL;
    }

    return (p_interface_t) interface;
}

static inline p_class_t class_translate_reference (class_reference_t class)
{
    p_reference_struct_t header;
    
    if (class == REFERENCE_NULL)
    {
        return NULL;
    }
    
    header = &((p_class_t) class)->header;
    
    if (header->magic_number != REFERENCE_MAGIC_NUMBER_CLASS)
    {
        return NULL;
    }

    return (p_class_t) class;
}

static inline p_security_t security_translate_reference (
    security_reference_t security)
{
    p_reference_struct_t header;
    
    if (security == REFERENCE_NULL)
    {
        return NULL;
    }
    
    header = &((p_security_t) security)->header;
    
    if (header->magic_number != REFERENCE_MAGIC_NUMBER_SECURITY)
    {
        return NULL;
    }
    
    return (p_security_t) security;
}

static inline p_object_t object_translate_reference (object_reference_t object)
{
    p_reference_struct_t header;
    
    if (object == REFERENCE_NULL)
    {
        return NULL;
    }
    
    header = &((p_object_t) object)->header;
    
    if (header->magic_number != REFERENCE_MAGIC_NUMBER_OBJECT)
    {
        return NULL;
    }
    
    return (p_object_t) object;
}

static inline p_handle_t handle_translate_reference (handle_reference_t handle)
{
    p_reference_struct_t header;
    
    if (handle == REFERENCE_NULL)
    {
        return NULL;
    }
    
    header = &((p_handle_t) handle)->header;
    
    if (header->magic_number != REFERENCE_MAGIC_NUMBER_HANDLE)
    {
        return NULL;
    }
    
    return (p_handle_t) handle;
}


