/* $chaos: system_call.h,v 1.8 2002/11/03 22:26:09 per Exp $ */
/* Abstract: System call prototypes etc. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file                system_call.h
 * @brief               System call implementation.
 */

#ifndef __STORM_IA32_SYSTEM_CALL_H__
#define __STORM_IA32_SYSTEM_CALL_H__

/**
 * @brief               The system call vector in the IDT. 
 */
#define SYSTEM_CALL_IDT_ENTRY \
                        (0x88)

/**
 * @brief               Set up the system call in the IDT.
 */
extern return_t system_call_init (int argc UNUSED, char *argv[] UNUSED, 
    char **envp UNUSED);


#endif /* !__STORM_IA32_SYSTEM_CALL_H__ */
