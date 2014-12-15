
#ifndef __INTERFACE_KEYBOARD_H__
#define __INTERFACE_KEYBOARD_H__

#include <Interfaces/event_observer.h>

/* The keyboard maps convert keys to standard UTF-8 sequences. */

enum
{
    KEYBOARD_MAP_BRITISH,
    KEYBOARD_MAP_DVORAK,
    KEYBOARD_MAP_RUSSIAN,
    KEYBOARD_MAP_SWEDISH,
    KEYBOARD_MAP_US,
};

enum
{
  IPC_KEYBOARD_SPECIAL_KEY_ESCAPE,
  IPC_KEYBOARD_SPECIAL_KEY_BACK_SPACE,
  IPC_KEYBOARD_SPECIAL_KEY_TAB,
  IPC_KEYBOARD_SPECIAL_KEY_ENTER,
  IPC_KEYBOARD_SPECIAL_KEY_CONTROL,
  IPC_KEYBOARD_SPECIAL_KEY_LEFT_SHIFT,
  IPC_KEYBOARD_SPECIAL_KEY_RIGHT_SHIFT,
  IPC_KEYBOARD_SPECIAL_KEY_PRINT_SCREEN,
  IPC_KEYBOARD_SPECIAL_KEY_ALT,
  IPC_KEYBOARD_SPECIAL_KEY_SPACE_BAR,
  IPC_KEYBOARD_SPECIAL_KEY_CAPS_LOCK,
  IPC_KEYBOARD_SPECIAL_KEY_F1,
  IPC_KEYBOARD_SPECIAL_KEY_F2,
  IPC_KEYBOARD_SPECIAL_KEY_F3,
  IPC_KEYBOARD_SPECIAL_KEY_F4,
  IPC_KEYBOARD_SPECIAL_KEY_F5, 
  IPC_KEYBOARD_SPECIAL_KEY_F6,
  IPC_KEYBOARD_SPECIAL_KEY_F7,
  IPC_KEYBOARD_SPECIAL_KEY_F8,
  IPC_KEYBOARD_SPECIAL_KEY_F9,
  IPC_KEYBOARD_SPECIAL_KEY_F10,
  IPC_KEYBOARD_SPECIAL_KEY_F11,
  IPC_KEYBOARD_SPECIAL_KEY_F12,
  IPC_KEYBOARD_SPECIAL_KEY_NUM_LOCK,
  IPC_KEYBOARD_SPECIAL_KEY_SCROLL_LOCK,
  IPC_KEYBOARD_SPECIAL_KEY_NUMERIC_7,
  IPC_KEYBOARD_SPECIAL_KEY_NUMERIC_8,
  IPC_KEYBOARD_SPECIAL_KEY_NUMERIC_9,
  IPC_KEYBOARD_SPECIAL_KEY_NUMERIC_MINUS,
  IPC_KEYBOARD_SPECIAL_KEY_NUMERIC_4,
  IPC_KEYBOARD_SPECIAL_KEY_NUMERIC_5,
  IPC_KEYBOARD_SPECIAL_KEY_NUMERIC_6,
  IPC_KEYBOARD_SPECIAL_KEY_NUMERIC_PLUS,
  IPC_KEYBOARD_SPECIAL_KEY_NUMERIC_1,
  IPC_KEYBOARD_SPECIAL_KEY_NUMERIC_2,
  IPC_KEYBOARD_SPECIAL_KEY_NUMERIC_3,
  IPC_KEYBOARD_SPECIAL_KEY_NUMERIC_0,
  IPC_KEYBOARD_SPECIAL_KEY_NUMERIC_DELETE,
  IPC_KEYBOARD_SPECIAL_KEY_LEFT_WINDOWS,
  IPC_KEYBOARD_SPECIAL_KEY_RIGHT_WINDOWS,
  IPC_KEYBOARD_SPECIAL_KEY_MENU,

  IPC_KEYBOARD_SPECIAL_KEY_ARROW_UP    = IPC_KEYBOARD_SPECIAL_KEY_NUMERIC_8,
  IPC_KEYBOARD_SPECIAL_KEY_ARROW_DOWN  = IPC_KEYBOARD_SPECIAL_KEY_NUMERIC_2,
  IPC_KEYBOARD_SPECIAL_KEY_ARROW_LEFT  = IPC_KEYBOARD_SPECIAL_KEY_NUMERIC_4,
  IPC_KEYBOARD_SPECIAL_KEY_ARROW_RIGHT = IPC_KEYBOARD_SPECIAL_KEY_NUMERIC_6,
  IPC_KEYBOARD_SPECIAL_KEY_DELETE      = IPC_KEYBOARD_SPECIAL_KEY_NUMERIC_DELETE,

#if FALSE
  IPC_KEYBOARD_SPECIAL_KEY_HOME,
  IPC_KEYBOARD_SPECIAL_KEY_END,
  IPC_KEYBOARD_SPECIAL_KEY_INSERT
#endif
};

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

} keyboard_packet_t;

//typedef return_t (* keyboard_handler_function_t) (keyboard_packet_t *event);

//extern return_t keyboard_switch_map_to_next (void);
//return_t keyboard_register_handler (keyboard_handler_function_t handler);

#endif /* !__INTERFACE_KEYBOARD_H__ */
