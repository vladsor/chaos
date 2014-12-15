#include <enviroment.h>

#define DEBUG_MODULE_NAME "ConsoleClass"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include <Classes/console.h>

#include "Include/console_class.h"

#include <debug/macros.h>

static description_reference_t class_description;

class_reference_t console_class_register (
	interface_reference_t interfaces[],     
	event_supplier_interface_reference_t supplier_interfaces[],
	event_consumer_interface_reference_t consumer_interfaces[],
    handle_reference_t object_factory)
{
    sequence_t int_seq = {data: interfaces, count: 3};
    sequence_t sup_seq = {data: supplier_interfaces, count: 0};
    sequence_t cons_seq = {data: consumer_interfaces, count: 0};
    
    class_description = class_description_register (
        CLASS_CONSOLE_ID,
        L"console",
        CLASS_TYPE_STATIC,
        3, 0, 0);
        
    return class_create (class_description, int_seq, sup_seq, cons_seq, 
        object_factory, 0);
}

