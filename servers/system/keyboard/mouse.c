/* $Id: mouse.c,v 1.3 2000/10/16 17:06:48 plundis Exp $ */
/* Abstract: PS/2 mouse code for the keyboard server. */
/* Authors: Per Lundberg <plundis@chaosdev.org> 
            Henrik Hallin <hal@chaosdev.org> */

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
#include "common.h"
#include "controller.h"
#include "mouse.h"
#include "config.h"

/* Have we got a PS/2 mouse port? As of yet, we don't probe for the
   actual existance of a *mouse*, just the port. This makes
   hotswapping PS/2 mice easy. */

bool has_mouse = FALSE;

/* This buffer holds the mouse scan codes. The PS/2 protocol sends
   three characters for each event. */

static u8 mouse_buffer[3];
static int mouse_buffer_position = 0;

/* The number of mouse replies expected. */

static int mouse_replies_expected = 0;

/* Hold the state of the mouse somewhere. */

static mouse_type mouse;

/* The mailbox ID of our receiver, if any. */

static volatile mailbox_id_type mouse_target_mailbox_id = MAILBOX_ID_NONE;

/* Handler for the mouse IRQ. */

void mouse_irq_handler (void)
{
  system_thread_name_set ("Mouse IRQ handler");

  /* Register our IRQ. */

  if (system_call_irq_register (MOUSE_IRQ, "PS/2 controller")
      != STORM_RETURN_SUCCESS)
  {
    //    log_print (&log_structure, LOG_URGENCY_EMERGENCY,
    //         "Could not allocate IRQ.");
    return;
  }

  while (TRUE)
  {
    system_call_irq_wait (MOUSE_IRQ);
    handle_event ();
    system_call_irq_acknowledge (MOUSE_IRQ);
  }
}

/* Handle a mouse event. */

void mouse_handle_event (u8 scancode)
{
  if (mouse_replies_expected > 0) 
  {
    if (scancode == MOUSE_ACK) 
    {
      mouse_replies_expected--;
      return;
    }

    mouse_replies_expected = 0;
  }
  
  /* Add this scancode to the mouse event queue. */

  mouse_buffer[mouse_buffer_position] = scancode;
  mouse_buffer_position++;

  /* If the buffer is full, parse this event. */

  if (mouse_buffer_position == 3)
  {
    mouse_buffer_position = 0;

    mouse.button_state = mouse_buffer[0] & MOUSE_BUTTON_MASK;
    
    /* Some PS/2 mice send reports with negative bit set in data[0]
       and zero for movement.  I think this is a bug in the mouse, but
       working around it only causes artifacts when the actual report
       is -256; they'll be treated as zero. This should be rare if the
       mouse sampling rate is set to a reasonable value; the default
       of 100 Hz is plenty. (Stephen Tell) */
    
    /* Have the mouse moved horizontally? */

    if (mouse_buffer[1] == 0)
    {
      mouse.delta_x = 0;
    }
    else
    {
      mouse.delta_x = (mouse_buffer[0] & MOUSE_NEGATIVE_X) != 0 ?
        mouse_buffer[1] - 256 :
        mouse_buffer[1];
    }

    /* Or vertically? */
    
    if (mouse_buffer[2] == 0)
    {
      mouse.delta_y = 0;
    }
    else
    {
      mouse.delta_y = (mouse_buffer[0] & MOUSE_NEGATIVE_Y) != 0 ?
        mouse_buffer[2] - 256 :
        mouse_buffer[2];
    }

    mouse.x_divider +=  mouse.x_scale * mouse.delta_x;
    mouse.y_divider -=  mouse.y_scale * mouse.delta_y;

    /* Make sure we don't get Type'o Negative. */

    if (mouse.x_divider < 0)
    {
      mouse.x_divider = 0;
    }
    else if (mouse.x_divider >= 1000000)
    {
      mouse.x_divider = 1000000 - 1;
    }

    if (mouse.y_divider < 0)
    {
      mouse.y_divider = 0;
    }
    else if (mouse.y_divider >= 1000000)
    {
      mouse.y_divider = 1000000 - 1;
    }
    
    /* Should we pass this event on to someone? */

    if (mouse_target_mailbox_id != MAILBOX_ID_NONE)
    {
      message_parameter_type message_parameter;
      ipc_mouse_event_type ipc_mouse_event;
      
      ipc_mouse_event.x_divider = mouse.x_divider;
      ipc_mouse_event.y_divider = mouse.y_divider; 
      ipc_mouse_event.button = mouse.button_state;

      /* Send the key to the receiver. */
    
      message_parameter.protocol = IPC_PROTOCOL_CONSOLE;
      message_parameter.message_class = IPC_MOUSE_EVENT;
      message_parameter.block = FALSE;
      message_parameter.length = sizeof (ipc_mouse_event_type);
      message_parameter.data = &ipc_mouse_event;
      
      ipc_send (mouse_target_mailbox_id, &message_parameter);
    }

  }

}

/* Write a PS/2 mouse command. */

