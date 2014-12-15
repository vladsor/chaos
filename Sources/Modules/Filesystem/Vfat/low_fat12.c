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

/*
 * FUNCTION: Retrieve the next FAT12 cluster from the FAT table
 */
return_t fat12_get_next_cluster (
    p_vfat_volume_t vfat_volume, 
    uint32_t current_cluster,
    uint32_t *next_cluster)
{
    return_t return_value;

    void *base_address;
  
    uint32_t fat_offset;
    uint32_t entry;
    uint8_t *block;

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE, 
        L"%S: %s ()\n", 
        DEBUG_MODULE_NAME, __FUNCTION__);

    return_value = memory_allocate (&base_address, vfat_volume->fat_length);

    if (return_value != STORM_RETURN_SUCCESS)
    {
        return return_value;
    }

    return_value = vfat_read_sectors (vfat_volume->storage_device,
        vfat_volume->fat_offset, vfat_volume->fat_length, base_address);

    if (return_value != VFAT_RETURN_SUCCESS)
    {
        memory_deallocate (base_address);

        return return_value;
    }


    block = (uint8_t *) base_address;

    /* first byte containing value */ 
    fat_offset = (current_cluster * 12) / 8; 

    if ((current_cluster % 2) == 0)
    {
        entry = block[fat_offset];
        entry |= ((block[fat_offset + 1] & 0xF) << 8);
    }
    else
    {
        entry = (block[fat_offset] >> 4);
        entry |= (block[fat_offset + 1] << 4);
    }

    if (entry >= 0xFF8 && entry <= 0xFFF)
    {
        entry = UINT32_MAX;
    }

    (*next_cluster) = entry;

    memory_deallocate (base_address);

    return VFAT_RETURN_SUCCESS;
}

/*
 * FUNCTION: Finds the first available cluster in a FAT12 table
 */
return_t fat12_find_available_cluster (
    p_vfat_volume_t vfat_volume,
    uint32_t *cluster)
{
    return_t return_value;

    void *base_address;
  
    uint32_t fat_offset;
    uint32_t entry;
    uint8_t *block;
    uint32_t i;
    uint32_t number_of_clusters;

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE, 
        L"%S: %s ()\n", 
        DEBUG_MODULE_NAME, __FUNCTION__);
  
    (*cluster) = 0;
  
    return_value = memory_allocate (&base_address, vfat_volume->fat_length);

    if (return_value != STORM_RETURN_SUCCESS)
    {
        return return_value;
    }

    return_value = vfat_read_sectors (vfat_volume->storage_device,
        vfat_volume->fat_offset, vfat_volume->fat_length, base_address);

    if (return_value != VFAT_RETURN_SUCCESS)
    {
        memory_deallocate (base_address);

        return return_value;
    }

    block = (uint8_t *) base_address;

    number_of_clusters = (vfat_volume->total_volume_length - 
        vfat_volume->data_offset) / vfat_volume->sectors_per_cluster + 2;

    for (i = 2 ; i < number_of_clusters ; i++)
    {
        fat_offset = (i * 12) / 8;
        if ((i % 2) == 0)
        {
            entry = block[fat_offset];
            entry |= ((block[fat_offset + 1] & 0xF) << 8);
        }
        else
        {
            entry = (block[fat_offset] >> 4);
            entry |= (block[fat_offset + 1] << 4);
        }
        if (entry == 0)
        {
            DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1, 
                L"%S: Found available cluster 0x%X\n", 
                DEBUG_MODULE_NAME,
                i);

            (*cluster) = i;
            memory_deallocate (base_address);

            return VFAT_RETURN_SUCCESS;
        }
    }

    memory_deallocate (base_address);

    return VFAT_RETURN_DISK_FULL;
}

/*
 * FUNCTION: Counts free cluster in a FAT12 table
 */
