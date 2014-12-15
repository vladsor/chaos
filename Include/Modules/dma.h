extern handle_t handle_dma;

static inline return_t dma_register (int dma_channel, void **buffer)
{
    return dma$aregister (&handle_dma, dma_channel, buffer);
}

static inline return_t dma_unregister (int dma_channel)
{
    return dma$unregister (&handle_dma, dma_channel);
}

static inline return_t dma_transfer (unsigned int channel, unsigned int length, 
    unsigned int operation, unsigned int transfer_mode, bool autoinit)
{
    return dma$transfer (&handle_dma, channel, length, operation, 
        transfer_mode, autoinit);
}

