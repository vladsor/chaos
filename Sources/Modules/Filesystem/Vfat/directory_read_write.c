#include <enviroment.h>
#include <string.h>

#include "Include/return_values.h"
#include "Include/fat.h"
#include "Include/structs.h"
#include "Include/entry.h"

#include "Include/types.h"
#include "Include/volume.h"
#include "Include/file.h"

#include "Include/common.h"
#include "Include/low_fat.h"
#include "Include/read_write.h"
#include "Include/directory_entry.h"
#include "Include/directory_read_write.h"

#define DEBUG_MODULE_NAME L"VFAT"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#ifndef __STORM_KERNEL__
#   define DEBUG_SUPPLIER (vfat_debug_supplier)
#endif

#include <debug/macros.h>

return_t vfat_entry_find (
    p_vfat_file_t directory_file, 
    const wchar_t *file_name,
    uint32_t *start_index, 
    uint32_t *end_index)
{
    return_t return_value;
    wchar_t entry_name[256];
    uint32_t index = 0, next_index = 0;
    fat_entry_t directory_entry;

    for (return_value = VFAT_RETURN_SUCCESS; ;)
    {
        index = next_index;
        
        return_value = vfat_directory_entry_get_next (directory_file, 
            &next_index, entry_name, &directory_entry);
        
        if (return_value != VFAT_RETURN_SUCCESS)
        {
            return return_value;
        }

        DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE, 
            L"%S: %s: Compare: %S with %S)\n", 
            DEBUG_MODULE_NAME, __FUNCTION__,
            file_name, entry_name);

        if (wstrcmpjoki (file_name, entry_name))
        {
            if (start_index != NULL)
            {            
                (*start_index) = index;
            }
            
            if (end_index != NULL)
            {
                (*end_index) = next_index - 1;
            }
            
            return VFAT_RETURN_SUCCESS;
        }
    }
}

static const char *short_illegals = " ;+=[]',\"*\\<>/?:|";

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
    p_lfn_fat_entry_t slot, 
    const wchar_t *file_name)
{
    bool fill = FALSE;
    const wchar_t *src;
    ucs2_t *dst;
    int i;

    src = file_name;

    i = 5;
    dst = slot->name0_4;

    while (i-- > 0)
    {
        if (fill == FALSE)
        {
            *dst = *src;
        }
        else
        {
            *dst = UINT16_MAX;
        }

        if (fill == FALSE && (*src == 0))
        {
            fill = TRUE;
        }
        dst++;
        src++;
    }

    i = 6;
    dst = slot->name5_10;
    
    while (i-- > 0)
    {
        if (fill == FALSE)
        {
            *dst = *src;
        }
        else
        {
            *dst = UINT16_MAX;
        }
        
        if (fill == FALSE && (*src == 0))
        {
            fill = TRUE;
        }
        dst++;
        src++;
    }

    i = 2;
    dst = slot->name11_12;
    
    while (i-- > 0)
    {
        if (fill == FALSE)
        {
            *dst = *src;
        }
        else
        {
            *dst = UINT16_MAX;
        }

        if (fill == FALSE && (*src == 0))
        {
            fill = TRUE;
        }
        dst++;
        src++;
    }
}

#if 0
/*
  update an existing FAT entry
*/
return_t vfat_entry_update (
    vfat_volume_t *vfat_volume,
    vfat_file_t *pFileObject)
{
    return_t return_value;

    vfat_file_t fcb;

    uint32_t entry = 0;

    vfat_file_t *pDirFcb = NULL, *pFcb = NULL;

    wchar_t *pName;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	"updEntry PathFileName \'%s\'\n", 
	pFileObject->path_name);

    pName = pFileObject->object_name;
    
    if (*pName == '\\')
    {
	pName++;
    }
    
    return_value = find_file (
        vfat_volume, &file, directory_file, pName, &entry, NULL);
    
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

	return_value = vfat_write_file (directory_file, &pFcb->entry,
	    sizeof (fat_entry_t), entry  * sizeof (fat_entry_t));
	    
	if (return_value != VFAT_RETURN_SUCCESS)
	{
    	    DEBUG_PRINT (DEBUG_LEVEL_ERROR,
		"Failed to open \'%s\'. Return value %x\n",
		pDirFcb->path_name, return_value);
	}
    }
    
    vfat_file_release (directory_file);

    return return_value;
}
#endif

