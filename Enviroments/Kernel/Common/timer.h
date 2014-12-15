/* Copyright 2004 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file                timer.h
 * @brief               Timer handling.
 */

#ifndef __COMMON_TIMER_H__
#define __COMMON_TIMER_H__

#include "irq.h"

enum
{
    TIMER_NUMBER_SYSTEM = 0,
};    

/**
 * @brief               An Timer handler.
 */
typedef void (timer_handler_t) (unsigned int timer_number, p_void_t parameter, 
    p_irq_cpu_registers_t irq_cpu_registers);

typedef timer_handler_t * p_timer_handler_t;

#endif /* !__COMMON_TIMER_H__ */
