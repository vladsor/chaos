#include <enviroment.h>
#include <string.h>

#include <memory.h>

#include "return_values.h"
#include "fat.h"
#include "structs.h"
#include "block_io.h"
#include "cache.h"
#include "common.h"

#include "low_fat.h"
#include "file.h"
#include "directory.h"
#include "dirwr.h"
#include "read_write.h"

#include <debug.h>
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

const char *short_illegals = " ;+=[]',\"*\\<>/?:|";

static bool vfat_is_short_illegal (char c)
{
    int i;

    for (i = 0; short_illegals[i]; i++)
    {
	if (c == short_illegals[i])
	{
	    return TRUE;
	}
    }

    return FALSE;
}

/*
 * Copies a file name into a directory slot (long file name entry)
 * and fills trailing slot space with 0xFFFF. This keeps scandisk
 * from complaining.
 */
static void fill_slot (
    lfn_fat_entry_t *slot, 
    uint8_t *file_name)
{
    bool fill = FALSE;
    ucs2_t *src;
    ucs2_t *dst;
    ucs2_t tmp[256];
    int i;

    unicode_utf8_to_ucs2_string (tmp, file_name, 256);
    src = tmp;

    i = 5;
    dst = slot->name0_4;
    while (i-- > 0)
    {
      if (fill == FALSE)
	*dst = *src;
      else
	*dst = 0xffff;

      if (fill == FALSE && (*src == 0))
	fill = TRUE;
      dst++;
      src++;
    }

    i = 6;
    dst = slot->name5_10;
    
    while (i-- > 0)
    {
      if (fill == FALSE)
	*dst = *src;
      else
	*dst = 0xffff;

      if (fill == FALSE && (*src == 0))
	fill = TRUE;
      dst++;
      src++;
    }

    i = 2;
    dst = slot->name11_12;
    
    while (i-- > 0)
    {
      if (fill == FALSE)
	*dst = *src;
      else
	*dst = 0xffff;

      if (fill == FALSE && (*src == 0))
	fill = TRUE;
      dst++;
      src++;
    }
}

/*
  update an existing FAT entry
*/
return_t update_entry (
    vfat_volume_t *vfat_volume, 
    vfat_file_t *pFileObject)
{
    return_t return_value;

    vfat_file_t fcb;
//VFATCCB Ccb;
    uint32_t entry = 0;
//FILE_OBJECT FileObject;
//    vfat_file_t FileObject;
    vfat_file_t *pDirFcb = NULL, *pFcb = NULL;

//    PWCHAR pName;
    char *pName;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	"updEntry PathFileName \'%s\'\n", 
	pFileObject->path_name);
/*
    return_value = vfatGetFCBForFile (vfat_volume, &pDirFcb, &pFcb, 
	pFileObject->FileName.Buffer);
    if (pFcb != NULL)
    {
	vfatReleaseFCB (vfat_volume, pFcb);
    }
    
    if (return_value != VFAT_RETURN_SUCCESS)
    {
	if (pDirFcb != NULL)
	{
	    vfatReleaseFCB(DeviceExt, pDirFcb);
	}
	
	return return_value;
    }

    pName = ((PVFATCCB)(pFileObject->FsContext2))->pFcb->ObjectName;
*/    
    pName = pFileObject->object_name;
    
    if (*pName == '\\')
    {
	pName++;
    }
    
    return_value = find_file (vfat_volume, &fcb, pDirFcb, pName, &entry, NULL);
    
    if (return_value == VFAT_RETURN_SUCCESS)
    {
	DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	    "update entry: %d\n", 
	    entry);
	    
