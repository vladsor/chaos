/* $chaos: irq.h,v 1.12 2002/10/24 20:57:55 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file                irq.h
 * @brief               IRQ handling.
 *
 * The low-level IRQ handlers (written in assembly and defined in
 * irq_handlers.S) are the interrupt handlers defined in the IDT. They
 * pass on control to the highlevel handler irq_handler, which in turn
 * passes on to interrupt handlers registered by kernel modules.
 */

#ifndef __STORM_IA32_IRQ_H__
#define __STORM_IA32_IRQ_H__

/**
 * @brief               The IRQ:s are mapped to interrupt 0x20 and
 *                      upward.
 */
#define BASE_IRQ                        0x20

/**
 * @brief               The IDT entry for IRQ level a.
 */
#define IDT_ENTRY_FOR_IRQ(irq) \
                        (BASE_IRQ + (irq))

/**
 * @brief               High-level interrupt handler. 
 * @param irq_number    The number of the IRQ to handle.
 */
extern void irq_handler (unsigned int irq_number, 
    irq_cpu_registers_t registers);

extern irq_handler_t *irq_handlers[];

#endif /* !__STORM_IA32_IRQ_H__ */
