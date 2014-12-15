
#include "config.h"

static void hard_drive_handle_connection (ata_drive_type *ata_drive, 
                                          mailbox_id_type reply_mailbox_id)
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

        /* FIXME: Do some boundary checking. */
#ifdef DEBUG
        log_print_formatted (&log_structure, LOG_URGENCY_DEBUG,
                               "Reading blocks %u-%u data.", 
                               ipc_block_read->start_block_number,
                               ipc_block_read->start_block_number +
                               ipc_block_read->number_of_blocks);
#endif
        ata_read_block (ata_drive, ipc_block_read->start_block_number,
            message_parameter.data, ipc_block_read->number_of_blocks);
        message_parameter.length = ipc_block_read->number_of_blocks;
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
	break;
      }
    }
  }
}

static void create_hard_drive_service (ata_drive_type *ata_drive)
{
  /* Create the service. */

  if (ipc_service_create ("block", &ipc_structure, &empty_tag) != 
      IPC_RETURN_SUCCESS)
  {
    log_print (&log_structure, LOG_URGENCY_EMERGENCY,
               "Couldn't create block service.");
    return -1;
  }

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
      hard_drive_handle_connection (ata_drive, reply_mailbox_id);
    }
  }    
}

static void cdrom_handle_connection (ata_drive_type *ata_drive, 
                                     mailbox_id_type reply_mailbox_id)
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

        /* FIXME: Do some boundary checking. */
#ifdef DEBUG
        log_print_formatted (&log_structure, LOG_URGENCY_DEBUG,
                               "Reading blocks %u-%u data.", 
                               ipc_block_read->start_block_number,
                               ipc_block_read->start_block_number +
                               ipc_block_read->number_of_blocks);
#endif
        ata_read_block (ata_drive, ipc_block_read->start_block_number,
            message_parameter.data, ipc_block_read->number_of_blocks);
        message_parameter.length = ipc_block_read->number_of_blocks;
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
	break;
      }
    }
  }
}


static void create_cdrom_service (ata_drive_type *ata_drive)
{
  /* Create the service. */

  if (ipc_service_create ("block", &ipc_structure, &empty_tag) != 
      IPC_RETURN_SUCCESS)
  {
    log_print (&log_structure, LOG_URGENCY_EMERGENCY,
               "Couldn't create block service.");
    return -1;
  }

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
      cdrom_handle_connection (ata_drive, reply_mailbox_id);
    }
  }    
}

static bool register_ports (ata_drive_type *ata_drive)
{
  if (system_call_port_range_register (ata_drive->base_port, 8, "ATAPI") !=
       STORM_RETURN_SUCCESS)
  {
    log_print_formatted (&log_structure, LOG_URGENCY_EMERGENCY,
                         "Could not allocate port range %x-%x.",
                         ata_drive->base_port, ata_drive->base_port + 8);
    return FALSE;    
  }
  if (system_call_port_range_register (ata_drive->base_port + 0x206, 1, "ATAPI") 
     != STORM_RETURN_SUCCESS)
  {
    log_print_formatted (&log_structure, LOG_URGENCY_EMERGENCY,
                         "Could not allocate port range %x-%x.",
                         ata_drive->base_port + 0x206, ata_drive->base_port + 0x206);
    return FALSE;
  }

  return TRUE;
}

static bool unregister_ports (ata_drive_type ata_drive)
{
  system_call_port_range_unregister (ata_drive->base_port);
  system_call_port_range_unregister (ata_drive->base_port + 0x206);

  return TRUE;
}

ata_drive_type *ata_drives[4];
unsigned int number_of_drives = 0;

/* Main function. */

int main (void)
{
  ipc_structure_type ipc_structure;
  ata_drive_type *ata_drive;
  unsigned int drive_number;

  /* Set the name of the server. */

  system_process_name_set (PACKAGE_NAME);
  system_thread_name_set ("Initialising");

  log_init (&log_structure, PACKAGE_NAME, &empty_tag);

  for ( drive_number = 0 ; drive_number < number_of_probe ; drive_number++ )
  {
    if (!register_ports (ata_probe_drives[drive_number]))
    {
      continue;
    }

    ata_drive = ata_probe (ata_probe_drives[drive_number]);

    if (ata_drive != NULL)
    {
      switch (ata_drive->type)
      {
	case ATA_HARD_DRIVE :
        {
	  create_hard_drive_service (ata_drive);
          break;
        }

	case ATA_CDROM :
        {
	  create_cdrom_service (ata_drive);
          break;
        }
        /* FIXME: what we must do there ? */
        default :
        {
        }
      }
      ata_drivers[number_of_drives] = ata_drive;
      number_of_drives++;
    }
    else
    {
      unregister_ports (ata_probe_drives[drive_number]);
    }
  }

  system_call_process_parent_unblock ();
  return 0;
}
