
#ifndef REPOSITORY_EVENT_CLASS_INTERNAL_H
#define REPOSITORY_EVENT_CLASS_INTERNAL_H

#include "../../Include/reference.h"

static inline p_event_class_t event_class_create_static_internal (
    p_event_class_t event_class)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        event_class);

    reference_create_internal (&event_class->header, 
        REFERENCE_TYPE_EVENT_CLASS);

    return event_class;
}

static inline void event_class_destroy_static_internal (
    p_event_class_t event_class)
{
    reference_destroy_internal (event_class);
}

static inline p_event_class_t event_class_create_internal (
    p_event_class_description_t event_class_description)
{
    p_event_class_t event_class;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s: %s (%p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        event_class_description);
    
    memory_allocate ((void **) &event_class, sizeof (event_class_t));

    // Copyng event class description
    memory_allocate ((void **) &event_class->description, 
        sizeof (event_class_description_t));
    memory_copy (event_class->description, event_class_description, 
        sizeof (event_class_description_t));

    return event_class_create_static_internal (event_class);
}

static inline void event_class_destroy_internal (p_event_class_t event_class)
{
    event_class_destroy_static_internal (event_class);
    
    memory_deallocate (event_class->description);
    memory_deallocate (event_class);
}

#endif /* !REPOSITORY_CLASS_INTERNAL_H */

