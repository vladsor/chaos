/* Abstract: Providers keyboard and mouse for clients. */
/* Author: Vladimir Sorokin */

/* Copyright 2000 chaos development. */

#include <enviroment.h>
#include <string.h>

#include "Include/console.h"
#include "Include/console_output.h"
#include "Include/interface.h"

#define DEBUG_MODULE_NAME L"Console"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL 11
#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#ifndef __STORM_KERNEL__
#   define DEBUG_SUPPLIER (console_debug_supplier)
#endif

#include <debug/macros.h>

static void switch_to_next_console (void *parameter);
static void bind_console_to (void *parameter);
static void switch_console_to (void *parameter);
static void shutdown (void *parameter);
static void switch_keyboard_map_to_next (void *parameter);

hot_key_record_t table_of_hot_keys[] = 
{
    /* Left Alt + TAB -> switch to next console */
    { 
        key: { 
            has_character_code: FALSE, 
            has_special_key: TRUE, 
            key_pressed: TRUE, 
            left_shift_down: FALSE, 
            right_shift_down: FALSE, 
            left_alt_down: TRUE, 
            right_alt_down: FALSE, 
            left_control_down: FALSE, 
            right_control_down: FALSE, 
            left_windows_down: FALSE, 
            right_windows_down: FALSE, 
            task_list_down: FALSE, 
            special_key: KEYBOARD_SPECIAL_KEY_TAB, 
            character: L'\0',
        },
        function: switch_to_next_console, 
        parameter: NULL,
        description: L"Switch to next console",
    },
    /* Right Alt + TAB -> switch to next console */
    {
        { 
            FALSE, 
            TRUE, 
            TRUE, 
            FALSE, FALSE, FALSE, TRUE, FALSE, FALSE, FALSE, FALSE, 
            FALSE, 
            KEYBOARD_SPECIAL_KEY_TAB, 
            L'\0',
        },
        switch_to_next_console, 
        NULL,
        L"Switch to next console",
    },

    /* Left Alt + Left Control + Delete -> shutdown computer */
    {
        { 
            FALSE, 
            TRUE, TRUE, FALSE, FALSE, TRUE, FALSE, TRUE, FALSE, FALSE, FALSE, 
            FALSE, 
            KEYBOARD_SPECIAL_KEY_DELETE, 
            L'\0',
        },
        shutdown, 
        NULL,
        L"Shutdown computer",
    },
    /* Right Alt + Right Control + Delete -> shutdown computer */
    {
        { 
            FALSE, 
            TRUE, 
            TRUE, FALSE, FALSE, FALSE, TRUE, FALSE, TRUE, FALSE, FALSE, 
            FALSE, 
            KEYBOARD_SPECIAL_KEY_DELETE, 
            L'\0',
        },
        shutdown, 
        NULL,
        L"Shutdown computer",
    },

    /* Left Alt + F1 -> switch to 1 console */
    { 
        { 
            FALSE, 
            TRUE, 
            TRUE, 
            FALSE, FALSE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, 
            FALSE, 
            KEYBOARD_SPECIAL_KEY_F1, 
            L'\0',
        },
        switch_console_to, 
        (void *) 1,
        L"Switch to first console",
    },
    /* Right Alt + F1 -> switch to 1 console */
    {
        { 
            FALSE, 
            TRUE, 
            TRUE, FALSE, FALSE, FALSE, TRUE, FALSE, FALSE, FALSE, FALSE, 
            FALSE, 
            KEYBOARD_SPECIAL_KEY_F1, 
            L'\0',
        },
        switch_console_to, 
        (void *)1,
        L"Switch to first console",
    },

    /* Left Alt + F2 -> switch to 2 console */
    { 
        { 
            FALSE, 
            TRUE, 
            TRUE, 
            FALSE, 
            FALSE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, 
            FALSE, 
            KEYBOARD_SPECIAL_KEY_F2, 
            L'\0',
        },
        switch_console_to, 
        (void *)2,
        L"Switch to second console",
    },
    /* Right Alt + F2 -> switch to 2 console */
    {
        { 
            FALSE, 
            TRUE, 
            TRUE, 
            FALSE, 
            FALSE, FALSE, TRUE, FALSE, FALSE, FALSE, FALSE, 
            FALSE, 
            KEYBOARD_SPECIAL_KEY_F2, 
            L'\0',
        },
        switch_console_to, 
        (void *)2,
        L"Switch to second console",
    },

    /* Left Alt + F3 -> switch to 3 console */
    { 
        { 
            FALSE, 
            TRUE, 
            TRUE, 
            FALSE, FALSE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, 
            FALSE, 
            KEYBOARD_SPECIAL_KEY_F3, 
            L'\0',
        },
        switch_console_to, 
        (void *)3,
        L"Switch to third console",
    },
    /* Right Alt + F3 -> switch to 3 console */
    {
        { 
            FALSE, 
            TRUE, 
            TRUE, 
            FALSE, FALSE, FALSE, TRUE, FALSE, FALSE, FALSE, FALSE, 
            FALSE, 
            KEYBOARD_SPECIAL_KEY_F3, 
            L'\0',
        },
        switch_console_to, 
        (void *)3,
        L"Switch to third console",
    },

    /* Left Alt + Left Control + F3 -> bind console to 3 */
    { 
        { 
            FALSE, 
            TRUE, 
            TRUE, 
            FALSE, FALSE, TRUE, FALSE, TRUE, FALSE, FALSE, FALSE, 
            FALSE, 
            KEYBOARD_SPECIAL_KEY_F3, 
            L'\0',
        },
        bind_console_to, 
        (void *)3,
        L"Bind current console to third",
    },
    /* Right Alt + Right Control + F3 -> bind console to 3 */
    {
        { 
            FALSE, 
            TRUE, 
            TRUE, 
            FALSE, FALSE, FALSE, TRUE, FALSE, TRUE, FALSE, FALSE, 
            FALSE, 
            KEYBOARD_SPECIAL_KEY_F3, 
            L'\0',
        },
        bind_console_to, 
        (void *)3,
        L"Bind current console to third",
    },
    /* Right Control + Right Shift -> switch keyboard map to next */
    {
        { 
            FALSE, 
            FALSE, 
            FALSE, FALSE, TRUE, FALSE, FALSE, FALSE, TRUE, FALSE, FALSE,
            FALSE, 
            0, 
            L'\0',
        },
        switch_keyboard_map_to_next, 
        NULL,
        L"Switch keyboard map to next",
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
 /** @todo add more hotkeys */ 
 
};

unsigned int number_of_hot_keys = sizeof (table_of_hot_keys) / 
    sizeof (hot_key_record_t);

static bool hot_key_search (p_keyboard_event_data_t keyboard_packet)
{
    unsigned int i;

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1,
        L"%S: %s (%p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        keyboard_packet);
  
    for (i = 0; i < number_of_hot_keys; i++)
    {
        bool is_equals;
        p_keyboard_event_data_t template = 
            &(table_of_hot_keys[i].key);
        p_hot_key_function_t function = table_of_hot_keys[i].function;
        
        is_equals = memory_compare ((p_void_t) template, 
                (p_void_t) keyboard_packet, sizeof (keyboard_event_data_t));

        if (is_equals && (function != NULL))
        {
            DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1,
                L"%S: %s Function is %p.\n",
                DEBUG_MODULE_NAME, __FUNCTION__, 
                function);

            function (table_of_hot_keys[i].parameter);
                
            return TRUE;
        }
    }

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1,
        L"%S: %s Not a hot key.\n",
        DEBUG_MODULE_NAME, __FUNCTION__);
    
    return FALSE;
}

