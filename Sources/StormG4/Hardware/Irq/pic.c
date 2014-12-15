/* $Id: irq.c,v 1.2 2001/02/10 21:25:58 jojo Exp $ */

/* Copyright 1998-2002 chaos development. */
/**
 * @file                 pic.c
 * @brief                Programmable Interrupt Controller management.
 * @author               Per Lundberg <plundis@chaosdev.org> 
 *                       Henrik Hallin <hal@chaosdev.org> 
 *                       Vladimir Sorokin 
 * @version		 1.3
 * @date		 1998-2003
 */

#include <enviroment.h>

#include "Include/pic.h"

//#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

/* Remap all IRQ:s to <start>-<start + 0x10>. */

void pic_remap_irq (unsigned int start)
{
    DEBUG_ASSERT (start <= (INT16_MAX - NUMBER_OF_IRQ_CHANNELS), 
        "Invalid irqs.");
    
    /* Send initialisation sequence to 8259A-1 and 8259A-2. */

    port_uint8_out_pause (PIC_MASTER, 0x11);
    port_uint8_out_pause (PIC_SLAVE, 0x11);

    /* Start of hardware int's (0x20). */

    port_uint8_out_pause (PIC_MASTER + 1, start);

    /* Start of hardware int's 2 (0x28). */

    port_uint8_out_pause (PIC_SLAVE + 1, start + 
	NUMBER_OF_IRQ_CHANNELS_PER_CONTROLLER);

    /* 8259-1 is master. */

    port_uint8_out_pause (PIC_MASTER + 1, 0x04);

    /* 8259-2 is slave. */

    port_uint8_out_pause (PIC_SLAVE + 1, 0x02);

    /* 8086 mode for both. */

    port_uint8_out_pause (PIC_MASTER + 1, 0x01);
    port_uint8_out_pause (PIC_SLAVE + 1, 0x01);
}

/* Enable the given interrupt. */

void pic_enable_irq (unsigned int irq_number)
{
    uint8_t mask;

    DEBUG_ASSERT (irq_number < NUMBER_OF_IRQ_CHANNELS, "Invalid IRQ channel.");

    /* Check which interrupt controller to use. */

    if (irq_number < NUMBER_OF_IRQ_CHANNELS_PER_CONTROLLER)
    {
        mask = port_uint8_in (PIC_MASTER + 1) & ~BIT_VALUE (irq_number);
        port_uint8_out (PIC_MASTER + 1, mask);
    }
    else
    {
        mask = port_uint8_in (PIC_SLAVE + 1) & ~BIT_VALUE (irq_number - 8);
        port_uint8_out (PIC_SLAVE + 1, mask);
    }
}

/* Disable the given interrupt. */

void pic_disable_irq (unsigned int irq_number)
{
    uint8_t mask;
    
    DEBUG_ASSERT (irq_number < NUMBER_OF_IRQ_CHANNELS, "Invalid IRQ channel.");

    /* Check which interrupt controller to use. */
  
    if (irq_number < NUMBER_OF_IRQ_CHANNELS_PER_CONTROLLER)
    {
        mask = port_uint8_in (PIC_MASTER + 1) | BIT_VALUE (irq_number);
        port_uint8_out (PIC_MASTER + 1, mask);
    }
    else
    {
        mask = port_uint8_in (PIC_SLAVE + 1) | BIT_VALUE (irq_number - 
            NUMBER_OF_IRQ_CHANNELS_PER_CONTROLLER);
        port_uint8_out (PIC_SLAVE + 1, mask);
    }
}

void pic_enable_all_irq (void)
{
    port_uint8_out (PIC_MASTER + 1, 0x00);
    port_uint8_out (PIC_SLAVE + 1, 0x00);
}

void pic_disable_all_irq (void)
{
    port_uint8_out (PIC_MASTER + 1, 0xFF);
    port_uint8_out (PIC_SLAVE + 1, 0xFF);
}

void pic_init (void)
{
}

/* Acknowledge the given IRQ level. */

void pic_acknowledge (unsigned int irq_number)
{
    DEBUG_ASSERT (irq_number < NUMBER_OF_IRQ_CHANNELS, "Invalid IRQ channel.");

    if (irq_number > NUMBER_OF_IRQ_CHANNELS_PER_CONTROLLER)
    {
        port_uint8_out (PIC_SLAVE, 0x20);
    }

    port_uint8_out (PIC_MASTER, 0x20);
}
