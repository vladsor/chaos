
#include <Interfaces/block.h>

typedef struct 
{
} data_block_t;

extern return_t ramdisk_block_read (
  data_block_t *data,
  uint8_t *block,
  uint64_t offset,
  uint64_t length);

extern return_t ramdisk_block_write (
  data_block_t *object,
  uint8_t *block,
  uint64_t offset,
  uint64_t length);
