#include <enviroment.h>

#define DEBUG_MODULE_NAME "Repository"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include "../Include/internal.h"

#include <debug/macros.h>
#include <exception/macros.h>

event_supplier_interface_reference_t event_supplier_interface_create (
    description_reference_t event_description, 
    int type, 
    method_reference_t handler,
/*    reference_t factory, */
    uint32_t options)
{
    p_event_supplier_interface_t event_supplier_interface;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p, %u, %p, %X)\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        event_description, type, handler, options);

#if defined (SECURITY_ENABLED)
    event_supplier_interface_create_security_check ();
#endif

#if defined (CHECK_PARAMETERS)
    event_supplier_interface_create_check_parameters (event_class, type, 
        handle, options);
#endif
    
    event_supplier_interface = event_supplier_interface_create_internal (
        event_description, type, handler, options);

    event_supplier_interface->header.is_static = FALSE;

    return (event_supplier_interface_reference_t) event_supplier_interface;    
}

void event_supplier_interface_destroy (
    event_supplier_interface_reference_t event_supplier_interface_reference)
{
    p_event_supplier_interface_t event_supplier_interface;

#if defined (SECURITY_ENABLED)
    event_supplier_interface_destroy_security_check (event_supplier_interface);
#endif
    
//    event_supplier_interface = event_supplier_interface_translate_reference (
//        event_supplier_interface_reference);
    event_supplier_interface = (p_event_supplier_interface_t) 
        event_supplier_interface_reference;
    
#if defined (CHECK_PARAMETERS)
    event_supplier_interface_destroy_check_parameters (
        event_supplier_interface);
#endif

    event_supplier_interface_destroy_internal (event_supplier_interface);
}

void event_supplier_interface_set_factory (
    event_supplier_interface_reference_t event_supplier_interface_reference,
    reference_t factory)
{
    p_event_supplier_interface_t event_supplier_interface;

    event_supplier_interface = (p_event_supplier_interface_t) 
        event_supplier_interface_reference;

    event_supplier_interface_set_factory_internal (event_supplier_interface,
        factory);
}    

