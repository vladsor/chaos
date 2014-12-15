#include <enviroment.h>

#include "Include/internal.h"

#define MODULE_NAME "Repository"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>
#include <exception/macros.h>

p_exception_t exception_create_static_internal (p_exception_t exception)
{
    exception->owner = object_get_current ();

    return exception;
}

void exception_destroy_static_internal (p_exception_t exception UNUSED)
{
}

p_exception_t exception_create_internal (
    p_exception_description_t exception_description)
{
    p_exception_t exception;
    
    memory_allocate ((void **) &exception, sizeof (exception_t));

    exception->is_static = FALSE;
    exception->number_of_references = 0;
    
    memory_allocate ((void **) &exception->description, 
        sizeof (exception_description_t));
    memory_copy (exception->description, exception_description, 
        sizeof (exception_description_t));

    return exception_create_static_internal (exception);
}

void exception_destroy_internal (p_exception_t exception)
{
    exception_destroy_static_internal (exception);
    
    memory_deallocate (exception->description);
    memory_deallocate (exception);
}

