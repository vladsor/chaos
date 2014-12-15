#include "config.h"
#include "fat.h"
#include "mount.h"
#include "cache.h"
#include "structs.h"
#include "file.h"
#include "directory.h"

#include "return_values.h"

#define DEBUG TRUE

log_structure_type log_structure;
static tag_type empty_tag =
{
  0, 0, ""
};

/* Handle an IPC connection request. */

static void handle_connection (ipc_structure_type *ipc_structure)
{
  message_parameter_type message_parameter;
  file_mount_type mount = { "fat0" };
  mailbox_id_type mailbox_id[10];
  unsigned int services = 10;
  bool done = FALSE;
  bool mounted = FALSE;
//  fat_info_type fat_info;
  u8 *data;
  unsigned int data_size = 16384;
  device_type device;
  static bool has_fat = FALSE;
  return_type return_value;
  static vfat_volume_type vfat_volume;

  memory_allocate ((void **) &data, data_size);
  
#ifdef DEBUG
  log_print_formatted (&log_structure, LOG_URGENCY_DEBUG,
                       "Incoming connection...");
#endif

  system_thread_name_set ("Service handler");

  /* Find the block server. */
  
  if (ipc_service_resolve ("block", mailbox_id, &services, 5, &empty_tag) !=
      IPC_RETURN_SUCCESS)
  {
    log_print (&log_structure, LOG_URGENCY_EMERGENCY,
               "No block services found.");
    return;
  }

  device.block_structure.output_mailbox_id = mailbox_id[0];
  if (ipc_service_connection_request (&device.block_structure) !=
      IPC_RETURN_SUCCESS)
  {
    return;
  }

  log_print_formatted (&log_structure, LOG_URGENCY_EMERGENCY,
                       "output_mailbox: %d",
                       device.block_structure.output_mailbox_id);

  return_value = vfat_has_file_system (&device, &has_fat);
  if (return_value != VFAT_RETURN_SUCCESS || !has_fat)
  {
    log_print (&log_structure, LOG_URGENCY_ERROR, "No FAT filesystem detected.");
    return;
  }

  log_print (&log_structure, LOG_URGENCY_DEBUG, "FAT filesystem detected.");

  vfat_mount_device (&device, &vfat_volume);
#if DEBUG
  log_print_formatted (&log_structure, LOG_URGENCY_DEBUG,
    "Bytes per sector:        %lu", 
    vfat_volume.bytes_per_sector);

  log_print_formatted (&log_structure, LOG_URGENCY_DEBUG,
    "Sectors per cluster:     %lu", 
    vfat_volume.sectors_per_cluster);

  log_print_formatted (&log_structure, LOG_URGENCY_DEBUG,
    "FAT offset:              %lu", 
    vfat_volume.fat_offset);
    
  log_print_formatted (&log_structure, LOG_URGENCY_DEBUG,
    "Number of FATs:          %lu", 
    vfat_volume.number_of_fats);
    
  log_print_formatted (&log_structure, LOG_URGENCY_DEBUG,
    "Number of root entries:  %lu", 
    vfat_volume.number_of_root_entries);
    
  log_print_formatted (&log_structure, LOG_URGENCY_DEBUG,
    "Total sectors:           %lu", 
    vfat_volume.total_volume_length);
    
  log_print_formatted (&log_structure, LOG_URGENCY_DEBUG,
    "Size of FAT in sectors:  %lu", 
    vfat_volume.fat_length);
    
  log_print_formatted (&log_structure, LOG_URGENCY_DEBUG,
    "Sectors per track:       %u", 
    vfat_volume.sectors_per_track);
    
  log_print_formatted (&log_structure, LOG_URGENCY_DEBUG,
    "Number of heads:         %u", 
    vfat_volume.number_of_heads);
/*    
  log_print_formatted (&log_structure, LOG_URGENCY_DEBUG,
    "Number of hidden sectors: %lu", 
    vfat_volume.hidden_sectors);
*/    
  log_print_formatted (&log_structure, LOG_URGENCY_DEBUG,
    "Root starts at:          %lu (%lu)", 
    vfat_volume.root_offset, vfat_volume.root_length);

  log_print_formatted (&log_structure, LOG_URGENCY_DEBUG,
    "Data starts at:          %lu (%lu)", 
    vfat_volume.data_offset, vfat_volume.data_length);

  log_print_formatted (&log_structure, LOG_URGENCY_DEBUG,
    "Label:                   [%s]",
    vfat_volume.label);

  log_print_formatted (&log_structure, LOG_URGENCY_DEBUG,
    "Serial number:           %04X:%04X",
    (u16) (vfat_volume.serial_number >> 16),
    (u16) vfat_volume.serial_number);
#endif

/*
  {
  u32 free_clusters = 0;

  vfat_volume.count_available_clusters (
      (struct vfat_volume_type *) &vfat_volume, &free_clusters);

  log_print_formatted (&log_structure, LOG_URGENCY_DEBUG,
    "Available clusters:      %lu", 
    free_clusters);
  }
  {
  static u8 current_long_name[256];
  u32 directory_index = 0;
  bool finishedScanningDirectory;
  vfat_file_type *directory_fcb;
  fat_entry_type current_dir_entry;
  
  directory_fcb = vfat_make_root_fcb (&vfat_volume);
  
  finishedScanningDirectory = FALSE;

  log_print_formatted (&log_structure, LOG_URGENCY_DEBUG,
    "Begin scanning");

  while (!finishedScanningDirectory)
  {
    return_value = vfat_get_next_directory_entry (&vfat_volume, directory_fcb,
        &directory_index, current_long_name, &current_dir_entry);

    if (return_value == VFAT_RETURN_NO_MORE_ENTRIES)
    {
      finishedScanningDirectory = TRUE;
      continue;
    }
    else if (return_value != VFAT_RETURN_SUCCESS)
    {
      break;
    }
#if DEBUG
    if (!fat_entry_is_deleted (&current_dir_entry))
    {
      log_print_formatted (&log_structure, LOG_URGENCY_DEBUG,
          "    index:%lu  long name:[%s], name:[%.8s.%.3s]",
          directory_index, current_long_name, current_dir_entry.file_name,
          current_dir_entry.extension);
    }
#endif
  }
  }
*/
  {
    static file_info_type file_info;
    static u32 i, number_of_entries = 1;
    static file_handle_type file_handle = 1;
    static const u8 *path = "/";
  
    vfat_file_open (&vfat_volume, file_handle, (u8 *) path, 0, &file_info);

while (TRUE);
    
    for (i=0;i<30;i++)
    {
      vfat_file_list_read (0, &file_info, i, &number_of_entries);
      log_print_formatted (&log_structure, LOG_URGENCY_DEBUG, 
	    "file name: %s", file_info.name);
    }

  }
  mounted = TRUE;

  while (TRUE);

  /* Mount ourselves. */

  log_print (&log_structure, LOG_URGENCY_ERROR,
             "Telling VFS to mount volume.");

  message_parameter.block = TRUE;
  message_parameter.data = &mount;
  message_parameter.protocol = IPC_PROTOCOL_FILE;
  message_parameter.message_class = IPC_FILE_MOUNT_VOLUME;
  message_parameter.length = sizeof (file_mount_type);
  ipc_send (ipc_structure->output_mailbox_id, &message_parameter);

  message_parameter.block = TRUE;

  vfat_interface_init ();

  while (!done)
  {
    message_parameter.data = data;
    message_parameter.protocol = IPC_PROTOCOL_FILE;
    message_parameter.message_class = IPC_CLASS_NONE;
    message_parameter.length = data_size;
    
    if (ipc_receive (ipc_structure->input_mailbox_id, &message_parameter, 
                     &data_size) != IPC_RETURN_SUCCESS)
    {
      continue;
    }
    
    switch (message_parameter.message_class)
    {
      /* Read one or more directory entries. */

      case IPC_FILE_LIST_READ:
      {
        file_list_read_type *list_read =  (file_list_read_type *) data;
        file_info_type file_info;

#if DEBUG
        log_print_formatted (&log_structure, LOG_URGENCY_DEBUG, 
	    "IPC_FILE_LIST_READ [file_handle:%lu, offset:%lu, length:%lu]",
	    list_read->file_handle, list_read->offset, list_read->length);
#endif
/*          
        if (vfat_file_list_read (list_read->file_handle, &file_info, 
	    list_read->offset, &list_read->length) != VFAT_RETURN_SUCCESS)
        {
          file_info.last_file_in_list = TRUE;
        }
	else
	{
          file_info.last_file_in_list = FALSE;
	}
*/
        message_parameter.block = TRUE;
        message_parameter.data = &file_info;
        message_parameter.length = sizeof (file_info_type);

        log_print_formatted (&log_structure, LOG_URGENCY_DEBUG, 
            "Successfully read %lu entries",
             list_read->length);

        ipc_send (ipc_structure->output_mailbox_id, &message_parameter);

        break;
      }

      case IPC_FILE_OPEN:
      {
        file_open_type *open = (file_open_type *) data;
	static file_info_type file_info;

#if DEBUG
        log_print_formatted (&log_structure, LOG_URGENCY_DEBUG, 
            "IPC_FILE_OPEN [file_handle:%lu, file_name:%s, mode:%lu]",
	    open->file_handle, open->file_name, open->mode);    
#endif

        if (vfat_file_open (&vfat_volume, open->file_handle, open->file_name,
            open->mode, &file_info) != VFAT_RETURN_SUCCESS)
        {
          log_print (&log_structure, LOG_URGENCY_ERROR,
                     "Failed to open file.");
        }

        message_parameter.data = &file_info;
	message_parameter.length = sizeof (file_info_type);

        ipc_send (ipc_structure->output_mailbox_id, &message_parameter);

        break;
      }

      case IPC_FILE_CLOSE:
      {
        file_close_type *close = (file_close_type *) data;

#if DEBUG
        log_print (&log_structure, LOG_URGENCY_DEBUG, "IPC_FILE_CLOSE");    
#endif

        if (vfat_file_close (&vfat_volume, close->file_handle) !=
            VFAT_RETURN_SUCCESS)
        {
          log_print (&log_structure, LOG_URGENCY_ERROR,
                     "Failed to close file.");
        }

        break;
      }

      case IPC_FILE_READ:
      {
        file_read_type *read = (file_read_type *) data;
        u8 *read_buffer;

#if DEBUG
        log_print (&log_structure, LOG_URGENCY_DEBUG, "IPC_FILE_READ");    
#endif

        memory_allocate ((void **) &read_buffer, read->bytes);

        if (vfat_file_read (&vfat_volume, read->file_handle, read_buffer,
            read->offset, read->bytes) != VFAT_RETURN_SUCCESS)
        {
          log_print (&log_structure, LOG_URGENCY_ERROR,
                     "Failed read from file.");
        }
        
        message_parameter.data = read_buffer;
        message_parameter.length = read->bytes;
#ifdef DEBUG
        log_print_formatted (&log_structure, LOG_URGENCY_DEBUG,
                             "Sending %lu", read->bytes);
#endif
        ipc_send (ipc_structure->output_mailbox_id, &message_parameter);
        memory_deallocate ((void **) &read_buffer);

        break;
      }

      case IPC_FILE_WRITE:
      {
        file_write_type *write = (file_write_type *) data;

#if DEBUG
        log_print (&log_structure, LOG_URGENCY_DEBUG, "IPC_FILE_WRITE");    
#endif

        if (vfat_file_write (&vfat_volume, write->file_handle, write->data,
            write->offset, write->bytes) != VFAT_RETURN_SUCCESS)
        {
          log_print (&log_structure, LOG_URGENCY_ERROR,
                     "Failed write to file.");
        }

        return_value = 0;

        message_parameter.data = &return_value;
        message_parameter.length = sizeof (return_type);

        ipc_send (ipc_structure->output_mailbox_id, &message_parameter);

        break;
      }

      /* Unsupported functions. */

      case IPC_FILE_ACL_READ:
      case IPC_FILE_ACL_WRITE:
      case IPC_FILE_UNMOUNT_VOLUME:
      default:
      {
        return_value = IPC_RETURN_FILE_FUNCTION_UNSUPPORTED;

        message_parameter.data = &return_value;
        message_parameter.length = sizeof (return_type);

        ipc_send (ipc_structure->output_mailbox_id, &message_parameter);
        break;
      }
    }
  }
}

