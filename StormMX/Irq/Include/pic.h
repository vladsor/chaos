/**
 * @file		pic.h
 * @brief               Prommable Interrupt Controller management.
 * @author		Per Lundberg <plundis@chaosdev.org>
 *                      Henrik Hallin <hal@chaosdev.org> 
 *                      Vladimir Sorokin
 * @version             1.3
 * @date                1998-2003
 */

/* Copyright 1998-2002 chaos development. */

#ifndef __PIC_H__
#define __PIC_H__

/**
 * @brief               The base I/O address of 8259-1. 
 */
#define PIC_MASTER      0x20

/**
 * @brief               The base I/O address of 8259-2. 
 */
#define PIC_SLAVE       0xA0

/**
 * @brief		Number of IRQ controllers.
 */
#define NUMBER_OF_IRQ_CONTROLLERS \
			(2)

/**
 * @brief		Number of IRQ channels per controller.
 */
#define NUMBER_OF_IRQ_CHANNELS_PER_CONTROLLER \
			(8)

/**
 * @brief		Total number of IRQ channels.
 */
#define NUMBER_OF_IRQ_CHANNELS \
			(NUMBER_OF_IRQ_CONTROLLERS * \
			NUMBER_OF_IRQ_CHANNELS_PER_CONTROLLER)  

#define IRQ_CHANNEL_CASCADE (2)
/** 
 * @brief               Remap all IRQ channels to given interrupts. 
 * @param start
 */
void pic_remap_irq (unsigned int start);

/**
 * @brief               Enable the given IRQ channel. 
 * @param irq_channel   Index of IRQ channel
 */
extern void pic_enable_irq (unsigned int irq_channel);

/**
 * @brief               Disable the given IRQ channel. 
 * @param irq_channel   Index of IRQ channel
 */
extern void pic_disable_irq (unsigned int irq_channel);

/**
 * @brief               Enable all IRQ channels. 
 */
extern void pic_enable_all_irq (void);

/**
 * @brief               Disable all IRQ channels. 
 */
extern void pic_disable_all_irq (void);

/**
 * @brief               Initalize both pic controllers.
 */
extern void pic_init (void);

/**
 * @brief               Acknowledge the given IRQ channel. 
 * @param		Index of IRQ channel
 */
extern void pic_acknowledge (unsigned int irq_channel);

#endif /* __PIC_H__ */
