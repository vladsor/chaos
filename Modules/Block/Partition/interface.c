#include <enviroment.h>

#include <Classes/partition.h>

#include "interface.h"
#include "partition.h"

//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

static bool interface_initialized = FALSE;

static return_t partition_create (context_t *context, 
    void *partition_parameters)
{
    partition_data_t *partition;
    partition_create_parameters_t *parameters;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p, %p)\n",
        __FILE__, __FUNCTION__, context, partition_parameters);
    
    parameters = (partition_create_parameters_t *) partition_parameters;

    memory_allocate ((void **) &partition, sizeof (partition_data_t));

    register_handle_clone (parameters->generic, &partition->generic);
    partition->type = parameters->type;
    partition->start_block = parameters->start_block;
    partition->number_of_blocks = parameters->number_of_blocks;
    
    context->object_data = partition;
    
    return 0;
}

 
static return_t partition_destroy (context_t *context)
{
    partition_data_t *partition = context->object_data;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p)\n",
        __FILE__, __FUNCTION__, context);
    
    memory_deallocate (partition);
    
    return 0;
}

object_create_method_t partition_create_method =
{
    &partition_create,
    MID_OBJECT_CREATE,
    sizeof (void *),
    1,
    {
        {sizeof (void *)}
    }
};

object_destroy_method_t partition_destroy_method =
{
    &partition_destroy,
    MID_OBJECT_DESTROY,
    0,
    0,
};

static method_t *control_methods[] = 
{
    (method_t *) &partition_create_method,
    (method_t *) &partition_destroy_method,
};

static return_t partition_block_read (
    context_t *context,
    uint8_t *block,
    uint64_t offset,
    uint64_t length)
{
    return_t return_value;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	"Partition: Reading blocks...\n");

    return_value = block$read (
        &((partition_data_t *) context->object_data)->generic, 
        block, ((partition_data_t *) context->object_data)->start_block + 
            offset, length);

    return return_value;
}

static return_t partition_block_write (
    context_t *context,
    uint8_t *block,
    uint64_t offset,
    uint64_t length)
{
    return_t return_value;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
    	"Partition: writing blocks...\n");
        
    return_value = block$write (
        &((partition_data_t *) context->object_data)->generic, 
        block, ((partition_data_t *) context->object_data)->start_block + 
            offset, length);

    return return_value;
}

static block_read_method_t partition_read_method = {
    BLOCK_READ_METHOD (partition_block_read)
};

static block_write_method_t partition_write_method = {
    BLOCK_WRITE_METHOD (partition_block_write)
};

static method_t *methods[] = 
{
    (method_t *) &partition_read_method,
    (method_t *) &partition_write_method
};

#define number_of_methods 2

static interface_id_t object_control_interface_id;
static interface_id_t block_interface_id;
static class_id_t partition_class_id;

typedef struct
{
    char name[256];
} generic_device_t;

static generic_device_t generic_devices[] =
{
    {"/devices/hdd/ata0"},
};

#define number_of_generic_devices sizeof (generic_devices) / \
    sizeof (generic_device_t)

return_t partition_main (int argc UNUSED, char *argv[] UNUSED)
{
    return_t return_value;
    unsigned int i;
    handle_t generic_object;
    
    for (i = 0; i < number_of_generic_devices; i++)
    {
        return_value = global_namespace_resolve (generic_devices[i].name, 
            &generic_object);
        
        if (return_value != STORM_RETURN_SUCCESS)
        {
            continue;
        }

        register_object_open (&generic_object, IID_BLOCK);            

        scan_for_partitions (&generic_object, generic_devices[i].name);
    }

    return STORM_RETURN_SUCCESS;
}

return_t partition_block_create (
    handle_t *generic,
    char *name,
    unsigned int index,
    uint64_t start_block, 
    uint64_t length)
{
    partition_create_parameters_t parameters;
    handle_t object_partition = {HANDLE_HEADER_EMPTY, NULL};
    char object_name[STRING_MAX_LENGTH];

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "Partition: Creating new object...\n");

    parameters.generic = generic;
    parameters.start_block = start_block;
    parameters.number_of_blocks = length;

    if (!interface_initialized)
    {
        register_interface_register (&object_control_interface_id, 
	    IID_PARTITION_CLASS_CONTROL, INTERFACE_TYPE_CONTROL,
	    NUMBER_OF_OBJECT_CONTROL_METHODS, control_methods, NULL);
    
        register_interface_register (&block_interface_id, IID_BLOCK, 
	    INTERFACE_TYPE_DYNAMIC, number_of_methods, methods, NULL);

        register_class_register (&partition_class_id, CID_PARTITION, 
            CLASS_TYPE_DYNAMIC, 1, &block_interface_id, 
            object_control_interface_id);

        interface_initialized = TRUE;
    }

    register_object_create ((handle_t *) &object_partition, partition_class_id, 
        &parameters);

    string_print (object_name, "%s-parition%u", name, index);
    global_namespace_bind (object_name, (handle_t *) &object_partition);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "Partition: Creating new object...DONE\n");
    
    return 0;
}

return_t partition_block_destroy (void)
{
    return 0;
}

