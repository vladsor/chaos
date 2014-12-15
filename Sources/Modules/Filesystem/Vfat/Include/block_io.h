
#include <Interfaces/block.h>

static inline return_t vfat_read_sectors (
    handle_reference_t device, 
    uint32_t start_sector, 
    uint32_t number_of_sectors,
    void *buffer)
{
    sequence_t blocks;

    blocks.data = buffer;
    blocks.count = number_of_sectors * BLOCK_SIZE;
    
    block$read (device, blocks, start_sector);

    return VFAT_RETURN_SUCCESS;
}

static inline return_t vfat_write_sectors (
    handle_reference_t device,
    uint32_t start_sector,
    uint32_t number_of_sectors,
    void *buffer)
{
    sequence_t blocks;

    blocks.data = buffer;
    blocks.count = number_of_sectors * BLOCK_SIZE;

    block$write (device, blocks, start_sector);

    return VFAT_RETURN_SUCCESS;
}
