
#ifndef __EVENT_CLASS_IRQ_H__
#define __EVENT_CLASS_IRQ_H__

#define EVENT_CLASS_IRQ_ID 0x0001

typedef bool (irq_supplier_handler_t) (context_t context);
typedef irq_supplier_handler_t * p_irq_supplier_handler_t;

typedef void (irq_consumer_handler_t) (context_t context);
typedef irq_consumer_handler_t * p_irq_consumer_handler_t;

static inline event_supplier_reference_t irq$supplier$create (
    object_reference_t irq_object, uint32_t irq_number)
{
    uint32_t pars[1] = {irq_number};
    sequence_t event_seq = {data: pars, count: 1};

    return event_supplier_create (irq_object, 
        EVENT_CLASS_IRQ_ID, event_seq, 0);
}    

static inline event_consumer_reference_t irq$consumer$create (
    object_reference_t irq_object)
{
    sequence_t empty_seq = {data: NULL, count: 0};

    return event_consumer_create (irq_object, 
        EVENT_CLASS_IRQ_ID, empty_seq, 0);
}    

static inline void irq$fire (event_supplier_reference_t irq_supplier)
{
    sequence_t empty_seq = {data: NULL, count: 0};

    event_supplier_fire_event (irq_supplier, empty_seq, 0);
}    

static inline void irq$wait (event_consumer_reference_t irq_consumer)
{
    sequence_t empty_seq = {data: NULL, count: 0};

    event_consumer_wait_event (irq_consumer, empty_seq, 0);
}    

#endif /* !__EVENT_CLASS_IRQ_H__ */

