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

#define  CACHE_PAGE_SIZE(vfat_volume) ( \
    (vfat_volume)->bytes_per_cluster > PAGE_SIZE ? \
    (vfat_volume)->bytes_per_cluster : PAGE_SIZE)

#define  ENTRIES_PER_CACHE_PAGE(vfat_volume)  (ENTRIES_PER_SECTOR * \
    (CACHE_PAGE_SIZE (vfat_volume) / ((vfat_volume)->bytes_per_sector)))


uint32_t vfat_directory_entry_get_first_cluster (
    p_vfat_volume_t vfat_volume,
    p_fat_entry_t fat_entry)
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

bool vfat_directory_entry_is_deleted (
    p_fat_entry_t fat_entry)
{
    return (fat_entry->file_name[0] == 0xE5);
}

bool vfat_directory_entry_is_end_marker (
    p_fat_entry_t fat_entry)
{
    return (fat_entry->file_name[0] == 0);
}

bool vfat_directory_entry_is_long_name (
    p_fat_entry_t fat_entry)
{
    return (fat_entry->attribute == 0x0F);
}

bool vfat_directory_entry_is_volume (
    p_fat_entry_t fat_entry)
{
    return (fat_entry->attribute == 0x28);
}

void vfat_directory_entry_get_name (
    p_fat_entry_t fat_entry,
    wchar_t *entry_name)
{
    vfat_8_dot_3_to_wstring (fat_entry->file_name, fat_entry->extension, 
        entry_name);
}

return_t vfat_directory_entry_get_next (
    p_vfat_file_t directory_file,
    uint32_t *directory_index,
    wchar_t *file_name,
    p_fat_entry_t directory_entry)
{
    return_t return_value;
    p_vfat_volume_t vfat_volume;

    uint32_t chunk_size;
    uint32_t index_in_page;
    uint32_t page_number;
    p_uint8_t current_page = NULL;
    p_fat_entry_t fat_entry;
    p_lfn_fat_entry_t long_name_entry;
    bool is_lfn_entry = FALSE;

    vfat_volume = directory_file->volume;

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
        L"%S: %s (%p, %p, %p, %p, %p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        vfat_volume, directory_file, directory_index, file_name,
        directory_entry);

    index_in_page = (*directory_index) % ENTRIES_PER_CACHE_PAGE (vfat_volume);
    page_number = (*directory_index) / ENTRIES_PER_CACHE_PAGE (vfat_volume);
    (*file_name) = 0;

    chunk_size = CACHE_PAGE_SIZE (vfat_volume);

    return_value = memory_allocate ((void **) &current_page, chunk_size);

    if (return_value != STORM_RETURN_SUCCESS)
    {
        return return_value;
    }

    return_value = vfat_file_read_region (
        directory_file, page_number * CACHE_PAGE_SIZE (vfat_volume), 
        current_page, FALSE);

    if (return_value != VFAT_RETURN_SUCCESS)
    {
        return return_value;
    }

    while (TRUE)
    {
        fat_entry = (p_fat_entry_t) current_page;

        if (vfat_directory_entry_is_end_marker (&fat_entry [index_in_page]))
        {
            DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE, 
                L"%S: end of directory, returning no more entries.\n",
                DEBUG_MODULE_NAME);

            memory_deallocate (current_page);

            return VFAT_RETURN_NO_MORE_ENTRIES;
        }
        else if (!vfat_directory_entry_is_long_name (&fat_entry [index_in_page])
                 && 
                 !vfat_directory_entry_is_deleted (&fat_entry [index_in_page]) 
                 && !is_lfn_entry)
        {
            memory_copy (directory_entry, &fat_entry[index_in_page], 
                         sizeof (fat_entry_t));

            vfat_directory_entry_get_name (&fat_entry[index_in_page], 
                                           file_name);
            (*directory_index)++;

            break;
        }
        else if (vfat_directory_entry_is_long_name (&fat_entry [index_in_page])
                 && 
                 !vfat_directory_entry_is_deleted (&fat_entry [index_in_page]))
        {
            int i, j;
            ucs2_t ucs2_name[256];
            int number_of_lfn;
        
            DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
                         L"    long name entry found at %u", (*directory_index));
      
            is_lfn_entry = TRUE;

            long_name_entry = (p_lfn_fat_entry_t) current_page;
        
            memory_clear (ucs2_name, 256 * sizeof (ucs2_t));

            memory_copy (ucs2_name + 0, long_name_entry[index_in_page].name0_4, 
                         5 * sizeof (ucs2_t));
            memory_copy (ucs2_name + 5, long_name_entry[index_in_page].name5_10,
                         6 * sizeof (ucs2_t));
            memory_copy (ucs2_name + 11, 
                         long_name_entry[index_in_page].name11_12, 
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
              
                    return_value = vfat_file_read_region (
                        directory_file, 
                        page_number * CACHE_PAGE_SIZE (vfat_volume),
                        current_page, FALSE);

                    if (return_value != VFAT_RETURN_SUCCESS)
                    {
                        memory_deallocate (current_page);
                        return return_value;
                    }

                    long_name_entry = (p_lfn_fat_entry_t) current_page;
                }

                DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE, 
                            L"    index = %u to %p", 
                            (*directory_index), ucs2_name + number_of_lfn * 13);
                memory_copy (ucs2_name + number_of_lfn * 13 + 0, 
                             long_name_entry[index_in_page].name0_4, 5 * 
                             sizeof (ucs2_t));
                memory_copy (ucs2_name + number_of_lfn * 13 + 5, 
                             long_name_entry[index_in_page].name5_10, 6 * 
                             sizeof (ucs2_t));
                memory_copy (ucs2_name + number_of_lfn *13 + 11, 
                             long_name_entry[index_in_page].name11_12, 2 * 
                             sizeof (ucs2_t));

                number_of_lfn++; 
            }

            for (i = number_of_lfn - 1 ; i >= 0 ; i--)
            {
                for (j = 0 ; j < 13 ; j++)
                {
                    file_name[j + i * 13] = ucs2_name[j + i * 13];
                }
            }
            
            DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE, 
                         L"    long file name: [%S]", file_name);

            (*directory_index)++;
            index_in_page++;

            if (index_in_page == ENTRIES_PER_CACHE_PAGE (vfat_volume))
            {
                index_in_page = 0;
                page_number++;

                return_value = vfat_file_read_region (
                    directory_file, page_number * CACHE_PAGE_SIZE (vfat_volume),
                    current_page, FALSE);

                if (return_value != VFAT_RETURN_SUCCESS)
                {
                    memory_deallocate (current_page);
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

    memory_deallocate (current_page);

    return return_value;
}
