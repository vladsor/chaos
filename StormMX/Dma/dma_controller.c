/* $Id: dma.c,v 1.2 2001/02/10 21:25:55 jojo Exp $ */

/* Copyright 1999-2002 chaos development. */

/**
 * @file                 dma.c
 * @brief                Management of the DMA hardware. It is used for 
 *                       transferring memory blocks to and from hardware.
 * @author               Anders Ohrt <doa@chaosdev.org>
 *                       Vladimir Sorokin
 * @version              1.5
 * @date                 1993-2004
 */
 
#include <enviroment.h>

#include "Include/dma_controller.h"

//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

enum dma_channel_t
{
    DMA_CHANNEL_0 = 0,
    DMA_CHANNEL_1 = 1,
    DMA_CHANNEL_2 = 2,
    DMA_CHANNEL_3 = 3,
    DMA_CHANNEL_4 = 4,
    DMA_CHANNEL_5 = 5,
    DMA_CHANNEL_6 = 6,
    DMA_CHANNEL_7 = 7,

    /* Unavailable channels. */
    DMA_CHANNEL_CASCADE        = 4,
};

typedef struct
{
    uint8_t channel : 2;
    uint8_t mode : 2;
    uint8_t autoinit : 1;
    uint8_t decrement : 1;
    uint8_t transfer_mode : 2;
} dma_mode_register_t;

typedef struct
{
    uint8_t memory_to_memory_enable : 1;
    uint8_t : 1;
    uint8_t : 1;
    uint8_t : 1;
    uint8_t : 1;
    uint8_t : 1;
    uint8_t : 1;
    uint8_t : 1;
} dma_command_register_t;

/* Controller registers. */

static const unsigned int dma_command[NUMBER_OF_DMA_CONTROLLERS] =
{
    0x08, 0xD0
};

static const unsigned int dma_state[NUMBER_OF_DMA_CONTROLLERS] =
{
    0x08, 0xD0
};

static const unsigned int dma_request[NUMBER_OF_DMA_CONTROLLERS] =
{
    0x09, 0xD2
};

static const unsigned int dma_reset[NUMBER_OF_DMA_CONTROLLERS] =
{
    0x0D, 0xDA
};

static const unsigned int dma_reset_mask[NUMBER_OF_DMA_CONTROLLERS] =
{
    0x0E, 0xDC
};

static const unsigned int dma_temporary_register[NUMBER_OF_DMA_CONTROLLERS] =
{
    0x0D, 0xDA
};

static const unsigned int dma_all_mask[NUMBER_OF_DMA_CONTROLLERS] =
{
    0x0F, 0xDE
};

static const unsigned int dma_mask[NUMBER_OF_DMA_CONTROLLERS] =
{
    0x0A, 0xD4
};

static const unsigned int dma_mode[NUMBER_OF_DMA_CONTROLLERS] = 
{
    0x0B, 0xD6
};

static const unsigned int dma_flip_flop[NUMBER_OF_DMA_CONTROLLERS] =
{
    0x0C, 0xD8
};

/* Channel registers. */

static const unsigned int dma_page[NUMBER_OF_DMA_CHANNELS] =
{
    0x87, 0x83, 0x81, 0x82, 0x8F, 0x8B, 0x89, 0x8A 
};

static const unsigned int dma_address[NUMBER_OF_DMA_CHANNELS] = 
{
    0x00, 0x02, 0x04, 0x06, 0xC0, 0xC4, 0xC8, 0xCC 
};

static const unsigned int dma_count[NUMBER_OF_DMA_CHANNELS] =
{
    0x01, 0x03, 0x05, 0x07, 0xC2, 0xC6, 0xCA, 0xCE
};

#define DMA_RESET 			0
#define DMA_MASK_ALL_CHANNELS 		0x0F
#define CANCEL_DMA_TRANSFER 		0x04

/* Initialise the DMA code. */

return_t dma_controller_init (void)
{
    unsigned int controller;

    /* Master reset to all controllers */

    for (controller = 0; controller < NUMBER_OF_DMA_CONTROLLERS; controller++)
    {
        port_uint8_out (dma_reset[controller], DMA_RESET);
    }

    for (controller = 0; controller < NUMBER_OF_DMA_CONTROLLERS; controller++)
    {
        port_uint8_out (dma_reset_mask[controller], DMA_RESET);
    }

    port_uint8_out (dma_command[1], 
        DMA_MODE_AUTOINIT_ENABLE | DMA_MODE_CASCADE | 0);

    port_uint8_out (dma_all_mask[0], 0x0F);
    port_uint8_out (dma_all_mask[1], DMA_MASK_ALL_CHANNELS & 
        ~(BIT_VALUE(DMA_CHANNEL_CASCADE % 
            NUMBER_OF_DMA_CHANNELS_PER_CONTROLLER)));

    return STORM_RETURN_SUCCESS;
}

return_t dma_contoller_enable_channel (unsigned int channel)
{
    /* Controller channel number. */

    unsigned int controller_channel;

    /* Controller number. */

    unsigned int controller;

    DEBUG_ASSERT ((channel < NUMBER_OF_DMA_CHANNELS), "");
    DEBUG_ASSERT ((channel != DMA_CHANNEL_CASCADE), "");

    controller_channel = channel % NUMBER_OF_DMA_CHANNELS_PER_CONTROLLER;
    controller = channel / NUMBER_OF_DMA_CHANNELS_PER_CONTROLLER;

    port_uint8_out (dma_mask[controller], controller_channel);

    return STORM_RETURN_SUCCESS;
}

