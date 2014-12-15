#include <enviroment.h>

#define DEBUG_MODULE_NAME "ata_class"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include <Classes/ata_drive.h>

#include "Include/ata_drive_class.h"

#include <debug/macros.h>

class_reference_t ata_drive_class_register (interface_reference_t interfaces[])
{
    description_reference_t class_description;

    sequence_t empty_seq = {data: NULL, count: 0};
    sequence_t int_seq = {data: interfaces, count: 1};

    class_description = class_description_register (
        CLASS_ATA_DRIVE_ID,
        L"ata_drive",
        CLASS_TYPE_STATIC,
        1, 0, 0);
    
    return class_create (class_description, int_seq, empty_seq, empty_seq, 
        REFERENCE_NULL, 0);
}

