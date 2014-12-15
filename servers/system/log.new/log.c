/* $Id: log.c,v 1.4 2000/10/12 22:18:40 plundis Exp $ */
/* Abstract: Log server for chaos. This server's purpose is to collect
             debug and/or warnings from servers and from the
             kernel. */
/* Author: Per Lundberg <plundis@chaosdev.org>
           Henrik Hallin <hal@chaosdev.org> */
/*
  Changes: Vladimir Sorokin
*/

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
#include "log.h"

static console_structure_type console_structure_server;
static console_structure_type console_structure_kernel;

#define TITLE_FOREGROUND CONSOLE_COLOUR_GRAY
#define TITLE_BACKGROUND CONSOLE_COLOUR_RED
#define TITLE_ATTRIBUTE CONSOLE_ATTRIBUTE_BRIGHT

#define SELECT_FOREGROUND CONSOLE_COLOUR_GRAY
#define SELECT_BACKGROUND CONSOLE_COLOUR_BLUE
#define SELECT_ATTRIBUTE CONSOLE_ATTRIBUTE_BRIGHT

#define VERTICAL_RESOLUTION 50-10
#define HORIZONTAL_RESOLUTION 80

/* FIXME: This is ugly, but it really should not be exported. */

#define LOG_URGENCY_KERNEL (LOG_URGENCY_DEBUG + 1)

int urgency_colour[][3] =
{
  [LOG_URGENCY_EMERGENCY] =   { CONSOLE_COLOUR_GRAY,
                                CONSOLE_COLOUR_BLACK,
                                CONSOLE_ATTRIBUTE_BRIGHT },
  [LOG_URGENCY_ERROR] =       { CONSOLE_COLOUR_GRAY, 
                                CONSOLE_COLOUR_BLACK,
                                CONSOLE_ATTRIBUTE_BRIGHT },
  [LOG_URGENCY_WARNING] =     { CONSOLE_COLOUR_GRAY,
                                CONSOLE_COLOUR_BLACK,
                                CONSOLE_ATTRIBUTE_RESET },
  [LOG_URGENCY_INFORMATIVE] = { CONSOLE_COLOUR_GRAY,
                                CONSOLE_COLOUR_BLACK,
                                CONSOLE_ATTRIBUTE_RESET },
  [LOG_URGENCY_DEBUG] =       { CONSOLE_COLOUR_GRAY,
                                CONSOLE_COLOUR_BLACK,
                                CONSOLE_ATTRIBUTE_RESET },
  [LOG_URGENCY_KERNEL] =      { CONSOLE_COLOUR_GRAY,
                                CONSOLE_COLOUR_BLACK,
                                CONSOLE_ATTRIBUTE_RESET }
};

bool urgency_accept[] =
{
  [LOG_URGENCY_EMERGENCY] 	= TRUE,
  [LOG_URGENCY_ERROR] 		= TRUE,
  [LOG_URGENCY_WARNING] 	= TRUE,
  [LOG_URGENCY_INFORMATIVE] 	= TRUE,
  [LOG_URGENCY_DEBUG] 		= TRUE,
  [LOG_URGENCY_KERNEL] 		= TRUE
};

/* An empty tag list. */

tag_type empty_tag =
{
  0, 0, ""
};

internal_log_structure_type server_log_structure;
internal_log_structure_type kernel_log_structure;

char server_title[] = " " PACKAGE_NAME " version " PACKAGE_VERSION " server console.";
char kernel_title[] = " " PACKAGE_NAME " version " PACKAGE_VERSION " kernel console.";

/* Add a message to the log. Low-level function called from the
   wrappers. */

