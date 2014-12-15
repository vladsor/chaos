#include <enviroment.h>

#define DEBUG_MODULE_NAME "ConsoleManagerClass"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include <Classes/console_manager.h>

#include "Include/console_manager_class.h"

#include <debug/macros.h>

static description_reference_t class_description;

class_reference_t console_manager_class_register (
	interface_reference_t interfaces[],     
	event_supplier_interface_reference_t supplier_interfaces[],
	event_consumer_interface_reference_t consumer_interfaces[])
{
    sequence_t int_seq = {data: interfaces, count: 1};
    sequence_t sup_seq = {data: supplier_interfaces, count: 1};
    sequence_t cons_seq = {data: consumer_interfaces, count: 1};

    class_description = class_description_register (
        CLASS_CONSOLE_MANAGER_ID,
        L"console_manager",
        CLASS_TYPE_STATIC,
        1, 1, 1);
            
    return class_create (&class_description, int_seq, sup_seq, cons_seq, 
        REFERENCE_NULL, 0);
}

