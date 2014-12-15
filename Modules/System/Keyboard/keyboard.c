/* $Id: keyboard.c,v 1.2 2001/02/10 21:25:02 jojo Exp $ */
/* Abstract: Keyboard server for chaos. */
/* Authors: Per Lundberg <plundis@chaosdev.org>,
            Henrik Hallin <hal@chaosdev.org>
            Vladimir Sorokin */

/* Copyright 1999-2004 chaos development. */

/* Parts of this file was inspired by the Linux keyboard support. */

#include <enviroment.h>
#include <memory_inlines.h>
#include <string.h>

#include <Interfaces/keyboard.h>
#include <Interfaces/event_provider.h>

#include "controller.h"
#include "keyboard.h"
#include "mouse.h"
#include "scan_code.h"

//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

typedef struct 
{
    char* description;

    struct keyboard_map_t* next;

    const wchar_t *map;
  
    const wchar_t *shift_map;
  
    const wchar_t *altgr_map;

} keyboard_map_t;

/* Built-in keyboard maps. */
/* FIXME: add support for load/unload keyboard maps. */
#include "keyboard_maps/british.h"
#include "keyboard_maps/swedish.h"
#include "keyboard_maps/dvorak.h"
#include "keyboard_maps/us.h"
#include "keyboard_maps/russian.h"

keyboard_map_t built_in_keyboard_maps[] =
{
  [KEYBOARD_MAP_BRITISH] = { 
    "British", NULL, 
    british_keyboard_map, 
    british_keyboard_map_shift,
    british_keyboard_map_altgr,
  },

  [KEYBOARD_MAP_DVORAK] = { 
    "Dvorak", NULL, 
    dvorak_keyboard_map, 
    dvorak_keyboard_map_shift,
    dvorak_keyboard_map_altgr,
  },

  [KEYBOARD_MAP_RUSSIAN] = { 
    "Russian", NULL, 
    russian_keyboard_map, 
    russian_keyboard_map_shift,
    russian_keyboard_map_altgr,
  },

  [KEYBOARD_MAP_US] = { 
    "USA", NULL, 
    us_keyboard_map, 
    us_keyboard_map_shift,
    us_keyboard_map_altgr,
  },
};

keyboard_map_t* default_keyboard_maps = (keyboard_map_t *)
   built_in_keyboard_maps + KEYBOARD_MAP_US;
   
keyboard_map_t* current_keyboard_map = (keyboard_map_t *)
   built_in_keyboard_maps + KEYBOARD_MAP_US;

/* We need to create an array of 16 bytes, for storing the currently
   pressed keys in. (128 scan codes / 8). */

static volatile uint8_t keyboard_pressed_keys[16];

/* State of the *lock-keys. */

static volatile uint8_t keyboard_state_scroll = 0x0F;
static volatile uint8_t keyboard_state_num = 0x0F;
static volatile uint8_t keyboard_state_caps = 0x0F;

/* The shift state. */

static volatile unsigned int shift_state = 0;

/* Used only by send_data - set by keyboard_interrupt. */

static volatile int reply_expected = 0;
static volatile int acknowledge = 0;
static volatile int resend = 0;

bool keyboard_exists = TRUE;

/* Conversion table from keyboard scan codes to the standardised
   'special key' codes, which are generic between all platforms. */
