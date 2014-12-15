#include <enviroment.h>

#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

#include "Include/return_values.h"

#include "Include/fat.h"
#include "Include/structs.h"

#include "Include/cache.h"
#include "Include/string.h"
#include "Include/common.h"

#include "Include/file.h"

#include "Include/directory.h"

#define  CACHE_PAGE_SIZE(vfat_volume) ( \
    (vfat_volume)->bytes_per_cluster > PAGE_SIZE ? \
    (vfat_volume)->bytes_per_cluster : PAGE_SIZE)

#define  ENTRIES_PER_CACHE_PAGE(vfat_volume)  (ENTRIES_PER_SECTOR * \
    (CACHE_PAGE_SIZE (vfat_volume) / ((vfat_volume)->bytes_per_sector)))


uint32_t vfat_dir_entry_get_first_cluster (
    vfat_volume_t *vfat_volume,
    fat_entry_t *fat_entry)
{
    uint32_t cluster;

    if (vfat_volume->fat_type == FAT_32)
    {
	cluster = fat_entry->first_cluster_number_low + 
    	    (fat_entry->first_cluster_number_high << 16);
    }
    else
    {
        cluster = fat_entry->first_cluster_number_low;
    }

    return cluster;
}

bool fat_entry_is_deleted (
    fat_entry_t *fat_entry)
{
    return (fat_entry->file_name[0] == 0xE5);
}

bool vfat_is_directory_entry_end_marker (
    fat_entry_t *fat_entry)
{
    return (fat_entry->file_name[0] == 0);
}

bool vfat_is_directory_entry_long_name (
    fat_entry_t *fat_entry)
{
    return (fat_entry->attribute == 0x0F);
}

bool vfat_is_directory_entry_volume (
    fat_entry_t *fat_entry)
{
    return (fat_entry->attribute == 0x28);
}

void vfat_get_directory_entry_name (
  fat_entry_t *fat_entry,
  char *entry_name)
{
  vfat_8_dot_3_to_string (fat_entry->file_name, fat_entry->extension, 
      entry_name);
}

