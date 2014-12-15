/* Abstract: Providers keyboard and mouse for clients. */
/* Author: Vladimir Sorokin */

/* Copyright 2000 chaos development. */

#include <enviroment.h>
#include <memory_inlines.h>
#include <string.h>

#include "console.h"
#include "console_output.h"

#include <Classes/stream_channel.h>

#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL 11
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

static void switch_to_next_console (void *parameter);
static void bind_console_to (void *parameter);
static void switch_console_to (void *parameter);
static void shutdown (void *parameter);
static void switch_keyboard_map_to_next (void *parameter);

/*
typedef struct
{
  bool has_character_code;
  bool has_special_key;
  bool key_pressed;
  bool left_shift_down;
  bool right_shift_down;
  bool left_alt_down;
  bool right_alt_down;
  bool left_control_down;
  bool right_control_down;
  bool left_windows_down;
  bool right_windows_down;
  bool task_list_down;
  u32 special_key;
  u8 character_code[6];
} keyboard_packet_type;
*/

hot_key_record_t table_of_hot_keys[] = 
{
 /* Left Alt + TAB -> switch to next console */
 { 
   { TRUE, FALSE, TRUE, FALSE, FALSE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, 
     FALSE, 0, 'q',
   },
   switch_to_next_console, NULL,
   "Switch to next console",
 },

 /* Left Alt + TAB -> switch to next console */
 { 
   { FALSE, TRUE, TRUE, FALSE, FALSE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, 
     FALSE, IPC_KEYBOARD_SPECIAL_KEY_TAB, L'\0',
   },
   switch_to_next_console, NULL,
   "Switch to next console",
 },
 /* Right Alt + TAB -> switch to next console */
 {
   { FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, TRUE, FALSE, FALSE, FALSE, FALSE, 
     FALSE, IPC_KEYBOARD_SPECIAL_KEY_TAB, L'\0',
   },
   switch_to_next_console, NULL,
   "Switch to next console",
 },

 /* Left Alt + Left Control + Delete -> shutdown computer */
 {
   { FALSE, TRUE, TRUE, FALSE, FALSE, TRUE, FALSE, TRUE, FALSE, FALSE, FALSE, 
     FALSE, IPC_KEYBOARD_SPECIAL_KEY_DELETE, L'\0',
   },
   shutdown, NULL,
   "Shutdown computer",
 },
 /* Right Alt + Right Control + Delete -> shutdown computer */
 {
   { FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, TRUE, FALSE, TRUE, FALSE, FALSE, 
     FALSE, IPC_KEYBOARD_SPECIAL_KEY_DELETE, L'\0',
   },
   shutdown, NULL,
   "Shutdown computer",
 },

 /* Left Alt + F1 -> switch to 1 console */
 { 
   { FALSE, TRUE, TRUE, FALSE, FALSE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, 
     FALSE, IPC_KEYBOARD_SPECIAL_KEY_F1, L'\0',
   },
   switch_console_to, (void *)1,
   "Switch to first console",
 },
 /* Right Alt + F1 -> switch to 1 console */
 {
   { FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, TRUE, FALSE, FALSE, FALSE, FALSE, 
     FALSE, IPC_KEYBOARD_SPECIAL_KEY_F1, L'\0',
   },
   switch_console_to, (void *)1,
   "Switch to first console",
 },

 /* Left Alt + F2 -> switch to 2 console */
 { 
   { FALSE, TRUE, TRUE, FALSE, FALSE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, 
     FALSE, IPC_KEYBOARD_SPECIAL_KEY_F2, L'\0',
   },
   switch_console_to, (void *)2,
   "Switch to second console",
 },
 /* Right Alt + F2 -> switch to 2 console */
 {
   { FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, TRUE, FALSE, FALSE, FALSE, FALSE, 
     FALSE, IPC_KEYBOARD_SPECIAL_KEY_F2, L'\0',
   },
   switch_console_to, (void *)2,
   "Switch to second console",
 },

 /* Left Alt + F3 -> switch to 3 console */
 { 
   { FALSE, TRUE, TRUE, FALSE, FALSE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, 
     FALSE, IPC_KEYBOARD_SPECIAL_KEY_F3, L'\0',
   },
   switch_console_to, (void *)3,
   "Switch to third console",
 },
 /* Right Alt + F3 -> switch to 3 console */
 {
   { FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, TRUE, FALSE, FALSE, FALSE, FALSE, 
     FALSE, IPC_KEYBOARD_SPECIAL_KEY_F3, L'\0',
   },
   switch_console_to, (void *)3,
   "Switch to third console",
 },

 /* Left Alt + Left Control + F3 -> bind console to 3 */
 { 
   { FALSE, TRUE, TRUE, FALSE, FALSE, TRUE, FALSE, TRUE, FALSE, FALSE, FALSE, 
     FALSE, IPC_KEYBOARD_SPECIAL_KEY_F3, L'\0',
   },
   bind_console_to, (void *)3,
   "Bind current console to third",
 },
 /* Right Alt + Right Control + F3 -> bind console to 3 */
 {
   { FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, TRUE, FALSE, TRUE, FALSE, FALSE, 
     FALSE, IPC_KEYBOARD_SPECIAL_KEY_F3, L'\0',
   },
   bind_console_to, (void *)3,
   "Bind current console to third",
 },
 /* Right Control + Right Shift -> switch keyboard map to next */
 {
   { FALSE, FALSE, FALSE, FALSE, TRUE, FALSE, FALSE, FALSE, TRUE, FALSE, FALSE,
     FALSE, 0, L'\0',
   },
   switch_keyboard_map_to_next, NULL,
   "Switch keyboard map to next",
 },

#if SCROLL
 /* Left Shift + Arrow Up -> scroll screen up */
 { 
   { FALSE, TRUE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, 
     FALSE, IPC_KEYBOARD_SPECIAL_KEY_ARROW_UP, { 0, 0, 0, 0, 0, 0 },
   },
   scroll_screen, (void*)1,
 },
 /* Left Shift + Arrow Down -> scroll screen down */
 { 
   { FALSE, TRUE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, 
     FALSE, IPC_KEYBOARD_SPECIAL_KEY_ARROW_DOWN, { 0, 0, 0, 0, 0, 0 },
   },
   scroll_screen, (void*)-1,
 },
#endif
 /* #FIXME: add more hotkeys */ 
 
};
unsigned int number_of_hot_keys = sizeof (table_of_hot_keys) / 
                                  sizeof (hot_key_record_t);

