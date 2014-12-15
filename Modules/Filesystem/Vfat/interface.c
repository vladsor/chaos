#include <enviroment.h>
#include <memory_inlines.h>
#include <string.h>
#include <hash_table.h>

#include "block_public.h"
#include <repository.h>


#include "fat.h"
#include "structs.h"
#include "return_values.h"
#include "cache.h"
#include "file.h"
#include "directory.h"
#include "mount.h"
#include "read_write.h"
#include "dirwr.h"

#include <debug.h>
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

STATIC_POOL (handlers_pool, 100);

hash_table_t *file_table;
unsigned int limit_file_entries = 100;

static unsigned int file_handle_to_hash (void *key)
{
    return (unsigned int) (*(file_handle_t *) key);
}

static int file_handle_compare (void *key1, void *key2)
{
    return ((*(file_handle_t *) key1) == (*(file_handle_t *) key2)) ?
	CONDITION_EQUAL : CONDITION_NOT_EQUAL;
}

return_t vfat_main (int argc UNUSED, char *argv[] UNUSED)
{
    return_t return_value;
    bool has_fat;
    device_t device;
    vfat_volume_t vfat_volume;
    
    repository_get_object (&device.generic, "/devices/partition1");
    repository_get_interface (device.generic, BLOCK_IID);
    
    return_value = vfat_has_file_system (&device, &has_fat);
  
    if (return_value != VFAT_RETURN_SUCCESS || !has_fat)
    {
	DEBUG_PRINT (DEBUG_LEVEL_ERROR, "Vfat: No FAT filesystem detected.\n");
	
	return -1;
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Vfat: FAT filesystem detected.\n");

    return_value = vfat_mount_device (&device, &vfat_volume);

    if (return_value != VFAT_RETURN_SUCCESS || !has_fat)
    {
	DEBUG_PRINT (DEBUG_LEVEL_ERROR, "Vfat: Device mount failed.\n");
	
	return -2;
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	"Vfat: Type :                   %i\n",
	vfat_volume.fat_type);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	"Vfat: Bytes per sector:        %u\n", 
	vfat_volume.bytes_per_sector);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "Vfat: Sectors per cluster:     %u\n", 
	vfat_volume.sectors_per_cluster);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "Vfat: FAT offset:              %u\n", 
	vfat_volume.fat_offset);
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	"Vfat: Number of FATs:          %u\n", 
        vfat_volume.number_of_fats);
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	"Vfat: Number of root entries:  %u\n", 
        vfat_volume.number_of_root_entries);
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	"Vfat: Total sectors:           %u\n", 
        vfat_volume.total_volume_length);
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	"Vfat: Size of FAT in sectors:  %u\n", 
        vfat_volume.fat_length);
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	"Vfat: Sectors per track:       %u\n", 
        vfat_volume.sectors_per_track);
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	"Vfat: Number of heads:         %u\n", 
        vfat_volume.number_of_heads);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	"Vfat: Number of hidden sectors:%u\n", 
        vfat_volume.hidden_sectors);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "Vfat: Root starts at:          %u (%u)\n", 
	vfat_volume.root_offset, vfat_volume.root_length);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	"Vfat: Data starts at:          %u (%u)\n", 
	vfat_volume.data_offset, vfat_volume.data_length);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	"Vfat: Label:                   [%s]\n",
	vfat_volume.label);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	"Vfat: Serial number:           %04X:%04X\n",
        (uint16_t) (vfat_volume.serial_number >> 16),
	(uint16_t) vfat_volume.serial_number);

    return_value = vfat_interface_init ();

    if (return_value != VFAT_RETURN_SUCCESS || !has_fat)
    {
	DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
	    "Vfat: Initialisation interface failed.\n");
	
	return -3;
    }

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

    if (!fat_entry_is_deleted (&current_dir_entry))
    {
      log_print_formatted (&log_structure, LOG_URGENCY_DEBUG,
          "    index:%lu  long name:[%s], name:[%.8s.%.3s]",
          directory_index, current_long_name, current_dir_entry.file_name,
          current_dir_entry.extension);
    }

  }
  }
*/

    {
    file_info_t file_info;
    uint32_t i = 0, number_of_entries = 1;
    file_handle_t file_handle;
    uint8_t *path = "/";
  
    vfat_file_open (&vfat_volume, &file_handle, (uint8_t *) path, 0, &file_info);

    
    while (number_of_entries > 0)
    {
	if (vfat_file_list_read (file_handle, &file_info, i, 
	    &number_of_entries) == VFAT_RETURN_SUCCESS)
	{
	    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE - 10, 
		"Vfat: file name: %s{%u}\n", 
		file_info.name, file_info.file_size);
	}
	i++;
    }

  }
  
