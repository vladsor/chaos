
#include <enviroment.h>

#include <debug.h>
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

#include "fat.h"
#include "structs.h"
#include "string.h"

#include "cache.h"
#include "file.h"

#include "low_fat.h"
#include "read_write.h"
#include "directory.h"

#include "return_values.h"

#include "block_public.h"

vfat_file_t * vfat_new_fcb (
  char *file_name)
{
    vfat_file_t *rc_fcb;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "Vfat: %s (%s)\n", 
	__FUNCTION__, file_name);

    memory_allocate ((void **) &rc_fcb, sizeof (vfat_file_t));
    memory_set_uint8 ((uint8_t *) rc_fcb, 0, sizeof (vfat_file_t));

    if (file_name)
    {
	string_copy (rc_fcb->path_name, file_name);
	rc_fcb->object_name = rc_fcb->path_name + 1;
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	"Vfat: %s return %p\n", 
	__FUNCTION__, rc_fcb);

    return  rc_fcb;
}

void vfat_destroy_fcb (
    vfat_file_t *fcb)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Called: [%s]", __FUNCTION__);

    memory_deallocate ((void **) &fcb);
}

bool vfat_fcb_is_directory (
    vfat_file_t *fcb)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Called: [%s]", __FUNCTION__);

    return (fcb->entry.attribute & FILE_ATTRIBUTE_DIRECTORY);
}

bool vfat_fcb_is_root (
    vfat_file_t *file)
{
    return (string_compare (file->path_name, "/") == 0);
}

void vfat_grab_fcb (
    vfat_volume_t *vfat_volume UNUSED,
    vfat_file_t *fcb UNUSED)
{
}

void vfat_release_fcb (
    vfat_volume_t *vfat_volume UNUSED,
    vfat_file_t *fcb UNUSED)
{
}

void vfat_add_fcb_to_table (
    vfat_volume_t *vfat_volume UNUSED,
    vfat_file_t *fcb UNUSED)
{
}

vfat_file_t * vfat_grab_fcb_from_table (
    vfat_volume_t *vfat_volume UNUSED,
    uint8_t *file_name UNUSED)
{
    return  NULL;
}

return_t vfat_request_and_validate_region (
    vfat_volume_t *vfat_volume,
    vfat_file_t *fcb,
    uint32_t offset,
    void **buffer,
    cache_segment_t **cache_segment,
    bool extend)
{
    return_t return_value;

    bool valid;
    bool is_root;
    uint32_t current_cluster;
    uint32_t i;

//    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
//	"Vfat: %s (%p, %p, %u, %p, %p, %u)\n", __FUNCTION__, 
//	vfat_volume, fcb, offset, buffer, cache_segment, extend);

    return_value = cache_request_segment (offset,
 	PAGE_SIZE > vfat_volume->bytes_per_cluster ?
	    PAGE_SIZE : vfat_volume->bytes_per_cluster,
	buffer, &valid, cache_segment);

    if (return_value != VFAT_RETURN_SUCCESS)
    {
//        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Vfat: %s exit\n", __FUNCTION__);
    
	return return_value;
    }

    is_root = vfat_fcb_is_root (fcb);

    if (!valid)
    {
	current_cluster = vfat_dir_entry_get_first_cluster (vfat_volume, 
	    &fcb->entry);

//	DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
//	    "Vfat: first cluster is %u\n", current_cluster);

	return_value = offset_to_cluster (vfat_volume, 
    	    vfat_dir_entry_get_first_cluster (vfat_volume, &fcb->entry),
    	    offset, &current_cluster, extend);

//	DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
//	    "Vfat: current cluster is %u\n", current_cluster);

        if (return_value != VFAT_RETURN_SUCCESS)
	{
//	    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
//		"Vfat: %s exit\n", __FUNCTION__);
	
            return return_value;
        }

    if (PAGE_SIZE > vfat_volume->bytes_per_cluster)
    {
      for (i = 0 ; i < (PAGE_SIZE / vfat_volume->bytes_per_cluster) ; i++)
      {
        return_value = vfat_raw_read_cluster (vfat_volume,
            vfat_dir_entry_get_first_cluster (vfat_volume, &fcb->entry),
            ((uint8_t *) (*buffer)) + (i * vfat_volume->bytes_per_cluster),
            current_cluster);

        if (return_value != VFAT_RETURN_SUCCESS)
        {
          cache_release_segment ((*cache_segment), FALSE);

          return return_value;
        }
	
        return_value = next_cluster (vfat_volume,
          vfat_dir_entry_get_first_cluster (vfat_volume, &fcb->entry),
          &current_cluster, extend);
	  
        if (return_value != VFAT_RETURN_SUCCESS)
        {
          cache_release_segment ((*cache_segment), FALSE);

          return return_value;
        }
	
        if ((current_cluster) == UINT32_MAX)
        {
          break;
        }
      }
    }
    else
    {
      return_value = vfat_raw_read_cluster (vfat_volume,
          vfat_dir_entry_get_first_cluster (vfat_volume, &fcb->entry),
          (*buffer), current_cluster);
	  
      if (return_value != VFAT_RETURN_SUCCESS)
      {
        cache_release_segment ((*cache_segment), FALSE);

        return return_value;
      }
    }
  }

//    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Vfat: %s exit\n", __FUNCTION__);

    return VFAT_RETURN_SUCCESS;
}

