
#define IID_PARTITION_CLASS_CONTROL 0x00005000

typedef struct 
{
   handle_t *generic;
   
   unsigned int type;
   uint64_t start_block;
   uint64_t number_of_blocks;
} partition_create_parameters_t;