static bool hot_key_search (keyboard_packet_t *keyboard_packet)
{
    unsigned int i;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
        "%s::%s (%p)\n",
        __FILE__, __FUNCTION__, keyboard_packet);
  
    for (i = 0; i < number_of_hot_keys; i++)
    {
        int res;
        int j;
        keyboard_packet_t *template = &(table_of_hot_keys[i].keyboard_packet);
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
            "Original: ");
        for (j=0;j<sizeof (keyboard_packet_t);j++)
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1, "%2.2X", 
                ((uint8_t *) keyboard_packet)[j]);
        }
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
            ".\nTemplate: ");
        for (j=0;j<sizeof (keyboard_packet_t);j++)
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1, "%2.2X", 
                ((uint8_t *) template)[j]);
        }
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
            "\n.");
        
//        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
//            "%s::%s Comparing %p [%u]...",
//            __FILE__, __FUNCTION__, 
//            &(table_of_hot_keys[i].keyboard_packet), i);
                
        res = memory_compare ((void *) &(table_of_hot_keys[i].keyboard_packet), 
                (void *) keyboard_packet, sizeof (keyboard_packet_t));

//        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
//            "%i.\n", res);
                
        if ((res != 0) && (table_of_hot_keys[i].hot_key_function != NULL))
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
                "%s::%s Function is %p.\n",
                __FILE__, __FUNCTION__, 
                table_of_hot_keys[i].hot_key_function);

            table_of_hot_keys[i].hot_key_function (
                table_of_hot_keys[i].parameter);
                
            return TRUE;
        }
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
        "%s::%s Not a hot key.\n",
        __FILE__, __FUNCTION__);
    
    return FALSE;
}

