
#include <Classes/kernel.h>
extern handle_reference_t kernel_handle_namespace;
extern event_queue_reference_t kernel_debug_queue;

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

extern event_supplier_reference_t partition_debug_supplier;

extern return_t partition_block_destroy (void);

extern return_t partition_main (int argc, char *argv[], char **envp);

