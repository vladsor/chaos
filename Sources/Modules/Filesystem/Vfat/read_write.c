#include <enviroment.h>

#include "Include/fat.h"
#include "Include/structs.h"
#include "Include/cache.h"
#include "Include/file.h"
#include "Include/return_values.h"
#include "Include/low_fat.h"
#include "Include/read_write.h"

#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

/*
 * Return the next cluster in a FAT chain, possibly extending the chain if
 * necessary
 */
return_t next_cluster (
    vfat_volume_t *vfat_volume,
    uint32_t first_cluster,
    uint32_t *current_cluster,
    bool extend)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "Vfat: %s (%p, %u, %p, %u)\n",
        __FUNCTION__, 
        vfat_volume, first_cluster, current_cluster, extend);
	
    if (first_cluster == 1)
    {
        (*current_cluster) += vfat_volume->sectors_per_cluster;

        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
	    "Vfat: %s return %u.\n",
	__FUNCTION__, VFAT_RETURN_SUCCESS);

        return VFAT_RETURN_SUCCESS;
    }
    else
   /* CN: FIXME: Real bug here or in dirwr, where CurrentCluster isn't initialized when 0*/
    if (first_cluster == 0)
    {
        return_t return_value;

        return_value = get_next_cluster (vfat_volume, 0, current_cluster, 
	    extend);

        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
	    "Vfat: %s return %u.\n",
	__FUNCTION__, return_value);
    
        return return_value;
    }
    else
    {
        return_t return_value;

	return_value = get_next_cluster (vfat_volume, (*current_cluster), 
	    current_cluster, extend);

        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
	    "Vfat: %s return %u.\n",
	__FUNCTION__, return_value);

        return return_value;
    }
}

/*
 * Return the cluster corresponding to an offset within a file,
 * possibly extending the file if necessary
 */

return_t offset_to_cluster (
    vfat_volume_t *vfat_volume,
    uint32_t first_cluster, 
    uint32_t file_offset,
    uint32_t *cluster,
    bool extend)
{
    return_t return_value;

    uint32_t current_cluster;
    uint32_t i;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "Vfat: %s (%p, %u, %u, %p, %u)\n",
	__FUNCTION__, vfat_volume, first_cluster, file_offset, cluster, extend);

    if (first_cluster == 1)
    {				
	/* root of FAT16 or FAT12 */
    
        (*cluster) = vfat_volume->root_offset + file_offset / 
	    vfat_volume->bytes_per_cluster * vfat_volume->sectors_per_cluster;
	    
	DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
	    "Vfat: %s return %u.\n",
	    __FUNCTION__, VFAT_RETURN_SUCCESS);

	return VFAT_RETURN_SUCCESS;
    }
    else
    {
	current_cluster = first_cluster;

	for (i = 0 ; i < file_offset / vfat_volume->bytes_per_cluster ; i++)
	{
	    return_value = get_next_cluster (vfat_volume, current_cluster, 
		&current_cluster, extend);

	    if (return_value != VFAT_RETURN_SUCCESS)
	    {
	        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
		    "Vfat: %s return %u.\n",
		    __FUNCTION__, return_value);
	    
		return return_value;
	    }
	}

	(*cluster) = current_cluster;

        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
	    "Vfat: %s return %u.\n",
    	    __FUNCTION__, VFAT_RETURN_SUCCESS);

	return VFAT_RETURN_SUCCESS;
    }
}