return_t console_keyboard_handler (keyboard_packet_t *keyboard_packet)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
        "%s::%s (%p)\n",
        __FILE__, __FUNCTION__, keyboard_packet);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
        "%s::%s Current console: %p\n",
        __FILE__, __FUNCTION__, current_console);

    if (hot_key_search (keyboard_packet))
    {
        return 0;
    }
            
    if (current_console != NULL)
    {
        if (current_console->wants_keyboard)
        {
            if (keyboard_packet->key_pressed)
            {
                char buffer[1];
                handle_t *buffhandl = &(current_console->okeyboard_buffer);
                
                if (keyboard_packet->has_character_code)
                {
                    buffer[0] = (char) keyboard_packet->character;
                    output_stream$write (buffhandl, buffer, 1);
                }
                else if (keyboard_packet->has_special_key)
                {
                    if (keyboard_packet->special_key == 
                        IPC_KEYBOARD_SPECIAL_KEY_ENTER)
                    {
                        buffer[0] = '\n';
                        output_stream$write (buffhandl, buffer, 1);
                    }
                }
            }
/*        
            if (!current_console->buffer_full)
            {
                current_console->keyboard_buffer[current_console->buffer_start]
                    = keyboard_packet->character_code[0];
                current_console->buffer_start++;
                current_console->buffer_start %= 20;
                
                if (current_console->buffer_start == 
                    current_console->buffer_end)
                {
                    current_console->buffer_full = TRUE;
                }
            }
*/            
        }
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
        "%s::%s Done\n",
        __FILE__, __FUNCTION__);
  
    return 0;
}

/* Hot key functions */

static void switch_to_next_console (void *parameter UNUSED)
{
    console_t *new_console; 

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s\n",
        __FILE__, __FUNCTION__);
  
    if (current_console == NULL)
    {
        return;
    }
    
    new_console = (console_t *) current_console->next;

    if (new_console == NULL)
    {
        new_console = console_list;
    }
                
    if (new_console != current_console)
    {
    /* FIXME: This is not purely correct, but what the
       heck... finish library_semaphore sometime, will
       you? */
/*            
    while (new_console->lock == TRUE)
    {
      system_call_dispatch_next ();
    }
*/            
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s new is %p\n",
        __FILE__, __FUNCTION__, new_console);
        
        new_console->lock = TRUE;
        console_flip (new_console);
        new_console->lock = FALSE;
    }
}

static void bind_console_to (void *parameter)
{
    int console_index = (int) parameter;
  
    if ((console_index < 1) || (console_index > 10))
    {
        return;
    }
    
    console_shortcut[console_index - 1] = current_console;
}

static void switch_console_to (void *parameter)
{
    int console_index = (int) parameter;
    console_t *new_console;
  
    if ((console_index < 1) || (console_index > 10))
    {
        return;
    }

    /* New console. */
                
    new_console = (console_t *) console_shortcut[console_index - 1];

    if (new_console != NULL)
    {
    /* FIXME: This is not purely correct, but what the
       heck... finish library_semaphore sometime, will you? */
/*                  
    while (new_console->lock == TRUE)
    {
      system_call_dispatch_next ();
    }
*/                  
        new_console->lock = TRUE;
        console_flip (new_console);
        new_console->lock = FALSE;
    }
}

static void shutdown (void *parameter UNUSED)
{
    cpu_halt (HALT_REBOOT);
//  system_call_thread_control (THREAD_ID_KERNEL, THREAD_TERMINATE, 0);
}

#if SCROLL
static void scroll_screen (void *parameter)
{
    int lines = (int) parameter;
    
    if ((current_console != NULL) && (current_console->scrollable)
)
    {
        console_scroll (current_console, lines);
    }
}
#endif

static void switch_keyboard_map_to_next (void *parameter UNUSED)
{
//    keyboard_switch_map_to_next ();
}

return_t console_mouse_handler (mouse_event_t *event)
{
    if (current_console->mouse_cursor_visibility)
    {
        mouse_cursor_update (current_console->width, current_console->height, 
            current_console->mouse_cursor_visibility, event);
    }
      
    if (current_console->wants_mouse)
    {

    }
    
    return 0;
}
