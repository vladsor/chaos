/* $Id: connection.c,v 1.4 2000/10/22 21:38:16 plundis Exp $ */
/* Abstract: Connection handling in the land of Oz. */
/* Author: Per Lundberg <plundis@chaosdev.org> */

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

static void connection_client
  (message_parameter_type *message_parameter, console_type **our_console, 
   console_application_type **our_application, u32 *data, 
   ipc_structure_type *ipc_structure)
{
  switch (message_parameter->message_class)
  {
    /* Output text to this console, no matter what mode we are
       in. */
    
    case IPC_CONSOLE_OUTPUT:
    {
      if (*our_console != NULL && has_video)
      {
        /* This is not purely correct, but it's better than
           nothing... */
        /* FIXME: library_semaphore. */
        
        while ((*our_console)->lock == TRUE)
        {
          system_call_dispatch_next ();
        }
        
        (*our_console)->lock = TRUE;
        console_output (*our_console, (u8 *) message_parameter->data);
        (*our_console)->lock = FALSE;
      }
      
      break;
    }

    case IPC_CONSOLE_OUTPUT_AT:
    {
      if (*our_console != NULL && has_video)
      {
        int x, y;
        /* This is not purely correct, but it's better than
           nothing... */
        /* FIXME: library_semaphore. */
        
        while ((*our_console)->lock == TRUE)
        {
          system_call_dispatch_next ();
        }
        x = *(int *)(message_parameter->data);
	y = *((int *) message_parameter->data + 1);

        if (x >= 0 && x < (*our_console)->width &&
	    y >= 0 && y < (*our_console)->height)
	{
          (*our_console)->lock = TRUE;
          console_output_at (*our_console, x, y,
	  (char *) message_parameter->data + 2 * sizeof (int) / sizeof (char));
          (*our_console)->lock = FALSE;
	}
      }
      break;
    }
    case IPC_CONSOLE_ENABLE_SCROLL:
    {
      (*our_console)->scrollable = TRUE;      
      break;
    }
    case IPC_CONSOLE_DISABLE_SCROLL:
    {
      (*our_console)->scrollable = FALSE;
      break;
    }

    case IPC_CONSOLE_KEYBOARD_CURSOR_SET:
    {
      keyboard_cursor_set (*our_console, *((bool *)message_parameter->data));
      break;
    }

    case IPC_CONSOLE_MOUSE_CURSOR_SET:
    {
      if ( (*our_console)->mouse_cursor_visibility != 
           *((bool *)message_parameter->data))
      {
        (*our_console)->mouse_cursor_visibility = 
           *((bool *)message_parameter->data);
        mouse_cursor_draw ( (*our_console)->width, (*our_console)->height, 
	                     *((bool *)message_parameter->data));
      }
      break;
    }
    
    case IPC_CONSOLE_GET_HOT_KEYS_AMOUNT:
    {
      message_parameter_type reply_message;
      
      reply_message.protocol = IPC_PROTOCOL_CONSOLE;
      reply_message.data = &number_of_hot_keys;
      reply_message.length = sizeof (unsigned int);
      reply_message.block = TRUE;
      ipc_send (ipc_structure->output_mailbox_id, &reply_message);
      
      break;
    }
    
    case IPC_CONSOLE_GET_HOT_KEYS_INFO:
    {
      message_parameter_type reply_message;
      
      reply_message.protocol = IPC_PROTOCOL_CONSOLE;

      memory_allocate ( (void **)&reply_message.data, number_of_hot_keys * 
                       sizeof (hot_key_record_type));
      memory_copy (reply_message.data, table_of_hot_keys, number_of_hot_keys * 
                   sizeof (hot_key_record_type));
      reply_message.length =  number_of_hot_keys * sizeof (hot_key_record_type);
      reply_message.block = TRUE;

      ipc_send (ipc_structure->output_mailbox_id, &reply_message);
      break;
    }
    
    case IPC_CONSOLE_KEYBOARD_EXTENDED:
    {
      (*our_application)->keyboard_type = CONSOLE_KEYBOARD_EXTENDED;
      break;
    }
    
    case IPC_CONSOLE_KEYBOARD_NORMAL:
    {
      (*our_application)->keyboard_type = CONSOLE_KEYBOARD_NORMAL;
      break;
    }
    
    case IPC_CONSOLE_ENABLE_KEYBOARD:
    {
      (*our_application)->wants_keyboard = TRUE;
      break;
    }
    
    case IPC_CONSOLE_DISABLE_KEYBOARD:
    {
      (*our_application)->wants_keyboard = FALSE;
      break;
    }
    
    case IPC_CONSOLE_ENABLE_MOUSE:
    {
      (*our_application)->wants_mouse = TRUE;
      break;
    }
    
    case IPC_CONSOLE_DISABLE_MOUSE:
    {
      (*our_application)->wants_mouse = FALSE;
      break;
    }
    
    /* Open a new console with the requested attributes. */
    
    case IPC_CONSOLE_OPEN:
    {
      ipc_console_attribute_type *console_attribute =
        (ipc_console_attribute_type *) data;
      video_mode_type video_mode;

//      system_call_debug_print_simple ("console: opening console\n");
      
      if (*our_console == NULL)
      {
        memory_allocate ((void **) our_console, sizeof (console_type));
        
        /* Fill in some required stuff. */
        
        (*our_console)->width = console_attribute->width;
        (*our_console)->height = console_attribute->height;
        (*our_console)->depth = console_attribute->depth;
        (*our_console)->type = console_attribute->mode_type;
        
        (*our_console)->cursor_x = 0;
        (*our_console)->cursor_y = 0;
        
        (*our_console)->cursor_saved_x = -1;
        (*our_console)->cursor_saved_y = -1;

        (*our_console)->keyboard_cursor_visibility = TRUE;
        (*our_console)->mouse_cursor_visibility = FALSE;

        (*our_console)->scrollable = FALSE;
        
        (*our_console)->state = CONSOLE_STATE_CHARACTER;
        (*our_console)->numeric_argument_index = 0;
        
        (*our_console)->current_attribute = CONSOLE_DEFAULT_ATTRIBUTE;
        
        /* Allocate memory for a buffer for this console. */
        
        if ((*our_console)->type == VIDEO_MODE_TYPE_TEXT)
        {
          memory_allocate ((void **) &((*our_console)->buffer),
                           (*our_console)->width *
                           (*our_console)->height *
                           sizeof (character_type));
        }
        else
        {
          memory_allocate ((void **) &((*our_console)->buffer),
                           (*our_console)->width *
                           (*our_console)->height *
                           (*our_console)->depth);
        }
        
        (*our_console)->output = (*our_console)->buffer;
        (*our_console)->lock = FALSE;
        
        (*our_console)->application_list = *our_application;
        (*our_console)->active_application = *our_application;
        
        (*our_application)->next = NULL;
        
        (*our_application)->ipc_structure.input_mailbox_id = 
          ipc_structure->input_mailbox_id;
        (*our_application)->ipc_structure.output_mailbox_id =
          ipc_structure->output_mailbox_id;
        
        /* Is this the first console? If so, activate it. */
        
        if (current_console == NULL)
        {
          current_console = *our_console;
          (*our_console)->output = screen;
          
          if (has_video)
          {
            /* Try to set the requested video mode. */
            /* FIXME: Error handling and return values! */
            
            video_mode.width = console_attribute->width;
            video_mode.height = console_attribute->height;
            video_mode.depth = console_attribute->depth;
            video_mode.mode_type = console_attribute->mode_type;
                        
            if (video_mode_set (&video_structure,
                                &video_mode) != VIDEO_RETURN_SUCCESS)
            {
              /* FIXME: Fail and return here. */
            }
          }else
	  {

	  }
        }
        
        console_link (*our_console);
        
        /* We have added a new console. */
        
        number_of_consoles++;
      }
      
      break;
    }
    
    /* Change the video mode for this console. */
    
    case IPC_CONSOLE_MODE_SET:
    {
      video_mode_type video_mode;
      ipc_console_attribute_type *console_attribute =
        (ipc_console_attribute_type *) data;
      
      video_mode.width = console_attribute->width;
      video_mode.height = console_attribute->height;
      video_mode.depth = console_attribute->depth;
      video_mode.mode_type = console_attribute->mode_type;
      
      if (video_mode_set (&video_structure, 
                          &video_mode) != VIDEO_RETURN_SUCCESS)
      {
        /* FIXME: Fail and return here. */
      }
      else
      {
        (*our_console)->width = console_attribute->width;
        (*our_console)->height = console_attribute->height;
        (*our_console)->depth = console_attribute->depth;
        (*our_console)->type = console_attribute->mode_type;
        
        (*our_console)->cursor_x = 0;
        (*our_console)->cursor_y = 0;
        
        (*our_console)->cursor_saved_x = -1;
        (*our_console)->cursor_saved_y = -1;
      }
      
      break;
    }
    
    /* Resize the console (character rows and columns), but do nothing
       to the mode of the console. */
    
    case IPC_CONSOLE_RESIZE:
    {
#if FALSE
      /* FIXME: Most of this is wrong. */
      
      video_mode_type video_mode;
      ipc_console_resize_type *ipc_console_resize =
        (ipc_console_resize_type *) data;
      
      if (our_console != NULL)
      {
        video_mode.width = ipc_console_resize->width;
        video_mode.height = ipc_console_resize->height;
        video_mode.depth = 4;
        video_mode.mode_type = VIDEO_MODE_TYPE_TEXT;
        
        if (video_mode_set (&video_mode) == VIDEO_RETURN_SUCCESS)
        {
          our_console->width = ipc_console_resize->width;
          our_console->height = ipc_console_resize->height;
        }            
        
        /* FIXME: Return something. */
      }
#endif
      break;
    }
  }
}

