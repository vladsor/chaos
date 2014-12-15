/* Abstract: CD-ROM drive server. */
/* Authors: Vladimir Sorokin */

/* Copyright 1999-2000 chaos development. */

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
#include "cd-rom.h"
#include "atapi.h"

/* Define as TRUE if you are debugging this server. */

#define DEBUG TRUE

static ipc_block_info_type ipc_block_info =
{
  1000,
  1000,
  
  /* Writable. */

  FALSE,

  /* Readable. */

  TRUE,
  
  /* Label. */

  "CD-ROM " PACKAGE_VERSION
};

log_structure_type log_structure;

static tag_type empty_tag = 
{
  0, 0, "" 
};

/* Handle an IPC connection request. */

static void cdrom_handle_connection (mailbox_id_type reply_mailbox_id)
{
  message_parameter_type message_parameter;
  ipc_structure_type ipc_structure;
  bool done = FALSE;
  bool tray_locked = FALSE;
  u32 *data;
  unsigned int data_size = 1024;

  memory_allocate ((void **) &data, data_size);

  /* Accept the connection. */ 

  ipc_structure.output_mailbox_id = reply_mailbox_id;
  ipc_connection_establish (&ipc_structure);

  message_parameter.block = TRUE;

  while (!done)
  {
    message_parameter.protocol = IPC_PROTOCOL_BLOCK;
    message_parameter.message_class = IPC_CLASS_NONE;
    message_parameter.length = data_size;
    message_parameter.data = data;
  
    if (ipc_receive (ipc_structure.input_mailbox_id, &message_parameter,
                     &data_size) != IPC_RETURN_SUCCESS)
    {
      continue;
    }
    
    switch (message_parameter.message_class)
    {
      case IPC_BLOCK_READ:
      {
        ipc_block_read_type *ipc_block_read = (ipc_block_read_type *) data;

        /* Do some boundary checking. */
        
        if (ipc_block_read->start_block_number +
            ipc_block_read->number_of_blocks > ipc_block_info.number_of_blocks)
        {
          /* FIXME: Should we do the error handling in some other way? */

          message_parameter.data = NULL;
          message_parameter.length = 0;
          log_print (&log_structure, LOG_URGENCY_ERROR,
                     "Tried to read out of range.");
        }
        else
        {
#ifdef DEBUG
          log_print_formatted (&log_structure, LOG_URGENCY_DEBUG,
                               "Reading blocks %u-%u data.", 
                               ipc_block_read->start_block_number,
                               ipc_block_read->start_block_number +
                               ipc_block_read->number_of_blocks);
#endif
#if TRUE
          read_block (cdrom_device, ipc_block_read->start_block_number,
	    message_parameter.data, ipc_block_read->number_of_blocks);
          message_parameter.length = ipc_block_read->number_of_blocks;
#endif
        }
        message_parameter.block = TRUE;
        
        ipc_send (ipc_structure.output_mailbox_id, &message_parameter);
	
        break;
      }
      
      case IPC_BLOCK_WRITE:
      {
        break;
      }
      
      case IPC_BLOCK_GET_INFO:
      {
        message_parameter.data = &ipc_block_info;
        message_parameter.length = sizeof (ipc_block_info_type);
        ipc_send (ipc_structure.output_mailbox_id, &message_parameter);
	
	break;
      }
      case IPC_BLOCK_CONTROL:
      {
        unsigned int command = *((unsigned int *) data);
	bool return_value = FALSE;
#ifdef DEBUG
        log_print_formatted (&log_structure, LOG_URGENCY_DEBUG,
                             "Control CD-ROM: %u.", command);
#endif
	switch (command)
	{
	  case 0:
	  {
	    return_value = exec_ATAPI_command (cdrom_device, 0, packet_eject_tray, NULL, 0);

	    break;
	  }
	  case 1:
	  {
	    return_value = exec_ATAPI_command (cdrom_device, 0, packet_close_tray, NULL, 0);
	    break;
	  }
	  case 2:
	  {
	    if (!tray_locked)
	    {
	      return_value = exec_ATAPI_command (cdrom_device, 0, packet_lock_tray, NULL, 0);
	    }
	    else
	    {
	      return_value = exec_ATAPI_command (cdrom_device, 0, packet_unlock_tray, NULL, 0);
	    }
            tray_locked = !tray_locked;
	    break;
	  }
	}
#ifdef DEBUG
        if (return_value)
	{
          log_print (&log_structure, LOG_URGENCY_DEBUG, "Control CD-ROM OK ");
	}
	else
	{
          log_print (&log_structure, LOG_URGENCY_DEBUG, "Control CD-ROM Fail");
	}
#endif	
        break;
      }
    }
  }
}

/* Main function. */

int main (void)
{
  ipc_structure_type ipc_structure;

  /* Set the name of the server. */

  system_process_name_set (PACKAGE_NAME);
  system_thread_name_set ("Initialising");

  log_init (&log_structure, PACKAGE_NAME, &empty_tag);

  if (!init())
  {
    log_print (&log_structure, LOG_URGENCY_EMERGENCY,
               "Couldn't find CD-ROM.");
    return -1;
  }

  if (exec_ATAPI_command (cdrom_device, 1, Info12, (void*)&Info12Buf, 
      sizeof(Info12Buf)))
  {
    log_print_formatted (&log_structure, LOG_URGENCY_EMERGENCY,
                         "Manuf: [%8.8s], Prod: [%16.16s], Rev: [%4.4s]",
			Info12Buf.Manuf,
			Info12Buf.Prod,
			Info12Buf.Rev);
  }
  
  /* Create the service. */

  if (ipc_service_create ("cdrom", &ipc_structure, &empty_tag) != 
      IPC_RETURN_SUCCESS)
  {
    log_print (&log_structure, LOG_URGENCY_EMERGENCY,
               "Couldn't create block service.");
    return -1;
  }

  system_call_process_parent_unblock ();

  /* Main loop. */

  system_thread_name_set ("Service handler");
  while (TRUE)
  {
    mailbox_id_type reply_mailbox_id;

    ipc_service_connection_wait (&ipc_structure);
    reply_mailbox_id = ipc_structure.output_mailbox_id;

    if (system_thread_create () == SYSTEM_RETURN_THREAD_NEW)
    {
      system_call_thread_name_set ("Handling connection");
      cdrom_handle_connection (reply_mailbox_id);
    }
  }    
}
