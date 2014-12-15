#include <enviroment.h>

//#include <Classes/kernel.h>
#include "Include/interface.h"

//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

#if defined (__STORM_KERNEL_MODULE__)

handle_reference_t kernel_handle_namespace = REFERENCE_NULL;
event_queue_reference_t kernel_debug_queue = REFERENCE_NULL;

return_t module_start (int argc, char *argv[], char **envp)
{
    return_t return_value;

    kernel_handle_namespace = namespace$handle$create (OBJECT_KERNEL);
    kernel_debug_queue = namespace$resolve (kernel_handle_namespace, 
        L"/Kernel/EventQueue/debug");
 
    return_value = realtek_pci_main (argc, argv, envp);
    
    return return_value;
}

return_t module_stop (void)
{
    return 0;
}

#endif /* defined (__STORM_KERNEL_MODULE__) */