return_t vfat_get_next_directory_entry (
  vfat_volume_t *vfat_volume,
  vfat_file_t *directory_file,
  uint32_t *directory_index,
  uint8_t *file_name,
  fat_entry_t *directory_entry)
{
  return_t return_value;

  uint32_t index_in_page;
  uint32_t page_number;
  void *current_page = NULL;
  cache_segment_t *cache_segment = NULL; 
  fat_entry_t *fat_entry;
  lfn_fat_entry_t *long_name_entry;
  bool is_lfn_entry = FALSE;  

  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
    "Vfat: %s (%p, %p, %p, %p, %p)\n",
    __FUNCTION__, vfat_volume, directory_file, directory_index, file_name,
    directory_entry);

  index_in_page = (*directory_index) % ENTRIES_PER_CACHE_PAGE (vfat_volume);
  page_number = (*directory_index) / ENTRIES_PER_CACHE_PAGE (vfat_volume);
  (*file_name) = 0;

  return_value = vfat_request_and_validate_region (vfat_volume, directory_file,
      page_number * CACHE_PAGE_SIZE (vfat_volume), (void **) &current_page,
      &cache_segment, FALSE);

  if (return_value != VFAT_RETURN_SUCCESS)
  {
    return return_value;
  }

  while (TRUE)
  {
    fat_entry = (fat_entry_t *) current_page;

    if (vfat_is_directory_entry_end_marker (&fat_entry [index_in_page]))
    {
      DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
          "end of directory, returning no more entries.");

      return_value = vfat_release_region (vfat_volume, directory_file,
          cache_segment);

      return VFAT_RETURN_NO_MORE_ENTRIES;
    }
    else if (!vfat_is_directory_entry_long_name (&fat_entry [index_in_page])
      && !fat_entry_is_deleted (&fat_entry [index_in_page]) && !is_lfn_entry)
    {
      memory_copy (directory_entry, &fat_entry[index_in_page], 
        sizeof (fat_entry_t));

      vfat_get_directory_entry_name (&fat_entry[index_in_page], file_name);
	
      (*directory_index)++;
      break;
    }
    else if (vfat_is_directory_entry_long_name (&fat_entry [index_in_page])
      && !fat_entry_is_deleted (&fat_entry [index_in_page]))
    {
      uint8_t *cur;
      int i,j;
      ucs2_t *ucs2_name;
      int number_of_lfn;
      unsigned int char_length;
      
      DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "    long name entry found at %u", (*directory_index));
      
      is_lfn_entry = TRUE;

      long_name_entry = (lfn_fat_entry_t *) current_page;
      
      memory_allocate ((void **) &ucs2_name, 256 * sizeof (ucs2_t));

      memory_set_uint8 ((uint8_t *) ucs2_name, 0, 256);

      memory_copy (ucs2_name + 0, long_name_entry[index_in_page].name0_4, 
          5 * sizeof (ucs2_t));
      memory_copy (ucs2_name + 5, long_name_entry[index_in_page].name5_10, 
          6 * sizeof (ucs2_t));
      memory_copy (ucs2_name + 11, long_name_entry[index_in_page].name11_12, 
          2 * sizeof (ucs2_t));

      number_of_lfn = 1;      

      while ((long_name_entry [index_in_page].id != 0x41) &&
             (long_name_entry [index_in_page].id != 0x01) &&
             (long_name_entry [index_in_page].attribute > 0))
      {
        (*directory_index)++;
        index_in_page++;
	
        if (index_in_page == ENTRIES_PER_CACHE_PAGE (vfat_volume))
        {
          index_in_page = 0;
          page_number++;

          return_value = vfat_release_region (vfat_volume,
 directory_file,
              cache_segment);

          if (return_value != VFAT_RETURN_SUCCESS)
          {
            return return_value;
          }

          return_value = vfat_request_and_validate_region (vfat_volume,
              directory_file, page_number * CACHE_PAGE_SIZE (vfat_volume),
              (void **) &current_page,
 &cache_segment,
 FALSE);

          if (return_value != VFAT_RETURN_SUCCESS)
          {
            return return_value;
          }

          long_name_entry = (lfn_fat_entry_t *) current_page;
        }

	DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	    "    index = %u to %p", 
	    (*directory_index), ucs2_name + number_of_lfn * 13);

        memory_copy (ucs2_name + number_of_lfn * 13 + 0, 
	    long_name_entry[index_in_page].name0_4, 5 * sizeof (ucs2_t));
        memory_copy (ucs2_name + number_of_lfn * 13 + 5, 
	    long_name_entry[index_in_page].name5_10, 6 * sizeof (ucs2_t));
        memory_copy (ucs2_name + number_of_lfn *13 + 11, 
	    long_name_entry[index_in_page].name11_12, 2 * sizeof (ucs2_t));

        number_of_lfn++;      
      }

      cur = file_name;
      for (i = number_of_lfn - 1 ; i >= 0 ; i--)
      {
         while(1);
        for (j = 0 ; j < 13 ; j++)
	{
          unicode_ucs2_to_utf8 (cur, ucs2_name[j + i * 13], &char_length);
	  cur += char_length;
	}
      }
      
      memory_deallocate ((void **) &ucs2_name);

      DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
          "    long file name: [%s]", file_name);

      (*directory_index)++;
      index_in_page++;

      if (index_in_page == ENTRIES_PER_CACHE_PAGE (vfat_volume))
      {
        index_in_page = 0;
        page_number++;

        return_value = vfat_release_region (vfat_volume,
 directory_file,
            cache_segment);
	    
        if (return_value != VFAT_RETURN_SUCCESS)
        {
          return return_value;
        }

        return_value = vfat_request_and_validate_region (vfat_volume,
            directory_file,
 page_number * CACHE_PAGE_SIZE (vfat_volume),
            (void **) &current_page,
 &cache_segment,
 FALSE);

        if (return_value != VFAT_RETURN_SUCCESS)
        {
          return return_value;
        }
      }
    }
    else
    {
      memory_copy (directory_entry, &fat_entry[index_in_page], 
        sizeof (fat_entry_t));
	
      (*directory_index)++;
      break;
    }
  }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
	"Vfat: Releasing current directory page.\n");

    return_value = vfat_release_region (vfat_volume,
 directory_file,
 
	cache_segment);

    return return_value;
}
/*
bool vfat_is_directory_empty (vfat_file_t *directory_file)
{
    fat_entry_t *fat_dir_entry;
    uint32_t index, max_index;

    if (vfat_fcb_is_root (directory_file))
    {
	index = 0;
    }
    else
    {
	index = 2;
    }

    max_index = Fcb->RFCB.FileSize.u.LowPart / sizeof(FAT_DIR_ENTRY);

    while (Index < MaxIndex)
    {
	if (Context == NULL || (Index % ENTRIES_PER_PAGE) == 0)
        {
	    if (!CcMapData(Fcb->FileObject, &FileOffset, PAGE_SIZE, TRUE, &Context, (PVOID*)&FatDirEntry))
	    {
		return TRUE;
	    }
	    
	    fat_dir_entry += index % ENTRIES_PER_PAGE;
	}
	 
	if (ENTRY_END (fat_dir_entry))
	{
	    return TRUE;
	}
	  
	if (!ENTRY_DELETED (fat_dir_entry))
	{
	    return FALSE;
	}
	
        index++;
        fat_dir_entry++;
    }
     
    return TRUE;
}

*/