static uint8_t special_key_conversion[] =
{
    [SCAN_CODE_ESCAPE] = KEYBOARD_SPECIAL_KEY_ESCAPE,
    [SCAN_CODE_BACK_SPACE] = KEYBOARD_SPECIAL_KEY_BACK_SPACE,
    [SCAN_CODE_TAB] = KEYBOARD_SPECIAL_KEY_TAB,
    [SCAN_CODE_ENTER] = KEYBOARD_SPECIAL_KEY_ENTER,
    [SCAN_CODE_LEFT_CONTROL] = KEYBOARD_SPECIAL_KEY_LEFT_CONTROL,
    [SCAN_CODE_RIGHT_CONTROL] = KEYBOARD_SPECIAL_KEY_RIGHT_CONTROL,
    [SCAN_CODE_LEFT_SHIFT] = KEYBOARD_SPECIAL_KEY_LEFT_SHIFT,
    [SCAN_CODE_RIGHT_SHIFT] = KEYBOARD_SPECIAL_KEY_RIGHT_SHIFT,
    [SCAN_CODE_PRINT_SCREEN] = KEYBOARD_SPECIAL_KEY_PRINT_SCREEN,
    [SCAN_CODE_LEFT_ALT] = KEYBOARD_SPECIAL_KEY_LEFT_ALT,
    [SCAN_CODE_RIGHT_ALT] = KEYBOARD_SPECIAL_KEY_RIGHT_ALT,
    [SCAN_CODE_SPACE_BAR] = KEYBOARD_SPECIAL_KEY_SPACE_BAR,
    [SCAN_CODE_CAPS_LOCK] = KEYBOARD_SPECIAL_KEY_CAPS_LOCK,
    [SCAN_CODE_F1] = KEYBOARD_SPECIAL_KEY_F1,
    [SCAN_CODE_F2] = KEYBOARD_SPECIAL_KEY_F2,
    [SCAN_CODE_F3] = KEYBOARD_SPECIAL_KEY_F3,
    [SCAN_CODE_F4] = KEYBOARD_SPECIAL_KEY_F4,
    [SCAN_CODE_F5] = KEYBOARD_SPECIAL_KEY_F5,
    [SCAN_CODE_F6] = KEYBOARD_SPECIAL_KEY_F6,
    [SCAN_CODE_F7] = KEYBOARD_SPECIAL_KEY_F7,
    [SCAN_CODE_F8] = KEYBOARD_SPECIAL_KEY_F8,
    [SCAN_CODE_F9] = KEYBOARD_SPECIAL_KEY_F9,
    [SCAN_CODE_F10] = KEYBOARD_SPECIAL_KEY_F10,
    [SCAN_CODE_NUM_LOCK] = KEYBOARD_SPECIAL_KEY_NUM_LOCK,
    [SCAN_CODE_SCROLL_LOCK] = KEYBOARD_SPECIAL_KEY_SCROLL_LOCK,
    [SCAN_CODE_NUMERIC_7] = KEYBOARD_SPECIAL_KEY_NUMERIC_7,
    [SCAN_CODE_NUMERIC_8] = KEYBOARD_SPECIAL_KEY_NUMERIC_8,
    [SCAN_CODE_NUMERIC_9] = KEYBOARD_SPECIAL_KEY_NUMERIC_9,
    [SCAN_CODE_NUMERIC_MINUS] = KEYBOARD_SPECIAL_KEY_NUMERIC_MINUS,
    [SCAN_CODE_NUMERIC_4] = KEYBOARD_SPECIAL_KEY_NUMERIC_4,
    [SCAN_CODE_NUMERIC_5] = KEYBOARD_SPECIAL_KEY_NUMERIC_5,
    [SCAN_CODE_NUMERIC_6] = KEYBOARD_SPECIAL_KEY_NUMERIC_6,
    [SCAN_CODE_NUMERIC_PLUS] = KEYBOARD_SPECIAL_KEY_NUMERIC_PLUS,
    [SCAN_CODE_NUMERIC_1] = KEYBOARD_SPECIAL_KEY_NUMERIC_1,
    [SCAN_CODE_NUMERIC_2] = KEYBOARD_SPECIAL_KEY_NUMERIC_2,
    [SCAN_CODE_NUMERIC_3] = KEYBOARD_SPECIAL_KEY_NUMERIC_3,
    [SCAN_CODE_NUMERIC_0] = KEYBOARD_SPECIAL_KEY_NUMERIC_0,
    [SCAN_CODE_NUMERIC_DELETE] = KEYBOARD_SPECIAL_KEY_NUMERIC_DELETE,
    [SCAN_CODE_NUMERIC_ENTER] = KEYBOARD_SPECIAL_KEY_NUMERIC_ENTER,
    [SCAN_CODE_F11] = KEYBOARD_SPECIAL_KEY_F11,
    [SCAN_CODE_F12] = KEYBOARD_SPECIAL_KEY_F12,
    [SCAN_CODE_LEFT_WINDOWS] = KEYBOARD_SPECIAL_KEY_LEFT_WINDOWS,
    [SCAN_CODE_RIGHT_WINDOWS] = KEYBOARD_SPECIAL_KEY_RIGHT_WINDOWS,
    [SCAN_CODE_MENU] = KEYBOARD_SPECIAL_KEY_MENU,
    [SCAN_CODE_INSERT] = KEYBOARD_SPECIAL_KEY_INSERT,
    [SCAN_CODE_DELETE] = KEYBOARD_SPECIAL_KEY_DELETE,
    [SCAN_CODE_HOME] = KEYBOARD_SPECIAL_KEY_HOME,
    [SCAN_CODE_END] = KEYBOARD_SPECIAL_KEY_END,
    [SCAN_CODE_PAGE_UP] = KEYBOARD_SPECIAL_KEY_PAGE_UP,
    [SCAN_CODE_PAGE_DOWN] = KEYBOARD_SPECIAL_KEY_PAGE_DOWN,
    [SCAN_CODE_UP] = KEYBOARD_SPECIAL_KEY_ARROW_UP,
    [SCAN_CODE_DOWN] = KEYBOARD_SPECIAL_KEY_ARROW_DOWN,
    [SCAN_CODE_LEFT] = KEYBOARD_SPECIAL_KEY_ARROW_LEFT,
    [SCAN_CODE_RIGHT] = KEYBOARD_SPECIAL_KEY_ARROW_RIGHT
};

