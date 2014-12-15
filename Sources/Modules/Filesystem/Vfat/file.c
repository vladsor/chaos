#include <enviroment.h>

#include "Include/return_values.h"
#include "Include/fat.h"
#include "Include/structs.h"
#include "Include/entry.h"

#include "Include/types.h"
#include "Include/volume.h"
#include "Include/file.h"

#include "Include/common.h"
#include "Include/low_fat.h"
#include "Include/read_write.h"
#include "Include/directory_entry.h"

#define DEBUG_MODULE_NAME L"VFAT"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#ifndef __STORM_KERNEL__
#   define DEBUG_SUPPLIER (vfat_debug_supplier)
#endif

#include <debug/macros.h>

p_vfat_file_t vfat_file_create_data (
    const wchar_t *file_name)
{
    p_vfat_file_t file;

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
        L"%S: %s (%p)\n", 
	DEBUG_MODULE_NAME, __FUNCTION__, 
        file_name);

    memory_allocate ((void **) &file, sizeof (vfat_file_t));
    memory_clear (file, sizeof (vfat_file_t));

    if (file_name)
    {
	wstring_copy (file->path_name, file_name);
	file->object_name = file->path_name + 1;
    }

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE, 
	L"%S: %s return %p\n", 
	DEBUG_MODULE_NAME, __FUNCTION__, 
        file);

    return  file;
}

void vfat_file_destroy_data (
    p_vfat_file_t file)
{
    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE, 
        L"%S: %s ()\n", 
        DEBUG_MODULE_NAME, __FUNCTION__);

    memory_deallocate (file);
}

bool vfat_file_is_directory (
    p_vfat_file_t file)
{
    return (file->entry.attribute & FILE_ATTRIBUTE_DIRECTORY);
}

bool vfat_file_is_root (
    p_vfat_file_t file)
{
    return (wstring_compare (file->path_name, L"/") == 0);
}

void vfat_file_acquire (
    p_vfat_file_t file)
{
    file->ref_count++;
}

void vfat_file_release (
    p_vfat_file_t file)
{
    file->ref_count--;
}

return_t vfat_file_read_region (
    p_vfat_file_t file,
    uint32_t offset,
    p_uint8_t buffer,
    bool extend)
{
    return_t return_value;
    p_vfat_volume_t vfat_volume;

    uint32_t current_cluster;
    uint32_t i;

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE, 
        L"%S: %s ( %p, %u, %p, %u)\n", 
        DEBUG_MODULE_NAME, __FUNCTION__, 
	file, offset, buffer, extend);

    vfat_volume = file->volume;

    current_cluster = vfat_directory_entry_get_first_cluster (
        vfat_volume, &file->entry);

    return_value = offset_to_cluster (
        vfat_volume, vfat_directory_entry_get_first_cluster (
            vfat_volume, &file->entry),
        offset, &current_cluster, extend);

    if (return_value != VFAT_RETURN_SUCCESS)
    {
        return return_value;
    }

    if (PAGE_SIZE > vfat_volume->bytes_per_cluster)
    {
        for (i = 0 ; i < (PAGE_SIZE / vfat_volume->bytes_per_cluster) ; i++)
        {
            return_value = vfat_raw_read_cluster (
                vfat_volume, vfat_directory_entry_get_first_cluster (
                    vfat_volume, &file->entry), 
                buffer + (i * vfat_volume->bytes_per_cluster), current_cluster);

            if (return_value != VFAT_RETURN_SUCCESS)
            {
                return return_value;
            }
          
            return_value = next_cluster (
                vfat_volume, vfat_directory_entry_get_first_cluster (
                    vfat_volume, &file->entry),
                &current_cluster, extend);
	  
            if (return_value != VFAT_RETURN_SUCCESS)
            {
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
        return_value = vfat_raw_read_cluster (
            vfat_volume, vfat_directory_entry_get_first_cluster (
                vfat_volume, &file->entry),
            buffer, current_cluster);
	  
        if (return_value != VFAT_RETURN_SUCCESS)
        {
            return return_value;
        }
    }
   
    return VFAT_RETURN_SUCCESS;
}

p_vfat_file_t vfat_file_create_root_data (
    p_vfat_volume_t vfat_volume)
{
    p_vfat_file_t file;

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE, 
        L"%S: %s ()\n", 
        DEBUG_MODULE_NAME, __FUNCTION__);

    file = vfat_file_create_data (L"/");
    file->parent_file = NULL;
    file->volume = vfat_volume;  

    memory_set_uint8 (file->entry.file_name, ' ', 11);

    file->entry.file_size = vfat_volume->root_length * BLOCK_SIZE;
    file->entry.attribute = FILE_ATTRIBUTE_DIRECTORY;

    if (vfat_volume->fat_type == FAT_32)
    {
        file->entry.first_cluster_number_low = 
            vfat_volume->root_cluster & 0xFFFF;
	file->entry.first_cluster_number_high = 
            vfat_volume->root_cluster >> 16;
    }
    else
    {
        file->entry.first_cluster_number_low = 1;
	file->entry.first_cluster_number_high = 0;
    }
  
    file->ref_count = 1;

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE, 
        L"%S: %s: Leave\n", 
        DEBUG_MODULE_NAME, __FUNCTION__);

    return file;
}