//	memory_set_uint8 (&FileObject, 0, sizeof(FILE_OBJECT));
//	memory_set_uint8 (&Ccb, 0, sizeof(VFATCCB));
//	FileObject.FsContext2 = &Ccb;
//	FileObject.FsContext = &pDirFcb->RFCB;
//	Ccb.pFcb = pDirFcb;

	return_value = vfat_write_file (vfat_volume, pDirFcb, &pFcb->entry,
	    sizeof (fat_entry_t), entry  * sizeof (fat_entry_t), FALSE);
	    
	if (return_value != VFAT_RETURN_SUCCESS)
	{
    	    DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
		"Failed to open \'%s\'. Return value %x\n", 
		pDirFcb->path_name, return_value);
	}
    }
    
    vfat_release_fcb (vfat_volume, pDirFcb);

    return return_value;
}

/*
  create a new FAT entry
*/
return_t add_entry (
    vfat_volume_t *vfat_volume,
    vfat_file_t *pFileObject, 
    uint32_t requested_options, 
    uint8_t requested_attributes)
{
    return_t return_value = VFAT_RETURN_SUCCESS;

//WCHAR dir_name[MAX_PATH], *file_name, *path_file_name;
    uint8_t dir_name[MAX_PATH], *file_name, *path_file_name;
    
    vfat_file_t file_fcb;
    fat_entry_t fat_entry;
//FILE_OBJECT FileObject;
//vfat_file_t FileObject;
    file_handle_t file_handle;

    fat_entry_t *pointer_to_entry;
    lfn_fat_entry_t *pSlots;
    uint32_t length_read, offset;

short nbSlots = 0, nbFree = 0, i, j, posCar, NameLen;
  
    char *buffer, *buffer2;
    bool need_tilde = FALSE, need_long = FALSE;
    vfat_file_t *new_fcb;
    uint32_t current_cluster;
//LARGE_INTEGER SystemTime, LocalTime;
    vfat_file_t *pFcb;
//    vfat_file_t *pCcb;

    path_file_name = pFileObject->path_name;
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	"addEntry: Pathname=%s\n", 
	path_file_name);

    /* find last \ in PathFileName */

    posCar = -1;
    for (i = 0; path_file_name[i]; i++)
    {
	if (path_file_name[i] == '\\')
	{
	    posCar = i;
	}
    }
    
    if (posCar == -1)
    {
	return VFAT_RETURN_UNSUCCESSFULL;
    }
	
    file_name = &path_file_name[posCar + 1];
    
    for (NameLen = 0; file_name[NameLen]; NameLen++);
    
    // extract directory name from pathname
    if (posCar == 0)
    {
	// root dir
	dir_name[0] = L'\\';
	dir_name[1] = 0;
    }
    else
    {
	memory_copy (dir_name, path_file_name, posCar * sizeof (uint8_t));
	dir_name[posCar] = 0;
    }
    
    // open parent directory