/* Acknowledge the keyboard controller. */

static int do_acknowledge (unsigned char scancode)
{
  if (reply_expected != 0) 
  {
    /* Unfortunately, we must recognise these codes only if we know
       they are known to be valid (i.e., after sending a command),
       because there are some brain-damaged keyboards (yes, FOCUS 9000
       again) which have keys with such codes :( */

    if (scancode == KEYBOARD_REPLY_ACK) 
    {
      acknowledge = 1;
      reply_expected = 0;
      return 0;
    }
    else if (scancode == KEYBOARD_REPLY_RESEND) 
    {
      resend = 1;
      reply_expected = 0;
      return 0;
    }
  }
  return 1;
}

/* send_data sends a character to the keyboard and waits for an
   acknowledge, possibly retrying if asked to. Returns the success
   status. */

static bool send_data (unsigned char data)
{
  int retries = 3;
  
  do 
  {
    unsigned long timeout = KEYBOARD_TIMEOUT;
    
    /* Set by interrupt routine on receipt of ACK. */

    acknowledge = 0;
    resend = 0;
    reply_expected = 1;
    controller_write_output_word (data);

    while (TRUE)
    {
      while (TRUE)
      {
        uint8_t status = controller_read_status ();
        uint8_t scancode;

        /* Loop until there is data available. */
        
        if ((status & CONTROLLER_STATUS_OUTPUT_BUFFER_FULL) == 0)
        {
          continue;
        }  

        /* Get it. */

        scancode = controller_read_input ();
        
        /* Wait until there is a message available. */

        if ((status & CONTROLLER_STATUS_MOUSE_OUTPUT_BUFFER_FULL) != 0)
        {
          continue;
        }
        else
        {
          do_acknowledge (scancode);
          break;
        }
      }

      if (acknowledge != 0)
      {
        return TRUE;
      }

      if (resend != 0)
      {
        break;
      }

      timer_sleep_milli (1);
      timeout--;
      
      if (timeout == 0)
      {
        return FALSE;
      }
    }
  } while (retries-- > 0);
  
  return FALSE;
}

/* Set the typematic repeat rate of the keyboard. */

const char *keyboard_set_repeat_rate (void)
{
  /* Finally, set the typematic rate to maximum. */

  controller_write_output_word (KEYBOARD_COMMAND_SET_RATE);
  if (controller_wait_for_input () != KEYBOARD_REPLY_ACK)
  {
    return "Set rate: no ACK.";
  }

  controller_write_output_word (0x00);
  if (controller_wait_for_input () != KEYBOARD_REPLY_ACK)
  {
    return "Set rate: no ACK.";
  }
  return NULL;
}

/* Update the keyboard LEDs. */
/* FIXME: Defines!!! */

