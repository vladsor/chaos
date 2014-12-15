#include <enviroment.h>

#include "Include/internal.h"

#define MODULE_NAME "Repository"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>
#include <exception/macros.h>

exception_reference_t exception_create_static_internal (p_exception_t exception)
{
    exception->owner = object_current;

    return exception;
}

void exception_destroy_static_internal (exception_reference_t exception)
{
}

exception_reference_t exception_create_internal (
    p_exception_description_t exception_description)
{
    exception_t exception;
    
    memory_allocate (&exception, sizeof (exception_t));

    exception->is_static = FALSE;
    exception->number_of_references = 0;
    
    memory_allocate (&exception->description, sizeof (exception_description_t));
    memory_copy (exception->description, exception_description);

    return exception_create_static_internal (exception);
}

void exception_destroy_internal (exception_reference_t exception)
{
    exception_destroy_static_internal (exception);
    
    memory_deallocate (exception->description);
    memory_deallocate (exception);
}

