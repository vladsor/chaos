#include <enviroment.h>

#include "Include/return_values.h"
#include "Include/fat.h"
#include "Include/structs.h"
#include "Include/block_io.h"
#include "Include/entry.h"

#include "Include/types.h"
#include "Include/volume.h"

#include "Include/low_fat.h"

#define DEBUG_MODULE_NAME L"VFAT"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#ifndef __STORM_KERNEL__
#   define DEBUG_SUPPLIER (vfat_debug_supplier)
#endif

#include <debug/macros.h>

#define  CACHE_PAGE_SIZE(vfat_volume) ( \
    (vfat_volume)->bytes_per_cluster > PAGE_SIZE ? \
    (vfat_volume)->bytes_per_cluster : PAGE_SIZE)


/*
 * FUNCTION: Retrieve the next FAT16 cluster from the FAT table
 */
return_t fat16_get_next_cluster (
    p_vfat_volume_t vfat_volume, 
    uint32_t current_cluster,
    uint32_t *next_cluster)
{
    return_t return_value;

    void *base_address;
    uint32_t fat_offset;
    uint32_t chunk_size;
  
    chunk_size = CACHE_PAGE_SIZE (vfat_volume);
  
    fat_offset = (vfat_volume->fat_offset * BLOCK_SIZE) + 
        (current_cluster * 2);
 
    return_value = memory_allocate (&base_address, chunk_size);

    if (return_value != STORM_RETURN_SUCCESS)
    {
        return return_value;
    }

    return_value = vfat_read_sectors (vfat_volume->storage_device,
        ROUND_DOWN (fat_offset, chunk_size) / BLOCK_SIZE, 
        chunk_size / BLOCK_SIZE, base_address);

    if (return_value != VFAT_RETURN_SUCCESS)
    {
        memory_deallocate (base_address);

        return VFAT_RETURN_SUCCESS;
    }
 
    current_cluster = *((uint16_t *) ((uint8_t *) base_address + 
        (fat_offset % chunk_size)));

    if (current_cluster >= 0xFFF8 && current_cluster <= 0xFFFF)
    {
        current_cluster = UINT32_MAX;
    }

    memory_deallocate (base_address);

    (*next_cluster) = current_cluster;

    return VFAT_RETURN_SUCCESS;
}

/*
 * FUNCTION: Finds the first available cluster in a FAT16 table
 */
return_t fat16_find_available_cluster (
    p_vfat_volume_t vfat_volume,
    uint32_t *cluster)
{
    return_t return_value;

    uint32_t fat_length;
    uint32_t i;
    void *base_address;
    uint32_t fat_offset;
    uint32_t chunk_size;
  
    chunk_size = CACHE_PAGE_SIZE (vfat_volume);
  
    fat_offset = vfat_volume->fat_offset * BLOCK_SIZE;

    fat_length = ((vfat_volume->total_volume_length - 
        vfat_volume->data_offset) / vfat_volume->sectors_per_cluster + 2) * 2;
  
    (*cluster) = 0;

    return_value = memory_allocate (&base_address, chunk_size);

    if (return_value != STORM_RETURN_SUCCESS)
    {
        return return_value;
    }


    for (i = 2 ; i < fat_length ; i += 2)
    {
        if (((fat_offset + i) % chunk_size) == 0 || i == 2)
        {
            return_value = vfat_read_sectors (vfat_volume->storage_device,
                ROUND_DOWN (fat_offset + i, chunk_size) / BLOCK_SIZE,
                chunk_size / BLOCK_SIZE, base_address);


            if (return_value != VFAT_RETURN_SUCCESS)
            {
                memory_deallocate (base_address);
                
                return return_value;
            }

        }

        if (*((uint16_t *) ((uint8_t *) base_address + 
            ((fat_offset + i) % chunk_size))) == 0)
        {
            DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1, 
                L"%S: Found available cluster 0x%X\n", 
                DEBUG_MODULE_NAME,
                i);

            (*cluster) = i / 2;
            
            memory_deallocate (base_address);

            return VFAT_RETURN_SUCCESS;
        }
    }

    memory_deallocate (base_address);

    return VFAT_RETURN_DISK_FULL;
}

