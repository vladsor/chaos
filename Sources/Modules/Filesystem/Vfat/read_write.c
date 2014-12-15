#include <enviroment.h>

#include "Include/return_values.h"
#include "Include/fat.h"
#include "Include/structs.h"
#include "Include/entry.h"

#include "Include/types.h"
#include "Include/volume.h"
#include "Include/file.h"

#include "Include/low_fat.h"
#include "Include/read_write.h"

#define DEBUG_MODULE_NAME L"VFAT"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#ifndef __STORM_KERNEL__
#   define DEBUG_SUPPLIER (vfat_debug_supplier)
#endif

#include <debug/macros.h>

/*
 * Return the next cluster in a FAT chain, possibly extending the chain if
 * necessary
 */
return_t next_cluster (
    p_vfat_volume_t vfat_volume,
    uint32_t first_cluster,
    uint32_t *current_cluster,
    bool extend)
{
    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
        L"%S: %s (%p, %u, %p, %u)\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        vfat_volume, first_cluster, current_cluster, extend);
	
    if (first_cluster == 1)
    {
        (*current_cluster) += vfat_volume->sectors_per_cluster;

        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
	    "%S: %s return OK.\n",
            DEBUG_MODULE_NAME, __FUNCTION__);

        return VFAT_RETURN_SUCCESS;
    }
   /* CN: FIXME: Real bug here or in dirwr, where CurrentCluster isn't initialized when 0*/
    else if (first_cluster == 0)
    {
        return_t return_value;

        return_value = get_next_cluster (vfat_volume, 0, current_cluster, 
	    extend);

        DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
	    L"%S: %s return %u.\n",
            DEBUG_MODULE_NAME, __FUNCTION__, 
            return_value);
    
        return return_value;
    }
    else
    {
        return_t return_value;

	return_value = get_next_cluster (vfat_volume, (*current_cluster), 
	    current_cluster, extend);

        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
	    "%S: %s return %u.\n",
            DEBUG_MODULE_NAME, __FUNCTION__, 
            return_value);

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

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
        L"%S: %s (%p, %u, %u, %p, %u)\n",
	DEBUG_MODULE_NAME, __FUNCTION__, 
        vfat_volume, first_cluster, file_offset, cluster, extend);

    if (first_cluster == 1)
    {				
	/* root of FAT16 or FAT12 */
    
        (*cluster) = vfat_volume->root_offset + file_offset / 
	    vfat_volume->bytes_per_cluster * vfat_volume->sectors_per_cluster;
	    
	DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
            L"%S: %s return OK.\n",
            DEBUG_MODULE_NAME, __FUNCTION__);

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
                DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
                    L"%S: %s return %u.\n",
                    DEBUG_MODULE_NAME, __FUNCTION__, 
                    return_value);
	    
		return return_value;
	    }
	}

	(*cluster) = current_cluster;

        DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
            L"%S: %s: return OK.\n",
            DEBUG_MODULE_NAME, __FUNCTION__);

	return VFAT_RETURN_SUCCESS;
    }
}

