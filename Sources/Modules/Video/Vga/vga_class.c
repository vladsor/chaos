#include <enviroment.h>

#define DEBUG_MODULE_NAME "vga_class"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include <Classes/vga.h>

#include "Include/vga_class.h"

#include <debug/macros.h>

static description_reference_t class_description;

class_reference_t vga_class_register (interface_reference_t interfaces[])
{
    sequence_t empty_seq = {data: NULL, count: 0};
    sequence_t ints_seq = {data: interfaces, count: 1};
    
    class_description = class_description_register (
        CLASS_VGA_ID,
        L"VGA",
        CLASS_TYPE_STATIC,
        1, 0, 0);
    
    return class_create (class_description, ints_seq, empty_seq, empty_seq, 
        REFERENCE_NULL, 0);
}