/*
 * FUNCTION: Counts free clusters in a FAT16 table
 */
return_t fat16_count_available_clusters (
    p_vfat_volume_t vfat_volume,
    uint32_t *number_of_clusters)
{
    return_t return_value;

    uint16_t *block;
    uint32_t ulCount = 0;
    uint32_t i;
    uint32_t number_of_fat_clusters;
    uint32_t number_of_fat_sectors;
    uint32_t sector;
    uint32_t forto;

    memory_allocate ((void **) &block, BLOCK_SIZE);

    number_of_fat_clusters = (vfat_volume->total_volume_length -
        vfat_volume->data_offset) / vfat_volume->sectors_per_cluster + 2;

    number_of_fat_sectors = (number_of_fat_clusters + 255) / 256;
    number_of_fat_clusters %= 256;

    for (sector = 0 ; sector < number_of_fat_sectors ; sector++)
    {
        return_value = vfat_read_sectors (vfat_volume->storage_device,
            vfat_volume->fat_offset + sector, 1, (uint8_t *) block);

        if (return_value != VFAT_RETURN_SUCCESS)
        {
            memory_deallocate (block);

            return return_value;
        }

        if (sector == number_of_fat_sectors - 1)
        {
            forto = number_of_fat_clusters;
        }
        else
        {
            forto = 256;
        }

        for (i = 0 ; i < forto ; i++)
        {
            if (block[i] == 0)
            {
                ulCount++;
            }
        }
    }

    memory_deallocate (block);

    (*number_of_clusters) = ulCount;

    return VFAT_RETURN_SUCCESS;
}

/*
 * FUNCTION: Writes a cluster to the FAT16 physical and in-memory tables
 */
return_t fat16_write_cluster (
    p_vfat_volume_t vfat_volume,
    uint32_t cluster_to_write,
    uint32_t new_value)
{
    return_t return_value;

    void *base_address;
    
    uint32_t fat_offset;
    uint32_t offset;
    uint32_t i;
    uint32_t chunk_size;
  
    chunk_size = CACHE_PAGE_SIZE (vfat_volume);
  
    offset = vfat_volume->fat_offset;
  
    fat_offset = (offset * BLOCK_SIZE) + (cluster_to_write * 2);
  
    return_value = memory_allocate (&base_address, chunk_size);

    if (return_value != STORM_RETURN_SUCCESS)
    {
        return return_value;
    }

    for (i = 0 ; i < vfat_volume->number_of_fats ; i++)
    {
        return_value = vfat_read_sectors (vfat_volume->storage_device,
            ROUND_DOWN (fat_offset, chunk_size) / BLOCK_SIZE,
            chunk_size / BLOCK_SIZE, base_address);
	  
        if (return_value != VFAT_RETURN_SUCCESS)
        {
            memory_deallocate (base_address);

            return return_value;
        }
    

        DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE, 
            L"%S: Writing 0x%X for offset 0x%X 0x%X\n", 
            DEBUG_MODULE_NAME,
            new_value, fat_offset, cluster_to_write);

        *((uint16_t *) ((uint8_t *) base_address + 
            (fat_offset % chunk_size))) = new_value;

        /* FIXME: Check return value */
        return_value = vfat_write_sectors (vfat_volume->storage_device,
            ROUND_DOWN (fat_offset, chunk_size) / BLOCK_SIZE,
            chunk_size / BLOCK_SIZE, base_address);

        DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE, 
            L"%S: vfat_volume->fat_length = %u\n", 
            DEBUG_MODULE_NAME,
            vfat_volume->fat_length);
  
        fat_offset = fat_offset + vfat_volume->fat_length * BLOCK_SIZE;
    }

    memory_deallocate (base_address);

    return VFAT_RETURN_SUCCESS;
}

