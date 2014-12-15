
#ifndef __EVENT_CLASS_DEBUG_H__
#define __EVENT_CLASS_DEBUG_H__

#define EVENT_CLASS_DEBUG_ID 0x0002

typedef struct
{
    uint32_t level;
    wchar_t module_name[STRING_MAX_LENGTH];
    wchar_t function[STRING_MAX_LENGTH];
    uint32_t line;
    wchar_t message[STRING_MAX_LENGTH];
} debug_event_data_t;    

typedef debug_event_data_t * p_debug_event_data_t;

typedef bool (debug_supplier_handler_t) (context_t context,
    p_uint32_t level, wchar_t *module_name, wchar_t *function_name, 
    p_uint32_t line, wchar_t *message);
typedef debug_supplier_handler_t * p_debug_supplier_handler_t;

typedef void (debug_consumer_handler_t) (context_t context, 
    uint32_t level, const wchar_t *module_name, const wchar_t *function_name, 
    uint32_t line, const wchar_t *message);
typedef debug_consumer_handler_t * p_debug_consumer_handler_t;

static inline event_supplier_reference_t debug$supplier$create (
    object_reference_t debug_object)
{
    sequence_t empty_seq = {data: NULL, count: 0};

    return event_supplier_create (debug_object, 
        EVENT_CLASS_DEBUG_ID, empty_seq, 0);
}    

static inline event_consumer_reference_t debug$consumer$create (
    object_reference_t debug_object)
{
    sequence_t empty_seq = {data: NULL, count: 0};

    return event_consumer_create (debug_object, 
        EVENT_CLASS_DEBUG_ID, empty_seq, 0);
}    

static inline void debug$fire (event_supplier_reference_t debug_supplier, 
    uint32_t level, const wchar_t *module_name, const wchar_t *function_name, 
    uint32_t line, const wchar_t *message)
{
    uint32_t pars[5] = {level, (uint32_t) module_name, (uint32_t) function_name, 
        line, (uint32_t) message};
    sequence_t event = {data: pars, count: 5};

    event_supplier_fire_event (debug_supplier, event, 0);
}    

static inline void debug$wait (event_consumer_reference_t debug_consumer, 
    p_uint32_t level, wchar_t *module_name, wchar_t *function_name, 
    p_uint32_t line, wchar_t *message)
{
    uint32_t pars[5] = {(uint32_t) level, (uint32_t) module_name, 
        (uint32_t) function_name, (uint32_t) line, (uint32_t) message};
    sequence_t event = {data: pars, count: 5};

    event_consumer_wait_event (debug_consumer, event, 0);
}    

#endif /* !__EVENT_CLASS_DEBUG_H__ */

