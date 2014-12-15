/* $Id: keyboard.c,v 1.2 2001/02/10 21:25:02 jojo Exp $ */
/* Abstract: Keyboard server for chaos. */
/* Authors: Per Lundberg <plundis@chaosdev.org>,
            Henrik Hallin <hal@chaosdev.org>
            Vladimir Sorokin */

/* Copyright 1999-2004 chaos development. */

/* Parts of this file was inspired by the Linux keyboard support. */

#include <enviroment.h>
#include <string.h>

#include <Interfaces/keyboard.h>
//#include <Interfaces/event_provider.h>

#include "Include/controller.h"
#include "Include/keyboard.h"
#include "Include/mouse.h"
#include "Include/scan_code.h"

#include "Include/interface.h"

#define DEBUG_MODULE_NAME L"Keyboard"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#ifndef __STORM_KERNEL__
#   define DEBUG_SUPPLIER (keyboard_debug_supplier)
#endif

#include <debug/macros.h>

typedef struct
{
    wchar_t general[128];
  
    wchar_t shift[128];
  
    wchar_t alt[128];

} keyboard_maps_t;    

typedef keyboard_maps_t * p_keyboard_maps_t;

typedef struct 
{
    wchar_t description[WSTRING_MAX_LENGTH];

    struct keyboard_map_t* next;

    p_keyboard_maps_t maps;
    
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
    [KEYBOARD_MAP_BRITISH] = 
    { 
        L"British", 
        NULL, 
        &british_keyboard_maps,
    },
/*
  [KEYBOARD_MAP_DVORAK] = { 
    L"Dvorak", NULL, 
    dvorak_keyboard_map, 
    dvorak_keyboard_map_shift,
    dvorak_keyboard_map_altgr,
  },
*/
    [KEYBOARD_MAP_RUSSIAN] = 
    { 
        L"Russian", 
        NULL, 
        &russian_keyboard_maps,
    },

    [KEYBOARD_MAP_US] = 
    { 
        L"USA", 
        NULL, 
        &us_keyboard_maps,
    },
};

keyboard_map_t* default_keyboard_maps = (keyboard_map_t *)
   built_in_keyboard_maps + KEYBOARD_MAP_US;
   

keyboard_map_t* current_keyboard_map = (keyboard_map_t *)
   built_in_keyboard_maps + KEYBOARD_MAP_US;


/* We need to create an array of 16 bytes, for storing the currently
   pressed keys in. (128 scan codes / 8). */

static volatile uint8_t keyboard_pressed_keys[128 / 8];

/* State of the *lock-keys. */

static volatile uint8_t keyboard_state_scroll = 0x0F;
static volatile uint8_t keyboard_state_num = 0x0F;
static volatile uint8_t keyboard_state_caps = 0x0F;

/* The shift state. */

static volatile unsigned int shift_state = 0;

/* Used only by send_data - set by keyboard_interrupt. */

static volatile bool reply_expected = FALSE;
static volatile bool acknowledge = FALSE;
static volatile bool resend = FALSE;

bool keyboard_exists = TRUE;

/* Conversion table from keyboard scan codes to the standardised
   'special key' codes, which are generic between all platforms. */
static uint8_t special_key_conversion[128] =
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

static bool do_acknowledge (unsigned char scancode)
{
    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
        L"%S: %s (%u)\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        scancode);

    if (reply_expected) 
    {
        /* Unfortunately, we must recognise these codes only if we know
           they are known to be valid (i.e., after sending a command),
           because there are some brain-damaged keyboards (yes, FOCUS 9000
           again) which have keys with such codes :( */

        if (scancode == KEYBOARD_REPLY_ACK) 
        {
            acknowledge = TRUE;
            reply_expected = FALSE;
            
            DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
                L"%S: %s ACK = TRUE\n",
                DEBUG_MODULE_NAME, __FUNCTION__);
            
            return FALSE;
        }
        else if (scancode == KEYBOARD_REPLY_RESEND) 
        {
            resend = TRUE;
            reply_expected = FALSE;
            
            return FALSE;
        }
    }
    
    return TRUE;
}

/* send_data sends a character to the keyboard and waits for an
   acknowledge, possibly retrying if asked to. Returns the success
   status. */

