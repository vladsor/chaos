#include <enviroment.h>
#include <string.h>

#include "Include/return_values.h"
#include "Include/fat.h"
#include "Include/structs.h"
#include "Include/block_io.h"
#include "Include/cache.h"
#include "Include/common.h"

#include "Include/low_fat.h"
#include "Include/file.h"
#include "Include/directory.h"
#include "Include/dirwr.h"
#include "Include/read_write.h"
#include "Include/create.h"
#include "Include/string.h"

#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

/*
 * FUNCTION: Determine if the given directory entry is the last
 */
static bool is_last_entry (
    void *block,
    uint32_t offset)
{
    return (((fat_entry_t *) block)[offset].file_name[0] == 0);
}

/*
 * FUNCTION: Determine if the given directory entry is a vol entry
 */
static bool is_vol_entry (
  void *block,
  uint32_t offset)
{
    return ((((fat_entry_t *) block)[offset].attribute) == 0x28)
;
}

/*
 * FUNCTION: Determines if the given entry is a deleted one
 */
static bool is_deleted_entry (
    void *block,
    uint32_t offset)
{
  /* Checks special character */

    return ((((fat_entry_t *) block)[offset].file_name[0] == 0xE5) ||
	    (((fat_entry_t *) block)[offset].file_name[0] == 0));
}
#if 0
void vfat_8_dot_3_to_string (
  uint8_t *base_name,
  uint8_t *extension,
  uint8_t *name)
{
  int from_index, to_index;

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
#endif
static void vfat_8_dot_3_to_volume_label (
  uint8_t *base_name,
  uint8_t *extension,
  uint8_t *name)
{
  int from_index, to_index;

  from_index = to_index = 0; 
  
  while (from_index < 8 && base_name[from_index] != ' ')
  {
    name[to_index++] = base_name[from_index++];
  }
  
  if (extension[0] != ' ')
  {
    from_index = 0;
    while (from_index < 3 && extension[from_index] != ' ')
    {
      name[to_index++] = extension[from_index++];
    }
  }

  name [to_index] = '\0';
}

/*
 * FUNCTION: Retrieves the file name, be it in short or long file name format
 */
return_t get_entry_name (
  vfat_volume_t *vfat_volume,
  void *block,
  file_handle_t file_handle,
  uint8_t *name,
  uint32_t *index,
  uint32_t *index2)
{
    return_t return_value;
    fat_entry_t *test;
    lfn_fat_entry_t *test2;
    uint32_t cpos;
    uint32_t offset = (*index) % ENTRIES_PER_SECTOR;
    uint32_t read;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	"Vfat: %s (%p, %p, %u, %p, %p, %p)\n",
	__FUNCTION__, vfat_volume, block,
 file_handle,
 name,
 index,
 index2);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	"Vfat: %s (%s, %u, %u)\n",
	__FUNCTION__, name,
 (*index),
 (*index2));

    (*name) = 0;
  
    while (TRUE)
    {
	test = (fat_entry_t *) block;
	test2 = (lfn_fat_entry_t *) block;

	if (vfat_is_directory_entry_end_marker (&test[offset]))
	{
	    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
		"Vfat: %s return NO MORE ENTRIES.\n",
		__FUNCTION__);
		
	    return VFAT_RETURN_NO_MORE_ENTRIES;
	}

	if (test2[offset].attribute == 0x0f && 
	    !fat_entry_is_deleted (&test[offset]))
	{
	    (*name) = 0;
	    
	    if (index2)
	    {
		(*index2) = (*index); // start of dir entry
	    }

	    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	         "  long name entry found at %d\n", 
	         *index);

	    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
	         "  name chunk1:[%.5s] chunk2:[%.6s] chunk3:[%.2s]\n",
	         test2[offset].name0_4,
	         test2[offset].name5_10,
	         test2[offset].name11_12);