/* Main function. */

int main (void)
{
  ipc_structure_type ipc_structure;
  mailbox_id_type mailbox_id[10];
  unsigned int services = 10;

  /* Set our name. */

  system_process_name_set (PACKAGE_NAME);
  system_thread_name_set ("Initializing");

  if (log_init (&log_structure, PACKAGE_NAME, 
                &empty_tag) != LOG_RETURN_SUCCESS)
  {
    return -1;
  }

  /* Create our service. */

  if (ipc_service_create ("file_system", &ipc_structure, 
                          &empty_tag) != STORM_RETURN_SUCCESS)
  {
    log_print (&log_structure, LOG_URGENCY_EMERGENCY,
               "Couldn't create a file system service.");
    return -1;
  }

  system_call_process_parent_unblock ();
  log_print (&log_structure, LOG_URGENCY_EMERGENCY,
             "Parent unblocked.");

  if (ipc_service_resolve ("virtual_file_system", mailbox_id, &services, 0,
                           &empty_tag) != IPC_RETURN_SUCCESS)
  {
    log_print (&log_structure, LOG_URGENCY_EMERGENCY,
               "Couldn't resolve VFS service.");
    return -1;
  }

  ipc_structure.output_mailbox_id = mailbox_id[0];
  ipc_service_connection_request (&ipc_structure);
  handle_connection (&ipc_structure);

  return 0;
}
