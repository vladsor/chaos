/* $chaos: system_call.h,v 1.8 2002/11/03 22:26:09 per Exp $ */
/* Abstract: System call prototypes etc. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file                system_call.h
 * @brief               System call implementation.
 */

#ifndef __STORM_HARDWARE_SYSTEM_CALL_H__
#define __STORM_HARDWARE_SYSTEM_CALL_H__

/**
 * @brief               The low-level system call handler.
 */
extern void system_call_lowlevel (void);

/**
 * @brief               The high-level system call handler.
 * @param stack         The callers stack (with the parameters to the
 *                      system call).
 * @return              The return value of the system call.
 */
extern return_t system_call (uint32_t ss, uint32_t *stack);

/* Easy access to the caller's stack. */
#define SYSTEM_CALL_NUMBER \
                        stack[0]

#define SYSTEM_CALL_ARGUMENTS \
                        stack[1]

/* The first argument, etc */
#define SYSTEM_CALL_ARGUMENT_0 \
                        stack[2]

#define SYSTEM_CALL_ARGUMENT_1 \
                        stack[3]

#define SYSTEM_CALL_ARGUMENT_2 \
                        stack[4]

#define SYSTEM_CALL_ARGUMENT_3 \
                        stack[5]

#define SYSTEM_CALL_ARGUMENT_4 \
                        stack[5]

#endif /* !__STORM_HARDWARE_SYSTEM_CALL_H__ */

