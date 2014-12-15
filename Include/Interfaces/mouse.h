
#ifndef __INTERFACE_MOUSE_H__
#define __INTERFACE_MOUSE_H__

#include <Interfaces/event_observer.h>

typedef struct
{
    unsigned int x;
    unsigned int y;
    unsigned int button;
} mouse_event_t;

typedef return_t (* mouse_handler_function_t) (mouse_event_t *event);

#endif /* !__INTERFACE_MOUSE_H__ */
