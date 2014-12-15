/* $chaos: module.c,v 1.33 2002/10/28 20:05:05 per Exp $ */
/* Abstract: Module support. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <enviroment.h>

#include "../../Executive/Include/elf.h"
#include "../../Init/Include/multiboot.h"

#include <Classes/storm_module.h>

#include "../objects.h"

#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>
#include <exception/macros.h>

/* Defines. */
#define MODULE_NAME_LENGTH              48
#define MODULE_VERSION_LENGTH           16

/** 
 * @brief               A module information structure. 
 */
typedef struct
{
    /** 
     * @brief           The module name.
     */
    char                name[MODULE_NAME_LENGTH];
    
    /**
     * @brief           The module version. 
     */
    char                version[MODULE_VERSION_LENGTH];
} module_info_t;

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

    { "exception_add_handler",
        (function_t) &exception_add_handler },

    { "exception_remove_handler",
        (function_t) &exception_remove_handler },
        
    { "exception_invoke_handler",
        (function_t) &exception_invoke_handler },

    { NULL, (function_t) NULL } /* End of list. */
};

typedef return_t (module_start_function_t) (int argc, char *argv[]);
typedef return_t (module_stop_function_t) (void);

typedef struct
{
    elf_parsed_t elf_parsed;
    
    module_start_function_t *start;
    module_stop_function_t *stop;
  
} storm_module_data_t;

static return_t storm_module_create (context_t *context, 
    void *parameter)
{
    storm_module_data_t *data;
    elf_header_t *elf_header;
    return_t return_value;
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p, %p)\n",
        __FILE__, __FUNCTION__, context, parameter);

    memory_allocate ((void **) &data, sizeof (storm_module_data_t));

    elf_header = (elf_header_t *) parameter;

    memory_set_uint8 ((uint8_t *) &data->elf_parsed, 0, sizeof (elf_parsed_t));

    /* Find the address of the symbol module_start, and pass control
       on to it. */
    return_value = elf_parse (elf_header, &data->elf_parsed);
    
    if (return_value != STORM_RETURN_SUCCESS)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, "Failed parse ELF.\n");
        
        THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
        
        return return_value;
    }

    /* Allocate pages and copy the sections to this space. */
    return_value = elf_load_module (&data->elf_parsed);
    
    if (return_value != STORM_RETURN_SUCCESS)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, "Failed loading ELF.\n");
        
        return return_value;
    }

    /* Try and resolve unresolved symbols */
    return_value = elf_resolve (&data->elf_parsed, function);
    
    if (return_value != STORM_RETURN_SUCCESS)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
            "Failed resolving unresolved symbols.\n");

        THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
        
        return return_value;
    }

    /* Relocate relocatable symbols (all kernel functions this module
       is accessing). */
    return_value = elf_relocate (&data->elf_parsed);
    
    if (return_value != STORM_RETURN_SUCCESS)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, "Failed relocating ELF.\n");
        return return_value;
    }

    return_value = elf_symbol_find_by_name (&data->elf_parsed, "module_start", 
        (address_t *) &data->start);
	
    if (return_value != STORM_RETURN_SUCCESS)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
            "Failed to find the module_start symbol.\n");
	    
        return return_value;
    }

    return_value = elf_symbol_find_by_name (&data->elf_parsed, "module_stop", 
        (address_t *) &data->stop);

    if (return_value != STORM_RETURN_SUCCESS)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
            "Failed to find the module_stop symbol.\n");
	    
//        return return_value;
    }
    
    context->object_data = data;
    
    return 0;
}

object_create_method_t storm_module_create_method =
{
    &storm_module_create,
    MID_OBJECT_CREATE,
    sizeof (void *),
    1,
    {
        {sizeof (void *)}
    }
};

static return_t storm_module_destroy (context_t *context)
{

    storm_module_data_t *data;
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p)\n",
        __FILE__, __FUNCTION__, context);

    data = (storm_module_data_t *) context->object_data;
    memory_deallocate (data);
    
    return 0;
}

object_destroy_method_t storm_module_destroy_method =
{
    &storm_module_destroy,
    MID_OBJECT_DESTROY,
    0,
    0,
};

