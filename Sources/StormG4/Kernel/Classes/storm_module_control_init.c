#include <enviroment.h>

#include <Interfaces/storm_module_control.h>

#include "storm_module.h"
#include "storm_module_control_interface.h"

#define DEBUG_MODULE_NAME "StormModuleControl"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE1
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>
#include <exception/macros.h>

static return_t start (context_t context,
    uint32_t argc, char *argv[], char **envp)
{
    p_storm_module_data_t module;
    return_t return_value;

    module = (p_storm_module_data_t) (address_t) context.object_data;
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s: %s (%p, %u, %p, %p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        module, argc, argv, envp);

    return_value = module->start (argc, argv, envp);
    
    return return_value;
}

static return_t stop (context_t context)
{
    p_storm_module_data_t module;
    return_t return_value;

    module = (p_storm_module_data_t) (address_t) context.object_data;
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s: %s (%p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        module);

    return_value = module->stop ();
    
    return return_value;
}

static storm_module_control_interface_table_t table = 
{
    &start,
    &stop,
};

/* Main function. */

interface_reference_t storm_module_control_init (void)
{
    return storm_module_control_interface_register (&table);
}

