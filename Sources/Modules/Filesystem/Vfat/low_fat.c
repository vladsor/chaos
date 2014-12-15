#include <enviroment.h>

#include "Include/return_values.h"

#include "Include/fat.h"
#include "Include/structs.h"
#include "Include/block_io.h"
#include "Include/entry.h"

#include "Include/types.h"
#include "Include/volume.h"

#include "Include/common.h"
#include "Include/low_fat.h"

#define DEBUG_MODULE_NAME L"VFAT"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#ifndef __STORM_KERNEL__
#   define DEBUG_SUPPLIER (vfat_debug_supplier)
#endif

#include <debug/macros.h>

/*
 * FUNCTION: Load a cluster from the physical device
 */
return_t vfat_raw_read_cluster (
    p_vfat_volume_t vfat_volume,
    uint32_t first_cluster,
    void *buffer,
    uint32_t cluster)
{
    return_t return_value;

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
        L"%S: %s (vfat_volume: %p, %u, buffer: %p, cluster: %u)\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        vfat_volume, first_cluster, buffer, cluster);

    if (first_cluster == 1)
    {
        return_value = vfat_read_sectors (vfat_volume->storage_device, 
            cluster, vfat_volume->sectors_per_cluster, buffer);

        return return_value;
    }
    else
    {
        uint32_t sector;
      
        sector = cluster_to_sector (vfat_volume, cluster);
      

        return_value = vfat_read_sectors (vfat_volume->storage_device, sector,
            vfat_volume->sectors_per_cluster, buffer);

        return return_value;
    }
}

/*
 * FUNCTION: Write a cluster to the physical device
 */
return_t vfat_raw_write_cluster (
    p_vfat_volume_t vfat_volume,
    uint32_t first_cluster,
    void *buffer,
    uint32_t cluster)
{
    return_t return_value;

    uint32_t sector;

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
        L"%S: %s (vfat_volume: %p, %u, buffer: %p, cluster: %u)\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        vfat_volume, first_cluster, buffer, cluster);

    if (first_cluster == 1)
    {
        return_value = vfat_write_sectors (vfat_volume->storage_device, 
            cluster, vfat_volume->sectors_per_cluster, buffer);
    }
    else
    {
        sector = cluster_to_sector (vfat_volume, cluster);
      
        return_value = vfat_write_sectors (vfat_volume->storage_device, 
            sector, vfat_volume->sectors_per_cluster, buffer);
    }
  
    return return_value;
}

/*
 * FUNCTION: Retrieve the next cluster depending on the FAT type
 */
return_t get_next_cluster (
    p_vfat_volume_t vfat_volume,
    uint32_t current_cluster,
    uint32_t *next_cluster,
    bool extend)
{
    return_t return_value;

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
        L"%S: %s (volume: %p, current cluster: %u, %p, %u)\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        vfat_volume, current_cluster, next_cluster, extend);
  
    /*
     * If the file hasn't any clusters allocated then we need special
     * handling
     */
    if ((current_cluster == 0) && extend)
    {
        uint32_t new_cluster;

	return_value = vfat_volume->find_available_cluster (
    	    vfat_volume, &new_cluster);

        if (return_value != VFAT_RETURN_SUCCESS)
	{
    	    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
		L"%S: %s return %u.\n",
		DEBUG_MODULE_NAME, __FUNCTION__, 
                return_value);

            return return_value;
	}

        /* Mark the new AU as the EOF */
	vfat_volume->write_cluster (vfat_volume, new_cluster, UINT32_MAX);
        (*next_cluster) = new_cluster;

        DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
	    L"%S: %s return OK.\n",
	    DEBUG_MODULE_NAME, __FUNCTION__);

	return VFAT_RETURN_SUCCESS;
    }
    else if (current_cluster == 0)
    {
        DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
	    L"%S: %s return FAIL.\n",
	    DEBUG_MODULE_NAME, __FUNCTION__);
    
	return VFAT_RETURN_UNSUCCESSFULL;
    }

    return_value = vfat_volume->get_next_cluster (vfat_volume, current_cluster,
        next_cluster);

    if (extend && ((*next_cluster) == UINT32_MAX))
    {
        uint32_t new_cluster;

	/* We are after last existing cluster, we must add one to file */
	/* Firstly, find the next available open allocation unit */

        return_value = vfat_volume->find_available_cluster (vfat_volume, 
            &new_cluster);

        if (return_value != VFAT_RETURN_SUCCESS)
	{
    	    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
		L"%S: %s return %u.\n",
		DEBUG_MODULE_NAME, __FUNCTION__, 
                return_value);
		
            return return_value;
        }

        /* Mark the new AU as the EOF */
	vfat_volume->write_cluster (vfat_volume, new_cluster, UINT32_MAX);

        /* Now, write the AU of the LastCluster with the value of the newly
	   found AU */
        vfat_volume->write_cluster (vfat_volume, current_cluster, new_cluster);
    
	(*next_cluster) = new_cluster;
    }

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
        L"%S: %s return %u.\n",
	DEBUG_MODULE_NAME, __FUNCTION__, 
        return_value);

    return return_value;
}

/* Some functions don't have access to the cluster they're really reading from.
   Maybe this is a dirty solution, but it will allow them to handle 
   fragmentation. */
return_t get_next_sector (
    p_vfat_volume_t vfat_volume,
    uint32_t current_sector,
    uint32_t *next_sector,
    bool extend)
{
    return_t return_value;

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
        L"%S: %s (volume: %p, current sector: %X)\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        vfat_volume, current_sector);

    /* Basically, if the next sequential sector would be on a cluster border, 
       then we'll need to check in the FAT */
    if (current_sector < vfat_volume->data_offset || 
        ((current_sector - vfat_volume->data_offset + 1) % 
         vfat_volume->sectors_per_cluster))
    {
        (*next_sector) = current_sector + 1;

        return VFAT_RETURN_SUCCESS;
    }
    else
    {
        current_sector = (current_sector - vfat_volume->data_offset) / 
            vfat_volume->sectors_per_cluster + 2;

        return_value = get_next_cluster (vfat_volume, current_sector, 
            next_sector, extend);

        if (return_value != VFAT_RETURN_SUCCESS)
        {
            return return_value;
        }

        if ((*next_sector) == 0 || (*next_sector) == UINT32_MAX)
        {
            /* The caller wants to know a sector. These FAT codes don't 
               correspond to any sector. */
            return VFAT_RETURN_UNSUCCESSFULL;
        }

        (*next_sector) = cluster_to_sector (vfat_volume, (*next_sector));

        return VFAT_RETURN_SUCCESS;
    }
}