void console_keyboard_handler (context_t context UNUSED, 
    p_keyboard_event_data_t keyboard_packet)
{
    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
        L"%S: %s (%p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        keyboard_packet);

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1,
        L"%S: %s Current console: %p, Char: %c {%u}\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        current_console, (char) keyboard_packet->character, 
        (uint32_t) keyboard_packet->character);

    if (hot_key_search (keyboard_packet))
    {
        return;
    }
            
    if (current_console == NULL)
    {
        return;
    }

    if (!current_console->wants_keyboard)
    {
        return;
    }    

    if (current_console->echo_enabled)
    {
        if (keyboard_packet->key_pressed)
        {
            wchar_t text[2] = {0,0};
                
            if (keyboard_packet->has_character_code)
            {
                text[0] = keyboard_packet->character;
                console_output ((console_t *) current_console, 
                    (const wchar_t *) text);
            }
            else if (keyboard_packet->has_special_key)
            {
                if (keyboard_packet->special_key == KEYBOARD_SPECIAL_KEY_ENTER)
                {
                    text[0] = L'\n';
                    console_output ((console_t *) current_console, 
                        (const wchar_t *) text);
                }    
                else if (keyboard_packet->special_key == 
                    KEYBOARD_SPECIAL_KEY_SPACE_BAR)
                {
                    text[0] = L' ';
                    console_output ((console_t *) current_console, 
                        (const wchar_t *) text);
                }
            }    
        }    
    }
        
    if (current_console->keyboard_count.value < (20 - 1))
    {
        memory_copy (&((console_t *) current_console)->keyboard_buffer[
            ((console_t *) current_console)->keyboard_buffer_head], 
            keyboard_packet,
            sizeof (keyboard_event_data_t));

        current_console->keyboard_buffer_head++;
        current_console->keyboard_buffer_head %= 20;
        
        count_up (&((console_t *) current_console)->keyboard_count);
    }
    
    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1,
        L"%S: %s Done\n",
        DEBUG_MODULE_NAME, __FUNCTION__);
  
    return;
}

/* Hot key functions */

static void switch_to_next_console (void *parameter UNUSED)
{
    console_t *new_console; 

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
        L"%S: %s ()\n",
        DEBUG_MODULE_NAME, __FUNCTION__);
  
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
    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
        L"%S: %s: new is %p\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        new_console);
        
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

void console_mouse_handler (context_t context UNUSED, uint32_t mouse_x, 
    uint32_t mouse_y, uint32_t mouse_button_state)
{
    if (current_console->mouse_cursor_visibility)
    {
        mouse_cursor_update (current_console->width, current_console->height, 
            current_console->mouse_cursor_visibility, mouse_x, mouse_y, 
            mouse_button_state);
    }
      
    if (current_console->wants_mouse)
    {

    }
}

