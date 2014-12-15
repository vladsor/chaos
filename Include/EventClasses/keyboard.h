
#ifndef __EVENT_CLASS_KEYBOARD_H__
#define __EVENT_CLASS_KEYBOARD_H__

#define EVENT_CLASS_KEYBOARD_ID 0x0003


/* A keyboard packet is what gets sent whenever a key is pressed or
   released. */

typedef struct
{
    /* Does this packet contain a character code? If not, it is just one
       of the shift states that has been modified, or perhaps a 'special
       key'. */

    bool has_character_code;

    /* Is this a special key? */

    bool has_special_key;
  
    /* Was the key pressed or released? */

    bool key_pressed;
  
    /* The shift states. */

    bool left_shift_down;
    bool right_shift_down;
    bool left_alt_down;
    bool right_alt_down;
    bool left_control_down;
    bool right_control_down;
    bool left_windows_down;
    bool right_windows_down;
    bool task_list_down;

    /* If has_special_key is TRUE, this field contains the key code for
       this key. */

    uint32_t special_key;

    wchar_t character;  

} keyboard_event_data_t;

typedef keyboard_event_data_t * p_keyboard_event_data_t;

typedef bool (keyboard_supplier_handler_t) (context_t context, 
    p_keyboard_event_data_t keyboard_event_data);
typedef keyboard_supplier_handler_t * p_keyboard_supplier_handler_t;

typedef void (keyboard_consumer_handler_t) (context_t context, 
    p_keyboard_event_data_t keyboard_event_data);
typedef keyboard_consumer_handler_t * p_keyboard_consumer_handler_t;

static inline event_supplier_reference_t keyboard$supplier$create (
    object_reference_t keyboard_object)
{
    sequence_t empty_seq = {data: NULL, count: 0};

    return event_supplier_create (keyboard_object, 
        EVENT_CLASS_KEYBOARD_ID, empty_seq, 0);
}    

static inline event_consumer_reference_t keyboard$consumer$create (
    object_reference_t keyboard_object)
{
    sequence_t empty_seq = {data: NULL, count: 0};

    return event_consumer_create (keyboard_object, 
        EVENT_CLASS_KEYBOARD_ID, empty_seq, 0);
}    

static inline void keyboard$fire (event_supplier_reference_t keyboard_supplier, 
    p_keyboard_event_data_t keyboard_data)
{
    uint32_t pars[1] = {(uint32_t) keyboard_data};
    sequence_t event = {data: pars, count: 1};
    event_supplier_fire_event (keyboard_supplier, event, 0);
}    

static inline void keyboard$wait (event_consumer_reference_t keyboard_consumer, 
    p_keyboard_event_data_t keyboard_data)
{
    uint32_t pars[1] = {(uint32_t) keyboard_data};
    sequence_t event = {data: pars, count: 1};
    event_consumer_wait_event (keyboard_consumer, event, 0);
}    

#endif /* !__EVENT_CLASS_KEYBOARD_H__ */

