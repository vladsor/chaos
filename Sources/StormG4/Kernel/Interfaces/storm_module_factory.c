#include <enviroment.h>

#include "../interfaces.h"

#include "../Classes/storm_module.h"

#include <Interfaces/storm_module_factory.h>

#include "storm_module_factory_interface.h"

#define DEBUG_MODULE_NAME "StormModuleFactory"

#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE1
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>
#include <exception/macros.h>

static void dummy (void) 
{
}    

/* A list of functions provided through dynamic linking to kernel
   modules. We could export everything, but we don't want to do that
   to keep the API clean. */
function_info_t functions_table[] = 
{
    { "reference_release",
        (p_function_t) &reference_release },

    { "method_description_register",
        (p_function_t) &method_description_register },
    { "interface_description_register",
        (p_function_t) &interface_description_register },
    { "event_description_register",
        (p_function_t) &event_description_register },
    { "class_description_register",
        (p_function_t) &class_description_register },

    { "method_create",      (p_function_t) &method_create },
    { "method_destroy",     (p_function_t) &method_destroy },
//    { "method_invoke",      (p_function_t) &method_invoke },
    
    { "interface_create",   (p_function_t) &interface_create },
    
    { "class_create",       (p_function_t) &class_create },

    { "security_get_current",
        (p_function_t) &security_get_current },
    
    { "object_create",      
        (p_function_t) &object_create },
    { "object_get_current", 
        (p_function_t) &object_get_current },
    { "object_get_kernel",
        (p_function_t) &object_get_kernel },
    
    { "handle_create",      (p_function_t) &handle_create },
    { "handle_invoke_method",      (p_function_t) &handle_invoke_method },
    
    { "event_supplier_interface_create", 
        (p_function_t) &event_supplier_interface_create },
    { "event_supplier_interface_set_factory",
        (p_function_t) &event_supplier_interface_set_factory },

    { "event_consumer_interface_create", 
        (p_function_t) &event_consumer_interface_create },
    { "event_consumer_interface_set_factory",
        (p_function_t) &event_consumer_interface_set_factory },

    { "event_supplier_create",
        (p_function_t) &event_supplier_create },
    { "event_supplier_fire_event",
        (p_function_t) &event_supplier_fire_event },
    { "event_supplier_set_queue",
        (p_function_t) &event_supplier_set_queue },

    { "event_consumer_create",
        (p_function_t) &event_consumer_create },
    { "event_consumer_wait_event",
        (p_function_t) &event_consumer_wait_event },
    { "event_consumer_set_queue",
        (p_function_t) &event_consumer_set_queue },

    { "event_queue_create",
        (p_function_t) &event_queue_create },

    { "cpu_create",
        (p_function_t) &cpu_create },
    { "cpu_sleep_milli",
        (p_function_t) &cpu_sleep_milli },
    { "cpu_get_current",
        (p_function_t) &cpu_get_current },

    { "computer_create",
        (p_function_t) &computer_create },
    { "computer_fire_exception",
        (p_function_t) &computer_fire_exception },
    { "computer_get_current",
        (p_function_t) &computer_get_current },

    { "quality_set",
        (p_function_t) &dummy },
    { "quality_reset",
        (p_function_t) &dummy },
        
    { NULL,
        (p_function_t) NULL } /* End of list. */
};

static uint64_t storm_module_create (context_t context UNUSED, 
    elf_header_t *elf_header)
{
    return_t return_value;
    storm_module_data_t *data;
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s: %s (%llX, %p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        context.object_data, elf_header);

    memory_allocate ((void **) &data, sizeof (storm_module_data_t));
    memory_clear (data, sizeof (storm_module_data_t));

    /* Find the address of the symbol module_start, and pass control
       on to it. */
    return_value = elf_parse (elf_header, &data->elf_parsed);
    
    if (return_value != STORM_RETURN_SUCCESS)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
            "%s: Failed parse ELF.\n",
            DEBUG_MODULE_NAME);
        
        EXCEPTION_THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
    }

    /* Allocate pages and copy the sections to this space. */
    return_value = elf_load_module (&data->elf_parsed);
    
    if (return_value != STORM_RETURN_SUCCESS)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
            "%s: Failed loading ELF.\n",
            DEBUG_MODULE_NAME);
        
        EXCEPTION_THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
    }

    /* Try and resolve unresolved symbols */
    return_value = elf_resolve (&data->elf_parsed, functions_table);
    
    if (return_value != STORM_RETURN_SUCCESS)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
            "%s: Failed resolving unresolved symbols.\n",
            DEBUG_MODULE_NAME);

        EXCEPTION_THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
    }

    /* Relocate relocatable symbols (all kernel functions this module
       is accessing). */
    return_value = elf_relocate (&data->elf_parsed);
    
    if (return_value != STORM_RETURN_SUCCESS)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
            "%s: Failed relocating ELF.\n",
            DEBUG_MODULE_NAME);
            
        EXCEPTION_THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
    }

    return_value = elf_symbol_find_by_name (&data->elf_parsed, "module_start", 
        (address_t *) &data->start);
	
    if (return_value != STORM_RETURN_SUCCESS)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
            "%s: Failed to find the \"module_start\" symbol.\n",
            DEBUG_MODULE_NAME);
	    
        EXCEPTION_THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
    }

    return_value = elf_symbol_find_by_name (&data->elf_parsed, "module_stop", 
        (address_t *) &data->stop);

    if (return_value != STORM_RETURN_SUCCESS)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
            "%s: Failed to find the \"module_stop\" symbol.\n",
            DEBUG_MODULE_NAME);
	    
        EXCEPTION_THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
    }
    
    return (address_t) data;
}

static void storm_module_destroy (context_t context UNUSED, uint64_t data)
{
    storm_module_data_t *module_data;
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s: %s (%llX)\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        data);

    module_data = (storm_module_data_t *) (address_t) data;

    memory_deallocate (module_data);
}

static storm_module_factory_interface_table_t table = 
{
    &storm_module_create,
    &storm_module_destroy,
};

/* Main function. */

interface_reference_t storm_module_factory_interface_init (void)
{
    return storm_module_factory_interface_register (&table);
}