static bool send_data (unsigned char data)
{
    int retries = 3;

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
        L"%S: %s (%u)\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        data);
  
    do 
    {
        unsigned int timeout = KEYBOARD_TIMEOUT;
    
        /* Set by interrupt routine on receipt of ACK. */

        acknowledge = FALSE;
        resend = FALSE;
        reply_expected = TRUE;
        controller_write_output_word (data);

        while (TRUE)
        {
            while (TRUE)
            {
                uint8_t status = controller_read_status ();
                uint8_t scancode;

                DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1,
                    L"%S: %s: Status: %X, %X, %X\n",
                    DEBUG_MODULE_NAME, __FUNCTION__,
                    status, CONTROLLER_STATUS_OUTPUT_BUFFER_FULL, 
                    CONTROLLER_STATUS_MOUSE_OUTPUT_BUFFER_FULL);

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

            if (acknowledge)
            {
                DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1,
                    L"%S: %s: Return TRUE\n",
                    DEBUG_MODULE_NAME, __FUNCTION__);

                return TRUE;
            }

            if (resend)
            {
                break;
            }

//      timer_sleep_milli (1);
            cpu_sleep_milli (CPU_CURRENT, 1);
      
            timeout--;
      
            if (timeout == 0)
            {
                DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1,
                    L"%S: %s: Return FALSE\n",
                    DEBUG_MODULE_NAME, __FUNCTION__);

                return FALSE;
            }
        }
    } while (retries-- > 0);

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1,
        L"%S: %s: Return FALSE\n",
        DEBUG_MODULE_NAME, __FUNCTION__);
  
    return FALSE;
}

/* Set the typematic repeat rate of the keyboard. */

const char *keyboard_set_repeat_rate (void)
{
    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
        L"%S: %s ()\n",
        DEBUG_MODULE_NAME, __FUNCTION__);

    /* Finally, set the typematic rate to maximum. */

    controller_write_output_word (KEYBOARD_COMMAND_SET_RATE);
    
    if (controller_wait_for_input () != KEYBOARD_REPLY_ACK)
    {
        DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
            L"%S: %s: Done\n",
            DEBUG_MODULE_NAME, __FUNCTION__);

        return "Set rate: no ACK.";
    }

    controller_write_output_word (0x00);
    if (controller_wait_for_input () != KEYBOARD_REPLY_ACK)
    {
        DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
            L"%S: %s: Done\n",
            DEBUG_MODULE_NAME, __FUNCTION__);
            
        return "Set rate: no ACK.";
    }

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
        L"%S: %s: Done\n",
        DEBUG_MODULE_NAME, __FUNCTION__);
    
    return NULL;
}

/* Update the keyboard LEDs. */
/* FIXME: Defines!!! */

void keyboard_update_leds (void)
{
    uint8_t output = 0;
    
    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
        L"%S: %s ()\n",
        DEBUG_MODULE_NAME, __FUNCTION__);

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

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
        L"%S: %s: Done\n",
        DEBUG_MODULE_NAME, __FUNCTION__);
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
    if (((shift_state & KEYBOARD_LEFT_SHIFT) == KEYBOARD_LEFT_SHIFT) ||
        ((shift_state & KEYBOARD_RIGHT_SHIFT) == KEYBOARD_RIGHT_SHIFT) ||
        (keyboard_state_caps == 0xF0))
    {
        return current_keyboard_map->maps->shift[scancode];
    }
    else if (key_pressed (SCAN_CODE_RIGHT_ALT))
    {
        return current_keyboard_map->maps->alt[scancode];
    }
    else
    {
        return current_keyboard_map->maps->general[scancode];
    }
}

/* Check if the pressed key is a lock key. */
static bool update_key_locks (uint8_t scancode)
{      
    switch (scancode)
    {
        case SCAN_CODE_CAPS_LOCK:
        {
            keyboard_state_caps = ~keyboard_state_caps;
#if defined (KEYBOARD_SAFE_IRQ_HANDLER)
            keyboard_update_leds ();
#endif
            
            return TRUE;
        }
      
        case SCAN_CODE_NUM_LOCK:
        {
            keyboard_state_num = ~keyboard_state_num;
#if defined (KEYBOARD_SAFE_IRQ_HANDLER)
            keyboard_update_leds ();
#endif
            
            return TRUE;
        }
      
        case SCAN_CODE_SCROLL_LOCK:
        {
            keyboard_state_scroll = ~keyboard_state_scroll;
#if defined (KEYBOARD_SAFE_IRQ_HANDLER)
            keyboard_update_leds ();
#endif
            
            return TRUE;
        }
    }    
    
    /* Other key. */
    
    return FALSE;
}

/* Does this change the shift state? If so, set the flag and notify our 
   recipient. */
static bool update_shift_state_after_press (uint8_t scancode)
{
    switch (scancode)
    {
        case SCAN_CODE_LEFT_SHIFT:
        {
            shift_state |= KEYBOARD_LEFT_SHIFT;
            
            return TRUE;
        }

        case SCAN_CODE_RIGHT_SHIFT:
        {
            shift_state |= KEYBOARD_RIGHT_SHIFT;
            
            return TRUE;
        }

        case SCAN_CODE_LEFT_ALT:
        {
            shift_state |= KEYBOARD_LEFT_ALT;
            
            return TRUE;
        }
              
        case SCAN_CODE_RIGHT_ALT:
        {
            shift_state |= KEYBOARD_RIGHT_ALT;
            
            return TRUE;
        }

        case SCAN_CODE_LEFT_CONTROL:
        {
            shift_state |= KEYBOARD_LEFT_CONTROL;
            
            return TRUE;
        }
              
        case SCAN_CODE_RIGHT_CONTROL:
        {
            shift_state |= KEYBOARD_RIGHT_CONTROL;
            
            return TRUE;
        }
    }    
    
    return FALSE;
}

