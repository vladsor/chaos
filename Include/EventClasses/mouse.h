
#ifndef __EVENT_CLASS_MOUSE_H__
#define __EVENT_CLASS_MOUSE_H__

#define EVENT_CLASS_MOUSE_ID 0x0004

typedef bool (mouse_supplier_handler_t) (context_t context, 
    p_uint32_t x, p_uint32_t y, p_uint32_t button);
typedef mouse_supplier_handler_t * p_mouse_supplier_handler_t;

typedef void (mouse_consumer_handler_t) (context_t context, 
    uint32_t x, uint32_t y, uint32_t button);
typedef mouse_consumer_handler_t * p_mouse_consumer_handler_t;

static inline event_supplier_reference_t mouse$supplier$create (
    object_reference_t mouse_object)
{
    sequence_t empty_seq = {data: NULL, count: 0};

    return event_supplier_create (mouse_object, 
        EVENT_CLASS_MOUSE_ID, empty_seq, 0);
}    

static inline event_consumer_reference_t mouse$consumer$create (
    object_reference_t mouse_object)
{
    sequence_t empty_seq = {data: NULL, count: 0};

    return event_consumer_create (mouse_object, 
        EVENT_CLASS_MOUSE_ID, empty_seq, 0);
}    

static inline void mouse$fire (event_supplier_reference_t mouse_supplier, 
    uint32_t x, uint32_t y, uint32_t button)
{
    uint32_t pars[3] = {x, y, button};
    sequence_t event = {data: pars, count: 3};

    event_supplier_fire_event (mouse_supplier, event, 0);
}    

static inline void mouse$wait (event_consumer_reference_t mouse_consumer, 
    p_uint32_t x, p_uint32_t y, p_uint32_t button)
{
    uint32_t pars[3] = {(uint32_t) x, (uint32_t) y, (uint32_t) button};
    sequence_t event = {data: pars, count: 3};

    event_consumer_wait_event (mouse_consumer, event, 0);
}    

#endif /* !__EVENT_CLASS_MOUSE_H__ */

