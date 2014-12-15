
#define IID_STREAM_CHANNEL_CLASS_CONTROL 0x00005000

typedef struct 
{
    uint32_t block_size;
    uint32_t max_blocks;
} stream_channel_create_parameters_t;