void keyboard_update_leds (void)
{
  uint8_t output = 0;


  if (keyboard_state_scroll == 0xF0)
  {
    output = 1;
  }

  if (keyboard_state_num == 0xF0)
  {
    output |= 2;
  }

  if (keyboard_state_caps == 0xF0)
  {
    output |= 4;
  }

  if (keyboard_exists && (!send_data (KEYBOARD_COMMAND_SET_LEDS) ||
                          !send_data (output))) 
  {
    /* Re-enable keyboard if any errors. */

    send_data (KEYBOARD_COMMAND_ENABLE);
    keyboard_exists = FALSE;
  }
}

/* Check if the given code is currently pressed. */

static inline bool key_pressed (uint8_t scancode)
{
  if ((keyboard_pressed_keys[scancode / 8] & (1 << (scancode % 8))) != 0)
  {
    return TRUE;
  }
  else
  {
    return FALSE;
  }
}

/* Translate the given key according to the current keyboard map. */

static wchar_t translate_key (uint8_t scancode)
{
  if ((shift_state & KEYBOARD_LEFT_SHIFT) == KEYBOARD_LEFT_SHIFT ||
      (shift_state & KEYBOARD_RIGHT_SHIFT) == KEYBOARD_RIGHT_SHIFT ||
      keyboard_state_caps == 0xF0)
  {
    return current_keyboard_map->shift_map[scancode];
  }
  else if (key_pressed (SCAN_CODE_RIGHT_ALT))
  {
    return current_keyboard_map->altgr_map[scancode];
  }
  else
  {
    return current_keyboard_map->map[scancode];
  }
}

/* Handle a keyboard event. This function is called from the interrupt
   handler. */

