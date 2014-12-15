#include <enviroment.h>
#include <string.h>

#include <Interfaces/block.h>

#include "Include/interface.h"

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

static vfat_volume_t vfat_volume;

return_t vfat_main (int argc UNUSED, char *argv[] UNUSED, char **envp UNUSED)
{
    return_t return_value;
    bool has_fat;
    object_reference_t block_device;
    handle_reference_t block;
    
    block_device = namespace$resolve (kernel_handle_namespace, 
        L"/devices/hdd/ata0-partition0");
    block = block$handle$create (block_device);
    
    return_value = vfat_has_file_system (block, &has_fat);
  
    if (return_value != VFAT_RETURN_SUCCESS || !has_fat)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
            "%S: No FAT filesystem detected.\n",
            DEBUG_MODULE_NAME);
	
        return -1;
    }

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE, 
        L"%S: FAT filesystem detected.\n",
        DEBUG_MODULE_NAME);

    return_value = vfat_volume_create_data (&vfat_volume, block);

    if (return_value != VFAT_RETURN_SUCCESS)
    {
        DEBUG_PRINTW (DEBUG_LEVEL_ERROR, 
            L"%S: Device mount failed.\n",
            DEBUG_MODULE_NAME);
	
        return -2;
    }

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE, 
	L"%S: Initialisation successfull.\n",
        DEBUG_MODULE_NAME);

{
    p_vfat_file_t file;
    
    file = vfat_file_open_root (&vfat_volume);

{
    p_vfat_file_t test_file;
    vfat_entry_add (file, L"XMY_DIR", &test_file, FILE_OPTION_DIRECTORY, 
        FILE_ATTRIBUTE_READ_ONLY|FILE_ATTRIBUTE_HIDDEN|FILE_ATTRIBUTE_SYSTEM|
        FILE_ATTRIBUTE_ARCHIVE);
}
//    vfat_entry_delete (file, L"autoexec.bat");
/*
{
    uint32_t current_index;
    wchar_t current_long_name[VFAT_MAX_PATH];
    fat_entry_t current_dir_entry;
    for (current_index = 0; ;)
    {
	return_value = vfat_directory_entry_get_next (file,
	    &current_index, current_long_name, &current_dir_entry);

	if (return_value == VFAT_RETURN_NO_MORE_ENTRIES)
	{
	    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
		"Vfat: No more entries\n");

	    break;
	}
	else if (return_value != VFAT_RETURN_SUCCESS)
	{
	    DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
		"Vfat: Unknown error.\n");
		
	    break;
	}

	if (vfat_directory_entry_is_deleted (&current_dir_entry))
	{
	    DEBUG_PRINT (DEBUG_LEVEL_WARNING, 
		"Vfat: Sciping deleted entry.\n");
		
	    continue;
	}
	
	DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE, 
    	    L"Vfat:    index:%u  long name:[%S], name:[%.8s.%.3s]\n",
    	    current_index, current_long_name, 
	    current_dir_entry.file_name, current_dir_entry.extension);
    }
}
*/
}

    return 0;
}