/*
  create a new FAT entry
*/
return_t vfat_entry_add (
    p_vfat_file_t directory_file,
    const wchar_t *file_name, 
    p_vfat_file_t *new_file,
    uint32_t requested_options, 
    uint8_t requested_attributes)
{
    return_t return_value = VFAT_RETURN_SUCCESS;
    p_vfat_volume_t vfat_volume;
    wchar_t short_name[13];    
    fat_entry_t fat_entry;

    fat_entry_t *pointer_to_entry;
    lfn_fat_entry_t *pSlots;
    uint32_t length_read, offset;

    short nbSlots = 0, nbFree = 0, i, j, posCar, NameLen;
  
    char *buffer, *buffer2;
    bool need_tilde = FALSE, need_long = FALSE;
    
    uint32_t current_cluster = 0;
//LARGE_INTEGER SystemTime, LocalTime;

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE, 
	L"%S: %s (name=%S)\n", 
        DEBUG_MODULE_NAME, __FUNCTION__,
	file_name);

    vfat_volume = directory_file->volume;

    NameLen = wstring_length (file_name);
  
    //nb of entry needed for long name+normal entry
    nbSlots = (NameLen + 12) / 13 + 1;	

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	"Vfat: NameLen=%d, nbSlots=%d\n", 
	NameLen, nbSlots);

    memory_allocate ((void **) &buffer, (nbSlots + 1) * sizeof (fat_entry_t));
    memory_clear (buffer, (nbSlots + 1) * sizeof (fat_entry_t));
    
    pointer_to_entry = (fat_entry_t *) (buffer + (nbSlots - 1) * 
	sizeof (fat_entry_t));
    pSlots = (lfn_fat_entry_t *) buffer;
    
    // create 8.3 name
    need_tilde = FALSE;
    
    // find last point in name
    posCar = j = 0;

    for (i = 0; file_name[i] != L'\0'; i++)
    {
	if (file_name[i] == L'.')
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
	    
	for (posCar = 0; 
             posCar < 8 && pointer_to_entry->file_name[posCar] != ' '; 
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
	vfat_8_dot_3_to_wstring (pointer_to_entry->file_name,
	    pointer_to_entry->extension, short_name);
	
	//try first with xxxxxx~y.zzz
	for (i = 1; i < 10; i++)
	{
	    short_name[posCar-1] = '0' + i;
	    pointer_to_entry->file_name[posCar - 1] = '0' + i;
            
	    return_value = vfat_entry_find (
                directory_file, short_name, NULL, NULL);
	    
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

	    vfat_8_dot_3_to_wstring (pointer_to_entry->file_name, 
		pointer_to_entry->extension, short_name);
	    
	    //try second with xxxxx~yy.zzz
	    for (i = 10; i < 100; i++)
	    {
		short_name[posCar - 1] = '0' + i % 10;
		short_name[posCar - 2] = '0' + i / 10;
		pointer_to_entry->file_name[posCar - 1] = '0' + i % 10;
		pointer_to_entry->file_name[posCar - 2] = '0' + i / 10;
		
		return_value = vfat_entry_find (
                    directory_file, short_name, NULL, NULL);
		    
		if (return_value != VFAT_RETURN_SUCCESS)
		{
		    break;
		}
	    }
	    
	    if (i == 100) //FIXME : what to do after 99 tilde ?
	    {
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
		need_long = TRUE;
	    }
	}
	
	if (file_name[i])
	{
            //jump on point char
	    i++;			
	    for (j = 0, i = posCar + 1; file_name[i] && i < posCar + 4; i++)
	    {
		if (pointer_to_entry->extension[j++] != file_name[i])
		{
		    need_long = TRUE;
		}
	    }
	}
    }
  
    if (need_long == FALSE)
    {
	nbSlots = 1;
	memory_copy (buffer, pointer_to_entry, sizeof (fat_entry_t));
	memory_clear (pointer_to_entry, sizeof (fat_entry_t));
	pointer_to_entry = (p_fat_entry_t) buffer;
    }
//    else
//    {
//	memory_set_uint8 ((uint8_t *) directory_name, 0xFF, 
//            sizeof (directory_name));
//	memory_copy (directory_name, file_name, NameLen * sizeof (wchar_t));
//	directory_name[NameLen] = 0;
//    }
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
                 "dos name=%11.11s\n", 
                 pointer_to_entry->file_name);

    /* set attributes */
    pointer_to_entry->attribute = requested_attributes;
    
    if (requested_options & FILE_OPTION_DIRECTORY)
    {
	pointer_to_entry->attribute |= FILE_ATTRIBUTE_DIRECTORY;
    }

    /** @todo set dates and times */
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
	pSlots[0].alias_checksum = (((pSlots[0].alias_checksum & 1) << 7 | 
	    ((pSlots[0].alias_checksum & 0xfe) >> 1)) + 
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
	return_value = vfat_read_file (directory_file, &fat_entry, 
	    sizeof (fat_entry_t), i * sizeof (fat_entry_t), &length_read);
	    
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
	
	if (vfat_directory_entry_is_end_marker (&fat_entry))
	{
	    break;
	}
	
	if (vfat_directory_entry_is_deleted (&fat_entry))
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
	"nbSlots %d nbFree %d, entry number %d, options: %u\n",
	nbSlots, nbFree, i, requested_options);

    if (requested_options & FILE_OPTION_DIRECTORY)
    {
	current_cluster = UINT32_MAX;
        
	return_value = get_next_cluster (vfat_volume, 0, &current_cluster,
	    TRUE);
	
	if ((current_cluster == UINT32_MAX) || 
	    (return_value != VFAT_RETURN_SUCCESS))
	{
	    memory_deallocate (buffer);
	    
	    if (return_value != VFAT_RETURN_SUCCESS)
	    {
		return return_value;
	    }
	    
	    return VFAT_RETURN_DISK_FULL;
	}
	
	// zero the cluster
	memory_allocate ((void **) &buffer2, vfat_volume->bytes_per_cluster);
	
	memory_clear (buffer2, vfat_volume->bytes_per_cluster);
	vfat_raw_write_cluster (vfat_volume, 0, buffer2, current_cluster);
	memory_deallocate (buffer2);

        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
            "Start cluster: %u\n",
            current_cluster);
	
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
    {				
        //use old slots
	offset = (i - nbSlots + 1) * sizeof (fat_entry_t);
        
	return_value = vfat_write_file (directory_file, buffer,
            sizeof (fat_entry_t) * nbSlots, offset);
		      
	DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	    "VfatWriteFile() returned: %x\n", 
	    return_value);
    }
    else
    {	
        //write at end of directory
	offset = (i - nbFree) * sizeof (fat_entry_t);
	return_value = vfat_write_file (directory_file, buffer,
	    sizeof (fat_entry_t) * (nbSlots + 1), offset);
    }
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	"write entry offset %d, cluster: %u, status=%x\n", 
	offset, current_cluster, return_value);
    
    if (return_value != VFAT_RETURN_SUCCESS)
    {
	DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	    "EXIT\n");

	if (requested_options & FILE_OPTION_DIRECTORY)
	{
	    // free the reserved cluster
	    vfat_volume->write_cluster (vfat_volume, current_cluster, 0);
	}
	
	memory_deallocate (buffer);
	
	return return_value;
    }

    /** @todo check status */
    vfat_file_create_data_from_directory_entry (
        directory_file, file_name, pointer_to_entry, new_file);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
                 "new : entry=%11.11s\n", 
                 (*new_file)->entry.file_name);
	
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
                 "new : entry=%11.11s\n", 
                 pointer_to_entry->file_name);

    if (requested_options & FILE_OPTION_DIRECTORY)
    {
	DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	    "create . and ..\n");
	memory_copy (pointer_to_entry->file_name, (void *) ".          ", 11);

	return_value = vfat_write_file (*new_file,
	    pointer_to_entry, sizeof (fat_entry_t), 0);
	    
        pointer_to_entry->first_cluster_number_low = 
            directory_file->entry.first_cluster_number_low;
        pointer_to_entry->first_cluster_number_high = 
            directory_file->entry.first_cluster_number_high;

