#include <enviroment.h>
#include <memory_inlines.h>
#include <string.h>

#include "fat.h"
#include "structs.h"

#include "low_fat.h"
#include "block_io.h"
#include "mount.h"
#include "return_values.h"
#include "common.h"

#include "block_public.h"

#include <debug.h>
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

return_t vfat_has_file_system (
  device_t *device,
  bool *has_fat)
{
    return_t return_value;
    boot_sector_t *test_boot_sector;

    (*has_fat) = FALSE;

    memory_allocate ((void **) &test_boot_sector, 512);

    if (test_boot_sector == NULL)
    {
	return VFAT_RETURN_UNSUCCESSFULL;
    }

    return_value = vfat_read_sectors (device, 0, 1, test_boot_sector);

    if (return_value != VFAT_RETURN_SUCCESS)
    {
	return return_value;
    }

#if DEBUG_LEVEL >= DEBUG_LEVEL_INFORMATIVE

    if (test_boot_sector->filesystem_type[0] != 0)
    {
	DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	    "Vfat: test_boot_sector->filesystem_type: [%s]\n",
	    test_boot_sector->filesystem_type);
    } 
    else if (((boot_sector_32_t *) test_boot_sector)->filesystem_type[0] 
	    != 0)
    {
	DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	    "Vfat: test_boot_sector->filesystem_type: [%s]\n", 
	    ((boot_sector_32_t *) test_boot_sector)->filesystem_type);
    }
#endif

    if (string_compare_max (test_boot_sector->filesystem_type, "FAT12", 5) == 0
	|| 
	string_compare_max (test_boot_sector->filesystem_type, "FAT16", 5) == 0 
	||
	string_compare_max (
	    ((boot_sector_32_t *) test_boot_sector)->filesystem_type, "FAT32", 
	    5) == 0)
    {
	memory_deallocate ((void **) &test_boot_sector);

	(*has_fat) = TRUE;
	return VFAT_RETURN_SUCCESS;
    }

    memory_deallocate ((void **) &test_boot_sector);

    return VFAT_RETURN_UNSUCCESSFULL;
}

/*
 * FUNCTION: Mounts the device
 */