//    memory_set_uint8 ((uint8_t *) &FileObject, 0, sizeof (FileObject));
    return_value = vfat_file_open (vfat_volume, &file_handle, dir_name, 0, 
	NULL);

    if (return_value != VFAT_RETURN_SUCCESS)
    {
	return return_value;
    }
  
    nbSlots = (NameLen + 12) / 13 + 1;	//nb of entry needed for long name+normal entry
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	"Vfat: NameLen=%d, nbSlots=%d\n", 
	NameLen, nbSlots);

    memory_allocate ((void **) &buffer, (nbSlots + 1) * sizeof (fat_entry_t));
    
    memory_set_uint8 (buffer, 0, (nbSlots + 1) * sizeof (fat_entry_t));
    
    pointer_to_entry = (fat_entry_t *) (buffer + (nbSlots - 1) * 
	sizeof (fat_entry_t));
    pSlots = (lfn_fat_entry_t *) buffer;
    
    // create 8.3 name
    need_tilde = FALSE;
    
    // find last point in name
    posCar = j = 0;

    for (i = 0; file_name[i]; i++)
    {
	if (file_name[i] == '.')
	{
	    posCar = i;
	    if (i == j)
	    {
		j++;
	    }
	}
    }
    
    if (!posCar)
    {
	posCar = i;
    }
    
    if (posCar < j)
    {
	posCar = i;
	need_tilde = TRUE;
    }
    
    if (posCar > 8)
    {
	need_tilde = TRUE;
    }
    
    //copy 8 characters max
    memory_set_uint8 ((uint8_t *) pointer_to_entry, ' ', 11);
    
    for (i = 0, j = 0; j < 8 && i < posCar; i++)
    {
	if (vfat_is_short_illegal (file_name[i]))
	{
	    need_tilde = TRUE;
	    pointer_to_entry->file_name[j++] = '_';
	}
	else
	{
	    if (file_name[i] == '.')
	    {
		need_tilde = TRUE;
	    }
	    else
	    {
		pointer_to_entry->file_name[j++] = 
		    char_to_upper_case ((char) file_name[i]);
	    }
	}
    }
  
    //copy extension
    if (file_name[posCar])
    {
	for (j = 0, i = posCar + 1; file_name[i] && j < 3; i++)
	{
	    if (vfat_is_short_illegal (file_name[i]))
	    {
		need_tilde = TRUE;
		pointer_to_entry->extension[j++] = '_';
	    }
	    else
	    {
		if (file_name[i] == '.')
		{
		    need_tilde = TRUE;
		}
		else
		{
		    pointer_to_entry->extension[j++] = char_to_upper_case (
			(char) (file_name[i] & 0x7F));
		}
	    }
	}
    }
    
    if (file_name[i])
    {
	need_tilde = TRUE;
    }
    
    //find good value for tilde
    if (need_tilde)
    {
	need_long = TRUE;
	
	DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	    "searching a good value for tilde\n");
	    
	for (posCar = 0; posCar < 8 && pointer_to_entry->file_name[posCar] != ' '; 
	    posCar++);
	
	if (posCar == 0) // ??????????????????????
	{
	    pointer_to_entry->file_name[posCar++] = '_';
	}
	
	posCar += 2;
	
	if (posCar > 8)
	{
	    posCar = 8;
	}
	
	pointer_to_entry->file_name[posCar - 2] = '~';
	pointer_to_entry->file_name[posCar - 1] = '1';
	vfat_8_dot_3_to_string (pointer_to_entry->file_name, 
	    pointer_to_entry->extension, dir_name);
	
	//try first with xxxxxx~y.zzz
	for (i = 1; i < 10; i++)
	{
	    dir_name[posCar-1] = '0' + i;
	    pointer_to_entry->file_name[posCar - 1] = '0' + i;
	    return_value = find_file (vfat_volume, &file_fcb, pFcb, dir_name, 
		NULL, NULL);
	    
	    if (return_value != VFAT_RETURN_SUCCESS)
	    {
		break;
	    }
	}
	
	if (i == 10)
	{
	    posCar++;
	    if (posCar > 8)
	    {
		posCar = 8;
	    }
	    
	    pointer_to_entry->file_name[posCar - 3] = '~';
	    pointer_to_entry->file_name[posCar - 2] = '1';
	    pointer_to_entry->file_name[posCar - 1] = '0';
	    vfat_8_dot_3_to_string (pointer_to_entry->file_name, 
		pointer_to_entry->extension, dir_name);
	    
	    //try second with xxxxx~yy.zzz
	    for (i = 10; i < 100; i++)
	    {
		dir_name[posCar - 1] = '0' + i % 10;
		dir_name[posCar - 2] = '0' + i / 10;
		pointer_to_entry->file_name[posCar - 1] = '0' + i % 10;
		pointer_to_entry->file_name[posCar - 2] = '0' + i / 10;
		
		return_value = find_file (vfat_volume, &file_fcb, pFcb, 
		    dir_name, NULL, NULL);
		    
		if (return_value != VFAT_RETURN_SUCCESS)
		{
		    break;
		}
	    }
	    
	    if (i == 100) //FIXME : what to do after 99 tilde ?
	    {
		vfat_file_close (vfat_volume, file_handle);
		memory_deallocate (buffer);
		
		return VFAT_RETURN_UNSUCCESSFULL;
	    }
	}
    }
    else
    {
	DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	    "check if long name entry needed, needlong=%d\n", 
	    need_long);
	    
	for (i = 0; i < posCar; i++)
	{
	    if (pointer_to_entry->file_name[i] != file_name[i])
	    {
		DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
		    "i=%d,%d,%d\n", 
		    i, pointer_to_entry->file_name[i], file_name[i]);
		need_long = TRUE;
	    }
	}
	
	if (file_name[i])
	{
	    i++;			//jump on point char
	    for (j = 0, i = posCar + 1; file_name[i] && i < posCar + 4; i++)
	    {
		if (pointer_to_entry->extension[j++] != file_name[i])
		{
		    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
			"i=%d,j=%d,%d,%d\n", 
			i, j, pointer_to_entry->file_name[i], file_name[i]);
		    need_long = TRUE;
		}
	    }
	}
    }
  
    if (need_long == FALSE)
    {
	nbSlots = 1;
	memory_copy (buffer, pointer_to_entry, sizeof (fat_entry_t));
	memory_set_uint8 ((uint8_t *) pointer_to_entry, 0, 
	    sizeof (fat_entry_t));
	pointer_to_entry = (fat_entry_t *) buffer;
    }
    else
    {
	memory_set_uint8 ((uint8_t *) dir_name, 0xFF, sizeof (dir_name));
	memory_copy (dir_name, file_name, NameLen * sizeof (uint8_t));
	dir_name[NameLen] = 0;
    }
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	"dos name=%11.11s\n", 
	pointer_to_entry->file_name);

    /* set attributes */
    pointer_to_entry->attribute = requested_attributes;
    
    if (requested_options & FILE_OPTION_DIRECTORY)
    {
	pointer_to_entry->attribute |= FILE_ATTRIBUTE_DIRECTORY;
    }

    /* set dates and times */
    /*
    KeQuerySystemTime (&SystemTime);
    ExSystemTimeToLocalTime (&SystemTime, &LocalTime);
    FsdFileTimeToDosDateTime ((TIME *) & LocalTime,
	&pEntry->CreationDate, &pEntry->CreationTime);
    pEntry->UpdateDate = pEntry->CreationDate;
    pEntry->UpdateTime = pEntry->CreationTime;
    pEntry->AccessDate = pEntry->CreationDate;
    */

    // calculate checksum for 8.3 name
    for (pSlots[0].alias_checksum = i = 0; i < 11; i++)
    {
	pSlots[0].alias_checksum = (((pSlots[0].alias_checksum & 1) << 7 | 
	    ((pSlots[0].alias_checksum & 0xfe) >> 1)) + 
	    pointer_to_entry->file_name[i]);
    }
    
    //construct slots and entry
    for (i = nbSlots - 2; i >= 0; i--)
    {
	DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	    "construct slot %d\n", i);
	    
	pSlots[i].attribute = 0xF;
	
	if (i)
	{
	    pSlots[i].id = nbSlots - i - 1;
	}
	else
	{
	    pSlots[i].id = nbSlots - i - 1 + 0x40;
	}
	
	pSlots[i].alias_checksum = pSlots[0].alias_checksum;
