#include <enviroment.h>

#define DEBUG_MODULE_NAME "Repository"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include "../Include/internal.h"

#include <debug/macros.h>
#include <exception/macros.h>

event_class_reference_t event_class_create (p_event_class_description_t event_class_description)
{
    p_event_class_t event_class;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        event_class_description);

#if defined (SECURITY_ENABLED)
    event_class_create_security_check ();
#endif

#if defined (CHECK_PARAMETERS)
    event_class_create_check_parameters (event_class_description);
#endif
    
    event_class = event_class_create_internal (event_class_description);

    event_class->header.is_static = FALSE;        

    return (event_class_reference_t) event_class;        
}

void event_class_destroy (event_class_reference_t event_class_reference)
{
    p_event_class_t event_class;

#if defined (SECURITY_ENABLED)
    event_class_destroy_security_check (event_class);
#endif
    
    event_class = event_class_translate_reference (event_class_reference);
    
#if defined (CHECK_PARAMETERS)
    event_class_destroy_check_parameters (event_class);
#endif

    event_class_destroy_internal (event_class);
}