static method_t *control_methods[] = 
{
    (method_t *) &storm_module_create_method,
    (method_t *) &storm_module_destroy_method,
};

#define number_of_control_methods 2

static return_t storm_module_start (
    context_t *context,
    uint32_t argc, char *argv[])
{
    storm_module_data_t *data;
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p, %u, %p)\n",
        __FILE__, __FUNCTION__, context, argc, argv);

    data = (storm_module_data_t *) context->object_data;
    
    data->start (argc, argv);
    
    return 0;
}

static return_t storm_module_stop (
    context_t *context)
{
    storm_module_data_t *data;
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p)\n",
        __FILE__, __FUNCTION__, context);

    data = (storm_module_data_t *) context->object_data;
    
    data->stop ();
    
    return 0;
}

static storm_module_start_method_t storm_module_start_method =
{
    STORM_MODULE_START_METHOD (storm_module_start)
};

static storm_module_stop_method_t storm_module_stop_method =
{
    STORM_MODULE_STOP_METHOD (storm_module_stop)
};

static method_t *methods[] = 
{
    (method_t *) &storm_module_start_method,
    (method_t *) &storm_module_stop_method,
};

#define number_of_methods 2

typedef struct
{
    handle_t handle;
    
    bool enabled;
    
} storm_module_info_t;

storm_module_info_t *storm_modules;

static interface_id_t storm_module_repository_id;
static interface_id_t storm_module_interface_id;
static class_id_t storm_module_class_id;

return_t storm_module_init (int argc UNUSED, char *argv[] UNUSED)
{
    return_t return_value;
    
    if (multiboot_info.has_module_info == 0 || 
        multiboot_info.number_of_modules == 0)
    {
        DEBUG_PRINT (DEBUG_LEVEL_WARNING, 
            "Warning: No modules loaded.\n");
    }
    else
    {
        unsigned int counter;

        char temp_buffer[STRING_MAX_LENGTH];
        uint32_t number_of_arguments;
        char *array_of_arguments[STRING_MAX_LENGTH / 2];
        char module_name[STRING_MAX_LENGTH];
        
        register_interface_register (&storm_module_repository_id, 
            IID_STORM_MODULE_REPOSITORY, INTERFACE_TYPE_CONTROL, 
            number_of_control_methods, control_methods, NULL);

        register_interface_register (&storm_module_interface_id, 
            IID_STORM_MODULE, INTERFACE_TYPE_DYNAMIC, 
            number_of_methods, methods, NULL);

        register_class_register (&storm_module_class_id, CID_STORM_MODULE, 
            CLASS_TYPE_DYNAMIC, 1, &storm_module_interface_id, 
            storm_module_repository_id);

        memory_allocate ((void **) &storm_modules,
            sizeof (storm_module_info_t) * multiboot_info.number_of_modules);
        memory_set_uint8 ((uint8_t *) storm_modules, 0,
            sizeof (storm_module_info_t) * multiboot_info.number_of_modules);
	
        /* Check what modules GRUB has provided for us. */
        for (counter = 0; counter < multiboot_info.number_of_modules; 
            counter++)
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
                "Starting module %s %X.\n", 
                multiboot_module_info[counter].name,
                multiboot_module_info[counter].start);
            
            register_object_create (&storm_modules[counter].handle, 
                storm_module_class_id, 
                (elf_header_t *) multiboot_module_info[counter].start);

            string_copy (temp_buffer, multiboot_module_info[counter].name);                

            number_of_arguments = arguments_parse (temp_buffer, 
                array_of_arguments);
       
            string_print (module_name, "/storm/modules%s", 
                string_find_last_char (array_of_arguments[0], '/'));
            global_namespace_bind (module_name, &storm_modules[counter].handle);
            
            register_object_open (&storm_modules[counter].handle, 
                IID_STORM_MODULE);
            
            storm_module$start (&storm_modules[counter].handle, 
                number_of_arguments, array_of_arguments);

        	DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
            	    "Module %s started successfull.\n", 
		    multiboot_module_info[counter].name);
		
            physical_memory_deallocate (
                multiboot_module_info[counter].start / PAGE_SIZE,
                SIZE_IN_PAGES (multiboot_module_info[counter].end - 
                multiboot_module_info[counter].start));
        }
    }
    
    return 0;
}
