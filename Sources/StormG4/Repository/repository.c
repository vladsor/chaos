#include <enviroment.h>

#include "Include/init.h"

#define DEBUG_MODULE_NAME "Repository"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include <debug/macros.h>
#include <exception/macros.h>

return_t repository_init (int argc UNUSED, char *argv[] UNUSED, 
    char **envp UNUSED)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%u, %p, %p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        argc, argv, envp);

    repository_method_init ();

    repository_interface_init ();
    repository_event_supplier_interface_init ();
    repository_event_consumer_interface_init ();
    
    repository_class_init ();
    repository_object_init ();
    
    repository_handle_init ();
    repository_event_supplier_init ();
    repository_event_consumer_init ();
    
    repository_cpu_init ();
    repository_memory_init ();
    repository_computer_init ();
    
    return 0;
}

