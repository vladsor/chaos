#include <enviroment.h>

#define DEBUG_MODULE_NAME "Kernel"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include <Classes/kernel.h>

#include "../event_supplier_interfaces.h"
#include "Include/debug_event_class.h"

#include <debug/macros.h>

description_reference_t debug_event_class;

event_supplier_interface_reference_t debug_supplier_init (void)
{
    event_supplier_interface_reference_t interface;

    debug_event_class = debug_description_register ();

    interface = debug_supplier_interface_register (EVENT_SUPPLIER_TYPE_PUSH,
        NULL, REFERENCE_NULL);

    return interface;
}    

