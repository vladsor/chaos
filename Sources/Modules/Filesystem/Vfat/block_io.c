#include <enviroment.h>

#include <Interfaces/block.h>

#include "Include/fat.h"
#include "Include/block_io.h"
#include "Include/return_values.h"

//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

//#define READ_ENABLE
//#define WRITE_ENABLE

return_t vfat_read_sectors (
    handle_reference_t device, 
    uint32_t start_sector, 
    uint32_t number_of_sectors,
    void *data_buffer)
{
    sequence_t blocks;
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "Vfat: Reading sectors: %u-%u to %p\n", 
        start_sector, start_sector + number_of_sectors - 1, data_buffer);

    blocks.data = data_buffer;
    blocks.count = number_of_sectors * 512;
    
    block$read (device, blocks, start_sector);

    return VFAT_RETURN_SUCCESS;
}

return_t vfat_write_sectors (
    handle_reference_t device, 
    uint32_t start_sector, 
    uint32_t number_of_sectors,
    void *data_buffer)
{
    sequence_t blocks;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "Vfat: Writing sectors: %u-%u from %p\n", 
        start_sector, start_sector + number_of_sectors - 1, data_buffer);

    blocks.data = data_buffer;
    blocks.count = number_of_sectors * 512;

    block$write (device, blocks, start_sector);

    return VFAT_RETURN_SUCCESS;
}

