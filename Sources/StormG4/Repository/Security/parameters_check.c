#include <enviroment.h>

#define DEBUG_MODULE_NAME "Repository"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include "Include/parameters_check.h"

#include <debug/macros.h>
#include <exception/macros.h>

#if defined (CHECK_PARAMETERS)

void security_create_check_parameters (bool security_is_absolute, 
    p_generic_acl_t generic_acl)
{
    if (generic_acl == NULL)
    {
        THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
    }
}

void security_destroy_check_parameters (p_security_t security UNUSED)
{
}

#endif

