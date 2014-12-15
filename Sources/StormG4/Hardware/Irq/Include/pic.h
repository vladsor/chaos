/**
 * @file                pic.h
 * @brief               Prommable Interrupt Controller management.
 * @author              Per Lundberg <plundis@chaosdev.org>
 *                      Henrik Hallin <hal@chaosdev.org> 
 *                      Vladimir Sorokin
 * @version             1.4
 * @date                1998-2004
 */

/* Copyright 1998-2004 chaos development. */

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
 * @param               Index of IRQ channel
 */
extern void pic_acknowledge (unsigned int irq_channel);

#endif /* __PIC_H__ */

