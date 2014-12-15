/**
 * @file                irq.h
 * @brief               IRQ handling.
 * @author              Per Lundberg <per@chaosdev.org>
 * @author              Vladimir Sorokin
 * @version             1.4
 * @date                1998-2004
 *
 * The low-level IRQ handlers (written in assembly and defined in
 * irq_handlers.S) are the interrupt handlers defined in the IDT. They
 * pass on control to the highlevel handler irq_handler, which in turn
 * passes on to interrupt handlers registered by kernel modules.
 */

/* Copyright 1998-2004 chaos development. */

#ifndef __STORM_IA32_IRQ_H__
#define __STORM_IA32_IRQ_H__

/**
 * @brief               High-level interrupt handler. 
 * @param irq_number    The number of the IRQ to handle.
 */
extern void irq_handler (unsigned int irq_number, 
    irq_cpu_registers_t registers);

extern irq_handler_t *irq_handlers[];

#endif /* !__STORM_IA32_IRQ_H__ */

