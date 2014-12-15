#include <enviroment.h>

#include "fat.h"
#include "block_io.h"
#include "return_values.h"
#include "block_public.h"
#include <Interfaces/block.h>

#include <debug.h>
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

//#define READ_ENABLE
//#define WRITE_ENABLE

return_t vfat_read_sectors (
    device_t *device, 
    uint32_t start_sector, 
    uint32_t number_of_sectors,
    void *data_buffer)
{
    return_t return_value;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
	"Vfat: Reading sectors: %u-%u to %p\n", 
	start_sector, start_sector + number_of_sectors - 1, data_buffer);

    return_value = block$read (device->generic, data_buffer, start_sector, 
	number_of_sectors);

    return VFAT_RETURN_SUCCESS;
}

return_t vfat_write_sectors (
  device_t *device, 
  uint32_t start_sector, 
  uint32_t number_of_sectors,
  void *data_buffer)
{
    return_t return_value;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
	"Vfat: Writing sectors: %u-%u from %p\n", 
	start_sector, start_sector + number_of_sectors - 1, data_buffer);

    return_value = block$write (device->generic, data_buffer, start_sector, 
	number_of_sectors);

    return VFAT_RETURN_SUCCESS;
}

