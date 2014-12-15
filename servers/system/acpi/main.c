/* Abstract: ACPI server. */
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
#include "acpi.h"

/* Define as TRUE if you are debugging this server. */

#define DEBUG TRUE

log_structure_type log_structure;
ipc_structure_type pci_structure;

static tag_type empty_tag = 
{
  0, 0, "" 
};

/* Handle an IPC connection request. */

static void handle_connection (mailbox_id_type reply_mailbox_id)
{
  message_parameter_type message_parameter;
  ipc_structure_type ipc_structure;
  bool done = FALSE;
  u32 *data;
  unsigned int data_size = 1024;

  memory_allocate ((void **) &data, data_size);

  /* Accept the connection. */ 

  ipc_structure.output_mailbox_id = reply_mailbox_id;
  ipc_connection_establish (&ipc_structure);

  message_parameter.block = TRUE;

  while (!done)
  {
    message_parameter.protocol = IPC_PROTOCOL_ACPI;
    message_parameter.message_class = IPC_CLASS_NONE;
    message_parameter.length = data_size;
    message_parameter.data = data;
  
    if (ipc_receive (ipc_structure.input_mailbox_id, &message_parameter,
                     &data_size) != IPC_RETURN_SUCCESS)
    {
      continue;
    }
/*    
    switch (message_parameter.message_class)
    {
    }
*/
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

  if (pci_init (&pci_structure, &empty_tag) != PCI_RETURN_SUCCESS)
  {
    log_print (&log_structure, LOG_URGENCY_EMERGENCY, 
               "Couldn't create connection to PCI service.");
    return -1;
  }

  acpi_init();  
  
  /* Create the service. */

  if (ipc_service_create ("acpi", &ipc_structure, &empty_tag) != 
      IPC_RETURN_SUCCESS)
  {
    log_print (&log_structure, LOG_URGENCY_EMERGENCY,
               "Couldn't create ACPI service.");
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
      handle_connection (reply_mailbox_id);
    }
  }    
}
