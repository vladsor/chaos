/* $Id: dma.h,v 1.2 2001/02/10 21:26:28 jojo Exp $ */
/* Copyright 1999-2000 chaos development. */

/**
 * @file                dma_controller.h
 * @brief		Function prototypes for lowlevel DMA support.
 * @author		Anders Ohrt <doa@chaosdev.org>
 *			Per Lundberg <plundis@chaosdev.org>
 *			Vladimir Sorokin
 * @version		1.4
 * @date		1999-2003
 */

#ifndef __STORM_IA32_DMA_CONTROLLER_H__
#define __STORM_IA32_DMA_CONTROLLER_H__

/**
 * @brief		Number of DMA controllers.
 */
#define NUMBER_OF_DMA_CONTROLLERS \
			(2)

/**
 * @brief		Number of DMA channels per controller.
 */
#define NUMBER_OF_DMA_CHANNELS_PER_CONTROLLER  \
			(4)

/**
 * @brief		Total number of DMA channels.
 */
#define NUMBER_OF_DMA_CHANNELS \
			(NUMBER_OF_DMA_CONTROLLERS * \
                        NUMBER_OF_DMA_CHANNELS_PER_CONTROLLER)

/* 
  Command Register specification:

   7 6 5 4 3 2 1 0
   | | | | | | | \---/ 0 - Memory-to-memory disable
   | | | | | | |     \ 1 - Memory-to-memory enable
   | | | | | | |
   | | | | | | |     / 0 - Channel 0 address hold disable
   | | | | | | \----|  1 - Channel 0 address hold enable
   | | | | | |       \ X - If bit 0 = 0
   | | | | | |
   | | | | | \-------/ 0 - Controller enable
   | | | | |         \ 1 - Controller disable
   | | | | |
   | | | | |         / 0 - Normal timing
   | | | | \--------|  1 - Compressed timing
   | | | |           \ X - If bit 0 = 1
   | | | |
   | | | \-----------/ 0 - Fixed priority
   | | |             \ 1 - Rotating priority
   | | |
   | | |             / 0 - Late write selection
   | | \------------|  1 - Extended write selection
   | |               \ X - If bit 3 = 1
   | |
   | \---------------/ 0 - DREQ sense active high
   |                 \ 0 - DREQ sense active low
   |
   \-----------------/ 0 - DACK sense active low
                     \ 1 - DACK sense active high
*/

#define DMA_COMMAND_MEMORY_TO_MEMORY_DISABLE (0)
#define DMA_COMMAND_MEMORY_TO_MEMORY_ENABLE (BIT_VALUE (0))

//#define DMA_COMMAND_CHANNEL_0_ADDRESS_HOLD_DISABLE (0)
#define DMA_COMMAND_CHANNEL_0_ADDRESS_HOLD_ENABLE (BIT_VALUE (1))

//#define DMA_COMMAND_CONTROLLER_ENABLE (0)
#define DMA_COMMAND_CONTROLLER_DISABLE (BIT_VALUE (2))

//#define DMA_COMMAND_NORMAL_TIMING (0)
#define DMA_COMMAND_COMPRESSED_TIMING (BIT_VALUE (3))

//#define DMA_COMMAND_FIXED_PRIORITY (0)
#define DMA_COMMAND_ROTATING_PRIORITY (BIT_VALUE (4))

//#define DMA_COMMAND_LATE_WRTE_SELECTION (0)
#define DMA_COMMAND_EXTENDED_WRITE_SELECTION (BIT_VALUE (5))

//#define DMA_COMMAND_DREQ_SENSE_ACTIVE_HIGH (0)
#define DMA_COMMAND_DREQ_SENSE_ACTIVE_LOW (BIT_VALUE (6))

//#define DMA_COMMAND_DACK_SENSE_ACTIVE_LOW (0)
#define DMA_COMMAND_DACK_SENSE_ACTIVE_HIGH (BIT_VALUE (7))

/*
  Mode Register specification:

   7 6 5 4 3 2 1 0
   | | | | | | \-\---/ 00 - Channel 0, 01 - Channel 1
   | | | | | |       \ 10 - Channel 2, 11 - Channel 3
   | | | | | |
   | | | | | |       / 00 - Verify transfer, 01 - Write transfer
   | | | | \-\------|  10 - Read transfer, 11 - Illegal
   | | | |           \ XX - If bits 6-7 = 11
   | | | |
   | | | \-----------/ 0 - Autoinitialization disabled
   | | |             \ 1 - Autoinitialization enabled
   | | |
   | | \-------------/ 0 - Address increment
   | |               \ 1 - Address decrement
   | |
   \-\---------------/ 00 - Demand, 01 - Single
                     \ 10 - Block, - 11 Cascade
*/

#define DMA_MODE_READ   (BIT_VALUE (3))
#define DMA_MODE_WRITE  (BIT_VALUE (2))
#define DMA_MODE_VERIFY (0)

#define DMA_MODE_AUTOINIT_ENABLE (BIT_VALUE (4))
#define DMA_MODE_AUTOINIT_DISABLE (0)

#define DMA_MODE_ADDRESS_INCREMENT (0)
#define DMA_MODE_ADDRESS_DECREMENT (BIT_VALUE (5))

#define DMA_MODE_DEMAND  (0)
#define DMA_MODE_SINGLE  (BIT_VALUE (6))
#define DMA_MODE_BLOCK   (BIT_VALUE (7))
#define DMA_MODE_CASCADE (BIT_VALUE (6) | BIT_VALUE (7))

/**
 * @brief		Init DMA controllers.
 * @return		Common result code.
 */
extern return_t dma_controller_init (void);

/**
 * @brief		Enable DMA channel.
 * @param channel	Index of DMA channel
 * @return		Common result code.
 */
extern return_t dma_contoller_enable_channel (unsigned int channel);

/**
 * @brief		Disable DMA channel.
 * @param channel	Index of DMA channel
 * @return	 	Common result code.
 */
extern return_t dma_contoller_disable_channel (unsigned int channel);

/**
 * @brief		Start DMA transfer.
 * @param channel	Index of DMA channel used for transfer
 * @param physical_buffer
 *			Physical address of accessed memory
 * @param length	Length of transfered data
 * @param mode		Transfer mode
 * @return		Result code of operation.
 */
extern return_t dma_controller_transfer_start (
    unsigned int channel, 
    address_t physical_buffer,     
    unsigned int length,
    unsigned int mode);

/**
 * @brief		Cancel DMA operation.
 * @param channel       DMA channel on which is performed transfer.
 * @return		Result code of operation.
 */
extern return_t dma_controller_transfer_cancel (
    unsigned int channel);

#endif	/* !__STORM_IA32_DMA_CONTROLLER_H__ */
