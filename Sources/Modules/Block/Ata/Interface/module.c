#include <enviroment.h>

//#include <Classes/kernel.h>
#include "interface.h"

//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>
#include <debug/exception.h>

handle_reference_t kernel_handle_namespace;
event_class_reference_t kernel_irq_event_class;
event_class_reference_t kernel_debug_event_class;

event_supplier_reference_t debug_supplier;

return_t module_start (int argc, char *argv[], char **envp)
{
    return_t return_value;

    kernel_handle_namespace = namespace$handle$create (OBJECT_KERNEL);
//    ata_class = ata_class_register (NULL, NULL, ata_event_consumer_interfaces);
//    ata_object = object_create (ata_class, SECURITY_CURRENT, 
//        empty_seq, 0);

    debug_supplier = event_supplier_create ();
    {
        event_consumer_reference debug_consumer;
        
        debug_consumer = object_get_event_consumer (OBJECT_KERNEL, 0);
        event_supplier_add_consumer (debug_supplier, debug_consumer);
    }    

    return_value = ata_main (argc, argv, envp);
    
    return return_value;
}

return_t module_stop (void)
{
    event_supplier_destroy (debug_supplier);
    namespace$handle$destroy (kernel_handle_namespace);
}
    
