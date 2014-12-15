#include <enviroment.h>

#define DEBUG_MODULE_NAME "Kernel"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include <Classes/kernel.h>

#include "../event_supplier_interfaces.h"
#include "../interfaces.h"
#include "Include/irq_event_class.h"

#include <debug/macros.h>

event_supplier_interface_reference_t irq_supplier_init (void)
{
    event_supplier_interface_reference_t interface;
    
    interface = irq_supplier_interface_register (EVENT_SUPPLIER_TYPE_PUSH, NULL,
        REFERENCE_NULL);

    event_supplier_interface_set_factory (interface,
        kernel_interfaces_info[
            KERNEL_INTERFACE_IRQ_SUPPLIER_FACTORY_INDEX].interface);

    return interface;
}    