static void fill_structure(internal_log_structure_type* internal_log_structure,
  ipc_log_print_type *ipc_log_print)
{
  kernelfs_time_type kernelfs_time;
  log_record_type* log_record;

  memory_allocate((void**)&log_record,sizeof(log_record_type));

  kernelfs_time.kernelfs_class = KERNELFS_CLASS_TIME_READ;
  system_call_kernelfs_entry_read (&kernelfs_time);

  log_record->number 	= internal_log_structure->log_counter;
  log_record->hours 	= time_to_hours (kernelfs_time.time);
  log_record->minutes 	= time_to_minutes (kernelfs_time.time);
  log_record->seconds 	= time_to_seconds (kernelfs_time.time);
  
  log_record->urgency = ipc_log_print->urgency;
  string_copy(log_record->sender_name,ipc_log_print->log_class);
  string_copy(log_record->message,ipc_log_print->message);

  internal_log_structure->last_list_element = add_after(
    internal_log_structure->last_list_element, (void*)log_record);
  
  if(internal_log_structure->first_list_element == NULL)  
  {
    internal_log_structure->first_list_element = 
      internal_log_structure->last_list_element;
  }
  
  if(internal_log_structure->page_list_element == NULL)  
  {
    internal_log_structure->page_list_element = 
      internal_log_structure->last_list_element;
  }

  if( ((list_structure_type*)internal_log_structure->last_list_element->previous) 
    == internal_log_structure->current_list_element)
  {
    internal_log_structure->current_list_element =
      internal_log_structure->last_list_element;
  }

  if((internal_log_structure->log_counter - ((log_record_type *)
    (internal_log_structure->page_list_element->data))->number) > (VERTICAL_RESOLUTION - 10) )
  {
    (list_structure_type*)internal_log_structure->page_list_element = 
      (list_structure_type*)internal_log_structure->page_list_element->next;
  }
}

static void update_view (internal_log_structure_type* internal_log_structure)
{
  console_structure_type* console = internal_log_structure->console;
  char* title = internal_log_structure->title;
  unsigned int line_number = 0;

  log_record_type* current_log;

  list_structure_type* current_element = 
    internal_log_structure->page_list_element; 

  console_clear(console);

  console_attribute_set (console,
                         TITLE_FOREGROUND,
                         TITLE_BACKGROUND,
                         TITLE_ATTRIBUTE);

  console_print_formatted (console, "%s - [messages:%u]", 
			     title,internal_log_structure->log_counter);
  console_attribute_set (console,
                          CONSOLE_COLOUR_GRAY,
                          CONSOLE_COLOUR_BLACK,
                          CONSOLE_ATTRIBUTE_RESET);

  line_number++;
        
  while( (current_element != NULL) && (line_number < VERTICAL_RESOLUTION ) )
  {
    current_log = (log_record_type*)current_element->data;

    /* Print the log message with correct attributes. */

    if(current_element == internal_log_structure->current_list_element)
    {
      console_attribute_set (console,
                             SELECT_FOREGROUND,
                             SELECT_BACKGROUND,
                             SELECT_ATTRIBUTE);

      console_print(console, "*");
    }
    else
    {
      console_attribute_set (console,
                             urgency_colour[current_log->urgency][0],
                             urgency_colour[current_log->urgency][1],
                             urgency_colour[current_log->urgency][2]);

      console_print(console, " ");
    }
    console_print_formatted (console, "%03u [%02u:%02u:%02u]:[%s]->%s ",
    current_log->number,current_log->hours,current_log->minutes,
    current_log->seconds,current_log->sender_name,current_log->message);

    /* Go to next line (with correct colour). */
    console_attribute_set (console,
                           CONSOLE_COLOUR_GRAY,
                           CONSOLE_COLOUR_BLACK,
                           CONSOLE_ATTRIBUTE_RESET);
    console_print (console, "\n");
    current_element = (list_structure_type*)current_element->next;
    line_number+= (19 + string_length(current_log->sender_name) + 
      string_length(current_log->message)) / HORIZONTAL_RESOLUTION + 1;
  }
}

