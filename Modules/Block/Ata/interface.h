typedef struct 
{
    unsigned int device;

} ata_data_t;


extern return_t ata_main (int argc, char *argv[]);
extern return_t ata_block_create (unsigned int index, int num);extern return_t ata_block_destroy (void);