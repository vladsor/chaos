#include <enviroment.h>

#define DEBUG_MODULE_NAME "KeyboardClass"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include <Classes/keyboard.h>

#include "Include/keyboard_class.h"

#include <debug/macros.h>
#include <exception/macros.h>

static description_reference_t class_description;

class_reference_t keyboard_class_register (
	interface_reference_t interfaces[],     
	event_supplier_interface_reference_t supplier_interfaces[],
	event_consumer_interface_reference_t consumer_interfaces[],
    handle_reference_t object_factory)
{
    sequence_t int_seq = {data: interfaces, count: 1};
    sequence_t sup_seq = {data: supplier_interfaces, count: 2};
    sequence_t cons_seq = {data: consumer_interfaces, count: 1};
    
    class_description = class_description_register (
        CLASS_KEYBOARD_ID,
        L"keyboard",
        CLASS_TYPE_STATIC,
        1,
        1,
        1);
    
    return class_create (class_description, int_seq, sup_seq, cons_seq, 
        object_factory, 0);
}

