#include <enviroment.h>

#include "../classes.h"
#include "../interfaces.h"

#include <Classes/storm_program.h>

#include "storm_program.h"

#define DEBUG_MODULE_NAME "StormProgramClass"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include <debug/macros.h>
#include <exception/macros.h>

static description_reference_t class_description;

/* Main function. */

class_reference_t storm_program_class_init (void)
{
    class_reference_t class;
    interface_reference_t interfaces[1];
    sequence_t int_seq = { data: interfaces, count: 1 };
    sequence_t event_sup_seq = { data: NULL, count: 0 }; 
    sequence_t event_cons_seq = { data: NULL, count: 0 }; 

    class_description = class_description_register (
        CLASS_STORM_PROGRAM_ID,
        L"storm_program",
        CLASS_TYPE_STATIC,
        1,
        0,
        0);

    interfaces[0] = storm_program_control_init ();

    class = class_create (class_description, int_seq, 
        event_sup_seq, event_cons_seq, 
        kernel_interfaces_info[
            KERNEL_INTERFACE_STORM_PROGRAM_FACTORY_INDEX].interface, 0);
    
    return class;
}