//	    vfat_initstr (name, 255);
//	    vfat_wcsncpy (name, test2[offset].name0_4, 5);
//	    vfat_wcsncat (name, test2[offset].name5_10, 5, 6);
//	    vfat_wcsncat (name, test2[offset].name11_12, 11, 2);

	    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	         "  longName: [%s]\n", 
	         name);
		
	    cpos = 0;
	    
	    while ((test2[offset].id != 0x41) && (test2[offset].id != 0x01) &&
 
		(test2[offset].attribute > 0))
	    {
		(*index)++;
		offset++;

		if (offset == ENTRIES_PER_SECTOR)
		{
		    offset = 0;

		    return_value = vfat_file_read (vfat_volume, file_handle, 
			block, BLOCK_SIZE,
 (*index) * sizeof (fat_entry_t), 
			&read);

		    if ((return_value != VFAT_RETURN_SUCCESS) || 
			(read != BLOCK_SIZE)
)
		    {
			DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
			    "Vfat: %s return NO MORE ENTRIES.\n",
			    __FUNCTION__);
			    
			return VFAT_RETURN_NO_MORE_ENTRIES;
		    }
		    
		    test2 = (lfn_fat_entry_t *) block;
		}
		
		DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
		    "  long name entry found at %d\n", 
		    *index);

		DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
		    "  name chunk1:[%.*S] chunk2:[%.*S] chunk3:[%.*S]\n",
		    5, test2[offset].name0_4,
		    6, test2[offset].name5_10,
		    2, test2[offset].name11_12);

		cpos++;
//		vfat_movstr (name, 13, 0, cpos * 13);
//		vfat_wcsncpy (name, test2[offset].name0_4, 5);
//		vfat_wcsncat (name, test2[offset].name5_10, 5, 6);
//		vfat_wcsncat (name, test2[offset].name11_12, 11, 2);

		DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
		    "  longName: [%s]\n", 
		    name);
	    }
	    
	    (*index)++;
	    offset++;
	    
	    if (offset == ENTRIES_PER_SECTOR)
	    {
		offset = 0;
		
		return_value = vfat_file_read (vfat_volume, file_handle, block, 
		    BLOCK_SIZE,
 (*index) * sizeof (fat_entry_t), &read);

		if ((return_value != VFAT_RETURN_SUCCESS) || 
		    (read != BLOCK_SIZE)
)
		{
		    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
			"Vfat: %s return NO MORE ENTRIES.\n",
			__FUNCTION__);
		
		    return VFAT_RETURN_NO_MORE_ENTRIES;
		}

		test2 = (lfn_fat_entry_t *) block;
		test = (fat_entry_t *) block;
	    }
	}
	else
	{
	    if (vfat_is_directory_entry_end_marker (&test[offset]))
	    {
		DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
		    "Vfat: %s return NO MORE ENTRIES.\n",
		    __FUNCTION__);
	    
		return VFAT_RETURN_NO_MORE_ENTRIES;
	    }
      
	    if (fat_entry_is_deleted (&test[offset]))
	    {
		return VFAT_RETURN_UNSUCCESSFULL;
	    }
      
	    if ((*name) == 0)
	    {
		vfat_8_dot_3_to_string (test[offset].file_name, 
		    test[offset].extension, name);
		
		if (index2)
		{
		    (*index2) = (*index);
		}
	    }
	    break;
	}
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	"Vfat: %s return OK [name=%s].\n",
	__FUNCTION__, name);

    return VFAT_RETURN_SUCCESS;
}

/*
 * FUNCTION: Read the volume label
 */
