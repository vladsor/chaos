/* $Id: kernelfs.c,v 1.1.1.1 2000/09/26 19:08:14 plundis Exp $ */
/* Abstract: Kernelfs file system server. */
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

#include "kernelfs.h"

static log_structure_type log_structure;

/* An empty tag list. */

static tag_type empty_tag =
{
  0, 0, ""
};

static kernelfs_entry_type kernelfs[] __attribute__ ((unused)) =
{
  { FILE_ENTRY_TYPE_DIRECTORY, "thread",  KERNELFS_CLASS_THREAD_INFO },
  { FILE_ENTRY_TYPE_DIRECTORY, "process", KERNELFS_CLASS_PROCESS_INFO },
  { FILE_ENTRY_TYPE_FILE,      "uptime",  KERNELFS_CLASS_UPTIME_INFO },
  { FILE_ENTRY_TYPE_FILE,      "memory",  KERNELFS_CLASS_MEMORY_INFO },
  { FILE_ENTRY_TYPE_DIRECTORY, "cpu",     KERNELFS_CLASS_CPU_INFO },
  { FILE_ENTRY_TYPE_FILE,      "storm",   KERNELFS_CLASS_STORM_INFO },
  { FILE_ENTRY_TYPE_FILE,      "video",   KERNELFS_CLASS_VIDEO_INFO },
  { FILE_ENTRY_TYPE_FILE,      "self",    KERNELFS_CLASS_SELF_INFO },
  { FILE_ENTRY_TYPE_FILE,      "port",    KERNELFS_CLASS_PORT_INFO },
  { FILE_ENTRY_TYPE_FILE,      "irq",     KERNELFS_CLASS_IRQ_INFO },
};

#define KERNELFS_ENTRIES (sizeof (kernelfs) / sizeof (kernelfs_entry_type))

/* Handle an IPC connection request. */

static void handle_connection (mailbox_id_type reply_mailbox_id)
{
  message_parameter_type message_parameter;
  bool done = FALSE;
  bool mounted = FALSE;
  ipc_structure_type ipc_structure;
  u8 *data;
  unsigned int data_size = 16384;

  memory_allocate ((void **) &data, data_size);

  /* Accept the connection. */ 

  ipc_structure.output_mailbox_id = reply_mailbox_id;
  if (ipc_connection_establish (&ipc_structure) != IPC_RETURN_SUCCESS)
  {
    return;
  }

  message_parameter.block = TRUE;

  while (!done)
  {
    message_parameter.data = data;
    message_parameter.protocol = IPC_PROTOCOL_FILE_SYSTEM;
    message_parameter.message_class = IPC_CLASS_NONE;
    message_parameter.length = data_size;
    
    if (ipc_receive (ipc_structure.input_mailbox_id, &message_parameter, 
                     &data_size) != IPC_RETURN_SUCCESS)
    {
      continue;
    }
    
    switch (message_parameter.message_class)
    {
      /* Read one or more directory entries. */

      case IPC_FILE_SYSTEM_DIRECTORY_ENTRY_READ:
      {
        if (mounted)
        {
          file_directory_entry_read_type *directory_entry_read = 
            (file_directory_entry_read_type *) data;
          
          /* TODO: Write the code. */
          
          directory_entry_read->entries = 0;
          message_parameter.length =
            sizeof (file_directory_entry_read_type) +
            sizeof (file_directory_entry_type) *
            directory_entry_read->entries ;
          ipc_send (ipc_structure.output_mailbox_id, &message_parameter);
        }
        break;
      }

      case IPC_FILE_SYSTEM_FILE_GET_INFO:
      {
        if (mounted)
        {
#if FALSE
          unsigned int input_index;
          unsigned int output_index = 0;
          unsigned int max_entries = directory_entry_read->entries;
          
          directory_entry_read->entries = 0;
          
          for (input_index = directory_entry_read->start_entry;
               input_index < (directory_entry_read->start_entry + max_entries) &&
                 input_index < KERNELFS_ENTRIES; input_index++)
          {
            string_copy 
              (directory_entry_read->entry[output_index].name,
               kernelfs[input_index].name);
            directory_entry_read->entry[output_index].type = 
              kernelfs[input_index].type;
            directory_entry_read->entries++;
            output_index++;
          }
          
          if (input_index == KERNELFS_ENTRIES)
          {
            directory_entry_read->end_reached = TRUE;
          }
          else
          {
            directory_entry_read->end_reached = FALSE;
          }
          
          message_parameter.data = &return_value;
          message_parameter.length = sizeof (return_type);

          ipc_send (ipc_structure.output_mailbox_id, &message_parameter);
#endif
        }
        break;
      }

      case IPC_FILE_SYSTEM_MOUNT:
      {
        mounted = TRUE;

        break;
      }

      /* Unsupported functions. */

      case IPC_FILE_SYSTEM_FILE_OPEN:
        
        /* FIXME: For READ, we first create a buffer, fills it with
           the content of the 'file' and then pass the requested part
           of the file to the caller. */

      case IPC_FILE_SYSTEM_FILE_READ:
      case IPC_FILE_SYSTEM_FILE_CLOSE:
      case IPC_FILE_SYSTEM_FILE_SEEK:
      case IPC_FILE_SYSTEM_FILE_WRITE:
      case IPC_FILE_SYSTEM_ACL_READ:
      case IPC_FILE_SYSTEM_ACL_WRITE:
      case IPC_FILE_SYSTEM_UNMOUNT:
      default:
      {
        return_type return_value = IPC_RETURN_FILE_SYSTEM_FUNCTION_UNSUPPORTED;

        message_parameter.data = &return_value;
        message_parameter.length = sizeof (return_type);

        ipc_send (ipc_structure.output_mailbox_id, &message_parameter);
        break;
      }
    }
  }
}

int main (void)
{
  ipc_structure_type ipc_structure;

  system_process_name_set (PACKAGE_NAME);
  system_thread_name_set ("Initialising");
  
  if (log_init (&log_structure, PACKAGE_NAME, &empty_tag) !=
      LOG_RETURN_SUCCESS)
  {
    return -1;
  }
    
  /* Create our service. */

  if (ipc_service_create ("file_system", &ipc_structure, &empty_tag) != 
      STORM_RETURN_SUCCESS)
  {
    log_print (&log_structure, LOG_URGENCY_EMERGENCY,
               "Couldn't create a file system service.");
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
      system_thread_name_set ("Handling connection");
      handle_connection (reply_mailbox_id);
      return 0;
    }
  }    

}
