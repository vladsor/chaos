/* Abstract: Providers keyboard and mouse for clients. */
/* Author: Vladimir Sorokin */

/* Copyright 2000 chaos development. */

/* This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
   USA. */

#include "config.h"
#include "console.h"
#include "console_output.h"

static void switch_to_next_console(void *parameter);
static void bind_console_to(void *parameter);
static void switch_console_to(void *parameter);
static void shutdown(void *parameter);

static inline int memory_compare
  (void *memory1, void *memory2, unsigned int size)
{
  register int eax;
  int esi, edi, ecx;

  asm volatile
  ("\
    cld
1:  decl %3
    js 2f
    lodsb
    scasb
    jne 3f
    jmp 1b
2:  xorl %%eax, %%eax
    jmp 4f
3:  sbbl %%eax, %%eax
    orb $1, %%al
4:
"
   : "=a" (eax), "=&S" (esi), "=&D" (edi), "=&c" (ecx)
   : "1" (memory1), "2" (memory2), "3" (size));

  return eax;
}

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

hot_key_record_type table_of_hot_keys[] = 
{
 /* Left Alt + TAB -> switch to next console */
 { 
   { FALSE, TRUE, TRUE, FALSE, FALSE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, 
     FALSE, IPC_KEYBOARD_SPECIAL_KEY_TAB, { 0, 0, 0, 0, 0, 0 },
   },
   switch_to_next_console, NULL,
   "Switch to next console",
 },
 /* Right Alt + TAB -> switch to next console */
 {
   { FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, TRUE, FALSE, FALSE, FALSE, FALSE, 
     FALSE, IPC_KEYBOARD_SPECIAL_KEY_TAB, { 0, 0, 0, 0, 0, 0 },
   },
   switch_to_next_console, NULL,
   "Switch to next console",
 },

 /* Left Alt + Left Control + Delete -> shutdown computer */
 {
   { FALSE, TRUE, TRUE, FALSE, FALSE, TRUE, FALSE, TRUE, FALSE, FALSE, FALSE, 
     FALSE, IPC_KEYBOARD_SPECIAL_KEY_DELETE, { 0, 0, 0, 0, 0, 0 },
   },
   shutdown, NULL,
   "Shutdown computer",
 },
 /* Right Alt + Right Control + Delete -> shutdown computer */
 {
   { FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, TRUE, FALSE, TRUE, FALSE, FALSE, 
     FALSE, IPC_KEYBOARD_SPECIAL_KEY_DELETE, { 0, 0, 0, 0, 0, 0 },
   },
   shutdown, NULL,
   "Shutdown computer",
 },

 /* Left Alt + F1 -> switch to 1 console */
 { 
   { FALSE, TRUE, TRUE, FALSE, FALSE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, 
     FALSE, IPC_KEYBOARD_SPECIAL_KEY_F1, { 0, 0, 0, 0, 0, 0 },
   },
   switch_console_to, (void *)1,
   "Switch to first console",
 },
 /* Right Alt + F1 -> switch to 1 console */
 {
   { FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, TRUE, FALSE, FALSE, FALSE, FALSE, 
     FALSE, IPC_KEYBOARD_SPECIAL_KEY_F1, { 0, 0, 0, 0, 0, 0 },
   },
   switch_console_to, (void *)1,
   "Switch to first console",
 },

 /* Left Alt + F2 -> switch to 2 console */
 { 
   { FALSE, TRUE, TRUE, FALSE, FALSE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, 
     FALSE, IPC_KEYBOARD_SPECIAL_KEY_F2, { 0, 0, 0, 0, 0, 0 },
   },
   switch_console_to, (void *)2,
   "Switch to second console",
 },
 /* Right Alt + F2 -> switch to 2 console */
 {
   { FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, TRUE, FALSE, FALSE, FALSE, FALSE, 
     FALSE, IPC_KEYBOARD_SPECIAL_KEY_F2, { 0, 0, 0, 0, 0, 0 },
   },
   switch_console_to, (void *)2,
   "Switch to second console",
 },

 /* Left Alt + F3 -> switch to 3 console */
 { 
   { FALSE, TRUE, TRUE, FALSE, FALSE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, 
     FALSE, IPC_KEYBOARD_SPECIAL_KEY_F3, { 0, 0, 0, 0, 0, 0 },
   },
   switch_console_to, (void *)3,
   "Switch to third console",
 },
 /* Right Alt + F3 -> switch to 3 console */
 {
   { FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, TRUE, FALSE, FALSE, FALSE, FALSE, 
     FALSE, IPC_KEYBOARD_SPECIAL_KEY_F3, { 0, 0, 0, 0, 0, 0 },
   },
   switch_console_to, (void *)3,
   "Switch to third console",
 },

 /* Left Alt + Left Control + F3 -> bind console to 3 */
 { 
   { FALSE, TRUE, TRUE, FALSE, FALSE, TRUE, FALSE, TRUE, FALSE, FALSE, FALSE, 
     FALSE, IPC_KEYBOARD_SPECIAL_KEY_F3, { 0, 0, 0, 0, 0, 0 },
   },
   bind_console_to, (void *)3,
   "Bind current console to third",
 },
 /* Right Alt + Right Control + F3 -> bind console to 3 */
 {
   { FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, TRUE, FALSE, TRUE, FALSE, FALSE, 
     FALSE, IPC_KEYBOARD_SPECIAL_KEY_F3, { 0, 0, 0, 0, 0, 0 },
   },
   bind_console_to, (void *)3,
   "Bind current console to third",
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
                                  sizeof (hot_key_record_type);

static bool hot_key_search(keyboard_packet_type *keyboard_packet)
{
  unsigned int i;
  
  for( i = 0 ; i < number_of_hot_keys ; i++ )
  {
    if( !memory_compare((void *)&table_of_hot_keys[i], (void *)keyboard_packet, 
                        sizeof(keyboard_packet_type)) && 
         (table_of_hot_keys[i].hot_key_function != NULL) )
    {
      table_of_hot_keys[i].hot_key_function(table_of_hot_keys[i].parameter);
      return TRUE;
    }
  }
  return FALSE;
}

void connection_provider_keyboard
  (message_parameter_type *message_parameter)
{
  switch (message_parameter->message_class)
  {
    case IPC_CONSOLE_KEYBOARD_EVENT:
    {
      keyboard_packet_type *keyboard_packet = (keyboard_packet_type *)
        message_parameter->data;
            
      if (current_console != NULL)
      {
        hot_key_search(keyboard_packet);
	              
        /* Send on... If we are allowed to. */
              
        if (current_console->active_application != NULL)
        {
          if (current_console->active_application->wants_keyboard)
          {

            message_parameter->block = FALSE;
            message_parameter->protocol = IPC_PROTOCOL_CONSOLE;
            message_parameter->message_class = IPC_CONSOLE_KEYBOARD_EVENT;
            message_parameter->length = sizeof (keyboard_packet_type);
            ipc_send (current_console->active_application->ipc_structure.output_mailbox_id,
                      message_parameter);

          }
        }
        else if (current_console->active_application == NULL)
        {
          /* console: Something is broken. A mutex will fix this! */
        }
      }        
    }
                
    default:
    {
      break;
    }
  }
}

/* Hot key functions */

static void switch_to_next_console(void *parameter __attribute__ ((unused)) )
{
  console_type *new_console = (console_type *) current_console->next;

  if (new_console == NULL)
  {
    new_console = console_list;
  }
                
  if (new_console != current_console)
  {
    /* FIXME: This is not purely correct, but what the
       heck... finish library_semaphore sometime, will
       you? */
            
    while (new_console->lock == TRUE)
    {
      system_call_dispatch_next ();
    }
            
    new_console->lock = TRUE;
    console_flip (new_console);
    new_console->lock = FALSE;
  }
}

static void bind_console_to(void *parameter)
{
  int console_index = (int)parameter;
  
  if( (console_index < 1) || (console_index > 10))
  {
    return;
  }
  console_shortcut[console_index - 1] = current_console;
}

static void switch_console_to(void *parameter)
{
  int console_index = (int)parameter;
  console_type *new_console;
  
  if( (console_index < 1) || (console_index > 10))
  {
    return;
  }

  /* New console. */
                
  new_console = (console_type *)console_shortcut[console_index - 1];

  if (new_console != NULL)
  {
    /* FIXME: This is not purely correct, but what the
       heck... finish library_semaphore sometime, will you? */
                  
    while (new_console->lock == TRUE)
    {
      system_call_dispatch_next ();
    }
                  
    new_console->lock = TRUE;
    console_flip (new_console);
    new_console->lock = FALSE;
  }
}

static void shutdown(void *parameter __attribute__ ((unused)) )
{
  system_call_thread_control (THREAD_ID_KERNEL, THREAD_TERMINATE, 0);
}

#if SCROLL
static void scroll_screen(void *parameter)
{
  int lines = (int)parameter;
  if (current_console->scrollable)
  {
    console_scroll (current_console, lines);
  }
}
#endif

void connection_provider_mouse
  (message_parameter_type *message_parameter)
{

  switch (message_parameter->message_class)
  {
    case IPC_MOUSE_EVENT:
    {
      if (current_console->mouse_cursor_visibility)
      {
//        system_call_debug_print_simple ("console: mouse event\n");
	mouse_cursor_update ( current_console->width, current_console->height, 
	  current_console->mouse_cursor_visibility, 
	  (ipc_mouse_event_type *)message_parameter->data );
      }
      
      if (current_console->active_application != NULL)
      {
        if (current_console->active_application->wants_mouse)
        {
          message_parameter->block = FALSE;
          message_parameter->protocol = IPC_PROTOCOL_CONSOLE;
          message_parameter->message_class = IPC_CONSOLE_MOUSE_EVENT;
          message_parameter->length = sizeof (ipc_mouse_event_type);
          ipc_send (current_console->active_application->ipc_structure.output_mailbox_id,
                    message_parameter);
        }
      }
    }
    
    default:
    {
      break;
    }
  }
}