static void log_add (internal_log_structure_type* internal_log_structure,
                     ipc_log_print_type *ipc_log_print)
{

  list_structure_type* page_list_element =
    internal_log_structure->page_list_element;

  internal_log_structure->log_counter++;

  fill_structure(internal_log_structure, ipc_log_print);
  
  if(internal_log_structure->page_list_element == NULL)
  {
    update_view(internal_log_structure);
  }
  else if( ((internal_log_structure->log_counter - ((log_record_type *)(page_list_element->data))->number) 
         < (VERTICAL_RESOLUTION - 10 )) && (urgency_accept[ipc_log_print->urgency]))
  {
    update_view(internal_log_structure);
  }
 
}

static void keyboard_handler (internal_log_structure_type* 
    internal_log_structure)
{
  keyboard_packet_type keyboard_packet;
  int event_type;
  
  unsigned int page_top = ((log_record_type*) ((list_structure_type*)internal_log_structure->page_list_element)->data)->number;
  list_structure_type* current_element = 
  (list_structure_type*)internal_log_structure->current_list_element;

  if(current_element == NULL)
  {
    return;
  }

  console_event_wait (internal_log_structure->console, &keyboard_packet, 
    &event_type, TRUE);

  if (event_type == CONSOLE_EVENT_KEYBOARD && keyboard_packet.key_pressed
    && keyboard_packet.has_special_key)
  {
    switch(keyboard_packet.special_key)
    {
      case IPC_KEYBOARD_SPECIAL_KEY_ARROW_UP:

        if(current_element->previous != NULL)
	{
	  internal_log_structure->current_list_element = 
	    (list_structure_type*)current_element->previous;

	  if( current_element == internal_log_structure->page_list_element )
	  {
            internal_log_structure->page_list_element = 
            (list_structure_type*)internal_log_structure->page_list_element->previous;
	  }
	  update_view(internal_log_structure);
	}

        break;
      
      case IPC_KEYBOARD_SPECIAL_KEY_ARROW_DOWN:
      
        if(current_element->next != NULL)
	{
	  internal_log_structure->current_list_element = 
	    (list_structure_type*)current_element->next;

	  if( (page_top + VERTICAL_RESOLUTION) < 
	    ((log_record_type*)current_element->data)->number)
	  {
            internal_log_structure->page_list_element = 
            (list_structure_type*)internal_log_structure->page_list_element->next;
	  }
	  update_view(internal_log_structure);
	}

        break;
      
      case IPC_KEYBOARD_SPECIAL_KEY_DELETE:
      
	internal_log_structure->current_list_element =  
	  (list_structure_type*)internal_log_structure->current_list_element->previous;
	
	delete_after(internal_log_structure->current_list_element);

	internal_log_structure->log_counter--;

        update_view(internal_log_structure);

        break;

      default:      
    }
  }
}

/* Handle an IPC connection request. */

static void handle_connection (mailbox_id_type reply_mailbox_id)
{
  message_parameter_type message_parameter;
  ipc_structure_type ipc_structure;
  bool done = FALSE;
  u32 *data;
  unsigned int data_size = 1024;

  if (system_thread_create () == SYSTEM_RETURN_THREAD_NEW)
  {
    system_thread_name_set ("keyboard handler");

    while (TRUE)
    {
      keyboard_handler(&server_log_structure);
    }      
  }


  memory_allocate ((void **) &data, data_size);

  /* Accept the connection. */ 

  ipc_structure.output_mailbox_id = reply_mailbox_id;
  ipc_connection_establish (&ipc_structure);

  message_parameter.data = data;
  message_parameter.block = TRUE;

  while (!done)
  {
    message_parameter.protocol = IPC_PROTOCOL_LOG;
    message_parameter.message_class = IPC_CLASS_NONE;
    message_parameter.length = data_size;
    
    if (ipc_receive (ipc_structure.input_mailbox_id, &message_parameter,
                     &data_size) != IPC_RETURN_SUCCESS)
    {
      continue;
    }
    
    switch (message_parameter.message_class)
    {
      case IPC_LOG_PRINT:
      {
        ipc_log_print_type *ipc_log_print = (ipc_log_print_type *) data;

        log_add (&server_log_structure,ipc_log_print);
	
        break;
      }
    }
  }
}