void keyboard_handle_event (uint8_t scancode)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%u).",
        __FILE__, __FUNCTION__, scancode);
        
    keyboard_exists = TRUE;

    if (do_acknowledge (scancode))
    {
        wchar_t translated_key;

        keyboard_packet_t keyboard_packet;

        memory_set_uint8 ((uint8_t *) &keyboard_packet, 0, 
            sizeof (keyboard_packet_t));

    /* Special case -- this one is sent to us when the keyboard is
       reset from an external device (like a keyboard/monitor
       switch). It is also sent when right shift is released. What a
       sick world this is... */

    if (scancode == 170)
    {
      keyboard_update_leds ();
      keyboard_set_repeat_rate ();
    }

    if ((scancode & 0x80) == 0) 
    {
      /* A key was pressed. */
      keyboard_packet.key_pressed = TRUE;
      
      keyboard_pressed_keys[scancode / 8] |= (1 << (scancode % 8));
      
      /* Check if the pressed key is a lock key. */
      
      switch (scancode)
      {
        case SCAN_CODE_CAPS_LOCK:
        {
          keyboard_state_caps = ~keyboard_state_caps;
          keyboard_update_leds ();
          break;
        }
      
        case SCAN_CODE_NUM_LOCK:
        {
          keyboard_state_num = ~keyboard_state_num;
          keyboard_update_leds ();
          break;
        }
      
        case SCAN_CODE_SCROLL_LOCK:
        {
          keyboard_state_scroll = ~keyboard_state_scroll;
          keyboard_update_leds ();
          break;
        }

        /* Other key. */
        
        default:
        {
          /* Do we have a receiver registered? */

//          if (keyboard_handler != NULL)
          {
            /* Does this change the shift state? If so, set the flag
               and notify our recipient. */

            switch (scancode)
            {
              case SCAN_CODE_LEFT_SHIFT:
              {
                shift_state |= KEYBOARD_LEFT_SHIFT;
                break;
              }

              case SCAN_CODE_RIGHT_SHIFT:
              {
                shift_state |= KEYBOARD_RIGHT_SHIFT;
                break;
              }

              case SCAN_CODE_LEFT_ALT:
              {
                shift_state |= KEYBOARD_LEFT_ALT;
                break;
              }
              
              case SCAN_CODE_RIGHT_ALT:
              {
                shift_state |= KEYBOARD_RIGHT_ALT;
                break;
              }

              case SCAN_CODE_LEFT_CONTROL:
              {
                shift_state |= KEYBOARD_LEFT_CONTROL;
                break;
              }
              
              case SCAN_CODE_RIGHT_CONTROL:
              {
                shift_state |= KEYBOARD_RIGHT_CONTROL;
                break;
              }
              
              default:
              {
                /* Seems to be a normal keypress. */
                
                keyboard_packet.key_pressed = TRUE;

                /* Convert it to the chaos format. */

                translated_key = translate_key (scancode);
                
                if (translated_key == '\0')
                {
                  keyboard_packet.has_special_key = 1;
                  keyboard_packet.special_key =
                    special_key_conversion[scancode];
                }
                else
                {
                  keyboard_packet.has_character_code = 1;
                  keyboard_packet.character = translated_key;
                }
                break;
              }
            }
          }
          
          break;
        }
      }
    }
    else
    {
      /* A key was released. Start by masking away the highest bit and
         update the keyboard_pressed_keys structure. */
      keyboard_packet.key_pressed = FALSE;

      scancode &= 0x7F;
      keyboard_pressed_keys[scancode / 8] &= (~(1 << (scancode % 8)));

      /* If we have someone to send this to, do it. */

//      if (keyboard_handler != NULL)
      {
        switch (scancode)
        {
          case SCAN_CODE_LEFT_SHIFT:
          {
            shift_state &= ~KEYBOARD_LEFT_SHIFT;
            break;
          }
          
          case SCAN_CODE_RIGHT_SHIFT:
          {
            shift_state &= ~KEYBOARD_RIGHT_SHIFT;
            break;
          }
          
          case SCAN_CODE_LEFT_ALT:
          {
            shift_state |= KEYBOARD_LEFT_ALT;
            break;
          }
              
          case SCAN_CODE_RIGHT_ALT:
          {
            shift_state &= ~KEYBOARD_RIGHT_ALT;
            break;
          }

          case SCAN_CODE_LEFT_CONTROL:
          {
            shift_state |= KEYBOARD_LEFT_CONTROL;
            break;
          }
          
          case SCAN_CODE_RIGHT_CONTROL:
          {
            shift_state &= ~KEYBOARD_RIGHT_CONTROL;
            break;
          }
      
          /* Anything else will be E-lectric. */
    
          default:
          {
            keyboard_packet.key_pressed = FALSE;
            translated_key = translate_key (scancode);
            
            /* If the key couldn't be translated, translate it in our own
               way. */
            
            if (translated_key == L'\0')
            {
              keyboard_packet.has_special_key = 1;
              keyboard_packet.special_key = special_key_conversion[scancode];
            }
            else
            {
              keyboard_packet.has_character_code = 1;
              keyboard_packet.character = translated_key;
            }
          }
        }
      }
    }
    
//    if (keyboard_handler != NULL)
    {
      keyboard_packet.left_shift_down = 
        ((shift_state & KEYBOARD_LEFT_SHIFT) ==
         KEYBOARD_LEFT_SHIFT ? 1 : 0);

      keyboard_packet.right_shift_down = 
        ((shift_state & KEYBOARD_RIGHT_SHIFT) ==
         KEYBOARD_RIGHT_SHIFT ? 1 : 0);

      keyboard_packet.left_alt_down = 
        ((shift_state & KEYBOARD_LEFT_ALT) ==
         KEYBOARD_LEFT_ALT ? 1 : 0);

      keyboard_packet.right_alt_down = 
        ((shift_state & KEYBOARD_RIGHT_ALT) ==
         KEYBOARD_RIGHT_ALT ? 1 : 0);

      keyboard_packet.left_control_down = 
        ((shift_state & KEYBOARD_LEFT_CONTROL) ==
         KEYBOARD_LEFT_CONTROL ? 1 : 0);

      keyboard_packet.right_control_down = 
        ((shift_state & KEYBOARD_RIGHT_CONTROL) ==
         KEYBOARD_RIGHT_CONTROL ? 1 : 0);

      DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
          "Character: [%c](%i){%u%u%u%u}\n", 
          (char) keyboard_packet.character, scancode,
          keyboard_packet.left_shift_down,
          keyboard_packet.right_shift_down);      
      /* Send the key to the receiver. */

//      keyboard_handler (&keyboard_packet);
      event_provider$write (&keyboard_event_channel, (void *) &keyboard_packet);
    }
  }
}       

/* Initialise the keyboard. */

