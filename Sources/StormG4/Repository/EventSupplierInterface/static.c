#include <enviroment.h>

#define MODULE_NAME "Repository"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>
#include <exception/macros.h>

#include "../Include/internal.h"

event_supplier_interface_reference_t event_supplier_interface_create_static (
    p_event_supplier_interface_t interface)
{
    event_supplier_interface_reference_t interface_reference;
    
#if defined (SECURITY_ENABLED)
    event_supplier_interface_create_security_check ();
#endif
    
    interface_reference = (event_supplier_interface_reference_t) 
    	event_supplier_interface_create_static_internal (interface);

    interface->header.is_static = TRUE;

    return interface_reference;    
}

void event_supplier_interface_destroy_static (
    event_supplier_interface_reference_t interface_reference)
{
    p_event_supplier_interface_t interface = 
        (p_event_supplier_interface_t) interface_reference;

#if defined (SECURITY_ENABLED)
    event_supplier_interface_destroy_security_check (interface);
#endif

    event_supplier_interface_destroy_static_internal (interface);
}