static bool update_shift_state_after_release (uint8_t scancode)
{
    switch (scancode)
    {
        case SCAN_CODE_LEFT_SHIFT:
        {
            shift_state &= ~KEYBOARD_LEFT_SHIFT;
            
            return TRUE;
        }
          
        case SCAN_CODE_RIGHT_SHIFT:
        {
            shift_state &= ~KEYBOARD_RIGHT_SHIFT;
            
            return TRUE;
        }
          
        case SCAN_CODE_LEFT_ALT:
        {
            shift_state |= KEYBOARD_LEFT_ALT;
            
            return TRUE;
        }
              
        case SCAN_CODE_RIGHT_ALT:
        {
            shift_state &= ~KEYBOARD_RIGHT_ALT;
            
            return TRUE;
        }

        case SCAN_CODE_LEFT_CONTROL:
        {
            shift_state |= KEYBOARD_LEFT_CONTROL;
            
            return TRUE;
        }
          
        case SCAN_CODE_RIGHT_CONTROL:
        {
            shift_state &= ~KEYBOARD_RIGHT_CONTROL;
            
            return TRUE;
        }
    }              
    
    return FALSE;
}

/* Handle a keyboard event. This function is called from the interrupt
   handler. */

void keyboard_handle_event (uint8_t scancode)
{
    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
        L"%S: %s (%u).",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        scancode);
        
    keyboard_exists = TRUE;

    if (!do_acknowledge (scancode))
    {
        return;
    }    
    {
        wchar_t translated_key;
        keyboard_event_data_t keyboard_packet;

        memory_clear (&keyboard_packet, sizeof (keyboard_event_data_t));

#if defined (KEYBOARD_SAFE_IRQ_HANDLER)
        /* Special case -- this one is sent to us when the keyboard is
           reset from an external device (like a keyboard/monitor
           switch). It is also sent when right shift is released. What a
           sick world this is... */

        if (scancode == 170)
        {
            keyboard_update_leds ();
            keyboard_set_repeat_rate ();
        }
#endif

        if ((scancode & 0x80) == 0) 
        {
            DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
                L"%S: %s: Key pressed\n",
                DEBUG_MODULE_NAME, __FUNCTION__);

            /* A key was pressed. */
            keyboard_packet.key_pressed = TRUE;
      
            keyboard_pressed_keys[scancode / 8] |= (1 << (scancode % 8));
      
            if (!update_key_locks (scancode) && 
                !update_shift_state_after_press (scancode))
            {
                /* Seems to be a normal keypress. */
                
                /* Convert it to the chaos format. */

                translated_key = translate_key (scancode);
                
                if (translated_key == L'\0')
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
            }
        }
        else
        {
            DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
                L"%S: %s: Key released\n",
                DEBUG_MODULE_NAME, __FUNCTION__);
                
            /* A key was released. Start by masking away the highest bit and
               update the keyboard_pressed_keys structure. */
            keyboard_packet.key_pressed = FALSE;

            scancode &= 0x7F;
            keyboard_pressed_keys[scancode / 8] &= (~(1 << (scancode % 8)));

            if (!update_shift_state_after_release (scancode))
            {
                /* Anything else will be E-lectric. */

                translated_key = translate_key (scancode);
          
                /* If the key couldn't be translated, translate it in our own 
                   way. */
            
                if (translated_key == L'\0')
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
            }
        }
    
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

        DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE, 
            L"%S: Character: [%c]\n", 
            DEBUG_MODULE_NAME,
            (char) keyboard_packet.character);  
                
        /* Send the key to the receiver. */

        interface_fire_keyboard_event (&keyboard_packet);
    }
}       

/* Initialise the keyboard. */

const char *keyboard_init (void)
{
    int status;

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
        L"%S: %s ()\n",
        DEBUG_MODULE_NAME, __FUNCTION__);

    /* Test the keyboard interface. This seems to be the only way to get
       it going.  If the test is successful a x55 is placed in the
       input buffer. */

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
        L"%S: %s: Self test...\n",
        DEBUG_MODULE_NAME, __FUNCTION__);

    controller_write_command_word (CONTROLLER_COMMAND_SELF_TEST);
    
    if (controller_wait_for_input () != 0x55)
    {
        return "Keyboard failed self test.";
    }

    /* Perform a keyboard interface test.  This causes the controller
       to test the keyboard clock and data lines.  The results of the
       test are placed in the input buffer. */

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
        L"%S: %s: Interface test...\n",
        DEBUG_MODULE_NAME, __FUNCTION__);

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
        CONTROLLER_MODE_SYS | CONTROLLER_MODE_DISABLE_MOUSE | 
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

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
        L"%S: %s: Done\n",
        DEBUG_MODULE_NAME, __FUNCTION__);
  
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
    memory_clear (&keyboard_pressed_keys, sizeof (keyboard_pressed_keys));
}