return_t read_volume_label (
    vfat_volume_t *vfat_volume)
{
    return_t return_value;

    uint32_t i = 0;
    uint32_t j;
    uint32_t size;
    char *block;
    uint32_t starting_sector;
    uint32_t next_cluster;

    /* FIXME : in fat32, no limit */
  
    size = vfat_volume->root_length;
    starting_sector = vfat_volume->root_offset;
    next_cluster = 0;

    memory_allocate ((void **) &block, BLOCK_SIZE);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
	"read_volume_label : start at sector %lx, entry %lu\n", 
	starting_sector, i);

    for (j = 0; j < size; j++)
    {
        return_value = vfat_read_sectors (&vfat_volume->storage_device, 
	    starting_sector, 1, block);

	if (return_value != VFAT_RETURN_SUCCESS)
	{
	    vfat_volume->volume_label[0] = 0;
	    vfat_volume->volume_label_length = 0;

	    memory_deallocate ((void **) &block);
      
	    return return_value;
	}

	for (i = 0 ; i < ENTRIES_PER_SECTOR ; i++)
	{
	    if (is_vol_entry (block, i))
	    {
		fat_entry_t *test = (fat_entry_t *) block;

		/* copy volume label */
		vfat_8_dot_3_to_volume_label (test[i].file_name, 
		    test[i].extension, vfat_volume->volume_label);
		    
		vfat_volume->volume_label_length = 0;//wcslen (Vpb->VolumeLabel);

		memory_deallocate (block);
	
		return VFAT_RETURN_SUCCESS;
	    }

	    if (is_last_entry ((void *) block, i))
	    {
		vfat_volume->volume_label[0] = 0;
		vfat_volume->volume_label_length = 0;
		memory_deallocate (block);

		return VFAT_RETURN_UNSUCCESSFULL;
	    }
	}

	/* not found in this sector, try next : */

	/* directory can be fragmented although it is best to keep them
 
	   unfragmented.*/
	starting_sector++;

	if (vfat_volume->fat_type == FAT_32)
	{
	    if (starting_sector == cluster_to_sector (vfat_volume, 
		next_cluster + 1))
	    {
		return_value = get_next_cluster (vfat_volume, next_cluster, 
		    &next_cluster,
 FALSE);

		if ((next_cluster == 0) || (next_cluster == UINT32_MAX))
		{
		    vfat_volume->volume_label[0] = 0;
		    vfat_volume->volume_label_length = 0;
	  
		    memory_deallocate (block);

		    return VFAT_RETURN_UNSUCCESSFULL;
		}
        
		starting_sector = cluster_to_sector (vfat_volume, next_cluster);
	    }
	}
    }

    vfat_volume->volume_label[0] = 0;
    vfat_volume->volume_label_length = 0;

    memory_deallocate ((void **) &block);

    return VFAT_RETURN_UNSUCCESSFULL;
}

/*
 * FUNCTION: Find a file
 */