return_t vfat_read_big_cluster (
  vfat_volume_t *vfat_volume,
  vfat_file_t *fcb UNUSED,
  uint32_t start_offset,
  uint32_t first_cluster,
  uint32_t *current_cluster,
  void *destination,
  uint32_t no_cache,
  uint32_t internal_offset,
  uint32_t internal_length)
{
  bool valid;
  void *base_address = NULL;
  cache_segment_t *cache_segment = NULL;
  return_t return_value;

  /*
   * In this case the size of a cache segment is the same as a cluster
   */

  if (!no_cache)
  {
     return_value = cache_request_segment (start_offset,
       vfat_volume->bytes_per_cluster, &base_address, &valid, &cache_segment);

    if (return_value != VFAT_RETURN_SUCCESS)
    {
      return return_value;
    }
  }
  else
  {
    valid = FALSE;

    if (internal_length == vfat_volume->bytes_per_cluster)
    {
      base_address = destination;
    }
    else
    {
      memory_allocate ((void **) &base_address, vfat_volume->bytes_per_cluster);

      if (base_address == NULL)
      {
        return VFAT_RETURN_NO_MEMORY;
      }
    }
  }

  if (!valid)
  {
    /*
     * If necessary read the cluster from the disk
     */
    return_value = vfat_raw_read_cluster (vfat_volume, first_cluster, 
        base_address, (*current_cluster));

    if (return_value != VFAT_RETURN_SUCCESS)
    { 
       if (!no_cache)
       {
           cache_release_segment (cache_segment, FALSE);
       }
       else if (internal_length != vfat_volume->bytes_per_cluster)
       {
            memory_deallocate ((void **) &base_address);
       }

       return return_value;
    }
  }

  /*
   * Copy the data from the cache to the caller
   */
  if (internal_length != vfat_volume->bytes_per_cluster || !no_cache)
  {
    memory_copy (destination, (uint8_t *) base_address + internal_offset, 
        internal_length);
  }

  if (!no_cache)
  {
    cache_release_segment (cache_segment, TRUE);
  }
  else if (internal_length != vfat_volume->bytes_per_cluster)
  {
    memory_deallocate ((void **) &base_address);
  }

  return_value = next_cluster (vfat_volume, first_cluster, current_cluster, 
      FALSE);
      
  if (return_value != VFAT_RETURN_SUCCESS)
  {
    return return_value;
  }
  
  return VFAT_RETURN_SUCCESS;
}

return_t vfat_read_small_cluster (
  vfat_volume_t *vfat_volume,
  vfat_file_t *fcb UNUSED,
  uint32_t start_offset,
  uint32_t first_cluster,
  uint32_t *current_cluster,
  void *destination,
  uint32_t no_cache,
  uint32_t internal_offset,
  uint32_t internal_length)
{
  return_t return_value;

  bool valid;
  void *base_address = NULL;
  cache_segment_t *cache_segment = NULL;
  uint32_t i;

  /*
   * Otherwise we read a page of clusters together
   */
  if (!no_cache)
  {
    return_value = cache_request_segment (start_offset, PAGE_SIZE, 
        &base_address, &valid, &cache_segment);
	
    if (return_value != VFAT_RETURN_SUCCESS)
    {
      return return_value;
    }
  }
  else
  {
    valid = FALSE;
    
    if (internal_length == PAGE_SIZE)
    {
      base_address = destination;
    }
    else
    {
       memory_allocate ((void **) &base_address, PAGE_SIZE);
       
       if (base_address == NULL)
       {
         return VFAT_RETURN_NO_MEMORY;
       }
    }
  }

  /*
   * If necessary read all the data for the page, unfortunately the
   * file length may not be page aligned in which case the page will
   * only be partially filled.
   * FIXME: So zero fill the rest?
   */
  if (!valid)
  {
    for (i = 0 ; i < (PAGE_SIZE / vfat_volume->bytes_per_cluster) ; i++)
    {
      return_value = vfat_raw_read_cluster (vfat_volume, first_cluster,
          (uint8_t *) base_address + (i * vfat_volume->bytes_per_cluster),
 
	  (*current_cluster));
	  
      if (return_value != VFAT_RETURN_SUCCESS)
      {
        if (!no_cache)
        {
           cache_release_segment (cache_segment, FALSE);
        }
        else if (internal_length != PAGE_SIZE)
        {
          memory_deallocate ((void **) &base_address);
        }
	
        return return_value;
      }
      
      return_value = next_cluster (vfat_volume, first_cluster, current_cluster, 
          FALSE);
	  
      if ((*current_cluster) == UINT32_MAX)
      {
        break;
      }
    }
  }
  else
  {
    /*
     * Otherwise just move onto the next cluster
     */
    for (i = 0 ; i < (PAGE_SIZE / vfat_volume->bytes_per_cluster) ; i++)
    {
      next_cluster (vfat_volume, first_cluster, current_cluster, FALSE);
      
      if ((*current_cluster) == UINT32_MAX)
      {
        break;
      }
    }
  }
  
  /*
   * Copy the data from the cache to the caller
   */
  if (internal_length != PAGE_SIZE || !no_cache)
  {
    memory_copy (destination, (uint8_t *) base_address + internal_offset, 
        internal_length);
  }
  
  if (!no_cache)
  {
    cache_release_segment (cache_segment, valid || 
        internal_length == PAGE_SIZE ? TRUE : FALSE);
  }
  else if (internal_length != PAGE_SIZE)
  {
    memory_deallocate ((void **) &base_address);
  }

  return VFAT_RETURN_SUCCESS;
}