//        memory_copy (pointer_to_entry, &directory_file->entry, 
//            sizeof (fat_entry_t));
	memory_copy (pointer_to_entry->file_name, (void *) "..         ", 11);

        if (vfat_file_is_root (directory_file))
        {	
	    pointer_to_entry->first_cluster_number_low = 0;
            pointer_to_entry->first_cluster_number_high = 0;
	}
	
	return_value = vfat_write_file (*new_file, 
	    pointer_to_entry, sizeof (fat_entry_t), sizeof (fat_entry_t));
    }

    memory_deallocate (buffer);
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "addentry ok\n");

    return VFAT_RETURN_SUCCESS;
}

/*
  deleting an existing FAT entry
*/
return_t vfat_entry_delete (
    p_vfat_file_t directory_file,
    const wchar_t *name)
{
    return_t return_value;
    p_vfat_volume_t vfat_volume;

    uint32_t last_entry, start_entry, read, current_cluster, next_cluster, i;
    fat_entry_t directory_entry;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	"Vfat: %s (%p, %p)\n", 
	__FUNCTION__, 
        directory_file, name);

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE, 
        L"delEntry FileName \'%S\'\n", 
	name);

    vfat_volume = directory_file->volume;

    return_value = vfat_entry_find (directory_file, name, &start_entry,
	&last_entry);

    if (return_value == VFAT_RETURN_SUCCESS)
    {
	DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
	    "delete entry: %d to %d\n",
	    start_entry, last_entry);

	for (i = start_entry; i <= last_entry; i++)
	{
	    // FIXME: check status
	    vfat_read_file (directory_file, &directory_entry,
		sizeof (fat_entry_t), i * sizeof (fat_entry_t), &read);
	    directory_entry.file_name[0] = 0xe5;
	    
	    // FIXME: check status
	    vfat_write_file (directory_file, &directory_entry,
		sizeof (fat_entry_t), i * sizeof (fat_entry_t));
	}
	
	current_cluster = vfat_directory_entry_get_first_cluster (
            vfat_volume, &directory_entry);

	while ((current_cluster != 0) && (current_cluster != UINT32_MAX))
	{
	    get_next_cluster (vfat_volume, current_cluster, &next_cluster,
		FALSE);
	    
	    // FIXME: check status
	    vfat_volume->write_cluster (vfat_volume, current_cluster, 0);
	    current_cluster = next_cluster;
	}
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	"Vfat: %s return %u\n", 
	__FUNCTION__, return_value);

    return return_value;
}
