#include <enviroment.h>

#define MODULE_NAME "Repository"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>
#include <exception/macros.h>

void exception_create_check_parameters (
    p_exception_description_t exception_description)
{
    if (exception_description == NULL)
    {
        THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
    }
}

void exception_destroy_check_parameters (exception_reference_t exception)
{
    if (exception == NULL)
    {
        THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
    }
    
    if (exception->is_static)
    {
        THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
    }
    
    if (exception->number_of_references > 0)
    {
        THROW_SYSTEM (EXCEPTION_IS_LOCKED);
    }
}

