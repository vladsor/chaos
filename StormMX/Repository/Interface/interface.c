#include <enviroment.h>

#define MODULE_NAME "interface"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>
#include <exception/macros.h>

void interface_register (p_interface_reference_t interface_reference, 
    p_interface_description_t interface_description, 
    sequence_t interface_methods)
{
    interface_t interface;

#if defined (SECURITY)    
    p_security_t security;
#endif
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p, %p, {%p, %u})\n",
        __FILE__, __FUNCTION__, interface_reference, interface_description, 
        interface_methods.data, interface_methods.length);

#if defined (SECURITY)
    security = (p_security_t) object_reference_current->security_reference;
    
    if (!security->is_absolute && !security->generic_acl.interface_register)
    {
#   if defined (SECURITY_GENERATE_ACCESS_DENIED)
        THROW_SYSTEM (EXCEPTION_ACCESS_DENIED);
#   else
        THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
#   endif        
    }
#endif    

    if (interface_reference == NULL || interface_description == NUL || 
        interface_table == NULL)
    {
        THROW (EXCEPTION_INVALID_PARAMETERS);
    }

    interface = (interface_t) (*interface_reference);

    if (interface == NULL)
    {
        THROW (EXCEPTION_INVALID_PARAMETERS);
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
        "%s::%s Interface = %p\n",
        __FILE__, __FUNCTION__, interface);

    interface->description = interface_description;
    interface->methods = interface_methods;
    interface->number_of_references = 0;
}

void interface_unregister (interface_reference_t interface_reference)
{
    interface_t interface;

#if defined (SECURITY)    
    p_security_t security;
#endif

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p)\n",
        __FILE__, __FUNCTION__, interface_reference);

#if defined (SECURITY)
    security = (p_security_t) object_reference_current->security_reference;
    
    if (!security->is_absolute && !security->generic_acl.interface_unregister)
    {
#   if defined (SECURITY_GENERATE_ACCESS_DENIED)
        THROW_SYSTEM (EXCEPTION_ACCESS_DENIED);
#   else
        THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
#   endif        
    }
#endif    

    interface = (interface_t) interface_reference;

    if (interface == NULL)
    {
        THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
    }
    
    if (interface->number_of_references > 0)
    {
        THROW_SYSTEM (EXCEPTION_IS_LOCKED);
    }
}