/*
    {
        file_info_t file_info;
        file_handle_t file_handle;
	uint8_t *path = "/autoexec.bat";
	uint32_t offset = 0;
	uint32_t bytes = 1;
	char buffer[100];
  
        vfat_file_open (&vfat_volume, &file_handle, (uint8_t *) path, 0, 
	    &file_info);
	
	while (bytes != 0)
	{
	    if (vfat_file_read (&vfat_volume, file_handle, buffer, offset, 1, 
		&bytes) == VFAT_RETURN_SUCCESS)
	    {
		offset += bytes;		

    		DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE - 10, "%c",buffer[0]);
	    }
	    else
	    {
		break;
	    }
	}
    }
*/
/*
    {
	uint8_t *path = "/wininst0.400";

	vfat_file_delete (&vfat_volume, path);
    }
*/
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	"Vfat: Initialisation successfull.\n");

    return 0;
}

return_t vfat_interface_init (void)
{
    pool_of_integers_init (handlers_pool, 100);

    memory_allocate ((void **) &file_table, 
	SIZEOF_HASH_TABLE (limit_file_entries));

    if (file_table == NULL)
    {
	return VFAT_RETURN_UNSUCCESSFULL;
    }

    hash_table_create (file_table, limit_file_entries, 
	file_handle_to_hash, file_handle_compare);

    return VFAT_RETURN_SUCCESS;
}

return_t vfat_file_list_read (
  file_handle_t file_handle,
  file_info_t *file_info,
  uint32_t first_entry,
  uint32_t *number_of_entries)
{
    return_t return_value;

    vfat_file_t *file;
    uint32_t current_index = 0, directory_index = 0;
    static uint8_t current_long_name [256];
    fat_entry_t current_dir_entry;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	"Vfat: %s (%u, %p, %u, %p)\n", 
	__FUNCTION__, file_handle, file_info, first_entry, number_of_entries);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	"Vfat: %s Request %u entries.\n", 
	__FUNCTION__, (*number_of_entries));

    file = (vfat_file_t *) hash_table_search_element (file_table, &file_handle);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	"Vfat: file is %p\n", file);

    if (file == NULL)
    {
	DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
	    "Vfat: file not opened.\n");
	    
	return VFAT_RETURN_FILE_NOT_OPENED;
    }

    for (current_index = 0; current_index < first_entry;)
    {
	return_value = vfat_get_next_directory_entry (file->volume, file,
	    &directory_index, current_long_name, &current_dir_entry);

	if (return_value == VFAT_RETURN_NO_MORE_ENTRIES)
	{
	    (*number_of_entries) = 0;

	    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
		"Vfat: No more entries\n");

	    return VFAT_RETURN_NO_MORE_ENTRIES;
	}
	else if (return_value != VFAT_RETURN_SUCCESS)
	{
	    DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
		"Vfat: Unknown error.\n");
		
	    return return_value;
	}

	if (fat_entry_is_deleted (&current_dir_entry))
	{
	    DEBUG_PRINT (DEBUG_LEVEL_WARNING, 
		"Vfat: Sciping deleted entry.\n");
		
	    continue;
	}
	
	current_index++;
    }

    for (; current_index < (first_entry + (*number_of_entries));)
    {
	return_value = vfat_get_next_directory_entry (file->volume, file, 
	    &directory_index, current_long_name, &current_dir_entry);

	if (return_value == VFAT_RETURN_NO_MORE_ENTRIES)
	{
	    (*number_of_entries) = current_index - first_entry;

	    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
		"Vfat: No more entries\n");

	    return VFAT_RETURN_NO_MORE_ENTRIES;
	}
	else if (return_value != VFAT_RETURN_SUCCESS)
	{
	    DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
		"Vfat: Unknown error.\n");

	    return return_value;
	}

	if (fat_entry_is_deleted (&current_dir_entry))
	{
	    DEBUG_PRINT (DEBUG_LEVEL_WARNING, 
		"Vfat: Sciping deleted entry.\n");
		
	    continue;
	}

	DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
    	    "Vfat:    index:%u  long name:[%s], name:[%.8s.%.3s]\n",
    	    directory_index, current_long_name, 
	    current_dir_entry.file_name, current_dir_entry.extension);

	string_copy (file_info->name, current_long_name);
	file_info->file_size = current_dir_entry.file_size;
	
	current_index++;
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	"Vfat: %s OK.\n",
	__FUNCTION__);
	
    return VFAT_RETURN_SUCCESS;
}

