/* $chaos: multiboot.c,v 1.8 2002/10/04 19:01:21 per Exp $ */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE.
   reference documentation. */

/**
 * @file                multiboot.c
 * @brief               Parse multiboot header.
 * @author              Per Lundberg <per@chaosdev.org>
 * @author              Henrik Hallin <hal@chaosdev.org>
 * @version
 * @date                1999-2003
 */

#include <enviroment.h>
#include <string.h>

#include "Include/multiboot.h"

/* Multiboot header. */
static uint32_t multiboot_header[] 
    __attribute__ ((section (".init.pre"), unused)) = 
{
    MULTIBOOT_MAGIC,
    MULTIBOOT_FLAGS,
    - (MULTIBOOT_MAGIC + MULTIBOOT_FLAGS)
};

multiboot_info_t multiboot_info;
multiboot_module_info_t multiboot_module_info[MAX_NUMBER_OF_MULTIBOOT_MODULES];
multiboot_memory_map_t multiboot_memory_map[MEMORY_MAP_SIZE];

static char module_name[MODULE_NAME_SIZE];
static char command_line[COMMAND_LINE_SIZE];

/* Copy off some of the Multiboot data we need, so it won't be
   overwritten. */
void multiboot_init (void)
{
    char *target = (char *) module_name;
    unsigned int module;

    /* Make sure we don't get out of bounds. */
    if (multiboot_info.number_of_modules > MAX_NUMBER_OF_MULTIBOOT_MODULES)
    {
        multiboot_info.number_of_modules = MAX_NUMBER_OF_MULTIBOOT_MODULES;
    }

    /* Copy the module parameters. */
    memory_copy (multiboot_module_info, 
                 (multiboot_module_info_t *) multiboot_info.module_base,
                 (multiboot_info.number_of_modules * 
		 sizeof (multiboot_module_info_t)));

    /* First of all, make sure module names and parameters are stored
       in a safe place. Otherwise, we may overwrite them later on in
       the boot process. */
    for (module = 0; module < multiboot_info.number_of_modules;
         module++)
    {
        if (multiboot_module_info[module].name == NULL) 
        {
            multiboot_module_info[module].name = NULL;
        }
        else
        {
            string_copy (target, multiboot_module_info[module].name);
            multiboot_module_info[module].name = target;
            target += string_length (target) + 1;
        }
    }

    /* Now, save the memory map. */
    memory_copy ((void *) &multiboot_memory_map,
                 (void *) multiboot_info.memory_map_address, 
                 multiboot_info.memory_map_length);

    /* Save the kernel arguments so that we can parse them later
       on.*/
    string_copy_max (command_line, (void *) multiboot_info.command_line, 
                     COMMAND_LINE_SIZE - 1);
    (char *) multiboot_info.command_line = command_line;
}