p_vfat_file_t vfat_file_open_root (
    p_vfat_volume_t vfat_volume)
{
    p_vfat_file_t file;

    file = vfat_volume_get_file_data (vfat_volume, L"/");
  
    if (file == NULL)
    {
	file = vfat_file_create_root_data (vfat_volume);
    }

    return file;
}

return_t vfat_file_create_data_from_directory_entry (
    p_vfat_file_t directory_file,
    const wchar_t *long_name,
    p_fat_entry_t directory_entry,
    p_vfat_file_t *file_data)
{
    p_vfat_file_t file;
    wchar_t path_name[VFAT_MAX_PATH];
    p_vfat_volume_t vfat_volume;
    
    vfat_volume = directory_file->volume;

    if (long_name[0] != L'\0' && wstring_length (directory_file->path_name) +
        sizeof (wchar_t) + wstring_length (long_name) > VFAT_MAX_PATH)
    {
	return VFAT_RETURN_NAME_INVALID;
    }
  
    wstring_copy (path_name, directory_file->path_name);
  
    if (!vfat_file_is_root (directory_file))
    {
        wstring_append (path_name, L"/");
    }
  
    if (long_name[0] != L'\0')
    {
        wstring_append (path_name, long_name);
    }
    else
    {
	wchar_t entry_name[VFAT_MAX_PATH];

        vfat_directory_entry_get_name (directory_entry, entry_name);
        wstring_append (path_name, entry_name);
    }

    file = vfat_file_create_data (path_name);
    memory_copy (&file->entry, directory_entry, sizeof (fat_entry_t));
    file->volume = directory_file->volume;
    file->parent_file = directory_file;
    file->ref_count = 1;

    vfat_volume_add_file_data (vfat_volume, file);

    (*file_data) = file;

    return VFAT_RETURN_SUCCESS;
}

return_t vfat_directory_find_file (
    p_vfat_volume_t vfat_volume,
    p_vfat_file_t directory_file,
    const wchar_t *file_to_find,
    p_vfat_file_t *found_file)
{
    return_t return_value;

    bool finished_scanning_directory;
    uint32_t directory_index;
    wchar_t default_file_name[2];
    wchar_t current_long_name[256];
    fat_entry_t current_directory_entry;
    wchar_t current_entry_name[256];

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
        L"%S: %s (Volume:%p, Directory:%p, File:%S)\n",
	DEBUG_MODULE_NAME, __FUNCTION__, 
        vfat_volume, directory_file, file_to_find);

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
        L"%S: Directory Path:%S\n", 
        DEBUG_MODULE_NAME,
        directory_file->path_name);

    /*  default to '.' if no filename specified */
    if (wstring_length (file_to_find) == 0)
    {
        default_file_name[0] = L'.';
        default_file_name[1] = 0;
        file_to_find = default_file_name;
    }

    directory_index = 0;
    finished_scanning_directory = FALSE;
  
    while (!finished_scanning_directory)
    {
        return_value = vfat_directory_entry_get_next ( 
            directory_file, &directory_index, current_long_name, 
            &current_directory_entry);

        if (return_value == VFAT_RETURN_NO_MORE_ENTRIES)
        {
            finished_scanning_directory = TRUE;
            continue;
        }
        else if (return_value != VFAT_RETURN_SUCCESS)
        {
            return return_value;
        }
        
        DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE, 
                     L"    Index:%u, long name:%S\n",
                     directory_index, current_long_name);

        if (!vfat_directory_entry_is_deleted (&current_directory_entry) && 
            !vfat_directory_entry_is_volume (&current_directory_entry))
        {
            if (current_long_name[0] != L'\0' && 
                wstrcmpjoki (current_long_name, file_to_find))
            {
                DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE, 
                             L"Match found, %S\n", current_long_name);

                return_value = vfat_file_create_data_from_directory_entry (
                    directory_file, current_long_name, 
                    &current_directory_entry, found_file);
	    
                return return_value;
            }
            else
            {
                vfat_directory_entry_get_name (
                    &current_directory_entry, current_entry_name);

                DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE, 
                             L"    entry name:%S\n", current_entry_name);

                if (wstrcmpjoki (current_entry_name, file_to_find))
                {
                    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE, 
                                 L"Match found, %S\n", current_entry_name);

                    return_value = vfat_file_create_data_from_directory_entry (
                        directory_file, current_long_name, 
                        &current_directory_entry, found_file);

                    return return_value;
                }
            }
        }
    }

    return VFAT_RETURN_NAME_NOT_FOUND;
}

