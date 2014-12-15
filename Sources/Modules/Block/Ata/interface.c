#include <enviroment.h>

#include "Include/ata.h"
#include "Include/interface.h"

#include <Classes/kernel.h>
#include <Classes/ata_drive.h>

#include "Include/ata_class.h"
#include "Include/ata_drive_class.h"
#include "Include/block_interface.h"
#include "Include/irq_event_class.h"

#define DEBUG_MODULE_NAME "ATA"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

static uint32_t ata_block_read (
    context_t context,
    sequence_t block,
    uint32_t start_block)
{
    drive_command_t cmd;
    p_drive_t drive;
    int Temp;
    
    drive = (p_drive_t) (address_t) context.object_data;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s: %s (%p, {%p, %u}, %u)\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        drive, block.data, block.count, start_block);
    
    cmd.command = DRIVE_COMMAND_READ;
    cmd.data = block.data;
    cmd.bulk = start_block;
    cmd.count = block.count;
    
    Temp = ata_command (drive, &cmd);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
        "%s: %s Result=%i, Data=%X %X %X %X\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        Temp, ((p_uint32_t) cmd.data)[0], ((p_uint32_t) cmd.data)[1],
        ((p_uint32_t) cmd.data)[2], ((p_uint32_t) cmd.data)[3]);

    return block.count;
}

static uint32_t ata_block_write (
    context_t context,
    sequence_t block,
    uint32_t start_block)
{
    drive_command_t cmd;
    int Temp;
    p_drive_t drive;

    drive = (p_drive_t) (address_t) context.object_data;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s: %s (%p, {%p, %u}, %u)\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        drive, block.data, block.count, start_block);

    cmd.command = DRIVE_COMMAND_WRITE;
    cmd.data = block.data;
    cmd.bulk = start_block;
    cmd.count = block.count;

    Temp = ata_command (drive, &cmd);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
        "%s: %s Result=%i, Data=%X %X %X %X\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        Temp, ((p_uint32_t) cmd.data)[0], ((p_uint32_t) cmd.data)[1],
        ((p_uint32_t) cmd.data)[2], ((p_uint32_t) cmd.data)[3]);

    return block.count;
}

static block_interface_table_t block_table = 
{
    &ata_block_read,
    &ata_block_write
};

class_reference_t ata_drive_class;

static object_reference_t ata_object;
static class_reference_t ata_class;

event_consumer_reference_t irq14_consumer;
event_consumer_reference_t irq15_consumer;

event_supplier_reference_t irq14_supplier;
event_supplier_reference_t irq15_supplier;

event_queue_reference_t irq14_queue;
event_queue_reference_t irq15_queue;

/* Initialise a device. */

return_t ata_main (int argc UNUSED, char *argv[] UNUSED, char **envp UNUSED)
{
    interface_reference_t ata_drive_interfaces[1];
    event_consumer_interface_reference_t ata_event_consumer_interfaces[1];
    sequence_t empty_seq = {data: NULL, count: 0};

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s: %s ()\n",
        DEBUG_MODULE_NAME, __FUNCTION__);
 
    ata_drive_interfaces[0] = block_interface_register (&block_table);
    ata_drive_class = ata_drive_class_register (ata_drive_interfaces);


    ata_event_consumer_interfaces[0] = irq_consumer_interface_register (
        EVENT_CONSUMER_TYPE_PULL, NULL, REFERENCE_NULL);
        
    ata_class = ata_class_register (NULL, NULL, ata_event_consumer_interfaces);
    ata_object = object_create (ata_class, SECURITY_CURRENT, 
        empty_seq, 0);

    irq14_supplier = irq$supplier$create (OBJECT_KERNEL, 14);        
    irq14_consumer = irq$consumer$create (ata_object);

    irq14_queue = event_queue_create (irq_description_register (), 
        EVENT_QUEUE_TYPE_ASYNCHRONOUS, 1);
    event_supplier_set_queue (irq14_supplier, irq14_queue);
    event_consumer_set_queue (irq14_consumer, irq14_queue);

    irq15_supplier = irq$supplier$create (OBJECT_KERNEL, 15);        
    irq15_consumer = irq$consumer$create (ata_object);

    irq15_queue = event_queue_create (irq_description_register (), 
        EVENT_QUEUE_TYPE_ASYNCHRONOUS, 1);
    event_supplier_set_queue (irq15_supplier, irq15_queue);
    event_consumer_set_queue (irq15_consumer, irq15_queue);
    
    ata_probe ();
  
    return STORM_RETURN_SUCCESS;
}


