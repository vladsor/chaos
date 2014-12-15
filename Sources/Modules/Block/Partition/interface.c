#include <enviroment.h>

#include <Classes/kernel.h>
#include <Classes/partition.h>

#include "Include/partition_manager_class.h"
#include "Include/partition_class.h"
#include "Include/block_interface.h"

#include "Include/interface.h"
#include "Include/partition.h"

#include "Include/debug_event_class.h"
#include "Include/irq_event_class.h"

#define DEBUG_MODULE_NAME L"Partition"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#ifndef __STORM_KERNEL__
#   define DEBUG_SUPPLIER (partition_debug_supplier)
#endif

#include <debug/macros.h>

static uint32_t block_read (
    context_t context,
    sequence_t blocks,
    uint32_t offset)
{
    p_partition_data_t data;
    uint32_t count;
    
    data = (p_partition_data_t) (address_t) context.object_data;
    
    count = block$read (data->generic, blocks, data->start_block + offset);

    return count;
}

static uint32_t block_write (
    context_t context,
    sequence_t blocks,
    uint32_t offset)
{
    p_partition_data_t data;
    uint32_t count;

    data = (p_partition_data_t) (address_t) context.object_data;
    
    count = block$write (data->generic, blocks, data->start_block + offset);

    return count;
}

static block_interface_table_t block_table = 
{
    read: &block_read,
    write: &block_write
};

class_reference_t partition_class;

typedef struct
{
    wchar_t name[256];
} generic_device_t;

static generic_device_t generic_devices[] =
{
    {L"/devices/hdd/ata0"},
};

#define number_of_generic_devices sizeof (generic_devices) / \
    sizeof (generic_device_t)

event_supplier_reference_t partition_debug_supplier = REFERENCE_NULL;
static object_reference_t manager_object;
static class_reference_t manager_class;

return_t partition_main (int argc UNUSED, char *argv[] UNUSED, 
    char **envp UNUSED)
{
    sequence_t empty_seq = {data: NULL, count: 0};
    unsigned int i;
    interface_reference_t interfaces[1];
    event_supplier_interface_reference_t manager_supplier_interfaces[1];
    
    object_reference_t generic_object;
    handle_reference_t block_device;

    manager_supplier_interfaces[0] = debug_supplier_interface_register (
        EVENT_CONSUMER_TYPE_PUSH, NULL, REFERENCE_NULL);
    manager_class = partition_manager_class_register (NULL, 
        manager_supplier_interfaces, NULL);
    manager_object = object_create (manager_class, SECURITY_CURRENT, 
        empty_seq, 0);

    partition_debug_supplier = debug$supplier$create (manager_object);
    event_supplier_set_queue (partition_debug_supplier, kernel_debug_queue);

    interfaces[0] = block_interface_register (&block_table);
    partition_class = partition_class_register (interfaces);
    
    for (i = 0; i < number_of_generic_devices; i++)
    {
        generic_object = namespace$resolve (kernel_handle_namespace, 
            generic_devices[i].name);
        
        block_device = block$handle$create (generic_object);            

        scan_for_partitions (block_device, generic_devices[i].name);
        
        reference_release (block_device);
        reference_release (generic_object);
    }

    return STORM_RETURN_SUCCESS;
}

return_t partition_block_create (
    handle_reference_t generic,
    const wchar_t *name,
    unsigned int index,
    uint64_t start_block, 
    uint64_t length)
{
    p_partition_data_t data;
    wchar_t object_name[WSTRING_MAX_LENGTH];
    object_reference_t object;

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE, 
        L"%S: Creating new object...\n",
        DEBUG_MODULE_NAME);

    memory_allocate ((void **) &data, sizeof (p_partition_data_t));

    data->generic = reference_acquire (generic);
    data->start_block = start_block;
    data->number_of_blocks = length;

    object = partition$create (partition_class);
    object_set_data (object, (address_t) data);

    wstring_print (object_name, L"%S-partition%u", name, index);
    namespace$bind (kernel_handle_namespace, object_name, object);
    
    reference_release (object);

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE, 
        L"%S: Creating new object...DONE\n",
        DEBUG_MODULE_NAME);
    
    return 0;
}

return_t partition_block_destroy (void)
{
    return 0;
}

