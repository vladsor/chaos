#include <enviroment.h>

#define MODULE_NAME "Repository"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>
#include <exception/macros.h>

#include "../Include/internal.h"

interface_reference_t interface_create_static (p_interface_t interface)
{
    interface_reference_t interface_reference;
    
#if defined (SECURITY_ENABLED)
    interface_create_security_check ();
#endif
    
    interface_reference = (interface_reference_t) 
    	interface_create_static_internal (interface);

    interface->header.is_static = TRUE;

    return interface_reference;    
}

void interface_destroy_static (interface_reference_t interface_reference)
{
    p_interface_t interface = (p_interface_t) interface_reference;

#if defined (SECURITY_ENABLED)
    interface_destroy_security_check (interface);
#endif

    interface_destroy_static_internal (interface);
}

