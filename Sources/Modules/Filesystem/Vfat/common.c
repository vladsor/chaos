#include <enviroment.h>

#include "Include/fat.h"
#include "Include/common.h"

/*
 * FUNCTION: Converts the cluster number to a sector number for this physical
 *           device
 */
uint32_t cluster_to_sector (
  vfat_volume_t *vfat_volume,
  uint32_t cluster)
{
  return vfat_volume->data_offset +
    ((cluster - 2) * vfat_volume->sectors_per_cluster);
}

#if FALSE
/*
 * FUNCTION: Read the volume label
 */
return_t ReadVolumeLabel (
  PDEVICE_EXTENSION DeviceExt,
  PVPB Vpb)
{
  return_t return_value;

  ULONG i = 0;
  ULONG j;
  ULONG Size;
  char *block;
  ULONG StartingSector;
  ULONG NextCluster;

  Size = DeviceExt->rootDirectorySectors;      /* FIXME : in fat32, no limit */
  StartingSector = DeviceExt->rootStart;
  NextCluster = 0;

  block = ExAllocatePool (NonPagedPool, BLOCKSIZE);

  DPRINT ("ReadVolumeLabel : start at sector %lx, entry %ld\n", StartingSector, i);
  for (j = 0; j < Size; j++)
  {
    return_value = VfatReadSectors (DeviceExt->StorageDevice, StartingSector, 1, block);

    if (return_value != VFAT_RETURN_SUCCESS)
    {
      *(Vpb->VolumeLabel) = 0;
      Vpb->VolumeLabelLength = 0;
      ExFreePool(block);
      return return_value;
    }

    for (i = 0; i < ENTRIES_PER_SECTOR; i++)
    {
      if (IsVolEntry ((PVOID) block, i))
      {
        FATDirEntry *test = (FATDirEntry *) block;

        /* copy volume label */
        vfat8Dot3ToVolumeLabel (test[i].Filename, test[i].Ext, Vpb->VolumeLabel);
        Vpb->VolumeLabelLength = wcslen (Vpb->VolumeLabel);

        ExFreePool (block);
        return VFAT_RETURN_SUCCESS;
      }

      if (IsLastEntry ((PVOID) block, i))
      {
        *(Vpb->VolumeLabel) = 0;
        Vpb->VolumeLabelLength = 0;
        ExFreePool (block);

        return VFAT_RETURN_STATUS_UNSUCCESSFULL;
      }
    }

    /* not found in this sector, try next : */

    /* directory can be fragmented although it is best to keep them
       unfragmented.*/
    StartingSector++;

    if (DeviceExt->FatType == FAT32)
    {
      if (StartingSector == ClusterToSector (DeviceExt, NextCluster + 1))
      {
        return_Value = GetNextCluster (DeviceExt, NextCluster, &NextCluster,
                                       FALSE);
        if (NextCluster == 0 || NextCluster == 0xffffffff)
        {
          *(Vpb->VolumeLabel) = 0;
          Vpb->VolumeLabelLength = 0;
          ExFreePool (block);

          return VFAT_RETURN_UNSUCCESSFULL;
        }
        
        StartingSector = ClusterToSector (DeviceExt, NextCluster);
      }
    }
  }

  *(Vpb->VolumeLabel) = 0;
  Vpb->VolumeLabelLength = 0;
  ExFreePool (block);

  return VFAT_RETURN_UNSUCCESSFULL;
}
#endif

void vfat_8_dot_3_to_string (
    uint8_t *base_name,
    uint8_t *extension,
    uint8_t *name)
{
    unsigned int from_index, to_index;
  
    from_index = to_index = 0; 

    while (from_index < 8 && base_name[from_index] != ' ')
    {
        name[to_index++] = base_name[from_index++];
    }

    if (extension[0] != ' ')
    {
        name[to_index++] = '.';

        from_index = 0;
        while (from_index < 3 && extension[from_index] != ' ')
        {
            name[to_index++] = extension[from_index++];
        }
    }

    name[to_index] = '\0';
}
