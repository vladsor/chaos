/* Copyright 2004 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/** 
 * @file exception.h
 * @brief Exception handling. 
 */

#ifndef __STORM_EXCEPTION_H__
#define __STORM_EXCEPTION_H__

#include <Common/exception.h>
#include "thread.h"

extern void exception_add_handler (thread_t *thread, 
    p_exception_context_t exception_context);
extern void exception_remove_handler (thread_t *thread);
extern void exception_invoke_handler (thread_t *thread,
    p_exception_info_t exception_info) NORETURN;

/**
 * @brief Initialize exception handling. 
 */
extern return_t exception_init (int argc, char *argv[]);

#endif /* !__STORM_EXCEPTION_H__ */
