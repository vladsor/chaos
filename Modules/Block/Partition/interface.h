typedef struct 
{
   handle_t generic;
   
   unsigned int type;
   uint64_t start_block;
   uint64_t number_of_blocks;
} partition_data_t;
//extern object_block_t partition1;

extern return_t partition_block_create (
    handle_t *generic,
    char *name,
    unsigned int index,
    uint64_t start_block, 
    uint64_t length);

extern return_t partition_block_destroy (void);

extern return_t partition_main (int argc, char *argv[]);