return_t vfat_mount_device (
  device_t *device_to_mount,
  vfat_volume_t *vfat_volume)
{
    return_t return_value;

    boot_sector_t *boot_sector;
    uint32_t number_of_clusters;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Mounting VFAT device...\n");
    
    memory_allocate ((void **) &boot_sector, 512);

    if (boot_sector == NULL)
    {
	return VFAT_RETURN_UNSUCCESSFULL;
    }

    return_value = vfat_read_sectors (device_to_mount, 0, 1, boot_sector);

    if (return_value != VFAT_RETURN_SUCCESS)
    {
	return return_value;
    }

    memory_copy (&vfat_volume->storage_device, device_to_mount, 
	sizeof (device_t));

    vfat_volume->sectors_per_cluster = boot_sector->sectors_per_cluster;
    vfat_volume->bytes_per_sector = boot_sector->bytes_per_sector;
    vfat_volume->bytes_per_cluster = (vfat_volume->sectors_per_cluster *
	vfat_volume->bytes_per_sector);
    vfat_volume->sectors_per_track = boot_sector->sectors_per_track;
    vfat_volume->number_of_heads = boot_sector->number_of_heads;

    vfat_volume->number_of_fats = boot_sector->number_of_fats;

    vfat_volume->number_of_root_entries = boot_sector->number_of_root_entries;
    vfat_volume->fat_entries_per_sector = boot_sector->bytes_per_sector / 32;

    vfat_volume->fat_offset = boot_sector->reserved_sectors;
    
    vfat_volume->hidden_sectors = boot_sector->hidden_sectors;

  {
  uint32_t root_directory_length, fat_size, total_sectors, first_data_sector, data_sectors;
  root_directory_length = (((boot_sector->number_of_root_entries * 32) +
                           (boot_sector->bytes_per_sector - 1)) / 
                           boot_sector->bytes_per_sector);

  fat_size = boot_sector->fat_size_16 != 0 ?
             boot_sector->fat_size_16 :
             ((boot_sector_32_t *) boot_sector)->fat_size_32;

  total_sectors = boot_sector->total_sectors_16 != 0 ?
                  boot_sector->total_sectors_16 :
                  boot_sector->total_sectors_32;

//    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Total sectors: %u\n", total_sectors);
    vfat_volume->total_volume_length = total_sectors;

  first_data_sector = (boot_sector->reserved_sectors +
                      (boot_sector->number_of_fats * fat_size) +
                       root_directory_length);
      
  data_sectors = total_sectors - first_data_sector;

  number_of_clusters = (data_sectors / boot_sector->sectors_per_cluster);
  }

  if (number_of_clusters < 4085)
  {
    vfat_volume->fat_type = FAT_12;
  }
  else if (number_of_clusters < 65525)
  {
    vfat_volume->fat_type = FAT_16;
  }
  else
  {
    vfat_volume->fat_type = FAT_32;
  }

  switch (vfat_volume->fat_type)
  {
    case FAT_12:
    case FAT_16:
    {
//      vfat_volume->total_volume_length = boot_sector->total_sectors_16;
      vfat_volume->fat_length = boot_sector->fat_size_16;

      vfat_volume->root_offset = vfat_volume->fat_offset +
          boot_sector->number_of_fats * boot_sector->fat_size_16;

      vfat_volume->root_length = (boot_sector->number_of_root_entries * 32) /
          boot_sector->bytes_per_sector;

      vfat_volume->data_offset = vfat_volume->root_offset +
          vfat_volume->root_length;

      memory_set_uint8 (vfat_volume->label, 0, 12);
      string_copy_max (vfat_volume->label, boot_sector->volume_label, 11);
//      vfat_volume->label[12] = 0;

      vfat_volume->serial_number = boot_sector->volume_id;

      break;
    }
    case FAT_32:
    {
//      vfat_volume->total_volume_length = boot_sector->total_sectors_32;
      vfat_volume->fat_length =
          ((boot_sector_32_t *) boot_sector)->fat_size_32;

      vfat_volume->data_offset = vfat_volume->fat_offset + 
          boot_sector->number_of_fats
          * ((boot_sector_32_t *) boot_sector)->fat_size_32;

      vfat_volume->root_offset = vfat_volume->data_offset + 
          (((boot_sector_32_t *) boot_sector)->root_cluster - 2) * 
	  vfat_volume->sectors_per_cluster;

      vfat_volume->root_length = boot_sector->sectors_per_cluster;

      string_copy_max (vfat_volume->label,
          ((boot_sector_32_t *) boot_sector)->volume_label, 11);
      vfat_volume->label[12] = 0;

      vfat_volume->serial_number =
          ((boot_sector_32_t *) boot_sector)->volume_id;

      vfat_volume->root_cluster = 
        ((boot_sector_32_t *) boot_sector)->root_cluster;
      
      break;
    }
  }

  vfat_volume->data_length = vfat_volume->total_volume_length -
      vfat_volume->data_offset;

  memory_deallocate ((void **) &boot_sector);

  switch (vfat_volume->fat_type)
  {
    case FAT_12:
    {
      vfat_volume->get_next_cluster = fat12_get_next_cluster;
  
      vfat_volume->find_available_cluster = fat12_find_available_cluster;

      vfat_volume->count_available_clusters = fat12_count_available_clusters;
  
      vfat_volume->write_cluster = fat12_write_cluster;

      break;
    }
    case FAT_16:
    {
      vfat_volume->get_next_cluster = fat16_get_next_cluster;
  
      vfat_volume->find_available_cluster = fat16_find_available_cluster;

      vfat_volume->count_available_clusters = fat16_count_available_clusters;
  
      vfat_volume->write_cluster = fat16_write_cluster;

      break;
    }
    case FAT_32:
    {
      vfat_volume->get_next_cluster = fat32_get_next_cluster;
  
      vfat_volume->find_available_cluster = fat32_find_available_cluster;

      vfat_volume->count_available_clusters = fat32_count_available_clusters;
  
      vfat_volume->write_cluster = fat32_write_cluster;

      break;
    }
  }

  if (vfat_volume->bytes_per_cluster >= PAGE_SIZE &&
      (vfat_volume->bytes_per_cluster % PAGE_SIZE) != 0)
  {
    DEBUG_PRINT (DEBUG_LEVEL_ERROR, "Invalid cluster size.\n");

    return VFAT_RETURN_UNSUCCESSFULL;
  }
  else if (vfat_volume->bytes_per_cluster < PAGE_SIZE &&
           (PAGE_SIZE % vfat_volume->bytes_per_cluster) != 0)
  {
    DEBUG_PRINT (DEBUG_LEVEL_ERROR, "Invalid cluster size 2.\n");

    return VFAT_RETURN_UNSUCCESSFULL;
  }

  return VFAT_RETURN_SUCCESS;
}
