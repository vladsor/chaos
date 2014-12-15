#include <enviroment.h>

#include "Include/controller.h"

#define DEBUG_MODULE_NAME "DMA"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include <debug/macros.h>

typedef struct
{
    unsigned int channel;
    
    bool is_used;

    /* This is the address of the buffer that the memory is put in, both
       it's physical and virtual address. */
    void *physical_buffer;
    
} dma_channel_t;

dma_channel_t dma_channels[7];

return_t dma_init (int argc UNUSED, char *argv[] UNUSED, char **envp UNUSED)
{
    int i;
    
    dma_controller_init ();

    for (i = 0; i < 7; i++)
    {
        dma_channels[i].channel = i;
        dma_channels[i].is_used = FALSE;
        dma_channels[i].physical_buffer = (void *) (BASE_DMA + 64 * KIB * i);
    }
    
    return STORM_RETURN_SUCCESS;
}

return_t dma_register (int dma_channel, void **buffer)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (channel=%u, buffer=%p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
	dma_channel, buffer);

    dma_channels[dma_channel].is_used = TRUE;
    (*buffer) = dma_channels[dma_channel].physical_buffer;

    return STORM_RETURN_SUCCESS;
}

return_t dma_unregister (int dma_channel)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (channel=%u)\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
	dma_channel);
            
    dma_channels[dma_channel].is_used = FALSE;

    return STORM_RETURN_SUCCESS;
}

return_t dma_transfer (
    unsigned int channel, 
    unsigned int length, 
    unsigned int operation,
    unsigned int transfer_mode, 
    bool autoinit)
{
    unsigned int mode;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (channel=%u, length=%u, operation=%u, transfer_mode=%u, "
            "autoinit=%u)\n",
        DEBUG_MODULE_NAME, __FUNCTION__, channel, length, operation, 
	    transfer_mode, autoinit);

    /*  There are 4 transfer types demand, single, block and cascade. In
    theory floppy dma channel 2 works with single transfer but I have
    tested it with block transfer and works ok. Anyway maybe another
    parameter to this function could be transfer mode, even autoinit
    option could be another parameter. */

    /* bits 76 are 00 demand, 01 single, 10 block, 11 cascade */

    if (operation == STORM_DMA_OPERATION_WRITE)
    {
        mode = DMA_MODE_WRITE;
    }
    else if (operation == STORM_DMA_OPERATION_READ)
    {
        mode = DMA_MODE_READ;
    }
    else
    {
        return STORM_RETURN_INVALID_ARGUMENT;
    }

    /* Set up transfer in selected channel. */

    switch (transfer_mode)
    {
        case STORM_DMA_TRANSFER_MODE_DEMAND: 
        {
            mode |= DMA_MODE_DEMAND;
            break;
        }

        case STORM_DMA_TRANSFER_MODE_SINGLE:
        {
            mode |= DMA_MODE_SINGLE;
            break;
        }

        case STORM_DMA_TRANSFER_MODE_BLOCK:
        {
            mode |= DMA_MODE_BLOCK;
            break;
        }

        case STORM_DMA_TRANSFER_MODE_CASCADE:
        {
            mode |= DMA_MODE_CASCADE;
            break;
        }
    
        default:
        {
            return STORM_RETURN_INVALID_ARGUMENT;
        }
    }

    if (autoinit)
    {
        mode |= DMA_MODE_AUTOINIT_ENABLE;
    }
    else
    {
        mode |= DMA_MODE_AUTOINIT_DISABLE;
    }

    dma_controller_transfer_start (channel,
        (address_t) dma_channels[channel].physical_buffer, length, mode);
        
    return STORM_RETURN_SUCCESS;
}