return_t vfat_read_cluster (
  vfat_volume_t *vfat_volume,
  vfat_file_t *fcb,
  uint32_t start_offset,
  uint32_t first_cluster,
  uint32_t *current_cluster,
  void *destination,
  uint32_t no_cache,
  uint32_t internal_offset,
  uint32_t internal_length)
{
  if (vfat_volume->bytes_per_cluster >= PAGE_SIZE)
  {
    return (vfat_read_big_cluster (vfat_volume,
                  fcb,
			      start_offset,
			      first_cluster,
			      current_cluster,
			      destination,
			      no_cache,
			      internal_offset,
			      internal_length));
  }
  else
  {
    return (vfat_read_small_cluster (vfat_volume,
				fcb,
				start_offset,
				first_cluster,
				current_cluster,
				destination,
				no_cache,
				internal_offset,
				internal_length));
  }
}

/*
 * FUNCTION: Reads data from a file
 */
return_t vfat_read_file (
  vfat_volume_t *vfat_volume, 
  vfat_file_t *fcb,
  void *buffer, 
  uint32_t length, 
  uint32_t read_offset,
  uint32_t *length_read, 
  uint32_t no_cache)
{
  return_t return_value;

  uint32_t current_cluster;
  uint32_t first_cluster;
  uint32_t chunk_size;
  uint32_t temp_length;

  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
      "Vfat: %s (vfat_volume %p, fcb %p, buffer %p, length %u, "
      "read offset 0x%X)\n", 
      __FUNCTION__, vfat_volume, fcb, buffer, length, read_offset);

  (*length_read) = 0;

  /*
   * Find the first cluster
   */
  if (vfat_volume->fat_type == FAT_32)
  {
    current_cluster = fcb->entry.first_cluster_number_low + 
        (fcb->entry.first_cluster_number_high << 16);
  }
  else
  {
    current_cluster = fcb->entry.first_cluster_number_low;
  }

  first_cluster = current_cluster;

  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
      "first cluster = %u.\n", first_cluster);

  /*
   * Truncate the read if necessary
   */
  if (!(fcb->entry.attribute & FILE_ATTRIBUTE_DIRECTORY))
  {
    if (read_offset >= fcb->entry.file_size)
    {
      return VFAT_RETURN_END_OF_FILE;
    }
    
    if ((read_offset + length) > fcb->entry.file_size)
    {
       length = fcb->entry.file_size - read_offset;
    }
  }

  if (first_cluster == 1)
  {
    /* root directory of FAT12 od FAT16 */
    if (read_offset + length > vfat_volume->root_length * BLOCK_SIZE)
    {
      length = vfat_volume->root_length * BLOCK_SIZE - read_offset;
    }
  }

  /*
   * Select an appropiate size for reads
   */
  if (vfat_volume->bytes_per_cluster >= PAGE_SIZE)
  {
    chunk_size = vfat_volume->bytes_per_cluster;
  }
  else
  {
    chunk_size = PAGE_SIZE;
  }

  /*
   * Find the cluster to start the read from
   * FIXME: Optimize by remembering the last cluster read and using if
   * possible.
   */
  return_value = offset_to_cluster (vfat_volume, first_cluster,
       ROUND_DOWN (read_offset, chunk_size), &current_cluster, FALSE);

  if (return_value != VFAT_RETURN_SUCCESS)
  {
    return return_value;
  }

  /*
   * If the read doesn't begin on a chunk boundary then we need special
   * handling
   */
  if ((read_offset % chunk_size) != 0 )
  {
    temp_length = MIN (length, chunk_size - (read_offset % chunk_size));
    
    return_value = vfat_read_cluster (vfat_volume, fcb, 
        ROUND_DOWN (read_offset, chunk_size), first_cluster, &current_cluster, 
        buffer, no_cache, read_offset % chunk_size, temp_length);

    if (return_value == VFAT_RETURN_SUCCESS)
    {
      (*length_read) = (*length_read) + temp_length;
      length = length - temp_length;
      buffer = (uint8_t *) buffer + temp_length;
      read_offset = read_offset + temp_length;
    }
  }

  while (length >= chunk_size && current_cluster != UINT32_MAX && 
         return_value == VFAT_RETURN_SUCCESS)
  {
    return_value = vfat_read_cluster (vfat_volume, fcb, read_offset,
         first_cluster, &current_cluster, buffer, no_cache, 0, chunk_size);

    if (return_value == VFAT_RETURN_SUCCESS)
    {
      (*length_read) = (*length_read) + chunk_size;
      buffer = (uint8_t *) buffer + chunk_size;
      length = length - chunk_size;
      read_offset = read_offset + chunk_size;
    }
  }

  if (length > 0 && current_cluster != UINT32_MAX && 
      return_value == VFAT_RETURN_SUCCESS)
  {
    return_value = vfat_read_cluster (vfat_volume, fcb, read_offset,
         first_cluster, &current_cluster, buffer, no_cache, 0, length);

    if (return_value == VFAT_RETURN_SUCCESS)
    {
      (*length_read) = (*length_read) + length;
    }
  }
  
  return return_value;
}

