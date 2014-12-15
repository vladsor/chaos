#include <enviroment.h>

#include "Include/ata.h"
#include "Include/interface.h"

#include <Classes/kernel.h>
#include <Classes/ata_drive.h>

#include "Include/ata_class.h"
#include "Include/ata_drive_class.h"
#include "Include/block_interface.h"

#define DEBUG_MODULE_NAME "ATA"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

event_consumer_reference_t irq14_consumer;
event_consumer_reference_t irq15_consumer;

/* Initialise a device. */

return_t ata_main (int argc UNUSED, char *argv[] UNUSED, char **envp UNUSED)
{
    interface_reference_t ata_drive_interfaces[1];
    event_consumer_interface_reference_t ata_event_consumer_interfaces[2];
    sequence_t empty_seq = {data: NULL, count: 0};

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s: %s ()\n",
        DEBUG_MODULE_NAME, __FUNCTION__);
 
    ata_event_consumer_interfaces[0] = event_consumer_interface_create (
        kernel_irq_event_class, EVENT_CONSUMER_TYPE_PULL, 
        REFERENCE_NULL, 0);
    ata_event_consumer_interfaces[1] = event_consumer_interface_create (
        kernel_irq_event_class, EVENT_CONSUMER_TYPE_PULL, 
        REFERENCE_NULL, 0);
        
    irq14_consumer = event_consumer_create (ata_object, 0);
    irq15_consumer = event_consumer_create (ata_object, 1);
    
    {
        event_supplier_reference_t irq_supplier;
        
        irq_supplier = object_get_event_supplier (OBJECT_KERNEL, 14);
        event_supplier_add_consumer (irq_supplier, irq14_consumer);
        
        irq_supplier = object_get_event_supplier (OBJECT_KERNEL, 15);
        event_supplier_add_consumer (irq_supplier, irq15_consumer);
    }

    ata_main ();
  
    return STORM_RETURN_SUCCESS;
}