const char *keyboard_init (void)
{
  int status;

  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Initing keyboard...\n");

  /* Test the keyboard interface. This seems to be the only way to get
     it going.  If the test is successful a x55 is placed in the
     input buffer. */

  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Doing self test...\n");

  controller_write_command_word (CONTROLLER_COMMAND_SELF_TEST);
  if (controller_wait_for_input () != 0x55)
  {
    return "Keyboard failed self test.";
  }

  /* Perform a keyboard interface test.  This causes the controller
     to test the keyboard clock and data lines.  The results of the
     test are placed in the input buffer. */

  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Doing interface test...\n");

  controller_write_command_word (CONTROLLER_COMMAND_KEYBOARD_TEST);
  if (controller_wait_for_input () != 0x00)
  {
    return "Keyboard interface failed self test.";
  }

  /* Enable the keyboard by allowing the keyboard clock to run. */

  controller_write_command_word (CONTROLLER_COMMAND_KEYBOARD_ENABLE);

  /* Reset keyboard. If the read times out then the assumption is that
     no keyboard is plugged into the machine. This defaults the
     keyboard to scan-code set 2.
    
     Set up to try again if the keyboard asks for RESEND. */

  do 
  {
      controller_write_output_word (KEYBOARD_COMMAND_RESET);
      status = controller_wait_for_input ();
      
      if (status == KEYBOARD_REPLY_ACK)
      {
          break;
      }

      if (status != KEYBOARD_REPLY_RESEND)
      {
          return "Keyboard reset failed, no ACK.";
      }
    
  } while (TRUE);

  if (controller_wait_for_input () != KEYBOARD_REPLY_POWER_ON_RESET)
  {
    return "Keyboard reset failed, bad reply.";
  }

  /* Set keyboard controller mode. During this, the keyboard should be
     in the disabled state.
     
     Set up to try again if the keyboard asks for RESEND. */
  do 
  {
    controller_write_output_word (KEYBOARD_COMMAND_DISABLE);
    
    status = controller_wait_for_input ();
    if (status == KEYBOARD_REPLY_ACK)
    {  
      break;
    }

    if (status != KEYBOARD_REPLY_RESEND)
    {
      return "Disable keyboard: no ACK.";
    }
  } while (TRUE);

  controller_write_command_word (CONTROLLER_COMMAND_WRITE_MODE);
  controller_write_output_word (CONTROLLER_MODE_KEYBOARD_INTERRUPT |
                                CONTROLLER_MODE_SYS |
                                CONTROLLER_MODE_DISABLE_MOUSE |
                                CONTROLLER_MODE_KCC);
  
  /* IBM Power-PC portables need this to use scan-code set 1 -- Cort */
  
  controller_write_command_word (CONTROLLER_COMMAND_READ_MODE);
  if ((controller_wait_for_input () & CONTROLLER_MODE_KCC) == 0) 
  {
    /* If the controller does not support conversion, Set the keyboard
       to scan-code set 1.  */

    controller_write_output_word (0xF0);
    controller_wait_for_input ();
    controller_write_output_word (0x01);
    controller_wait_for_input ();
  }

  /* Enable the keyboard. */

  controller_write_output_word (KEYBOARD_COMMAND_ENABLE);
  if (controller_wait_for_input () != KEYBOARD_REPLY_ACK)
  {
    return "Enable keyboard: no ACK.";
  }

  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "End keyboard initing.\n");
  
  /* Set the repeat rate. */

  return keyboard_set_repeat_rate ();
}


return_t keyboard_switch_map_to_next (void)
{
    /* FIXME: add mutex for changing map */
    if (current_keyboard_map->next != NULL)
    {
        current_keyboard_map = (keyboard_map_t *) current_keyboard_map->next;
    }
    else
    {
        current_keyboard_map = default_keyboard_maps;
    }
    
    return 0;
}
/*
return_t keboard_load_map (keyboard_map_t *)
{
}

return_t keyboard_unload_map (keyboard_map_t *)
{
}
*/

void keyboard_load_maps (void)
{
    (keyboard_map_t *) (built_in_keyboard_maps[KEYBOARD_MAP_US].next) = 
        &built_in_keyboard_maps[KEYBOARD_MAP_RUSSIAN];

    current_keyboard_map = default_keyboard_maps;  
}

void keyboard_reset_pressed_keys (void)
{
    memory_set_uint8 ((void *) &keyboard_pressed_keys, 0, 
        sizeof (keyboard_pressed_keys));
}
