#include "Common/dma.h"

#define IID_DMA 0x00000301

enum
{
    MID_DMA_AREGISTER,
    MID_DMA_UNREGISTER,
    MID_DMA_TRANSFER,
};

typedef return_t (dma_aregister_function_t) (int dma_channel, void **buffer);
typedef return_t (dma_unregister_function_t) (int dma_channel);
typedef return_t (dma_transfer_function_t) (unsigned int channel, 
    unsigned int length, unsigned int operation, unsigned int transfer_mode, 
    bool autoinit);
    
typedef struct
{
    dma_aregister_function_t *aregister;
    dma_unregister_function_t *unregister;
    dma_transfer_function_t *transfer;
} dma_interface_t;

#define dma$aregister(handle,dma_channel,buffer) \
    ((dma_interface_t *) ((handle)->functions))->aregister ( \
        (dma_channel), (buffer))

#define dma$unregister(handle,dma_channel) \
    ((dma_interface_t *) ((handle)->functions))->unregister ( \
        (dma_channel))
       
#define dma$transfer(handle,channel,length,operation,transfer_mode,autoinit) \
    ((dma_interface_t *) ((handle)->functions))->transfer ( \
        (channel), (length), (operation), (transfer_mode), (autoinit))