return_t vfat_file_get_data_for_name (
    p_vfat_volume_t vfat_volume,
    p_vfat_file_t *parent_file,
    p_vfat_file_t *file,
    const wchar_t *file_name)
{
    return_t return_value;
  
    wchar_t path_name[VFAT_MAX_PATH];
    wchar_t element_name[VFAT_MAX_PATH];
    wchar_t *current_element;
    p_vfat_file_t current_file;
    p_vfat_file_t current_parent_file;

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE, 
        L"%S: %s (%p, %p, %p, %S)\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        vfat_volume, parent_file, file, file_name);

    /*  Trivial case, open of the root directory on volume */
    if (file_name[0] == L'\0' || wstring_compare (file_name, L"/") == 0)
    {
        DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE, 
            L"%S: returning root file.\n",
            DEBUG_MODULE_NAME);

        current_file = vfat_file_open_root (vfat_volume);
        (*file) = current_file;
        (*parent_file) = NULL;

        return  (current_file != NULL) ? VFAT_RETURN_SUCCESS : 
            VFAT_RETURN_PATH_NOT_FOUND;
    }

    current_element = (wchar_t *) file_name + 1;
    wstring_copy (path_name, L"/");
    current_file = vfat_file_open_root (vfat_volume);
  
    current_parent_file = NULL;

    /*  Parse filename and check each path element for existance and access */
    while (vfat_get_next_path_element (current_element) != 0)
    {
        /*  Skip blank directory levels */
        if ((vfat_get_next_path_element (current_element) - 
             current_element) == 0)
        {
            current_element++;
            continue;
        }

        DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE, 
            L"%S: Parsing, current element:%S", 
            DEBUG_MODULE_NAME,
            current_element);
	
        DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE, 
            L"    parent file:%p, file:%p\n", 
	    current_parent_file, current_file);
        
        /*  descend to next directory level */
        if (current_parent_file)
        {
            vfat_file_release (current_parent_file);
            current_parent_file = NULL;
        }

        /*  fail if element in "file" is not a directory */
        if (!vfat_file_is_directory (current_file))
        {
            DEBUG_PRINTW (DEBUG_LEVEL_ERROR, 
                L"%S: Element in requested path is not a directory.\n",
                DEBUG_MODULE_NAME);

            vfat_file_release (current_file);

            (*parent_file) = NULL;
            (*file) = NULL;
            
            return VFAT_RETURN_PATH_NOT_FOUND;
        }
        
        current_parent_file = current_file;

        /*  Extract next directory level into dirName */
        vfat_sub_string (path_name, file_name,
            vfat_get_next_path_element (current_element) - file_name);

        DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE, 
                     L"  path name:%S", path_name);

        current_file = vfat_volume_get_file_data (vfat_volume, path_name);

        if (current_file == NULL)
        {
            vfat_sub_string (element_name, current_element,
                             vfat_get_next_path_element (current_element) - 
                             current_element);

            DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE, 
                         L"    element name:%S", element_name);

            return_value = vfat_directory_find_file (vfat_volume, 
                                               current_parent_file,
                                               element_name, &current_file);

            if (return_value == VFAT_RETURN_NAME_NOT_FOUND)
            {
                (*parent_file) = current_parent_file;
                (*file) = NULL;
	
                current_element = vfat_get_next_path_element (current_element);

                if (current_element[0] == L'\0' || 
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
                vfat_file_release (current_parent_file);

                (*parent_file) = NULL;
                (*file) = NULL;

                return return_value;
            }
        }
        current_element = vfat_get_next_path_element (current_element);
    }
    
    (*parent_file) = current_parent_file;
    (*file) = current_file;

    return VFAT_RETURN_SUCCESS;
}