//FIXME      pSlots[i].start=;
	fill_slot (&pSlots[i], file_name + (nbSlots - i - 2) * 13);
    }

    //try to find nbSlots contiguous entries frees in directory
    for (i = 0, return_value = VFAT_RETURN_SUCCESS; 
	return_value == VFAT_RETURN_SUCCESS; i++)
    {
	return_value = vfat_file_read (vfat_volume, file_handle, &fat_entry, 
	    sizeof (fat_entry_t), i * sizeof (fat_entry_t), &length_read);
	    
	if (return_value == VFAT_RETURN_END_OF_FILE)
	{
	    break;
	}
	    
	if (return_value != VFAT_RETURN_SUCCESS)
	{
	    DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
		"VfatReadFile failed to read the directory entry\n");
	    break;
	}
	
	if (length_read != sizeof (fat_entry_t))
	{
	    DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
		"VfatReadFile did not read a complete directory entry\n");
	    break;
	}
	
	if (vfat_is_directory_entry_end_marker (&fat_entry))
	{
	    break;
	}
	
	if (fat_entry_is_deleted (&fat_entry))
	{
	    nbFree++;
	}
	else
	{
	    nbFree = 0;
	}

	if (nbFree == nbSlots)
	{
	    break;
	}
    }
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	"nbSlots %d nbFree %d, entry number %d\n", 
	nbSlots, nbFree, i);

    if (requested_options & FILE_OPTION_DIRECTORY)
    {
	current_cluster = UINT32_MAX;
	return_value = get_next_cluster (vfat_volume, 0, &current_cluster, 
	    TRUE);
	
	if ((current_cluster == UINT32_MAX) || 
	    (return_value != VFAT_RETURN_SUCCESS))
	{
	    vfat_file_close (vfat_volume, file_handle);
	    memory_deallocate (buffer);
	    
	    if (return_value != VFAT_RETURN_SUCCESS)
	    {
		return return_value;
	    }
	    
	    return VFAT_RETURN_DISK_FULL;
	}
	
	// zero the cluster
	memory_allocate ((void **) &buffer2, vfat_volume->bytes_per_cluster);
	
	memory_set_uint8 (buffer2, 0, vfat_volume->bytes_per_cluster);
	vfat_raw_write_cluster (vfat_volume, 0, buffer2, current_cluster);
	memory_deallocate (buffer2);
	
	if (vfat_volume->fat_type == FAT_32)
	{
	    pointer_to_entry->first_cluster_number_high = current_cluster >> 16;
	    pointer_to_entry->first_cluster_number_low = current_cluster;
	}
	else
	{
	    pointer_to_entry->first_cluster_number_low = current_cluster;
	}
    }
    
    if (nbFree == nbSlots)
    {				//use old slots
	offset = (i - nbSlots + 1) * sizeof (fat_entry_t);
	return_value = vfat_file_write (vfat_volume, file_handle, buffer,
		      sizeof (fat_entry_t) * nbSlots, offset);
		      
	DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	    "VfatWriteFile() returned: %x\n", 
	    return_value);
    }
    else
    {				//write at end of directory
	offset = (i - nbFree) * sizeof (fat_entry_t);
	return_value = vfat_file_write (vfat_volume, file_handle, buffer, 
	    sizeof (fat_entry_t) * (nbSlots + 1), offset);
    }
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	"write entry offset %d status=%x\n", 
	offset, return_value);
    
    if (return_value != VFAT_RETURN_SUCCESS)
    {
	vfat_file_close (vfat_volume, file_handle);
	
	if (requested_options & FILE_OPTION_DIRECTORY)
	{
	    // free the reserved cluster
	    vfat_volume->write_cluster ((struct vfat_volume_t *) vfat_volume, 
		current_cluster, 0);
	}
	
	memory_deallocate (buffer);
	
	return return_value;
    }

    // FIXME: check status
    vfat_make_fcb_from_dir_entry (vfat_volume, pFcb, file_name, 
	pointer_to_entry, &new_fcb);