return_t vfat_write_big_cluster (
  vfat_volume_t *vfat_volume,
  vfat_file_t *fcb UNUSED,
  uint32_t start_offset,
  uint32_t first_cluster,
  uint32_t *current_cluster,
  void *source,
  uint32_t no_cache,
  uint32_t internal_offset,
  uint32_t internal_length,
  bool extend)
{
  return_t return_value;

  bool valid;
  void *base_address;
  cache_segment_t *cache_segment;

  /*
   * In this case the size of a cache segment is the same as a cluster
   */
  if (!no_cache)
  {
    return_value = cache_request_segment (start_offset,
         vfat_volume->bytes_per_cluster, &base_address, &valid, &cache_segment);
	
    if (return_value != VFAT_RETURN_SUCCESS)
    {
      return return_value;
    }
  }
  else
  {
    valid = FALSE;

    /*
     * If we are bypassing the cache and not writing starting on
     * cluster boundary then allocate a temporary buffer
     */
    if (internal_length != vfat_volume->bytes_per_cluster)
    {
      memory_allocate ((void **) &base_address, vfat_volume->bytes_per_cluster);

      if (base_address == NULL)
      {
        return VFAT_RETURN_NO_MEMORY;
      }
    }
  }

  if (!valid && internal_length != vfat_volume->bytes_per_cluster)
  {
    /*
     * If the data in the cache isn't valid or we are bypassing the
     * cache and not writing a cluster aligned, cluster sized region
     * then read data in to base address
     */
    return_value = vfat_raw_read_cluster (vfat_volume, first_cluster, 
        base_address, (*current_cluster));

    if (return_value != VFAT_RETURN_SUCCESS)
    {
      if (!no_cache)
      {
        cache_release_segment (cache_segment, FALSE);
      }
      else if (internal_length != vfat_volume->bytes_per_cluster)
      {
        memory_deallocate ((void **) &base_address);
      }
      
      return return_value;
    }
  }

  if (!no_cache || internal_length != vfat_volume->bytes_per_cluster)
  {
    /*
     * If we are writing into the cache or we are writing from a
     * temporary buffer then copy the data over
     */
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "internal offset: 0x%X, internal length: 0x%X, base address: %p.\n",
        internal_offset, internal_length, base_address);

    memory_copy ((uint8_t *) base_address + internal_offset, source, internal_length);
  }

  /*
   * Write the data back to disk
   */
  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
      "Writing to 0x%X.\n", (*current_cluster));

  return_value = vfat_raw_write_cluster (vfat_volume, first_cluster, 
      base_address, (*current_cluster));
      
  if (!no_cache)
  {
    cache_release_segment (cache_segment, TRUE);
  }
  else if (internal_length != vfat_volume->bytes_per_cluster)
  {
    memory_deallocate ((void **) &base_address);
  }

  return_value = next_cluster (vfat_volume, first_cluster, current_cluster, 
      extend);

  if (return_value != VFAT_RETURN_SUCCESS)
  {
    return return_value;
  }

  return VFAT_RETURN_SUCCESS;
}

