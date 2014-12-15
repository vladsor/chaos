#include <enviroment.h>

#define DEBUG_MODULE_NAME "Repository"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include "../Include/internal.h"

#include <debug/macros.h>
#include <exception/macros.h>

event_consumer_interface_reference_t event_consumer_interface_create (
    description_reference_t event_description, 
    int type, 
    method_reference_t handler,
/*    reference_t factory, */
    uint32_t options)
{
    p_event_consumer_interface_t event_consumer_interface;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p, %u, %p, %X)\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        event_description, type, handler, options);

#if defined (SECURITY_ENABLED)
    event_consumer_interface_create_security_check ();
#endif

#if defined (CHECK_PARAMETERS)
    event_consumer_interface_create_check_parameters (event_class, type, 
        handle, options);
#endif
    
    event_consumer_interface = event_consumer_interface_create_internal (
        event_description, type, handler, REFERENCE_NULL, options);

    event_consumer_interface->header.is_static = FALSE;

    return (event_consumer_interface_reference_t) event_consumer_interface;    
}

void event_consumer_interface_destroy (
    event_consumer_interface_reference_t event_consumer_interface_reference)
{
    p_event_consumer_interface_t event_consumer_interface;

#if defined (SECURITY_ENABLED)
    event_consumer_interface_destroy_security_check (event_consumer_interface);
#endif
    
//    event_consumer_interface = event_consumer_interface_translate_reference (
//        event_consumer_interface_reference);
    event_consumer_interface = (p_event_consumer_interface_t) 
        event_consumer_interface_reference;
    
#if defined (CHECK_PARAMETERS)
    event_consumer_interface_destroy_check_parameters (
        event_consumer_interface);
#endif

    event_consumer_interface_destroy_internal (event_consumer_interface);
}

void event_consumer_interface_set_factory (
    event_consumer_interface_reference_t event_consumer_interface_reference,
    reference_t factory)
{
    p_event_consumer_interface_t event_consumer_interface;

    event_consumer_interface = (p_event_consumer_interface_t) 
        event_consumer_interface_reference;

    event_consumer_interface_set_factory_internal (event_consumer_interface,
        factory);
}    

