#include <enviroment.h>

#include "ata.h"
#include "interface.h"

#include <Classes/ata.h>

#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

bool interface_initialized = FALSE;

static return_t ata_create (context_t *context, 
    void *ata_parameters)
{
    ata_data_t *ata;
    ata_create_parameters_t *parameters;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p, %p)\n",
        __FILE__, __FUNCTION__, context, ata_parameters);
    
    parameters = (ata_create_parameters_t *) ata_parameters;

    memory_allocate ((void **) &ata, sizeof (ata_data_t));

    ata->device = parameters->device; 
    
    context->object_data = ata;
    
    return 0;
}

 
static return_t ata_destroy (context_t *context)
{
    ata_data_t *ata = context->object_data;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p)\n",
        __FILE__, __FUNCTION__, context);
    
    memory_deallocate (ata);
    
    return 0;
}

object_create_method_t ata_create_method =
{
    &ata_create,
    MID_OBJECT_CREATE,
    sizeof (void *),
    1,
    {
        {sizeof (void *)}
    }
};

object_destroy_method_t ata_destroy_method =
{
    &ata_destroy,
    MID_OBJECT_DESTROY,
    0,
    0,
};

static method_t *control_methods[] = 
{
    (method_t *) &ata_create_method,
    (method_t *) &ata_destroy_method,
};

static return_t ata_block_read (
    context_t *context,
    uint8_t *block,
    uint64_t start_block,
    uint64_t number_of_blocks)
{
    drivecmd Cmd;
    
    int Temp;
    
    Cmd.Dev = ((ata_data_t *) context->object_data)->device;
    Cmd.Cmd = DRV_CMD_RD;
    Cmd.Data = block;
    Cmd.Blk = start_block;
    Cmd.Count = number_of_blocks << 9;
    
    Temp = ata_cmd (&Cmd);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s Temp: %i\n",
        __FILE__, __FUNCTION__, Temp);
    
    return Temp;
}

static return_t ata_block_write (
    context_t *context,
    uint8_t *block,
    uint64_t start_block,
    uint64_t number_of_blocks)
{
    drivecmd Cmd;
    int Temp;

    Cmd.Dev = ((ata_data_t *) context->object_data)->device;
    Cmd.Cmd = DRV_CMD_WR;
    Cmd.Data = block;
    Cmd.Blk = start_block;
    Cmd.Count = number_of_blocks << 9;
    Temp = ata_cmd (&Cmd);

    return Temp;
}


static block_read_method_t ata_read_method =
 {
    BLOCK_READ_METHOD (ata_block_read)
};


static block_write_method_t ata_write_method =
 {
    BLOCK_WRITE_METHOD (ata_block_write)
};

static method_t *methods[] = 
{
    (method_t *) &ata_read_method,
    (method_t *) &ata_write_method
};

#define number_of_methods 2

static interface_id_t ata_object_control_interface_id;
static interface_id_t block_interface_id;
static class_id_t ata_class_id;

/* Initialise a device. */

return_t ata_main (int argc UNUSED, char *argv[] UNUSED)
{
    irqStart ();
    ata_probe ();
  
    return STORM_RETURN_SUCCESS;
}

return_t ata_block_create (unsigned int index, int num)
{
    char name[STRING_MAX_LENGTH];
    handle_t object_ata = {HANDLE_HEADER_EMPTY, NULL};
    ata_create_parameters_t parameters = {num};

    if (!interface_initialized)
    {
        register_interface_register (&ata_object_control_interface_id, 
	    IID_ATA_CLASS_CONTROL, INTERFACE_TYPE_CONTROL,
	    NUMBER_OF_OBJECT_CONTROL_METHODS, control_methods, NULL);
    
        register_interface_register (&block_interface_id, IID_BLOCK, 
            INTERFACE_TYPE_DYNAMIC, number_of_methods, methods, NULL);

        register_class_register (&ata_class_id, CID_ATA, CLASS_TYPE_DYNAMIC, 1, 
            &block_interface_id, ata_object_control_interface_id);
    
        interface_initialized = TRUE;
    }    
    
    register_object_create ((handle_t *) &object_ata, ata_class_id, 
        &parameters);

    string_print (name, "/devices/hdd/ata%u", index);
    global_namespace_bind (name, (handle_t *) &object_ata);

    return 0;
}

return_t ata_block_destroy (void)
{
    return 0;
}

