
#include <enviroment.h>

#include "return_values.h"
#include "fat.h"
#include "structs.h"
#include "block_io.h"
#include "cache.h"
#include "common.h"
#include "low_fat.h"

#include <debug.h>
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

/*
 * FUNCTION: Load a cluster from the physical device
 */
return_t vfat_raw_read_cluster (
  vfat_volume_t *vfat_volume,
  uint32_t first_cluster,
  void *buffer,
  uint32_t cluster)
{
  return_t return_value;

  if (first_cluster == 1)
  {
    return_value = vfat_read_sectors (&vfat_volume->storage_device, cluster,
        vfat_volume->sectors_per_cluster, buffer);

    return return_value;
  }
  else
  {
    uint32_t sector;
      
    sector = cluster_to_sector (vfat_volume, cluster);
      
    return_value = vfat_read_sectors (&vfat_volume->storage_device, sector,
        vfat_volume->sectors_per_cluster, buffer);

    return return_value;
  }
}

/*
 * FUNCTION: Write a cluster to the physical device
 */
return_t vfat_raw_write_cluster (
  vfat_volume_t *vfat_volume,
  uint32_t first_cluster,
  void *buffer,
  uint32_t cluster)
{
  return_t return_value;

  uint32_t sector;

  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
      "Vfat: %s (vfat_volume: %p, buffer: %p, cluster: %u)\n",
      __FUNCTION__, vfat_volume, buffer, cluster);

  if (first_cluster == 1)
  {
    return_value = vfat_write_sectors (&vfat_volume->storage_device, cluster,
        vfat_volume->sectors_per_cluster, buffer);
  }
  else
  {
    sector = cluster_to_sector (vfat_volume, cluster);
      
    return_value = vfat_write_sectors (&vfat_volume->storage_device, sector,
        vfat_volume->sectors_per_cluster, buffer);
  }
  
  return return_value;
}

/*
 * FUNCTION: Retrieve the next cluster depending on the FAT type
 */
return_t get_next_cluster (
    vfat_volume_t *vfat_volume,
    uint32_t current_cluster,
    uint32_t *next_cluster,
    bool extend)
{
    return_t return_value;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "Vfat: %s (volume: %p, current cluster: %u, %p, %u)\n",
        __FUNCTION__, vfat_volume, current_cluster, next_cluster, extend);
  
    /*
     * If the file hasn't any clusters allocated then we need special
     * handling
     */
    if ((current_cluster == 0) && extend)
    {
        uint32_t new_cluster;

	return_value = vfat_volume->find_available_cluster (
    	    (struct vfat_volume_t *) vfat_volume, &new_cluster);

        if (return_value != VFAT_RETURN_SUCCESS)
	{
    	    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
		"Vfat: %s return %u.\n",
		__FUNCTION__, return_value);

            return return_value;
	}

        /* Mark the new AU as the EOF */
	vfat_volume->write_cluster ((struct vfat_volume_t *) vfat_volume, 
	    new_cluster, UINT32_MAX);
        (*next_cluster) = new_cluster;

        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
	    "Vfat: %s return %u.\n",
	    __FUNCTION__, VFAT_RETURN_SUCCESS);

	return VFAT_RETURN_SUCCESS;
    }
    else if (current_cluster == 0)
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
	    "Vfat: %s return %u.\n",
	    __FUNCTION__, VFAT_RETURN_UNSUCCESSFULL);
    
	return VFAT_RETURN_UNSUCCESSFULL;
    }

    return_value = vfat_volume->get_next_cluster (
        (struct vfat_volume_t *) vfat_volume, current_cluster, next_cluster);

    if (extend && ((*next_cluster) == UINT32_MAX))
    {
        uint32_t new_cluster;

	/* We are after last existing cluster, we must add one to file */
	/* Firstly, find the next available open allocation unit */

        return_value = vfat_volume->find_available_cluster (
	    (struct vfat_volume_t *) vfat_volume, &new_cluster);

        if (return_value != VFAT_RETURN_SUCCESS)
	{
    	    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
		"Vfat: %s return %u.\n",
		__FUNCTION__, return_value);
		
            return return_value;
        }

        /* Mark the new AU as the EOF */
	vfat_volume->write_cluster ((struct vfat_volume_t *) vfat_volume, 
	    new_cluster, UINT32_MAX);

        /* Now, write the AU of the LastCluster with the value of the newly
	   found AU */
        vfat_volume->write_cluster ((struct vfat_volume_t *) vfat_volume, 
	    current_cluster, new_cluster);
    
	(*next_cluster) = new_cluster;
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "Vfat: %s return %u.\n",
	__FUNCTION__, return_value);

    return return_value;
}

/* Some functions don't have access to the cluster they're really reading from.
   Maybe this is a dirty solution, but it will allow them to handle fragmentation. */
return_t get_next_sector (
  vfat_volume_t *vfat_volume,
  uint32_t current_sector,
  uint32_t *next_sector,
  bool extend)
{
  return_t return_value;

  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
      "Vfat: %s (volume: %p, current sector: %X)\n",
      __FUNCTION__, vfat_volume, current_sector);

  /* Basically, if the next sequential sector would be on a cluster border, then we'll need to check in the FAT */
  if (current_sector < vfat_volume->data_offset || ((current_sector - 
        vfat_volume->data_offset + 1) % vfat_volume->sectors_per_cluster))
  {
    (*next_sector) = current_sector + 1;

    return VFAT_RETURN_SUCCESS;
  }
  else
  {
    current_sector = (current_sector - vfat_volume->data_offset) / 
        vfat_volume->sectors_per_cluster + 2;

    return_value = get_next_cluster (vfat_volume, current_sector, next_sector, 
        extend);

    if (return_value != VFAT_RETURN_SUCCESS)
    {
      return return_value;
    }

    if ((*next_sector) == 0 || (*next_sector) == UINT32_MAX)
    {
      /* The caller wants to know a sector. These FAT codes don't correspond to any sector. */
      return VFAT_RETURN_UNSUCCESSFULL;
    }

    (*next_sector) = cluster_to_sector (vfat_volume, (*next_sector));

    return VFAT_RETURN_SUCCESS;
  }
}

