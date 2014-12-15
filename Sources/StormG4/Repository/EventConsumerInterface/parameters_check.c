#include <enviroment.h>

#include "Include/parameters_check.h"

#define MODULE_NAME "Repository"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>
#include <exception/macros.h>

#if defined (CHECK_PARAMETERS)

void interface_create_check_parameters (
    p_interface_description_t interface_description, 
    sequence_t interface_methods)
{
    if (interface_description == NULL)
    {
        THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
    }
    // TODO: check interface_methods
}

void interface_destroy_check_parameters (interface_reference_t interface)
{
    if (interface == NULL)
    {
        THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
    }
    
    if (interface->is_static)
    {
        THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
    }
    
    if (interface->number_of_references > 0)
    {
        THROW_SYSTEM (EXCEPTION_IS_LOCKED);
    }
}

#endif