return_t find_file (
    vfat_volume_t *vfat_volume,
    vfat_file_t *fcb,
    vfat_file_t *parent,
    char *file_to_find,
    uint32_t *pDirIndex,
    uint32_t *pDirIndex2)
{
    return_t return_value;

//  WCHAR name[256];
//  WCHAR name2[14];
    char name[256];
    char name2[14];

    file_handle_t tmpFileObject;
    char *block;
//  WCHAR TempStr[2];
    char temp_string[2];

    uint32_t length;
    uint32_t dir_index;
    uint32_t offset;
    uint32_t first_cluster;
    uint32_t read;
    bool is_root;
    bool first;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
	"Vfat %s (parent %p, file_to_find '%s', DirIndex: %d)\n", 
	__FUNCTION__, parent, file_to_find, pDirIndex ? *pDirIndex : 0);
	
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	"FindFile: old Pathname %x, old Objectname %x)\n",
	fcb->path_name, fcb->object_name);

    is_root = FALSE;
    dir_index = 0;
    
    if (string_length (file_to_find) == 0)
    {
	temp_string[0] = '.';
	temp_string[1] = 0;
	file_to_find = &temp_string;
    }
    
    if (parent)
    {
	first_cluster = vfat_dir_entry_get_first_cluster (vfat_volume, 
	    &parent->entry);
	    
	if (vfat_volume->fat_type == FAT_32)
	{
	    if (first_cluster == vfat_volume->root_cluster)
	    {
		is_root = TRUE;
	    }
	}
	else
	{
	    if (first_cluster == 1)
	    {
		is_root = TRUE;
	    }
	}
    }
    else
    {
	is_root = TRUE;
    }

    if (is_root)
    {
	if (vfat_volume->fat_type == FAT_32)
	{
	    first_cluster = vfat_volume->root_cluster;
	}
	else
	{
	    first_cluster = 1;
	}

	if (file_to_find[0] == 0 || (file_to_find[0] == '\\' && 
	    file_to_find[1] == 0)
 || (file_to_find[0] == '.' && 
	    file_to_find[1] == 0))
	{
	  /* it's root : complete essentials fields then return ok */

	    memory_set_uint8 ((uint8_t *) fcb, 0, sizeof (vfat_file_t));
	    memory_set_uint8 ((uint8_t *) fcb->entry.file_name, ' ', 11);

	    fcb->path_name[0] = '\\';
	    fcb->object_name = &fcb->path_name[1];
	    fcb->entry.file_size = vfat_volume->root_length * BLOCK_SIZE;
	    fcb->entry.attribute = FILE_ATTRIBUTE_DIRECTORY;
	    
	    if (vfat_volume->fat_type == FAT_32)
	    {
		fcb->entry.first_cluster_number_low = 
		    ((uint16_t *) first_cluster)[0];
		fcb->entry.first_cluster_number_high = 
		    ((uint16_t *) first_cluster)[1];
	    }
	    else
	    {
		fcb->entry.first_cluster_number_low = 1;
	    }
	    
	    if (pDirIndex)
	    {
		(*pDirIndex) = 0;
	    }
	    
	    if (pDirIndex2)
	    {
		(*pDirIndex2) = 0;
	    }
	    
	    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
		"FindFile: new Pathname %s, new Objectname %s)\n",
		fcb->path_name, fcb->object_name);
		
	    return VFAT_RETURN_SUCCESS;
	}
    }
    else
    {
	DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	    "Parent->entry.FileSize %x\n", 
	    parent->entry.file_size);
	    
	first_cluster = vfat_dir_entry_get_first_cluster (vfat_volume, 
	    &parent->entry);
    }
  
    if (pDirIndex && (*pDirIndex))
    {
	dir_index = (*pDirIndex);
    }

    return_value = vfat_file_open (vfat_volume, &tmpFileObject, 
        parent->path_name, 0, NULL);

    if (return_value != VFAT_RETURN_SUCCESS)
    {
	if (pDirIndex)
	{
	    (*pDirIndex) = dir_index;
	}

	return VFAT_RETURN_UNSUCCESSFULL;
    }

    offset = dir_index % ENTRIES_PER_SECTOR;
    first = TRUE;
    memory_allocate ((void **) &block, BLOCK_SIZE);
    
    while (TRUE)
    {
	if (first || offset == ENTRIES_PER_SECTOR)
	{
	    first = FALSE;
	    
	    if (offset == ENTRIES_PER_SECTOR)
	    {
		offset = 0;
	    }
	    
	    return_value = vfat_file_read (vfat_volume, tmpFileObject, block, 
		(dir_index - offset) * sizeof (fat_entry_t), BLOCK_SIZE,
		&read);
		
	    if (return_value != VFAT_RETURN_SUCCESS || read != BLOCK_SIZE)
	    {
		break;
	    }
	}
	
	if (vfat_is_directory_entry_volume (&((fat_entry_t *)block)[offset]))
	{
	    offset++;
	    dir_index++;
	    continue;
	}

	return_value = get_entry_name (vfat_volume, block, tmpFileObject, name, 
	    &dir_index, pDirIndex2);

	if (return_value == VFAT_RETURN_NO_MORE_ENTRIES)
	{
	    break;
	}

	offset = dir_index % ENTRIES_PER_SECTOR;
	
	if (return_value == VFAT_RETURN_SUCCESS)
	{
	    vfat_8_dot_3_to_string (((fat_entry_t *) block)[offset].file_name,
		((fat_entry_t *) block)[offset].extension, name2);

	    if (wstrcmpjoki (name, file_to_find) || wstrcmpjoki (name2, 
		file_to_find))
	    {
		if (parent && parent->path_name)
		{
		    length = string_length (parent->path_name);

		    memory_copy (fcb->path_name, parent->path_name, 
			length * sizeof (char));
		    
		    fcb->object_name = &fcb->path_name[length];
		    
		    if (length != 1 || fcb->path_name[0] != '/')
		    {
			fcb->object_name[0] = '/';
			fcb->object_name = &fcb->object_name[1];
		    }
		}
		else
		{
		    fcb->object_name = fcb->path_name;
		    fcb->object_name[0] = '/';
		    fcb->object_name = &fcb->object_name[1];
		}

		memory_copy (&fcb->entry, &((fat_entry_t *) block)[offset],
		    sizeof (fat_entry_t));
		    
		string_copy_max (fcb->object_name, name, MAX_PATH);
		
		if (pDirIndex)
		{
		    (*pDirIndex) = dir_index;
		}
		
		DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
		    "FindFile: new Pathname %s, new Objectname %s, DirIndex %d\n",
		    fcb->path_name, fcb->object_name, dir_index);
		    
		memory_deallocate (block);
		vfat_file_close (vfat_volume, tmpFileObject);

		return VFAT_RETURN_SUCCESS;
	    }
	}