return_t vfat_read_big_cluster (
    p_vfat_volume_t vfat_volume,
    uint32_t first_cluster,
    uint32_t *current_cluster,
    void *destination,
    uint32_t internal_offset,
    uint32_t internal_length)
{
    void *base_address = NULL;
    return_t return_value;

    if (internal_length == vfat_volume->bytes_per_cluster)
    {
        base_address = destination;
    }
    else
    {
        memory_allocate ((void **) &base_address, 
            vfat_volume->bytes_per_cluster);

        if (base_address == NULL)
        {
            return VFAT_RETURN_NO_MEMORY;
        }
    }

    /*
     * If necessary read the cluster from the disk
     */
    return_value = vfat_raw_read_cluster (vfat_volume, first_cluster, 
        base_address, (*current_cluster));

    if (return_value != VFAT_RETURN_SUCCESS)
    { 
       if (internal_length != vfat_volume->bytes_per_cluster)
       {
            memory_deallocate (base_address);
       }

       return return_value;
    }
  
    /*
     * Copy the data from the cache to the caller
     */
    if (internal_length != vfat_volume->bytes_per_cluster)
    {
        memory_copy (destination, (uint8_t *) base_address + internal_offset, 
            internal_length);
    }
    
    if (internal_length != vfat_volume->bytes_per_cluster)
    {
        memory_deallocate (base_address);
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
    p_vfat_volume_t vfat_volume,
    uint32_t first_cluster,
    uint32_t *current_cluster,
    void *destination,
    uint32_t internal_offset,
    uint32_t internal_length)
{
    return_t return_value;

    void *base_address = NULL;
    uint32_t i;

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

    /*
     * If necessary read all the data for the page, unfortunately the
     * file length may not be page aligned in which case the page will
     * only be partially filled.
     * FIXME: So zero fill the rest?
     */
    for (i = 0 ; i < (PAGE_SIZE / vfat_volume->bytes_per_cluster) ; i++)
    {
        return_value = vfat_raw_read_cluster (vfat_volume, first_cluster,
            (uint8_t *) base_address + (i * vfat_volume->bytes_per_cluster),
            (*current_cluster));
	  
        if (return_value != VFAT_RETURN_SUCCESS)
        {
            if (internal_length != PAGE_SIZE)
            {
                memory_deallocate (base_address);
            }
	
            return return_value;
        }
      
        return_value = next_cluster (vfat_volume, first_cluster, 
            current_cluster, FALSE);
	  
        if ((*current_cluster) == UINT32_MAX)
        {
            break;
        }
    }

    /*
     * Copy the data from the cache to the caller
     */
    if (internal_length != PAGE_SIZE)
    {
        memory_copy (destination, (uint8_t *) base_address + internal_offset, 
            internal_length);
    }
  
    if (internal_length != PAGE_SIZE)
    {
        memory_deallocate (base_address);
    }

    return VFAT_RETURN_SUCCESS;
}

return_t vfat_read_cluster (
    p_vfat_volume_t vfat_volume,
    uint32_t first_cluster,
    uint32_t *current_cluster,
    void *destination,
    uint32_t internal_offset,
    uint32_t internal_length)
{
    if (vfat_volume->bytes_per_cluster >= PAGE_SIZE)
    {
        return (vfat_read_big_cluster (vfat_volume,
                                       first_cluster,
                                       current_cluster,
                                       destination,
                                       internal_offset,
                                       internal_length));
    }
    else
    {
        return (vfat_read_small_cluster (vfat_volume,
                                         first_cluster,
                                         current_cluster,
                                         destination,
                                         internal_offset,
                                         internal_length));
    }
}

/*
 * FUNCTION: Reads data from a file
 */
return_t vfat_read_file (
    p_vfat_file_t file,
    void *buffer, 
    uint32_t length, 
    uint32_t read_offset,
    uint32_t *length_read)
{
    return_t return_value;
    p_vfat_volume_t vfat_volume;

    uint32_t current_cluster;
    uint32_t first_cluster;
    uint32_t chunk_size;
    uint32_t temp_length;

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
        L"%S: %s (file %p, buffer %p, length %u, offset %u)\n", 
        DEBUG_MODULE_NAME, __FUNCTION__, 
        file, buffer, length, read_offset);

    vfat_volume = file->volume;

    (*length_read) = 0;

    /*
     * Find the first cluster
     */
    if (vfat_volume->fat_type == FAT_32)
    {
        current_cluster = file->entry.first_cluster_number_low + 
            (file->entry.first_cluster_number_high << 16);
    }
    else
    {
        current_cluster = file->entry.first_cluster_number_low;
    }

    first_cluster = current_cluster;

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1,
        L"%S: %s: first cluster = %u.\n", 
        DEBUG_MODULE_NAME, __FUNCTION__,
        first_cluster);

    /*
     * Truncate the read if necessary
     */
    if (!(file->entry.attribute & FILE_ATTRIBUTE_DIRECTORY))
    {
        if (read_offset >= file->entry.file_size)
        {
            return VFAT_RETURN_END_OF_FILE;
        }
    
        if ((read_offset + length) > file->entry.file_size)
        {
            length = file->entry.file_size - read_offset;
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
    
        return_value = vfat_read_cluster (vfat_volume, first_cluster, 
            &current_cluster, buffer, read_offset % chunk_size, temp_length);

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
        return_value = vfat_read_cluster (vfat_volume, first_cluster, 
            &current_cluster, buffer, 0, chunk_size);

        if (return_value == VFAT_RETURN_SUCCESS)
        {
            (*length_read) = (*length_read) + chunk_size;
            buffer = (uint8_t *) buffer + chunk_size;
            length = length - chunk_size;
            read_offset = read_offset + chunk_size;
        }
    }

    if ((length > 0) && (current_cluster != UINT32_MAX) && 
        (return_value == VFAT_RETURN_SUCCESS))
    {
        return_value = vfat_read_cluster (vfat_volume, first_cluster, 
            &current_cluster, buffer, 0, length);

        if (return_value == VFAT_RETURN_SUCCESS)
        {
            (*length_read) = (*length_read) + length;
        }
    }
  
    return return_value;
}

