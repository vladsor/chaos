#include <enviroment.h>

#define DEBUG_MODULE_NAME "vga_class"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include <Classes/vga.h>

#include "Include/vga_class.h"

#include <debug/macros.h>

static description_reference_t class_description;

class_reference_t vga_class_register (
	interface_reference_t interfaces[],
	event_supplier_interface_reference_t supplier_interfaces[],
	event_consumer_interface_reference_t consumer_interfaces[])
{
    sequence_t int_seq = {data: interfaces, count: 1};
    sequence_t sup_seq = {data: supplier_interfaces, count: 1};
    sequence_t cons_seq = {data: consumer_interfaces, count: 0};
    
    class_description = class_description_register (
        CLASS_VGA_ID,
        L"vga",
        CLASS_TYPE_STATIC,
        1, 1, 0);
    
    return class_create (class_description, int_seq, sup_seq, cons_seq, 
        REFERENCE_NULL, 0);
}

