/* $Id: irq.h,v 1.2 2001/02/10 21:26:29 jojo Exp $ */
/* Abstract: Interrupt and IRQ related function prototypes and
   structure definitions. */
/* Authors: Per Lundberg <plundis@chaosdev.org>
            Henrik Hallin <hal@chaosdev.org> */

/**
 * @file
 * @brief
 * @author
 * @version
 * @date
 */

/* Copyright 1998-2000 chaos development. */

#ifndef __STORM_IA32_IRQ_HANDLERS_H__
#define __STORM_IA32_IRQ_HANDLERS_H__

/* Low level interrupt handlers. */

extern void irq0_handler (void);
extern void irq1_handler (void);
extern void irq3_handler (void);
extern void irq4_handler (void);
extern void irq5_handler (void);
extern void irq6_handler (void);
extern void irq7_handler (void);
extern void irq8_handler (void);
extern void irq9_handler (void);
extern void irq10_handler (void);
extern void irq11_handler (void);
extern void irq12_handler (void);
extern void irq13_handler (void);
extern void irq14_handler (void);
extern void irq15_handler (void);

#endif /* !__STORM_IA32_IRQ_HANDLERS_H__ */
