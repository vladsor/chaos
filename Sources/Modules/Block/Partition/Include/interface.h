
#include <Classes/kernel.h>

typedef struct 
{
   handle_reference_t generic;
   
   unsigned int type;
   uint64_t start_block;
   uint64_t number_of_blocks;
} partition_data_t;

typedef partition_data_t * p_partition_data_t;

extern return_t partition_block_create (
    handle_reference_t generic,
    const wchar_t *name,
    unsigned int index,
    uint64_t start_block, 
    uint64_t length);

extern return_t partition_block_destroy (void);

extern return_t partition_main (int argc, char *argv[], char **envp);

