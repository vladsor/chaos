/* $chaos: initial_ramdisk.c,v 1.10 2002/11/21 21:48:44 per Exp $ */
/* Abstract: Initial ramdisk server. */

#include <enviroment.h>
#include <memory_inlines.h>

#include "ramdisk.h"
#include "block_public.h"

#include <debug.h>
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#include <debug/macros.h>

return_t ramdisk_block_read (
  data_block_t *data UNUSED,
  uint8_t *block,
  uint64_t offset,
  uint64_t length)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	"Ramdisk: Copy from %p(%u) to %p\n", 
	ramdisk + offset * RAMDISK_BLOCK_SIZE, 
	(uint32_t) length * RAMDISK_BLOCK_SIZE, 
	block);
	
    memory_copy (block, (void *) (ramdisk + offset * RAMDISK_BLOCK_SIZE), 
	(unsigned int) length * RAMDISK_BLOCK_SIZE);

    return 0;
}

return_t ramdisk_block_write (
  data_block_t *data UNUSED,
  uint8_t *block,
  uint64_t offset,
  uint64_t length)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	"Ramdisk: Copy from %p(%u) to %p\n", 
	block, (uint32_t) length * RAMDISK_BLOCK_SIZE, 
	ramdisk + offset * RAMDISK_BLOCK_SIZE);
	
    memory_copy ((void *) (ramdisk + offset * RAMDISK_BLOCK_SIZE), block, 
	(unsigned int) length * RAMDISK_BLOCK_SIZE);

    return 0;
}

/* Main function. */
return_t ramdisk_init (void)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Ramdisk: Image: %p\n", ramdisk);
    return 0;
}
