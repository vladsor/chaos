#include <enviroment.h>

#define DEBUG_MODULE_NAME "Repository"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include "../Include/internal.h"

#include <debug/macros.h>
#include <exception/macros.h>

security_reference_t security_create_static (p_security_t security)
{
    security_reference_t security_reference;
 
    security_reference = (security_reference_t) 
        security_create_static_internal (security);

    security->header.is_static = TRUE;
    
    return security_reference;
}

void security_destroy_static (security_reference_t security_reference)
{
    p_security_t security = (p_security_t) security_reference;
    
    security_destroy_static_internal (security);
}