return_t vfat_release_region (
    vfat_volume_t *vfat_volume UNUSED,
    vfat_file_t *fcb UNUSED,
    cache_segment_t *cache_segment)
{
//    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Vfat: Called: [%s]\n", __FUNCTION__);

    return cache_release_segment (cache_segment, TRUE);
}

vfat_file_t * vfat_make_root_fcb (
    vfat_volume_t *vfat_volume)
{
    vfat_file_t *fcb;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Vfat: Enter: [%s]\n", __FUNCTION__);

    fcb = vfat_new_fcb ("/");
    fcb->parent_file = NULL;
  
    memory_set_uint8 (fcb->entry.file_name, ' ', 11);

    fcb->entry.file_size = vfat_volume->root_length * BLOCK_SIZE;
    fcb->entry.attribute = FILE_ATTRIBUTE_DIRECTORY;

    if (vfat_volume->fat_type == FAT_32)
    {
        fcb->entry.first_cluster_number_low = vfat_volume->root_cluster & 0xFFFF;
	fcb->entry.first_cluster_number_high = vfat_volume->root_cluster >> 16;
    }
    else
    {
        fcb->entry.first_cluster_number_low = 1;
	fcb->entry.first_cluster_number_high = 0;
    }
  
    fcb->ref_count = 1;

//  vfatFCBInitializeCache(pVCB, FCB);
//  vfatAddFCBToTable(pVCB, FCB);
//  vfatGrabFCB(pVCB, FCB);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Vfat: Leave: [%s]\n", __FUNCTION__);

    return fcb;
}

vfat_file_t * vfat_open_root_fcb (
    vfat_volume_t *vfat_volume)
{
    vfat_file_t *fcb;

    fcb = vfat_grab_fcb_from_table (vfat_volume, "/");
  
    if (fcb == NULL)
    {
	fcb = vfat_make_root_fcb (vfat_volume);
    }

    return fcb;
}

return_t vfat_make_fcb_from_dir_entry (
    vfat_volume_t *vfat_volume,
    vfat_file_t *directory_fcb,
    uint8_t *long_name,
    fat_entry_t *dir_entry,
    vfat_file_t **file_fcb)
{
    vfat_file_t *rc_fcb;
    uint8_t path_name[MAX_PATH];

    if (long_name[0] != 0 && string_length (directory_fcb->path_name) +
	sizeof (uint8_t) + string_length (long_name) > MAX_PATH)
    {
	return VFAT_RETURN_NAME_INVALID;
    }
  
    string_copy (path_name, directory_fcb->path_name);
  
    if (!vfat_fcb_is_root (directory_fcb))
    {
	wcscat (path_name, "/");
    }
  
    if (long_name[0] != 0)
    {
	wcscat (path_name, long_name);
    }
    else
    {
	uint8_t entry_name[MAX_PATH];

        vfat_get_directory_entry_name (dir_entry, entry_name);
        wcscat (path_name, entry_name);
    }

    rc_fcb = vfat_new_fcb (path_name);
    memory_copy (&rc_fcb->entry, dir_entry, sizeof (fat_entry_t));
    rc_fcb->parent_file = directory_fcb;

//  vfat_fcb_initialize_cache (vcb, rcFCB);
    rc_fcb->ref_count++;
    vfat_add_fcb_to_table (vfat_volume, rc_fcb);
//  vfatGrabFCB (vcb, rcFCB);
    (*file_fcb) = rc_fcb;

    return VFAT_RETURN_SUCCESS;
}

return_t vfat_dir_find_file (
    vfat_volume_t *vfat_volume,
    vfat_file_t *directory_fcb,
    uint8_t *file_to_find,
    vfat_file_t **found_fcb)
{
    return_t return_value;

    bool finished_scanning_directory;
    uint32_t directory_index;
    uint8_t default_file_name [2];
    uint8_t current_long_name [256];
    fat_entry_t current_dir_entry;
    uint8_t current_entry_name [256];

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
	"Vfat: %s (Volume:%p, Directory:%p, File:%s)\n",
	__FUNCTION__, vfat_volume, directory_fcb, file_to_find);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,       
	"Vfat: Directory Path:%s\n", directory_fcb->path_name);

  /*  default to '.' if no filename specified
 */
  if (string_length (file_to_find) == 0)
  {
    default_file_name [0] = '.';
    default_file_name [1] = 0;
    file_to_find = default_file_name;
  }

  directory_index = 0;
  finished_scanning_directory = FALSE;
  
  while (!finished_scanning_directory)
  {
    return_value = vfat_get_next_directory_entry (vfat_volume, directory_fcb,
        &directory_index, current_long_name, &current_dir_entry);

    if (return_value == VFAT_RETURN_NO_MORE_ENTRIES)
    {
      finished_scanning_directory = TRUE;
      continue;
    }
    else if (return_value != VFAT_RETURN_SUCCESS)
    {
      return return_value;
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "    Index:%u, long name:%s\n",
        directory_index, current_long_name);

    if (!fat_entry_is_deleted (&current_dir_entry) && 
        !vfat_is_directory_entry_volume (&current_dir_entry))
    {
      if (current_long_name[0] != '\0' && 
          wstrcmpjoki (current_long_name, file_to_find))
      {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	    "Match found, %s\n", current_long_name);

        return_value = vfat_make_fcb_from_dir_entry (vfat_volume, directory_fcb,
            current_long_name, &current_dir_entry, found_fcb);
	    
        return return_value;
      }
      else
      {
        vfat_get_directory_entry_name (&current_dir_entry, current_entry_name);

        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	    "    entry name:%s\n", current_entry_name);

        if (wstrcmpjoki (current_entry_name, file_to_find))
        {
          DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
  	        "Match found, %s\n", current_entry_name);

          return_value = vfat_make_fcb_from_dir_entry (vfat_volume,
 	        directory_fcb, current_long_name, &current_dir_entry, found_fcb);

          return return_value;
        }
      }
    }
  }

  return VFAT_RETURN_NAME_NOT_FOUND;
}

