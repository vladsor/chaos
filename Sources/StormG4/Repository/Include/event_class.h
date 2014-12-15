
#ifdef REPOSITORY_NOT_INLINE

extern p_event_class_t event_class_create_static_internal (
    p_event_class_t event_class);

extern void event_class_destroy_static_internal (p_event_class_t event_class);

extern p_event_class_t event_class_create_internal (
    p_event_class_description_t event_class_description);
    
extern void event_class_destroy_internal (p_event_class_t event_class);

#else

#include "../EventClass/Include/internal.h"

#endif /* REPOSITORY_NOT_INLINE */
