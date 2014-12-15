#include <enviroment.h>

#define DEBUG_MODULE_NAME "Repository"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include "../Include/internal.h"

#include <debug/macros.h>
#include <exception/macros.h>

interface_reference_t interface_create (
    description_reference_t interface_description, 
    sequence_t interface_methods, reference_t interface_factory, 
    uint32_t options)
{
    p_interface_t interface;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p, {%p, %u})\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        interface_description, interface_methods.data, 
        interface_methods.count);

#if defined (SECURITY_ENABLED)
    interface_create_security_check ();
#endif

#if defined (CHECK_PARAMETERS)
    interface_create_check_parameters (interface_description, 
        interface_methods);
#endif
    
    interface = interface_create_internal (interface_description, 
        interface_methods, interface_factory, options);

    interface->header.is_static = FALSE;

    return (interface_reference_t) interface;    
}

void interface_destroy (interface_reference_t interface_reference)
{
    p_interface_t interface;

#if defined (SECURITY_ENABLED)
    interface_destroy_security_check (interface);
#endif
    
    interface = interface_translate_reference (interface_reference);
    
#if defined (CHECK_PARAMETERS)
    interface_destroy_check_parameters (interface);
#endif

    interface_destroy_internal (interface);
}