return_t vfat_write_small_cluster (
  vfat_volume_t *vfat_volume,
  vfat_file_t *fcb UNUSED,
  uint32_t start_offset,
  uint32_t first_cluster,
  uint32_t *current_cluster,
  void *source,
  uint32_t no_cache,
  uint32_t internal_offset,
  uint32_t internal_length,
  bool extend)
{
  return_t return_value;

  bool valid;
  void *base_address;
  cache_segment_t *cache_segment;
  uint32_t next_cluster_number;
  uint32_t i;

  /*
   * Otherwise we read a page of clusters together
   */

  if (!no_cache)
  {
    return_value = cache_request_segment (start_offset, PAGE_SIZE, 
        &base_address, &valid, &cache_segment);
	
    if (return_value != VFAT_RETURN_SUCCESS)
    {
      return return_value;
    }
  }
  else
  {
    valid = FALSE;

    if (internal_length != PAGE_SIZE)
    {
      memory_allocate ((void **) &base_address, PAGE_SIZE);

      if (base_address == NULL)
      {
        return VFAT_RETURN_NO_MEMORY;
      }
    }
    else
    {
      base_address = source;
    }
  }

  /*
   * If necessary read all the data for the page, unfortunately the
   * file length may not be page aligned in which case the page will
   * only be partially filled.
   * FIXME: So zero fill the rest?
   */
  if (!valid || internal_length != PAGE_SIZE)
  {
    next_cluster_number = (*current_cluster);

    for (i = 0 ; i < (PAGE_SIZE / vfat_volume->bytes_per_cluster) ; i++)
    {
      return_value = vfat_raw_read_cluster (vfat_volume, first_cluster,
          (uint8_t *) base_address + (i * vfat_volume->bytes_per_cluster),
 
	  next_cluster_number);
	  
      if (return_value != VFAT_RETURN_SUCCESS)
      {
        if (!no_cache)
        {
          cache_release_segment (cache_segment, FALSE);
        }
        else if (internal_length != PAGE_SIZE)
        {
          memory_deallocate ((void **) &base_address);
        }

        return return_value;
      }

      return_value = next_cluster (vfat_volume, first_cluster, 
          &next_cluster_number, extend);

      if (next_cluster_number == UINT32_MAX)
      {
        break;
      }
    }
  }
  else
  {
    /*
     * Otherwise just move onto the next cluster
     */
    next_cluster_number = (*current_cluster);
    
    for (i = 0 ; i < (PAGE_SIZE / vfat_volume->bytes_per_cluster) ; i++)
    {
      next_cluster (vfat_volume, first_cluster, &next_cluster_number, extend);
      
      if (next_cluster_number == UINT32_MAX)
      {
        break;
      }
    }
  }

  if (!no_cache || internal_length != PAGE_SIZE)
  {
    /*
     * Copy the caller's data if we are using the cache or writing
     * from temporary buffer
     */
    memory_copy ((uint8_t *) base_address + internal_offset, source, internal_length);
  }

  /*
   * Write the data to the disk
   */
  next_cluster_number = (*current_cluster);

  for (i = 0 ; i < (PAGE_SIZE / vfat_volume->bytes_per_cluster) ; i++)
  {
    return_value = vfat_raw_write_cluster (vfat_volume, first_cluster,
        (uint8_t *) base_address + (i * vfat_volume->bytes_per_cluster),
 
	next_cluster_number);

    if (return_value != VFAT_RETURN_SUCCESS)
    {
      if (!no_cache)
      {
        cache_release_segment (cache_segment, FALSE);
      }
      else if (internal_length != PAGE_SIZE)
      {
        memory_deallocate ((void **) &base_address);
      }
      
      return return_value;
    }

    // FIXME: Overwriting the variable Extend isn't correct,
    //        but when VFatWriteFile writes the last cache segment,
    //        than is Extend set to FALSE. We must extend,
    //        when the data needs a next cluster.
    if (i < (PAGE_SIZE / vfat_volume->bytes_per_cluster) - 1 &&
        internal_offset + internal_length > (i + 1) * 
        vfat_volume->bytes_per_cluster)
    {
      extend = TRUE;
    }
    else
    {
      extend = FALSE;
    }

    return_value = next_cluster (vfat_volume, first_cluster, 
        &next_cluster_number, extend);
	
    if (next_cluster_number == UINT32_MAX)
    {
      break;
    }
  }

  (*current_cluster) = next_cluster_number;

  if (!no_cache)
  {
    cache_release_segment (cache_segment, valid || 
        internal_length == PAGE_SIZE ? TRUE : FALSE);
  }
  else if (internal_length != PAGE_SIZE)
  {
    memory_deallocate ((void **) &base_address);
  }

  return VFAT_RETURN_SUCCESS;
}

