#include <enviroment.h>

#define DEBUG_MODULE_NAME "ata_drive_class"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include <Classes/ata.h>

#include "Include/ata_class.h"

#include <debug/macros.h>

class_reference_t ata_class_register (
	interface_reference_t interfaces[],     
	event_supplier_interface_reference_t supplier_interfaces[],
	event_consumer_interface_reference_t consumer_interfaces[])
{
    description_reference_t class_description;

    sequence_t int_seq = {data: interfaces, count: 0};
    sequence_t sup_seq = {data: supplier_interfaces, count: 0};
    sequence_t cons_seq = {data: consumer_interfaces, count: 1};

    class_description = class_description_register (
        CLASS_ATA_ID,
        L"ata",
        CLASS_TYPE_STATIC,
        0, 0, 1);
    
    return class_create (class_description, int_seq, sup_seq, cons_seq, 
        REFERENCE_NULL, 0);
}

