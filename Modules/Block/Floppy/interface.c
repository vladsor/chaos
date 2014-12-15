/* Abstract: Floppy drive server. */
/* Authors: Vladimir Sorokin */

/* Copyright 2001 chaos development. */

#include <enviroment.h>
#include <memory_inlines.h>

#include "floppy.h"

#include <Classes/floppy.h>

#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#include <debug/macros.h>

#define BLOCK_SIZE       512
#define NUMBER_OF_BLOCKS 2881


static return_t floppy_block_read (
    context_t *context UNUSED,
    uint8_t *block,
    uint64_t start_block,
    uint64_t number_of_blocks)
{
    bool rv;
    
    rv = floppy_driver_read_block (start_block,  block, number_of_blocks);

    return rv ? 1 : 2;
}

static return_t floppy_block_write (
    context_t *context UNUSED,
    uint8_t *block,
    uint64_t start_block,
    uint64_t number_of_blocks)
{
    bool rv;

    rv = floppy_driver_write_block (start_block, block, number_of_blocks);

    return rv ? 1 : 2;
}

static block_read_method_t floppy_read_method =
{
    BLOCK_READ_METHOD (floppy_block_read)
};

static block_write_method_t floppy_write_method =
{
    BLOCK_WRITE_METHOD (floppy_block_write)
};

static method_t *methods[] = 
{
    (method_t *) &floppy_read_method,
    (method_t *) &floppy_write_method,
};
#define number_of_methods 2

handle_t object_floppy;

static interface_id_t floppy_interface_id;
static class_id_t floppy_class_id;

/* Main function. */

return_t floppy_main (int argc UNUSED, char *argv[] UNUSED)
{
//  system_process_name_set (PACKAGE_NAME);
//  system_thread_name_set ("Initialising");

//  log_init (&log_structure, PACKAGE_NAME, &empty_tag);

    if (!floppy_driver_init ())
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, "No Floppy Drive found.\n");
    
        return -1;
    }

    register_interface_register (&floppy_interface_id, IID_BLOCK, 
        INTERFACE_TYPE_DYNAMIC, number_of_methods, methods, NULL);

    register_class_register (&floppy_class_id, CID_FLOPPY, CLASS_TYPE_DYNAMIC,
        1, &floppy_interface_id, IID_NONE);

    register_object_create ((handle_t *) &object_floppy, floppy_class_id, 
        NULL);

    global_namespace_bind ("/devices/floppy", (handle_t *) &object_floppy);

    return 0;
}
