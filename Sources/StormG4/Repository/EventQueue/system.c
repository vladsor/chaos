#include <enviroment.h>

#define DEBUG_MODULE_NAME "Repository"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include "../Include/internal.h"

#include <debug/macros.h>
#include <exception/macros.h>


event_queue_reference_t event_queue_create (
    description_reference_t event_description, uint32_t type, 
    uint32_t capacity)
{
    p_event_queue_t event_queue;
    
    memory_allocate ((void **) &event_queue, sizeof (event_queue_t));
    event_queue->event_class = event_description;
    event_queue->type = type;
    event_queue->capacity = capacity;
    
    reference_create_internal (&event_queue->header, REFERENCE_TYPE_EVENT_QUEUE);

    return (event_queue_reference_t) event_queue;
}    
    
void event_queue_destroy (event_queue_reference_t event_queue_reference)
{
    p_event_queue_t event_queue;
    event_queue = (p_event_queue_t) event_queue_reference;

    reference_destroy_internal (event_queue);
    
    memory_deallocate (event_queue);
}    



