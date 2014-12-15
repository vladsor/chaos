/* Copyright 2004 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file                irq.h
 * @brief               IRQ handling.
 */

#ifndef __STORM_IRQ_H__
#define __STORM_IRQ_H__

#include <Common/irq.h>

/**
 * @brief               Initialize interrupt handling, and enable
 *                      interrupts. 
 */
extern return_t irq_init (int argc, char *argv[], char **envp);

/**
 * @brief               Register an IRQ handler. 
 * @param irq_number
 * @param function
 * @return
 */
extern return_t irq_register (unsigned int irq_number, 
    p_irq_handler_t function, p_void_t parameter);

/**
 * @brief               Unregister an IRQ handler. 
 * @param irq_number
 * @return
 */
extern return_t irq_unregister (unsigned int irq_number);

extern uint8_t *current_stack_pointer;

#endif /* !__STORM_IRQ_H__ */