return_t vfat_get_fcb_for_file (
    vfat_volume_t *vfat_volume,
    vfat_file_t **parent_fcb,
    vfat_file_t **fcb, 
    uint8_t *file_name)
{
  return_t return_value;
  
  static uint8_t path_name[MAX_PATH];
  static uint8_t element_name[MAX_PATH];
  uint8_t *current_element;
  vfat_file_t *current_fcb;
  vfat_file_t *current_parent_fcb;

  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
      "Vfat: %s (%p, %p, %p, %s)\n",
      __FUNCTION__, vfat_volume, parent_fcb, fcb, file_name);

  /*  Trivial case, open of the root directory on volume */
  if (file_name[0] == '\0' || string_compare (file_name, "/") == 0)
  {
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "Vfat: returning root FCB.\n");

    current_fcb = vfat_open_root_fcb (vfat_volume);
    (*fcb) = current_fcb;
    (*parent_fcb) = NULL;

    return  (current_fcb != NULL) ? VFAT_RETURN_SUCCESS : 
        VFAT_RETURN_PATH_NOT_FOUND;
  }

  current_element = file_name + 1;
  wcscpy (path_name, "/");
  current_fcb = vfat_open_root_fcb (vfat_volume);
  
  current_parent_fcb = NULL;

  /*  Parse filename and check each path element for existance and access */
  while (vfat_get_next_path_element (current_element) != 0)
  {
    /*  Skip blank directory levels */
    if ((vfat_get_next_path_element (current_element) - current_element) == 0)
    {
      current_element++;
      continue;
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "Parsing, current element:%s", 
        current_element);
	
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "    parent fcb:%p, fcb:%p", 
	    current_parent_fcb, current_fcb);

    /*  descend to next directory level */
    if (current_parent_fcb)
    {
      vfat_release_fcb (vfat_volume, current_parent_fcb);
      current_parent_fcb = NULL;
    }

    /*  fail if element in FCB is not a directory */
    if (!vfat_fcb_is_directory (current_fcb))
    {
      DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
          "Element in requested path is not a directory.");

      vfat_release_fcb (vfat_volume, current_fcb);
      fcb = NULL;
      
      (*parent_fcb) = NULL;
      (*fcb) = NULL;

      return VFAT_RETURN_PATH_NOT_FOUND;
    }
    
    current_parent_fcb = current_fcb;

    /*  Extract next directory level into dirName */
    vfat_sub_string (path_name, file_name,
        vfat_get_next_path_element (current_element) - file_name);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "  path name:%s", path_name);

    current_fcb = vfat_grab_fcb_from_table (vfat_volume, path_name);

    if (current_fcb == NULL)
    {
      vfat_sub_string (element_name, current_element,
          vfat_get_next_path_element (current_element) - current_element);

      DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
          "    element name:%s", element_name);

      return_value = vfat_dir_find_file (vfat_volume, current_parent_fcb, 
        element_name, &current_fcb);

      if (return_value == VFAT_RETURN_NAME_NOT_FOUND)
      {
        (*parent_fcb) = current_parent_fcb;
        (*fcb) = NULL;
	
        current_element = vfat_get_next_path_element (current_element);

        if (current_element[0] == '\0' || 
	    vfat_get_next_path_element (current_element + 1) == 0)
        {
          return VFAT_RETURN_NAME_NOT_FOUND;
        }
        else
        {
          return VFAT_RETURN_PATH_NOT_FOUND;
        }
      }
      else if (return_value != VFAT_RETURN_SUCCESS)
      {
        vfat_release_fcb (vfat_volume, current_parent_fcb);

        (*parent_fcb) = NULL;
        (*fcb) = NULL;

        return return_value;
      }
    }
    current_element = vfat_get_next_path_element (current_element);
  }

  (*parent_fcb) = current_parent_fcb;
  (*fcb) = current_fcb;

  return VFAT_RETURN_SUCCESS;
}