//    vfat_attach_fcb_to_file_object (vfat_volume, new_fcb, pFileObject);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	"new : entry=%11.11s\n", 
	new_fcb->entry.file_name);
	
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	"new : entry=%11.11s\n", 
	pointer_to_entry->file_name);

    if (requested_options & FILE_OPTION_DIRECTORY)
    {
	// create . and ..
	memory_copy (pointer_to_entry->file_name, ".          ", 11);
	return_value = vfat_write_file (vfat_volume, pFileObject, 
	    pointer_to_entry, sizeof (fat_entry_t), 0L, FALSE);
	    
//	pEntry->first_cluster =
//	((VFATCCB *) (FileObject.FsContext2))->pFcb->entry.first_cluster;
	
//	pEntry->FirstClusterHigh =
//	((VFATCCB *) (FileObject.FsContext2))->pFcb->entry.FirstClusterHigh;
	
	memory_copy (pointer_to_entry->file_name, "..         ", 11);
	
	if ((pointer_to_entry->first_cluster_number_low == 1) && 
	    (vfat_volume->fat_type != FAT_32))
	{
	    pointer_to_entry->first_cluster_number_low = 0;
	}
	
	return_value = vfat_file_write (vfat_volume, file_handle, 
	    pointer_to_entry, sizeof (fat_entry_t), sizeof (fat_entry_t));
    }

    vfat_file_close (vfat_volume, file_handle);
    memory_deallocate (buffer);
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "addentry ok\n");

    return VFAT_RETURN_SUCCESS;
}

