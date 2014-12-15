/* $chaos: module.c,v 1.33 2002/10/28 20:05:05 per Exp $ */
/* Abstract: Module support. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <enviroment.h>

#include "../Include/module.h"
#include "../Include/elf.h"
#include "../../Init/Include/multiboot.h"

#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#include <debug/macros.h>

/* A list of functions provided through dynamic linking to kernel
   modules. We could export everything, but we don't want to do that
   to keep the API clean. */
static function_info_t function[] = 
{
    { "register_object_create",
        (function_t) &register_object_create },
        
    { "register_object_open", 
        (function_t) &register_object_open },
        
    { "register_object_reopen",
        (function_t) &register_object_reopen },
        
    { "register_object_close",
        (function_t) &register_object_close },
        
    { "register_interface_register",
        (function_t) &register_interface_register },
        
    { "register_interface_unregister",
        (function_t) &register_interface_unregister },
        
    { "register_class_register", 
        (function_t) &register_class_register },
        
    { "register_class_unregister", 
        (function_t) &register_class_unregister },

    { "register_handle_clone", 
        (function_t) &register_handle_clone },

    { NULL, (function_t) NULL } /* End of list. */
};

/* Link the given shared module into the kernel. */
static return_t module_link (elf_header_t *elf_header)
{
    volatile return_t return_value;
    elf_parsed_t elf_parsed;
    function_t module_start = NULL;

    memory_set_uint8 ((uint8_t *) &elf_parsed, 0, sizeof (elf_parsed_t));

    /* Find the address of the symbol module_start, and pass control
       on to it. */
    return_value = elf_parse (elf_header, &elf_parsed);
    
    if (return_value != STORM_RETURN_SUCCESS)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, "Failed parse ELF.\n");
        return return_value;
    }

    /* Allocate pages and copy the sections to this space. */
    return_value = elf_load_module (&elf_parsed);
    
    if (return_value != STORM_RETURN_SUCCESS)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, "Failed loading ELF.\n");
        return return_value;
    }

    /* Try and resolve unresolved symbols */
    return_value = elf_resolve (&elf_parsed, function);
    
    if (return_value != STORM_RETURN_SUCCESS)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
            "Failed resolving unresolved symbols.\n");
        return return_value;
    }

    /* Relocate relocatable symbols (all kernel functions this module
       is accessing). */
    return_value = elf_relocate (&elf_parsed);
    if (return_value != STORM_RETURN_SUCCESS)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, "Failed relocating ELF.\n");
        return return_value;
    }

    // FIXME: Call the function module_info to get module name and
    // version from the module. This information should be added into
    // a linked list of all the modules.
    /* Everything seems to be fine. Now, we call module_start. */
    return_value = elf_symbol_find_by_name (&elf_parsed, "module_start", 
        (address_t *) &module_start);
	
    if (return_value != STORM_RETURN_SUCCESS)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
	    "Failed to find the module_start symbol.\n");
	    
        return return_value;
    }
    
    memory_allocate (&interface);
    interface->method[0] = module_start;
    interface->method[1] = module_stop;
    interface_register();
    class_register();
    object_create();

    /* Call the module entry point. */
    return_value = module_start ();

    // FIXME: If return_value != STORM_RETURN_SUCCESS, run module_stop.

    return return_value;
}

/* Initialize module support. */
return_t module_init (int argc UNUSED, char *argv[] UNUSED)
{
/*
    if (multiboot_info.has_elf_info == 0)
    {
        DEBUG_PRINT (DEBUG_LEVEL_WARNING, 
            "Warning: No ELF info.\n");
    }
    else
*/    
    {
        elf_parsed_t elf_parsed;
        memory_set_uint8 ((uint8_t *) &elf_parsed, 0, sizeof (elf_parsed_t));

        elf_parse ((elf_header_t *) MIB, 
            &elf_parsed);
    }

    if (multiboot_info.has_module_info == 0 || 
        multiboot_info.number_of_modules == 0)
    {
        DEBUG_PRINT (DEBUG_LEVEL_WARNING, 
            "Warning: No modules loaded.\n");
    }
    else
    {
        unsigned int counter;
	
        /* Check what modules GRUB has provided for us. */
        for (counter = 0; counter < multiboot_info.number_of_modules; counter++)
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
                "Starting module %s.\n", multiboot_module_info[counter].name);
                
            if (module_link (
                (elf_header_t *) multiboot_module_info[counter].start) != STORM_RETURN_SUCCESS)
            {
                DEBUG_PRINT (DEBUG_LEVEL_ERROR,             
                  "Starting module %s failed.\n",
                  multiboot_module_info[counter].name);
            }
            else
            {
#if 0
		unsigned int page_number;
		
                /* Free the memory used by the ELF image. */
                for (page_number = 
		    multiboot_module_info[counter].start / PAGE_SIZE; 
		    page_number < multiboot_module_info[counter].end 
			/ PAGE_SIZE; 
		    page_number++)
                {
                    physical_memory_deallocate (page_number, 1);
                }
#endif
        	DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
            	    "Module %s started successfull.\n", 
		    multiboot_module_info[counter].name);
		
            physical_memory_deallocate (
                multiboot_module_info[counter].start / PAGE_SIZE,
                SIZE_IN_PAGES (multiboot_module_info[counter].end - 
                multiboot_module_info[counter].start));
            }
        }
    }
    
    return 0;
}
