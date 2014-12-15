#include <enviroment.h>

#define MODULE_NAME "Repository"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>
#include <exception/macros.h>

#if defined (CHECK_PARAMETERS)

void object_create_check_parameters (class_reference_t class, 
    sequence_t object_own_interfaces, sequence_t joined_objects, 
    security_reference_t security, sequence_t parameters, 
    uint32_t options)
{
    if (class == NULL)
    {
        THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
    }

    if (security == NULL)
    {
        THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
    }
    
    /**
     * @todo add check for 'object_own_interfaces'
     */

    /**
     * @todo add check for 'joined_objects'
     */
}

void object_destroy_check_parameters (object_reference_t object)
{
    if (object == NULL)
    {
        THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
    }
    
    if (object->is_static)
    {
        THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
    }
    
    if (object->number_of_references > 0)
    {
        THROW_SYSTEM (EXCEPTION_IS_LOCKED);
    }
}

#endif
