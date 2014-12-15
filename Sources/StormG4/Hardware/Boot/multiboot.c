/* $chaos: multiboot.c,v 1.8 2002/10/04 19:01:21 per Exp $ */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE.
   reference documentation. */

/**
 * @file                Boot/multiboot.c
 * @brief               Parse multiboot header.
 * @author              Per Lundberg <per@chaosdev.org>
 * @author              Henrik Hallin <hal@chaosdev.org>
 * @author              Vladimir Sorokin
 * @version             1.10
 * @date                1999-2004
 */

#include <enviroment.h>
#include <string.h>

#include "Include/multiboot.h"

/* Multiboot header. */
uint32_t multiboot_header[] MULTIBOOT_HEADER_ATTR = 
{
    MULTIBOOT_MAGIC,
    MULTIBOOT_FLAGS,
    - (MULTIBOOT_MAGIC + MULTIBOOT_FLAGS)
};

multiboot_info_t multiboot_info;
//multiboot_module_info_t multiboot_module_info[MAX_NUMBER_OF_STORM_MODULES];
//multiboot_memory_map_t multiboot_memory_map[MAX_NUMBER_OF_STORM_MEMORY_MAPS];

/* Copy off some of the Multiboot data we need, so it won't be
   overwritten. */
void multiboot_init (void)
{
    unsigned int index;
    
    multiboot_module_info_t *multiboot_module_info;
    multiboot_memory_map_t *multiboot_memory_map;
    
    storm_info.memory_size = 1 * MIB + multiboot_info.memory_upper * KIB;

    /* Make sure we don't get out of bounds. */
    if (multiboot_info.number_of_modules > MAX_NUMBER_OF_STORM_MODULES)
    {
        storm_info.number_of_modules = MAX_NUMBER_OF_STORM_MODULES;
    }
    else
    {
        storm_info.number_of_modules = multiboot_info.number_of_modules;
    }
    
    multiboot_module_info = 
        (multiboot_module_info_t *) multiboot_info.module_base;

    for (index = 0; index < storm_info.number_of_modules; index++)
    {
        storm_info.module_info[index].start = 
            multiboot_module_info[index].start;
        storm_info.module_info[index].end = multiboot_module_info[index].end;
        
        if (multiboot_module_info[index].name != NULL) 
        {
            string_copy_max (storm_info.module_info[index].name, 
                multiboot_module_info[index].name, STRING_MAX_LENGTH);
        }

        else
        {
            storm_info.module_info[index].name[0] = '\0';
        }
    }

    /* Now, save the memory map. */
    storm_info.number_of_memory_maps = multiboot_info.memory_map_length /
        sizeof (multiboot_memory_map_t);
        
    multiboot_memory_map = 
        (multiboot_memory_map_t *) multiboot_info.memory_map_address;
     
    for (index = 0; index < storm_info.number_of_memory_maps; index++)
    {
        multiboot_memory_map_t *map = 
            (multiboot_memory_map_t *) multiboot_info.memory_map_address +
                index;
    
        storm_info.memory_map[index].size = map->size;
        storm_info.memory_map[index].base_address = 
            (p_uint8_t) (uint32_t) map->base_address;
        storm_info.memory_map[index].length = (size_t) map->length;
        storm_info.memory_map[index].type = map->type;
    }

    /* Save the kernel arguments so that we can parse them later
       on.*/
    string_copy_max (storm_info.command_line, 
        (char *) multiboot_info.command_line, COMMAND_LINE_SIZE - 1);
}

