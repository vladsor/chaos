/* $chaos: module.c,v 1.33 2002/10/28 20:05:05 per Exp $ */
/* Abstract: Module support. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <enviroment.h>

#include "../../Executive/Include/elf.h"
#include "../../Init/Include/multiboot.h"

#include <Classes/storm_module.h>

#define DEBUG_MODULE_NAME "Module"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>
#include <exception/macros.h>



p_storm_module_info_t storm_modules;

//static interface_id_t storm_module_repository_id;
//static interface_id_t storm_module_interface_id;
//static class_id_t storm_module_class_id;


return_t storm_module_init (int argc UNUSED, char *argv[] UNUSED)
{
//    return_t return_value;
    
    if (multiboot_info.has_module_info == 0 || 
        multiboot_info.number_of_modules == 0)
    {
        DEBUG_PRINT (DEBUG_LEVEL_WARNING, 
            "Warning: No modules loaded.\n");
    }
    else
    {
        
//        register_interface_register (&storm_module_repository_id, 
//            IID_STORM_MODULE_REPOSITORY, INTERFACE_TYPE_CONTROL, 
//            number_of_control_methods, control_methods, NULL);

//        register_interface_register (&storm_module_interface_id, 
//            IID_STORM_MODULE, INTERFACE_TYPE_DYNAMIC, 
//            number_of_methods, methods, NULL);

//        register_class_register (&storm_module_class_id, CID_STORM_MODULE, 
//            CLASS_TYPE_DYNAMIC, 1, &storm_module_interface_id, 
//            storm_module_repository_id);

    }
    
    return 0;
}