while(1);
		
	
	offset++;
	dir_index++;
    }

    if (pDirIndex)
    {
	(*pDirIndex) = dir_index;
    }
  
    memory_deallocate (block);
    vfat_file_close (vfat_volume, tmpFileObject);

    return VFAT_RETURN_UNSUCCESSFULL;
}

#if 0
return_t vfatMakeAbsoluteFilename (
  PFILE_OBJECT pFileObject,
  PWSTR pRelativeFileName,
  PWSTR *pAbsoluteFilename)
{
  PWSTR  rcName;
  PVFATFCB  fcb;
  PVFATCCB  ccb;

  DbgPrint ("try related for %S\n", pRelativeFileName);
  ccb = pFileObject->FsContext2;
  assert (ccb);
  fcb = ccb->pFcb;
  assert (fcb);

  /* verify related object is a directory and target name
     don't start with \. */
  if (!(fcb->entry.Attrib & FILE_ATTRIBUTE_DIRECTORY)
      || (pRelativeFileName[0] != '\\'))
  {
    return  STATUS_INVALID_PARAMETER;
  }

  /* construct absolute path name */
  assert (wcslen (fcb->PathName) + 1 + wcslen (pRelativeFileName) + 1
          <= MAX_PATH);
  rcName = ExAllocatePool (NonPagedPool, MAX_PATH);
  wcscpy (rcName, fcb->PathName);
  wcscat (rcName, L"\\");
  wcscat (rcName, pRelativeFileName);
  *pAbsoluteFilename = rcName;

  return  STATUS_SUCCESS;
}

/*
 * FUNCTION: Opens a file
 */
return_t
 VfatOpenFile (
  vfat_volume_t *vfat_volume, 
  PFILE_OBJECT FileObject,
  PWSTR FileName)
{
  PVFATFCB ParentFcb;
  PVFATFCB Fcb;
  return_t Status;
  PWSTR AbsFileName = NULL;

  DPRINT ("VfatOpenFile(%08lx, %08lx, %S)\n", vfat_volume, FileObject, FileName);

  if (FileObject->RelatedFileObject)
    {
      DPRINT ("Converting relative filename to absolute filename\n");
      Status = vfatMakeAbsoluteFilename (FileObject->RelatedFileObject,
                                         FileName,
                                         &AbsFileName);
      FileName = AbsFileName;
    }

  //FIXME: Get cannonical path name (remove .'s, ..'s and extra separators)

  DPRINT ("PathName to open: %S\n", FileName);

  /*  try first to find an existing FCB in memory  */
  DPRINT ("Checking for existing FCB in memory\n");
  Fcb = vfatGrabFCBFromTable (vfat_volume, FileName);
  if (Fcb == NULL)
  {
    DPRINT ("No existing FCB found, making a new one if file exists.\n");
    Status = vfatGetFCBForFile (vfat_volume, &ParentFcb, &Fcb, FileName);
    if (ParentFcb != NULL)
    {
      vfatReleaseFCB (vfat_volume, ParentFcb);
    }
    if (return_value != VFAT_RETURN_SUCCESS)
    {
      DPRINT ("Could not make a new FCB, status: %x\n", Status);

      if (AbsFileName)
        ExFreePool (AbsFileName);

      return  Status;
    }
  }

  if (Fcb->Flags & FCB_DELETE_PENDING)
  {
    vfatReleaseFCB (vfat_volume, Fcb);
    if (AbsFileName)
      ExFreePool (AbsFileName);
    return STATUS_DELETE_PENDING;
  }

  DPRINT ("Attaching FCB to fileObject\n");
  return_value = vfatAttachFCBToFileObject (vfat_volume, Fcb, FileObject);

  if (AbsFileName)
  {
    ExFreePool (AbsFileName);
  }

  return return_value;
}
#endif
