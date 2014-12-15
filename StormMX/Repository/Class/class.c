#include <enviroment.h>

#define MODULE_NAME "class"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>
#include <exception/macros.h>

void class_register (p_class_reference_t class_reference, 
    p_class_description_t class_description,
    sequence_t class_interfaces, handle_t class_repository)
{
    class_t class;
    uint32_t i;
    p_interface_t interface;

#if defined (SECURITY)    
    p_security_t security;
#endif

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p, %p, {%p, %u})\n",
        __FILE__, __FUNCTION__, class_reference, class_description, 
        class_interfaces.data, class_interfaces.length);

#if defined (SECURITY)
    security = (p_security_t) object_reference_current->security_reference;
    
    if (!security->is_absolute && !security->generic_acl.class_register)
    {
#   if defined (SECURITY_GENERATE_ACCESS_DENIED)
        THROW_SYSTEM (EXCEPTION_ACCESS_DENIED);
#   else
        THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
#   endif        
    }
#endif    

    if (class_reference == NULL || class_description == NULL || 
        class_repository == NULL)
    {
        THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
    }
    
    class = (class_t) (*class_reference);

    if (class == NULL)
    {
        THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
    }

    class->description = class_description;
    class->interfaces = class_interfaces;
    class->repository = repository;
    class->number_of_references = 0;

    for (i = 0; i < class_interfaces.length; i++)
    {
        interface = (p_interface_t) class_interfaces.data[i];
            
        if ((interface == NULL) || 
            ((interface->type != INTERFACE_TYPE_STATIC) &&
            (interface->type != INTERFACE_TYPE_DYNAMIC)))
        {
            DEBUG_PRINT (DEBUG_LEVEL_WARNING,
                "%s::%s Invalid interface: %p {%u}\n",
                __FILE__, __FUNCTION__, interface, i);
                
            THROW (EXCEPTION_INVALID_PARAMETERS);
        }
        
        interface->number_of_references++;
    }
    
    return class;
}

void class_unregister (class_reference_t class_reference)
{
    p_class_t class;
    uint32_t i;
    p_interface_t interface;

#if defined (SECURITY)    
    p_security_t security;
#endif

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p)\n",
        __FILE__, __FUNCTION__, class_reference);

#if defined (SECURITY)
    security = (p_security_t) object_reference_current->security_reference;
    
    if (!security->is_absolute && !security->generic_acl.class_unregister)
    {
#   if defined (SECURITY_GENERATE_ACCESS_DENIED)
        THROW_SYSTEM (EXCEPTION_ACCESS_DENIED);
#   else
        THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
#   endif        
    }
#endif    

    class = (p_class_t) class_reference;

    if (class == NULL)
    {
        THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
    }
    
    if (class->number_of_references > 0)
    {
        THROW_SYSTEM (EXCEPTION_IS_LOCKES);
    }

    for (i = 0; i < class->interfaces.length; i++)
    {
        interface = (p_interface_t) class->interfaces[i].data;
        
        interface->number_of_references--;
    }
}
/*
void class_set_interfaces (class_reference_t class_reference, 
    sequence_t class_interfaces)
{
    p_class_t class;
    uint32_t i;
    p_interface_t interface;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p, {%p, %u})\n",
        __FILE__, __FUNCTION__, class,
        class_interfaces.data, class_interfaces.length);

    class = (p_class_t) class_reference;

    if (class == NULL)
    {
        THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
    }
    
    for (i = 0; i < class->interfaces.length; i++)
    {
        interface = (p_interface_t) class->interfaces[i].data;
        
        interface->number_of_references--;
    }

    class->interfaces = class_interfaces;

    for (i = 0; i < class_interfaces.length; i++)
    {
        interface = (p_interface_t) class_interfaces.data[i];
            
        if ((interface == NULL) || 
            ((interface->type != INTERFACE_TYPE_STATIC) &&
            (interface->type != INTERFACE_TYPE_DYNAMIC)))
        {
            DEBUG_PRINT (DEBUG_LEVEL_WARNING,
                "%s::%s Invalid interface: %p {%u}\n",
                __FILE__, __FUNCTION__, interface, i);
                
            THROW (EXCEPTION_INVALID_PARAMETERS);
        }
        
        interface->number_of_references++;
    }
}

sequence_t class_get_interfaces (class_reference_t class_reference)
{
    p_class_t class;
    class = (p_class_t) class_reference;

    return class->interfaces;
}
*/
interface_reference_t class_get_interface (class_reference_t class_reference, 
    interface_id_t interface_id)
{
    p_class_t class;
    uint32_t i;
    p_interface_t interface;

    class = (p_class_t) class_reference;

    if (class == NULL)
    {
        THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
    }
    
    for (i = 0; i < class->interfaces.length; i++)
    {
        interface = (p_interface_t) class->interfaces[i].data;
        
        if (interface->id == interface_id)
        {
            return (interface_reference_t) interface;
        }
    }
    
    return NULL;
}