return_t fat12_count_available_clusters (
    p_vfat_volume_t vfat_volume,
    uint32_t *number_of_clusters)
{
    return_t return_value;

    void *base_address;
    uint32_t fat_offset;
    uint32_t entry;
    uint8_t *block;
    uint32_t clusters_count = 0;
    uint32_t i;

    uint32_t number_of_fat_clusters;

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE, 
        L"%S: %s ()\n", 
        DEBUG_MODULE_NAME, __FUNCTION__);

    return_value = memory_allocate (&base_address, vfat_volume->fat_length);

    if (return_value != STORM_RETURN_SUCCESS)
    {
        return return_value;
    }

    return_value = vfat_read_sectors (vfat_volume->storage_device,
        vfat_volume->fat_offset, vfat_volume->fat_length, base_address);

    if (return_value != VFAT_RETURN_SUCCESS)
    {
        memory_deallocate (base_address);
        
        return return_value;
    }

    block = (uint8_t *) base_address;
    number_of_fat_clusters = (vfat_volume->total_volume_length - 
        vfat_volume->data_offset) / vfat_volume->sectors_per_cluster + 2;
  
    for (i = 2 ; i < number_of_fat_clusters ; i++)
    {
        fat_offset = (i * 12) / 8;
        if ((i % 2) == 0)
        {
            entry = block[fat_offset];
            entry |= ((block[fat_offset + 1] & 0xF) << 8);
        }
        else
        {
            entry = (block[fat_offset] >> 4);
            entry |= (block[fat_offset + 1] << 4);
        }

        if (entry == 0)
        {
            clusters_count++;
        }
    }

    memory_deallocate (base_address);

    (*number_of_clusters) = clusters_count;

    return VFAT_RETURN_SUCCESS;
}

/*
 * FUNCTION: Writes a cluster to the FAT12 physical and in-memory tables
 */
return_t fat12_write_cluster (
    p_vfat_volume_t vfat_volume, 
    uint32_t cluster_to_write,
    uint32_t new_value)
{
    return_t return_value;

    uint8_t *block;
    void *base_address;

    uint32_t fat_sector;
    uint32_t fat_offset;
    uint32_t i;

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE, 
        L"%S: %s ()\n", 
        DEBUG_MODULE_NAME, __FUNCTION__);

    return_value = memory_allocate (&base_address, vfat_volume->fat_length);

    if (return_value != STORM_RETURN_SUCCESS)
    {
        return return_value;
    }

    return_value = vfat_read_sectors (vfat_volume->storage_device,
        vfat_volume->fat_offset, vfat_volume->fat_length, base_address);

    if (return_value != VFAT_RETURN_SUCCESS)
    {
        memory_deallocate (base_address);
        
        return return_value;
    }
  
    block = (uint8_t *) base_address;

    fat_offset = (cluster_to_write * 12) / 8;

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1, 
        L"%S: Writing 0x%X for 0x%X at 0x%X\n",
        DEBUG_MODULE_NAME,
        new_value, cluster_to_write, fat_offset);

    if ((cluster_to_write % 2) == 0)
    {
        block[fat_offset] = new_value;
        block[fat_offset + 1] &= 0xF0;
        block[fat_offset + 1] |= (new_value & 0xF00) >> 8;
    }
    else
    {
        block[fat_offset] &= 0x0F;
        block[fat_offset] |= (new_value & 0xF) << 4;
        block[fat_offset + 1] = new_value >> 4;
    }

    /* Write the changed FAT sector(s) to disk */

    fat_sector = fat_offset / BLOCK_SIZE;
  
    for (i = 0 ; i < vfat_volume->number_of_fats ; i++)
    {
        /* if entry is on 2 sectors */
        if ((fat_offset % BLOCK_SIZE) == (BLOCK_SIZE - 1))   
        {
            /* FIXME: Check status */
            vfat_write_sectors (vfat_volume->storage_device,
                vfat_volume->fat_offset + fat_sector + 
                i * vfat_volume->fat_length, 2, 
                block + fat_sector * BLOCK_SIZE);
        }
        else
        {
            /* FIXME: Check status */
            vfat_write_sectors (vfat_volume->storage_device,
                vfat_volume->fat_offset + fat_sector + 
                i * vfat_volume->fat_length, 1, 
                block + fat_sector * BLOCK_SIZE);
        }
    }
    memory_deallocate (base_address);

    return VFAT_RETURN_SUCCESS;
}

