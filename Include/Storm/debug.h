/* $chaos: debug.h,v 1.16 2002/10/23 21:06:45 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> 
           Henrik Hallin <hal@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/** @file               debug.h
    @brief              Functions used for debugging. */

#ifndef __STORM_DEBUG_H__
#define __STORM_DEBUG_H__

#include <Common/debug.h>

extern return_t system_debug_print (uint8_t level, char *module_name, 
    char *function_name, uint32_t line, char *message);

/**
 * @brief               Initialize debugging code. 
 */
extern return_t system_debug_init (int argc, char *argv[]);


#endif /* !__STORM_DEBUG_H__ */