return_t vfat_write_big_cluster (
    p_vfat_volume_t vfat_volume,
    uint32_t first_cluster,
    uint32_t *current_cluster,
    void *source,
    uint32_t internal_offset,
    uint32_t internal_length,
    bool extend)
{
    return_t return_value;

    void *base_address;

    /*
     * If we are bypassing the cache and not writing starting on
     * cluster boundary then allocate a temporary buffer
     */
    if (internal_length != vfat_volume->bytes_per_cluster)
    {
        memory_allocate ((void **) &base_address, 
            vfat_volume->bytes_per_cluster);

        if (base_address == NULL)
        {
            return VFAT_RETURN_NO_MEMORY;
        }
    }

    if (internal_length != vfat_volume->bytes_per_cluster)
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
            if (internal_length != vfat_volume->bytes_per_cluster)
            {
                memory_deallocate (base_address);
            }
      
            return return_value;
        }

        /*
         * If we are writing into the cache or we are writing from a
         * temporary buffer then copy the data over
         */
        DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
            L"%S: %s: internal offset: 0x%X, length: 0x%X, base: %p.\n",
            DEBUG_MODULE_NAME, __FUNCTION__,
            internal_offset, internal_length, base_address);

        memory_copy ((uint8_t *) base_address + internal_offset, source, 
            internal_length);
    }

    /*
     * Write the data back to disk
     */
    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
        L"%S: Writing to 0x%X.\n", 
        DEBUG_MODULE_NAME,
        (*current_cluster));

    return_value = vfat_raw_write_cluster (vfat_volume, first_cluster, 
        base_address, (*current_cluster));
      
    if (internal_length != vfat_volume->bytes_per_cluster)
    {
        memory_deallocate (base_address);
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
    p_vfat_volume_t vfat_volume,
    uint32_t first_cluster,
    uint32_t *current_cluster,
    void *source,
    uint32_t internal_offset,
    uint32_t internal_length,
    bool extend)
{
    return_t return_value;

    void *base_address;
    uint32_t next_cluster_number;
    uint32_t i;

    /*
     * Otherwise we read a page of clusters together
     */

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

    /*
     * If necessary read all the data for the page, unfortunately the
     * file length may not be page aligned in which case the page will
     * only be partially filled.
     * FIXME: So zero fill the rest?
     */
    if (internal_length != PAGE_SIZE)
    {
        next_cluster_number = (*current_cluster);

        for (i = 0 ; i < (PAGE_SIZE / vfat_volume->bytes_per_cluster) ; i++)
        {
            return_value = vfat_raw_read_cluster (vfat_volume, first_cluster,
               (uint8_t *) base_address + (i * vfat_volume->bytes_per_cluster),
               next_cluster_number);
	  
            if (return_value != VFAT_RETURN_SUCCESS)
            {
                if (internal_length != PAGE_SIZE)
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
            next_cluster (vfat_volume, first_cluster, &next_cluster_number, 
                extend);
      
            if (next_cluster_number == UINT32_MAX)
            {
                break;
            }
        }
    }

    if (internal_length != PAGE_SIZE)
    {
        /*
         * Copy the caller's data if we are using the cache or writing
         * from temporary buffer
         */
        memory_copy ((uint8_t *) base_address + internal_offset, source, 
            internal_length);
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
            if (internal_length != PAGE_SIZE)
            {
                memory_deallocate (base_address);
            }
      
            return return_value;
        }

        // FIXME: Overwriting the variable Extend isn't correct,
        //        but when VFatWriteFile writes the last cache segment,
        //        than is Extend set to FALSE. We must extend,
        //        when the data needs a next cluster.

        if ((i < (PAGE_SIZE / vfat_volume->bytes_per_cluster) - 1) &&
            (internal_offset + internal_length > (i + 1) * 
            vfat_volume->bytes_per_cluster))
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

    if (internal_length != PAGE_SIZE)
    {
        memory_deallocate (base_address);
    }

    return VFAT_RETURN_SUCCESS;
}

return_t vfat_write_cluster (
    p_vfat_volume_t vfat_volume,
    uint32_t first_cluster,
    uint32_t *current_cluster,
    void *source,
    uint32_t internal_offset,
    uint32_t internal_length,
    bool extend)
{

    if (vfat_volume->bytes_per_cluster >= PAGE_SIZE)
    {
        return (vfat_write_big_cluster (vfat_volume,
                                        first_cluster,
                                        current_cluster,
                                        source,
                                        internal_offset,
                                        internal_length,
                                        extend));
    }
    else
    {
        return (vfat_write_small_cluster (vfat_volume,
                                          first_cluster,
                                          current_cluster,
                                          source,
                                          internal_offset,
                                          internal_length,
                                          extend));
    }
}

/*
 * FUNCTION: Writes data to file
 */
return_t vfat_write_file (
    p_vfat_file_t file,
    void *buffer, 
    uint32_t length, 
    uint32_t write_offset)
{
    return_t return_value;
    p_vfat_volume_t vfat_volume;

    uint32_t current_cluster;
    uint32_t first_cluster;
    uint32_t temp_length;
    uint32_t chunk_size;
    bool extend;

//  LARGE_INTEGER SystemTime, LocalTime;

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
        L"%S: %s (file %p, buffer %p, length %u, offset %u).\n", 
        DEBUG_MODULE_NAME, __FUNCTION__, 
        file, buffer, length, write_offset);

    vfat_volume = file->volume;

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
        current_cluster = file->entry.first_cluster_number_low + 
            (file->entry.first_cluster_number_high << 16);
    }
    else
    {
        current_cluster = file->entry.first_cluster_number_low;
    }

    first_cluster = current_cluster;
  
    /* Find the cluster according to the offset in the file */
    if (current_cluster == 0)
    {
        /*
         * File of size zero
         */
        return_value = next_cluster (vfat_volume, first_cluster, 
            &current_cluster, TRUE);
	
        if (vfat_volume->fat_type == FAT_32)
        {
            file->entry.first_cluster_number_high = current_cluster >> 16;
            file->entry.first_cluster_number_low = current_cluster && 0xFFFF;
        }
        else
        {
            file->entry.first_cluster_number_low = current_cluster;
        }

        first_cluster = current_cluster;
    }
  
    return_value = offset_to_cluster (vfat_volume, first_cluster,
        ROUND_DOWN (write_offset, chunk_size), &current_cluster, TRUE);

    if (write_offset + length > file->entry.file_size &&
        !(file->entry.attribute & FILE_ATTRIBUTE_DIRECTORY))
    {
        file->entry.file_size = write_offset + length;
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
    
        return_value = vfat_write_cluster (vfat_volume, first_cluster,
            &current_cluster, buffer, write_offset % chunk_size, temp_length,
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

        return_value = vfat_write_cluster (vfat_volume, first_cluster,
            &current_cluster, buffer, 0, chunk_size, extend);

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
        return_value = vfat_write_cluster (vfat_volume, first_cluster,
            &current_cluster, buffer, 0, length, FALSE);

        if (return_value == VFAT_RETURN_SUCCESS)
        {
            length = 0;
        }
    }


    /* set dates and times */
    if (!(file->entry.attribute & FILE_ATTRIBUTE_DIRECTORY))
    {
/*
    KeQuerySystemTime (&SystemTime);
    ExSystemTimeToLocalTime (&SystemTime, &LocalTime);
    FsdFileTimeToDosDateTime ((TIME*)&LocalTime,
				&file->entry.UpdateDate,
				&file->entry.UpdateTime);
    file->entry.AccessDate = file->entry.UpdateDate;
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

