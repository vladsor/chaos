#include <enviroment.h>

#include "return_values.h"
#include "fat.h"
#include "structs.h"
#include "block_io.h"
#include "cache.h"

#include "low_fat.h"

#include "block_public.h"

#include <debug.h>
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

#define VOLUME ((vfat_volume_t *) vfat_volume)

#define  CACHE_PAGE_SIZE(vfat_volume) ( \
    (vfat_volume)->bytes_per_cluster > PAGE_SIZE ? \
    (vfat_volume)->bytes_per_cluster : PAGE_SIZE)


/*
 * FUNCTION: Retrieve the next FAT16 cluster from the FAT table
 */
return_t fat16_get_next_cluster (
  struct vfat_volume_t *vfat_volume, 
  uint32_t current_cluster,
  uint32_t *next_cluster)
{
  return_t return_value;

  void *base_address;
  bool valid;
  cache_segment_t *cache_segment;
  uint32_t fat_offset;
  uint32_t chunk_size;
  
  chunk_size = CACHE_PAGE_SIZE (VOLUME);
  
  fat_offset = (VOLUME->fat_offset * BLOCK_SIZE) + (current_cluster * 2);
 
  return_value = cache_request_segment (ROUND_DOWN (fat_offset, chunk_size),
        chunk_size, &base_address, &valid, &cache_segment);

  if (return_value != VFAT_RETURN_SUCCESS)
  {
    return return_value;
  }


  if (!valid)
  {
    return_value = vfat_read_sectors (&VOLUME->storage_device,
                              ROUND_DOWN (fat_offset, chunk_size) / BLOCK_SIZE,
                              chunk_size / BLOCK_SIZE,
                              base_address);

    if (return_value != VFAT_RETURN_SUCCESS)
    {
      cache_release_segment (cache_segment, FALSE);

      return VFAT_RETURN_SUCCESS;
    }
  }
  
  current_cluster = *((uint16_t *) ((uint8_t *) base_address + (fat_offset % chunk_size)));

  if (current_cluster >= 0xFFF8 && current_cluster <= 0xFFFF)
  {
    current_cluster = UINT32_MAX;
  }

  cache_release_segment (cache_segment, TRUE);
  (*next_cluster) = current_cluster;

  return VFAT_RETURN_SUCCESS;
}

/*
 * FUNCTION: Finds the first available cluster in a FAT16 table
 */
return_t fat16_find_available_cluster (
  struct vfat_volume_t *vfat_volume,
  uint32_t *cluster)
{
  return_t return_value;

  uint32_t fat_length;
  uint32_t i;
  void *base_address;
  cache_segment_t *cache_segment;
  bool valid;
  uint32_t fat_offset;
  uint32_t chunk_size;
  
  chunk_size = CACHE_PAGE_SIZE (VOLUME);
  
  fat_offset = VOLUME->fat_offset * BLOCK_SIZE;

  fat_length = ((VOLUME->total_volume_length - VOLUME->data_offset) /
      VOLUME->sectors_per_cluster + 2) * 2;
  
  cache_segment = NULL;
  (*cluster) = 0;

  for (i = 2 ; i < fat_length ; i += 2)
  {
    if (((fat_offset + i) % chunk_size) == 0 || cache_segment == NULL)
    {
      if (cache_segment != NULL)
      {
        cache_release_segment (cache_segment, TRUE);
      }

      return_value = cache_request_segment (
          ROUND_DOWN (fat_offset + i, chunk_size), chunk_size, &base_address,
          &valid, &cache_segment);

      if (return_value != VFAT_RETURN_SUCCESS)
      {
        return return_value;
      }
      

      if (!valid)
      {
        return_value = vfat_read_sectors (&VOLUME->storage_device,
            ROUND_DOWN (fat_offset + i, chunk_size) / BLOCK_SIZE,
            
	    chunk_size / BLOCK_SIZE, base_address);


        if (return_value != VFAT_RETURN_SUCCESS)
        {
          cache_release_segment (cache_segment, FALSE);

          return return_value;
        }
      }
    }

    if (*((uint16_t *) ((uint8_t *) base_address + ((fat_offset + i) % chunk_size))) == 0)
    {
      DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
          "Vfat: Found available cluster 0x%X\n", i);

      (*cluster) = i / 2;
      cache_release_segment (cache_segment, TRUE);

      return VFAT_RETURN_SUCCESS;
    }
  }

  cache_release_segment (cache_segment, TRUE);

  return VFAT_RETURN_DISK_FULL;
}

/*
 * FUNCTION: Counts free clusters in a FAT16 table
 */
return_t fat16_count_available_clusters (
  struct vfat_volume_t *vfat_volume,
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

  number_of_fat_clusters = (VOLUME->total_volume_length - VOLUME->data_offset) 
      / VOLUME->sectors_per_cluster + 2;

  number_of_fat_sectors = (number_of_fat_clusters + 255) / 256;
  number_of_fat_clusters %= 256;

  for (sector = 0 ; sector < number_of_fat_sectors ; sector++)
  {
    return_value = vfat_read_sectors (&VOLUME->storage_device,
        VOLUME->fat_offset + sector, 1, (uint8_t *) block);

    if (return_value != VFAT_RETURN_SUCCESS)
    {
      memory_deallocate ((void **) &block);

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

  memory_deallocate ((void **) &block);

  (*number_of_clusters) = ulCount;

  return VFAT_RETURN_SUCCESS;
}

/*
 * FUNCTION: Writes a cluster to the FAT16 physical and in-memory tables
 */
return_t fat16_write_cluster (
  struct vfat_volume_t *vfat_volume,
  uint32_t cluster_to_write,
  uint32_t new_value)
{
  return_t return_value;

  void *base_address;
  bool valid;
  cache_segment_t *cache_segment;
  uint32_t fat_offset;
  uint32_t offset;
  uint32_t i;
  uint32_t chunk_size;
  
  chunk_size = CACHE_PAGE_SIZE (VOLUME);
  
  offset = VOLUME->fat_offset;
  
  fat_offset = (offset * BLOCK_SIZE) + (cluster_to_write * 2);
  
  for (i = 0 ; i < VOLUME->number_of_fats ; i++)
  {
    return_value = cache_request_segment (ROUND_DOWN (fat_offset, chunk_size),
        chunk_size, &base_address, &valid, &cache_segment);

    if (return_value != VFAT_RETURN_SUCCESS)
    {
      return return_value;
    }

    if (!valid)
    {
      return_value = vfat_read_sectors (&VOLUME->storage_device,
          ROUND_DOWN (fat_offset, chunk_size) / BLOCK_SIZE,
          chunk_size / BLOCK_SIZE, base_address);
	  
      if (return_value != VFAT_RETURN_SUCCESS)
      {
        cache_release_segment (cache_segment, FALSE);

        return return_value;
      }
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "Vfat: Writing 0x%X for offset 0x%X 0x%X\n", 
        new_value, fat_offset, cluster_to_write);

    *((uint16_t *) ((uint8_t *) base_address + (fat_offset % chunk_size))) = new_value;

    /* FIXME: Check return value */
    return_value = vfat_write_sectors (&VOLUME->storage_device,
        ROUND_DOWN (fat_offset, chunk_size) / BLOCK_SIZE,
        chunk_size / BLOCK_SIZE, base_address);
    cache_release_segment (cache_segment, TRUE);

  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "Vfat: vfat_volume->fat_length = %u\n", VOLUME->fat_length);
  
    fat_offset = fat_offset + VOLUME->fat_length * BLOCK_SIZE;
  }

  return VFAT_RETURN_SUCCESS;
}

