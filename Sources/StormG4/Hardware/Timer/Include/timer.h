/* $chaos: timer.h,v 1.3 2002/10/08 20:16:14 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file timer.h
 * @brief Timer support.
 */

#ifndef __STORM_IA32_TIMER_H__
#define __STORM_IA32_TIMER_H__

#define NUMBER_OF_TIMERS (1)
#define TIMER_IRQ (0)

enum timer_state_t
{
    TIMER_STATE_COUNTED,
    TIMER_STATE_STOPED,
};    

#endif /* !__STORM_IA32_TIMER_H__ */