return_t dma_contoller_disable_channel (unsigned int channel)
{
    /* Controller channel number. */

    unsigned int controller_channel;

    /* Controller number. */

    unsigned int controller;

    DEBUG_ASSERT ((channel < NUMBER_OF_DMA_CHANNELS), "");
    DEBUG_ASSERT ((channel != DMA_CHANNEL_CASCADE), "");

    controller_channel = channel % NUMBER_OF_DMA_CHANNELS_PER_CONTROLLER;
    controller = channel / NUMBER_OF_DMA_CHANNELS_PER_CONTROLLER;

    port_uint8_out (dma_mask[controller], 0x04 | controller_channel);

    return STORM_RETURN_SUCCESS;
}


/* Perform a DMA transfer on the given DMA channel. */

return_t dma_controller_transfer_start (
    unsigned int channel,
    address_t physical_buffer, 
    unsigned int length,
    unsigned int mode)
{
    /* Controller channel number. */

    unsigned int controller_channel;

    /* Controller number. */

    unsigned int controller;

    /* Attention: DMA controller can transfer only 1 - 65526 bytes to/from lower
       memory (below 1 MB). */
    
    DEBUG_ASSERT ((channel < NUMBER_OF_DMA_CHANNELS), 
        "Invalid channel number.");
        
    DEBUG_ASSERT ((channel != DMA_CHANNEL_CASCADE), 
        "Try to use cascade channel.");
    
    DEBUG_ASSERT ((physical_buffer != 0UL), 
        "Physical buffer is NULL pointer.");
    DEBUG_ASSERT ((physical_buffer < 1 * MIB), "");
    DEBUG_ASSERT ((length <= 64 * KIB), "");
    DEBUG_ASSERT ((physical_buffer + length <= 1 * MIB), "");
    
    /* Calculate controller channel. */

    controller_channel = channel % NUMBER_OF_DMA_CHANNELS_PER_CONTROLLER;
    controller = channel / NUMBER_OF_DMA_CHANNELS_PER_CONTROLLER;

    mode |= controller_channel;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "Begining dma transfer on %u with mode=%X\n", 
        channel, mode);

    /* Mask channel. */

    port_uint8_out (dma_mask[controller], 0x04 | controller_channel);

    /* Reset flip-flop. */

    port_uint8_out (dma_flip_flop[controller], 0);

    port_uint8_out (dma_mode[controller], mode);

    /* First and second controllers differs in digits. */
    if (controller == 0)
    {
        /* First controller is 8 digit. */
    
        /* Low, high and page buffer address. */

        port_uint8_out (dma_address[channel], 
            BITS_GET ((uint32_t) physical_buffer,  7, 0));
        port_uint8_out (dma_address[channel], 
            BITS_GET ((uint32_t) physical_buffer, 15, 8));
        port_uint8_out (dma_page[channel], 
            BITS_GET ((uint32_t) physical_buffer, 23, 16));

        /* Low, high count. */

        port_uint8_out (dma_count[channel], LOW_8 (length - 1));
        port_uint8_out (dma_count[channel], HIGH_8 (length - 1));
    }
    else
    {
        /* Second controller is 16 digit. */
	
        if ((BIT_GET ((uint32_t) physical_buffer, 0) != 0) || 
            (BIT_GET (length, 0) != 0))
        {
            return STORM_RETURN_INVALID_ARGUMENT;
        }
	
        /* Low, high and page buffer address. */

        port_uint8_out (dma_address[channel], 
            BITS_GET ((uint32_t) physical_buffer,  8, 1));
        port_uint8_out (dma_address[channel], 
            BITS_GET ((uint32_t) physical_buffer, 16, 9));
        port_uint8_out (dma_page[channel], 
            BITS_GET ((uint32_t) physical_buffer, 23, 17));

        /* Low, high count. */

        port_uint8_out (dma_count[channel], LOW_8 (length / 2 - 1));
        port_uint8_out (dma_count[channel], HIGH_8 (length / 2 - 1));
    }

    /* Release_channel. */
  
    port_uint8_out (dma_mask[controller], controller_channel);


    return STORM_RETURN_SUCCESS;
}

/* Cancel a DMA transfer. */

return_t dma_controller_transfer_cancel (unsigned int channel)
{
    unsigned char controller, controller_channel;

    DEBUG_ASSERT ((channel < NUMBER_OF_DMA_CHANNELS), "");
    DEBUG_ASSERT ((channel != DMA_CHANNEL_CASCADE), "");

    /* Calculate controller channel. */

    controller_channel = channel % NUMBER_OF_DMA_CHANNELS_PER_CONTROLLER;
    controller = channel / NUMBER_OF_DMA_CHANNELS_PER_CONTROLLER;
    
    /* Mask that channel. */

    port_uint8_out (dma_mask[controller], CANCEL_DMA_TRANSFER | 
	controller_channel);

    return STORM_RETURN_SUCCESS;
}