/* Handle an IPC connection request. */

void handle_connection (mailbox_id_type reply_mailbox_id)
{
  u32 *data;
  message_parameter_type message_parameter;
  ipc_structure_type ipc_structure;
  bool done = FALSE;
  unsigned int connection_class = IPC_CONSOLE_CONNECTION_CLASS_NONE;
  console_type *our_console = NULL;
  console_application_type *our_application = NULL;
  unsigned int data_size = 4096;

  memory_allocate ((void **) &data, data_size);
  memory_allocate ((void **) &our_application,
                   sizeof (console_application_type));

  /* Accept the connection. */ 

  ipc_structure.output_mailbox_id = reply_mailbox_id;
  ipc_connection_establish (&ipc_structure);

  message_parameter.data = data;

  while (!done)
  {
    message_parameter.protocol = IPC_PROTOCOL_CONSOLE;
    message_parameter.message_class = IPC_CLASS_NONE;
    message_parameter.length = data_size;
    message_parameter.block = TRUE;
  
    if (ipc_receive (ipc_structure.input_mailbox_id, &message_parameter,
                     &data_size) != IPC_RETURN_SUCCESS)
    {
      continue;
    }
    
    switch (connection_class)
    {
      case IPC_CONSOLE_CONNECTION_CLASS_NONE:
      {
        if (message_parameter.message_class ==
            IPC_CONSOLE_CONNECTION_CLASS_SET)
        {
          connection_class = *((unsigned int *) message_parameter.data);

          if (connection_class == IPC_CONSOLE_CONNECTION_CLASS_PROVIDER_VIDEO)
          {
            has_video = TRUE;

            video_structure.output_mailbox_id = 
              ipc_structure.output_mailbox_id;
            video_structure.input_mailbox_id =
              ipc_structure.input_mailbox_id;
          }
        }

        break;
      }

      case IPC_CONSOLE_CONNECTION_CLASS_CLIENT:
      {
        connection_client (&message_parameter, &our_console, &our_application,
                           data, &ipc_structure);
        break;
      }

      /* A keyboard provider has something for us. */
      
      case IPC_CONSOLE_CONNECTION_CLASS_PROVIDER_KEYBOARD:
      {
        system_thread_name_set ("Handling keyboard");        
        connection_provider_keyboard (&message_parameter);
        break;
      }
        
      case IPC_CONSOLE_CONNECTION_CLASS_PROVIDER_MOUSE:
      {
        system_thread_name_set ("Handling mouse");        
        connection_provider_mouse (&message_parameter);
        break;
      }
      
      case IPC_CONSOLE_CONNECTION_CLASS_PROVIDER_JOYSTICK:
      {
        break;
      }
      
      case IPC_CONSOLE_CONNECTION_CLASS_PROVIDER_VIDEO:
      {
        //        connection_provider_video (&message_parameter);
        break;
      }

      break;
    }
  }
}