return_type main (void)
{
  ipc_structure_type ipc_structure;

  /* Initialise the memory library. */

  memory_init ();

  /* Set our name. */

  system_process_name_set (PACKAGE_NAME);

  /* Unblock any servers that may be waiting after us. FIXME: This
     should be done later than this to eliminate unecessary
     waiting. */

  system_call_process_parent_unblock ();

  /* Create another thread to handle the server logging. */

  if (system_thread_create () == SYSTEM_RETURN_THREAD_OLD)
  {
    /* Open a new console for the log. */
  
    if (console_init (&console_structure_server, &empty_tag,
                      IPC_CONSOLE_CONNECTION_CLASS_CLIENT) !=
        CONSOLE_RETURN_SUCCESS)
    {
      system_call_debug_print_simple ("Couldn't connect to console service.");
      return -1;
    }
    
    if (ipc_service_create ("log", &ipc_structure, 
                            &empty_tag) != IPC_RETURN_SUCCESS)
    {
      system_call_debug_print_simple ("Couldn't create log service.");
    }
    
    if (console_open (&console_structure_server, 80, 50, 4,
                      VIDEO_MODE_TYPE_TEXT) != 
        CONSOLE_RETURN_SUCCESS)
    {
      system_call_debug_print_simple ("Failed to open a console.");
      return -1;
    }

    console_use_keyboard (&console_structure_server, TRUE, CONSOLE_KEYBOARD_NORMAL);

    console_clear (&console_structure_server);

    init_internal_log_structure(&server_log_structure,&console_structure_server,
	server_title);

    /* Print the titlebar. */

    update_view(&server_log_structure);    
    /* Main loop. */
    
    system_thread_name_set ("Service handler");
    
    while (TRUE)
    {
      mailbox_id_type reply_mailbox_id;
      
      ipc_service_connection_wait (&ipc_structure);
      reply_mailbox_id = ipc_structure.output_mailbox_id;
      
      if (system_thread_create () == SYSTEM_RETURN_THREAD_NEW)
      {
        system_thread_name_set ("Handling connection");
        handle_connection (reply_mailbox_id);
      }
    }    

  }

  /* Kernel log handling thread. */

  else
  {
    kernelfs_log_type kernelfs_log;
    ipc_log_print_type *ipc_log_print;

    memory_allocate ((void **) &ipc_log_print, 1000);
    
    kernelfs_log.block = TRUE;
    kernelfs_log.kernelfs_class = KERNELFS_CLASS_LOG_READ;
    kernelfs_log.max_string_length = 1000;
    kernelfs_log.string = ipc_log_print->message;

    ipc_log_print->urgency = LOG_URGENCY_KERNEL;
    string_copy (ipc_log_print->log_class, "storm");

    system_thread_name_set ("Kernel log handler");

    /* Open a new console for the log. */
  
    if (console_init (&console_structure_kernel, &empty_tag,
                      IPC_CONSOLE_CONNECTION_CLASS_CLIENT) !=
        CONSOLE_RETURN_SUCCESS)
    {
      system_call_debug_print_simple ("Couldn't connect to console service.");
      return -1;
    }
    
    if (console_open (&console_structure_kernel, 80, 50, 4, VIDEO_MODE_TYPE_TEXT) != 
        CONSOLE_RETURN_SUCCESS)
    {
      system_call_debug_print_simple ("Failed to open a console.");
      return -1;
    }

    console_use_keyboard (&console_structure_kernel, TRUE, CONSOLE_KEYBOARD_NORMAL);

    console_clear (&console_structure_kernel);

    init_internal_log_structure(&kernel_log_structure,&console_structure_kernel,
	kernel_title);

    /* Print the titlebar. */

    update_view(&kernel_log_structure);    

    while (TRUE)
    {
      system_call_kernelfs_entry_read (&kernelfs_log);

      log_add (&kernel_log_structure,ipc_log_print);
    }    
  }
}
