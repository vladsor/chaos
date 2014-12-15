
#ifdef REPOSITORY_NOT_INLINE

extern p_event_consumer_interface_t 
    event_consumer_interface_create_static_internal (
        p_event_consumer_interface_t event_consumer_interface);

extern void event_consumer_interface_destroy_static_internal (
    p_event_consumer_interface_t event_consumer_interface);

extern p_event_consumer_interface_t event_consumer_interface_create_internal (
    p_event_consumer_interface_description_t event_consumer_interface_description, 
    sequence_t event_consumer_interface_methods);
    
extern void event_consumer_interface_destroy_internal (
    p_event_consumer_interface_t event_consumer_interface);

#else

#include "../EventConsumerInterface/Include/internal.h"

#endif /* REPOSITORY_NOT_INLINE */