static void mouse_write_command (int command)
{
  controller_wait ();
  controller_write_command (CONTROLLER_COMMAND_WRITE_MODE);
  controller_wait ();
  controller_write_output (command);
}

/* Send a byte to the PS/2 mouse & handle returned ACK. */

static void mouse_write_ack (int value)
{
  controller_wait ();
  controller_write_command (CONTROLLER_COMMAND_WRITE_MOUSE);
  controller_wait ();
  controller_write_output (value);

  /* We expect an ACK in response. */

  mouse_replies_expected++;
  controller_wait ();
}
 
/* Check if this is a dual port controller. */

static bool detect_ps2_port(void)
{
  int loops;
  bool return_value = FALSE;
  
  /* Put the value 0x5A in the output buffer using the "Write
     Auxiliary Device Output Buffer" command (0xD3). Poll the Status
     Register for a while to see if the value really turns up in the
     Data Register. If the KEYBOARD_STATUS_MOUSE_OBF bit is also set to 1 in
     the Status Register, we assume this controller has an Auxiliary
     Port (a.k.a. Mouse Port). */

  controller_wait ();
  controller_write_command (CONTROLLER_COMMAND_WRITE_MOUSE_OUTPUT_BUFFER);
  
  controller_wait ();

  /* 0x5A is a random dummy value. */

  controller_write_output (0x5A);
  
  for (loops = 0; loops < 10;  loops++)
  {
    unsigned char status = controller_read_status();
    
    if ((status & CONTROLLER_STATUS_OUTPUT_BUFFER_FULL) != 0)
    {
      (void) controller_read_input ();
      if ((status & CONTROLLER_STATUS_MOUSE_OUTPUT_BUFFER_FULL) != 0)
      {
        return_value = TRUE;
      }
      break;
    }

    system_sleep (1);
  }
  
  return return_value;
}

/* Initialise the PS/2 mouse support. */

bool mouse_init (void)
{
  if (!detect_ps2_port ())
  {
    return FALSE;
  }  

  has_mouse = TRUE;
  
 /* Enable the PS/2 mouse port. */

  controller_write_command_word (CONTROLLER_COMMAND_MOUSE_ENABLE);

  /* Samples/sec. */

  mouse_write_ack (MOUSE_SET_SAMPLE_RATE);
  mouse_write_ack (MOUSE_SAMPLES_PER_SECOND);

  /* 8 counts per mm. */

  mouse_write_ack (MOUSE_SET_RESOLUTION);
  mouse_write_ack (3);

  /* 2:1 scaling */

  mouse_write_ack (MOUSE_SET_SCALE21);

  /* Enable the PS/2 device. */

  mouse_write_ack (MOUSE_ENABLE_DEVICE);

  /* Enable controller interrupts. */
  
  mouse_write_command (MOUSE_INTERRUPTS_ON);

  mouse.x_scale = 400;
  mouse.y_scale = 400;
    
  return TRUE;
}


/* Handle a connection request. */

static void handle_connection (ipc_structure_type *ipc_structure)
{
  bool done = FALSE;
//  message_parameter_type message_parameter;
//  u8 *data;
//  ipc_structure_type ipc_structure;
//  unsigned int data_size = 100;

//  memory_allocate ((void **) &data, data_size);

  mouse_target_mailbox_id = ipc_structure->output_mailbox_id;

  /* Accept the connection. */ 

//  ipc_structure.output_mailbox_id = reply_mailbox_id;
//  ipc_connection_establish (&ipc_structure);

  /* Main loop. The connection is up, so we just handle the packets we
     get in the way we should. */

  while (!done)
  {
#if 0
    message_parameter.protocol = IPC_PROTOCOL_MOUSE;
    message_parameter.message_class = IPC_CLASS_NONE;
    message_parameter.length = data_size;
    message_parameter.data = data;
    message_parameter.block = TRUE;

    if (ipc_receive (ipc_structure.input_mailbox_id, &message_parameter,
                     &data_size) != IPC_RETURN_SUCCESS)
    {
      continue;
    }

    switch (message_parameter.message_class)
    {
      /* Someone wants to register as a receiver. */

      case IPC_MOUSE_REGISTER_TARGET:
      {
        mouse_target_mailbox_id = ipc_structure.output_mailbox_id;
        break;
      }
      
      /* Unregister a receiver. */
      
      case IPC_MOUSE_UNREGISTER_TARGET:
      {
        mouse_target_mailbox_id = MAILBOX_ID_NONE;
        break;
      }
    }
#endif
  }
}

/* Main function for the mouse handling. */

bool mouse_main (void)
{
  console_structure_type console_structure;

  /* Establish a connection to the console service. */

  if (console_init (&console_structure, &empty_tag,
                    IPC_CONSOLE_CONNECTION_CLASS_PROVIDER_MOUSE) !=
      CONSOLE_RETURN_SUCCESS)
  {
    system_call_debug_print_simple ("connection to console break\n");
    return FALSE;
  }

  /* Main loop. */
  system_thread_name_set ("Handling connection to mouse");

  handle_connection (&console_structure.ipc_structure);

  return TRUE;
}