/*
  deleting an existing FAT entry
*/
return_t delete_entry (
    vfat_volume_t *vfat_volume, 
    vfat_file_t *file)
{
    return_t return_value;

//    vfat_file_t fcb;
//    vfat_file_t *pFcb = NULL;
    vfat_file_t *parent_file = file->parent_file;
//    PWSTR pName;
    char *pName;
    uint32_t entry = 0, start_entry, read, current_cluster, next_cluster, i;
//FILE_OBJECT FileObject;
//    vfat_file_t FileObject;
//    file_handle_t file_handle;

//    VFATCCB Ccb;
    fat_entry_t dir_entry;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	"Vfat: %s (%p, %p)\n", 
	__FUNCTION__, vfat_volume, file);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	"delEntry PathFileName \'%s\', \'%s\'\n", 
	file->path_name, file->object_name);
/*
    return_value = vfat_get_fcb_for_file (vfat_volume, &pDirFcb, &pFcb, 
	pFileObject->FileName.Buffer);

    if (pFcb != NULL)
    {
	vfatReleaseFCB (DeviceExt, pFcb);
    }

    if (return_value != VFAT_RETURN_SUCCESS)
    {
	if (pDirFcb != NULL)
	{
	    vfatReleaseFCB(DeviceExt, pDirFcb);
	}
	
	return return_value;
    }

    pName = ((PVFATCCB)(pFileObject->FsContext2))->pFcb->ObjectName;
*/
    pName = file->object_name;

    if (*pName == '\\')
    {
	pName++;
    }

    return_value = find_file (vfat_volume, file, parent_file, pName, &entry, 
	&start_entry);

    if (return_value == VFAT_RETURN_SUCCESS)
    {
	DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	    "delete entry: %d to %d\n", 
	    start_entry, entry);
    
//	memset (&FileObject, 0, sizeof(FILE_OBJECT));
//	memset (&Ccb, 0, sizeof(VFATCCB));
//	FileObject.FsContext2 = &Ccb;
//	fileObject.FsContext = &pDirFcb->RFCB;
//	Ccb.pFcb = pDirFcb;

	for (i = start_entry; i <= entry; i++)
	{
	    // FIXME: check status
	    vfat_read_file (vfat_volume, parent_file, &dir_entry, 
		sizeof (fat_entry_t), i * sizeof (fat_entry_t), &read, FALSE);
	    dir_entry.file_name[0] = 0xe5;
	    
	    // FIXME: check status
	    vfat_write_file (vfat_volume, parent_file, &dir_entry, 
		sizeof (fat_entry_t), i * sizeof (fat_entry_t), FALSE);
	}
	
	current_cluster = vfat_dir_entry_get_first_cluster (vfat_volume, 
	    &dir_entry);

	while (current_cluster && current_cluster != UINT32_MAX)
	{
	    get_next_cluster (vfat_volume, current_cluster, &next_cluster, 
		FALSE);
	    
	    // FIXME: check status
	    vfat_volume->write_cluster ((struct vfat_volume_t *) vfat_volume, 
		current_cluster, 0);
	    current_cluster = next_cluster;
	}
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	"Vfat: %s return %u\n", 
	__FUNCTION__, return_value);

    return return_value;
}
