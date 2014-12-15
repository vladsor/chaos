#include <enviroment.h>

#define MODULE_NAME "Repository"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>
#include <exception/macros.h>

#include "../Include/internal.h"

event_class_reference_t event_class_create_static (p_event_class_t event_class)
{
    event_class_reference_t event_class_reference;
    
#if defined (SECURITY_ENABLED)
    event_class_create_security_check ();
#endif
    
    event_class_reference = (event_class_reference_t) 
        event_class_create_static_internal (event_class);
    
    event_class->header.is_static = TRUE;        

    return event_class_reference;    
}

void event_class_destroy_static (event_class_reference_t event_class_reference)
{
    p_event_class_t event_class = (p_event_class_t) event_class_reference;
    
#if defined (SECURITY_ENABLED)
    event_class_destroy_security_check (event_class);
#endif

    event_class_destroy_static_internal (event_class);
}