return_t vfat_file_open (
    vfat_volume_t *vfat_volume, 
    file_handle_t *file_handle,
    uint8_t *file_name,
    uint32_t mode,
    file_info_t *file_info)
{
    return_t return_value;

    vfat_file_t *file;
    vfat_file_t *parent_file;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "Vfat: %s (%p, %p, %s, %u, %p)\n", 
        __FUNCTION__, vfat_volume, file_handle, file_name, mode, file_info);

    return_value = vfat_get_fcb_for_file (vfat_volume, &parent_file, &file,
        file_name);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "Vfat: file is %p\n", file);

    if (return_value != VFAT_RETURN_SUCCESS)
    {
	return return_value;
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "Vfat: file: first cluster is %04X:%04X\n", 
         file->entry.first_cluster_number_low, 
         file->entry.first_cluster_number_high);

    pool_of_integers_allocate (handlers_pool, &file->handle);
    file->volume = vfat_volume;
    file->parent_file = (struct vfat_file_t *) parent_file;
    file->mode = mode;

    hash_table_add_element (file_table, (hash_element_t *) file);

    (*file_handle) = file->handle;

    if (file_info != NULL)
    {
        file_info->file_handle = file->handle;

	if (file->entry.attribute & FILE_ATTRIBUTE_DIRECTORY)
        {
	    file_info->file_type = FILE_TYPE_DIRECTORY;
	}
	else
	{
	    file_info->file_type = FILE_TYPE_FILE;
	}

	file_info->file_size = file->entry.file_size;
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "Vfat: %s exit\n", __FUNCTION__);
  
    return VFAT_RETURN_SUCCESS;
}

return_t vfat_file_close (
    vfat_volume_t *vfat_volume,
    file_handle_t file_handle)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	"%s::%s (%p, %u).\n", 
	__FILE__, __FUNCTION__, vfat_volume, file_handle);

    hash_table_delete_element (file_table, &file_handle);
    pool_of_integers_deallocate (handlers_pool, file_handle);

    return VFAT_RETURN_SUCCESS;
}

return_t vfat_file_read (
    vfat_volume_t *vfat_volume,
    file_handle_t file_handle, 
    void *read_buffer, 
    uint32_t offset, 
    uint32_t bytes,
    uint32_t *read_bytes)
{
    return_t return_value;

    vfat_file_t *file;
    uint32_t length_read;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	"Vfat: %s (%u, %p, %u, %u, %p)\n", 
	__FUNCTION__, file_handle, read_buffer, offset, bytes, read_bytes);

    file = (vfat_file_t *) hash_table_search_element (file_table, &file_handle);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	"Vfat: file is %p\n", file);

    if (file == NULL)
    {
	DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
	    "Vfat: file not opened.\n");
	    
	return VFAT_RETURN_FILE_NOT_OPENED;
    }
    
    return_value = vfat_read_file (vfat_volume, file, read_buffer, bytes, 
	offset, &length_read, TRUE);

    if (read_bytes != NULL)
    {
	(*read_bytes)= length_read;
    }	

    return return_value;
}

return_t vfat_file_write (
    vfat_volume_t *vfat_volume,
    file_handle_t file_handle, 
    void *write_buffer, 
    uint32_t offset, 
    uint32_t bytes)
{
    return_t return_value;

    vfat_file_t *file;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	"Vfat: %s (%u, %p, %u, %u)\n", 
	__FUNCTION__, file_handle, write_buffer, offset, bytes);

    file = (vfat_file_t *) hash_table_search_element (file_table, &file_handle);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	"Vfat: file is %p\n", file);

    if (file == NULL)
    {
	DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
	    "Vfat: file not opened.\n");
	    
	return VFAT_RETURN_FILE_NOT_OPENED;
    }
    
    return_value = vfat_write_file (vfat_volume, file, write_buffer, bytes, 
	offset, TRUE);

    return return_value;
}

/*
return_t vfat_file_create ()
{
}
*/
return_t vfat_file_delete (
    vfat_volume_t *vfat_volume, 
    uint8_t *file_name)
{
    return_t return_value;
    
    vfat_file_t *file;
    vfat_file_t *parent_file;
    
    return_value = vfat_get_fcb_for_file (vfat_volume, &parent_file, &file,
        file_name);

    return_value = delete_entry (vfat_volume, file);

    return return_value;
}