return_t vfat_write_cluster (
  vfat_volume_t *vfat_volume,
  vfat_file_t *fcb,
  uint32_t start_offset,
  uint32_t first_cluster,
  uint32_t *current_cluster,
  void *source,
  uint32_t no_cache,
  uint32_t internal_offset,
  uint32_t internal_length,
  bool extend)
{

  if (vfat_volume->bytes_per_cluster >= PAGE_SIZE)
  {
    return (vfat_write_big_cluster (vfat_volume,
			       fcb,
			       start_offset,
			       first_cluster,
			       current_cluster,
			       source,
			       no_cache,
			       internal_offset,
			       internal_length,
			       extend));
  }
  else
  {
    return (vfat_write_small_cluster (vfat_volume,
				 fcb,
				 start_offset,
				 first_cluster,
				 current_cluster,
				 source,
				 no_cache,
				 internal_offset,
				 internal_length,
				 extend));
  }
}

/*
 * FUNCTION: Writes data to file
 */
return_t vfat_write_file (
  vfat_volume_t *vfat_volume,
  vfat_file_t *fcb,
  void *buffer, 
  uint32_t length, 
  uint32_t write_offset,
  uint32_t no_cache)
{
  return_t return_value;

  uint32_t current_cluster;
  uint32_t first_cluster;
  uint32_t temp_length;
  uint32_t chunk_size;
  bool extend;

//  LARGE_INTEGER SystemTime, LocalTime;

  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
    "Vfat %s (fcb %p, buffer %p, length %X, write_offset %X).\n", 
    __FUNCTION__, fcb, buffer, length, write_offset);

  /* Locate the first cluster of the file */
  if (vfat_volume->bytes_per_cluster >= PAGE_SIZE)
  {
    chunk_size = vfat_volume->bytes_per_cluster;
  }
  else
  {
    chunk_size = PAGE_SIZE;
  }

  if (vfat_volume->fat_type == FAT_32)
  {
    current_cluster = fcb->entry.first_cluster_number_low + 
        (fcb->entry.first_cluster_number_high << 16);
  }
  else
  {
    current_cluster = fcb->entry.first_cluster_number_low;
  }

  first_cluster = current_cluster;
  
  /* Find the cluster according to the offset in the file */
  if (current_cluster == 0)
  {
    /*
     * File of size zero
     */
    return_value = next_cluster (vfat_volume, first_cluster, &current_cluster, 
        TRUE);
	
    if (vfat_volume->fat_type == FAT_32)
    {
      fcb->entry.first_cluster_number_high = current_cluster >> 16;
      fcb->entry.first_cluster_number_low = current_cluster && 0xFFFF;
    }
    else
    {
      fcb->entry.first_cluster_number_low = current_cluster;
    }

    first_cluster = current_cluster;
  }
  
  return_value = offset_to_cluster (vfat_volume, first_cluster,
       ROUND_DOWN (write_offset, chunk_size), &current_cluster, TRUE);

  if (write_offset + length > fcb->entry.file_size &&
      !(fcb->entry.attribute & FILE_ATTRIBUTE_DIRECTORY))
  {
    fcb->entry.file_size = write_offset + length;
  }

  if (first_cluster == 1)
  {
    /* root directory of FAT12 od FAT16 */
    if (write_offset + length > vfat_volume->root_length * BLOCK_SIZE)
    {
      return VFAT_RETURN_END_OF_FILE;
    }
  }

  /*
   * If the offset in the cluster doesn't fall on the cluster boundary
   * then we have to write only from the specified offset
   */

  return_value = VFAT_RETURN_SUCCESS;

  if ((write_offset % chunk_size) != 0)
  {
    temp_length = MIN (length, chunk_size - (write_offset % chunk_size));

    if ((length - temp_length) > 0)
    {
      extend = TRUE;
    }
    else
    {
      extend = FALSE;
    }
    
    return_value = vfat_write_cluster (vfat_volume,
			      fcb,
			      ROUND_DOWN (write_offset, chunk_size),
			      first_cluster,
			      &current_cluster,
			      buffer,
			      no_cache,
			      write_offset % chunk_size,
			      temp_length,
			      extend);
			      
    if (return_value == VFAT_RETURN_SUCCESS)
    {
      buffer = (uint8_t *) buffer + temp_length;
      length = length - temp_length;
      write_offset = write_offset + temp_length;
    }
  }

  while (length >= chunk_size && current_cluster != UINT32_MAX && 
         return_value == VFAT_RETURN_SUCCESS)
  {
    if ((length - chunk_size) > 0)
    {
      extend = TRUE;
    }
    else
    {
      extend = FALSE;
    }

    return_value = vfat_write_cluster (vfat_volume,
			      fcb,
			      ROUND_DOWN (write_offset, chunk_size),
			      first_cluster,
			      &current_cluster,
			      buffer,
			      no_cache,
			      0,
			      chunk_size,
			      extend);

    if (return_value != VFAT_RETURN_SUCCESS)
    {
      break;
    }

    buffer = (uint8_t *) buffer + chunk_size;
    length = length - chunk_size;
    write_offset = write_offset + chunk_size;
  }

  /* Write the remainder */
  if (length > 0 && current_cluster != UINT32_MAX && 
      return_value == VFAT_RETURN_SUCCESS)
  {
    return_value = vfat_write_cluster (vfat_volume,
			      fcb,
			      ROUND_DOWN (write_offset, chunk_size),
			      first_cluster,
			      &current_cluster,
			      buffer,
			      no_cache,
			      0,
		              length,
			      FALSE);

    if (return_value == VFAT_RETURN_SUCCESS)
    {
      length = 0;
    }
  }


  /* set dates and times */
  if (!(fcb->entry.attribute & FILE_ATTRIBUTE_DIRECTORY))
  {
/*
    KeQuerySystemTime (&SystemTime);
    ExSystemTimeToLocalTime (&SystemTime, &LocalTime);
    FsdFileTimeToDosDateTime ((TIME*)&LocalTime,
				&Fcb->entry.UpdateDate,
				&Fcb->entry.UpdateTime);
    Fcb->entry.AccessDate = Fcb->entry.UpdateDate;
    updEntry (DeviceExt, FileObject);
*/
  }

  if (return_value != VFAT_RETURN_SUCCESS)
  {
    return return_value;
  }
 
  if (length > 0)
  {
    return VFAT_RETURN_DISK_FULL;
  }
  
  return VFAT_RETURN_SUCCESS;
}

