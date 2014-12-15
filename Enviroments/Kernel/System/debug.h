/* $chaos: debug.h,v 1.16 2002/10/23 21:06:45 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> 
           Henrik Hallin <hal@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/** @file               debug.h
    @brief              Functions used for debugging. */

#ifndef __STORM_DEBUG_H__
#define __STORM_DEBUG_H__

/**
 * @brief               Initialize debugging code. 
 */
extern return_t system_debug_init (int argc, char *argv[], char **envp);

extern return_t system_debug_print (uint8_t level, const char *module_name, 
    const char *function_name, uint32_t line, const char *message);

extern return_t system_debug_printw (uint8_t level, const wchar_t *module_name, 
    const char *function_name, uint32_t line, const wchar_t *message);

#endif /* !__STORM_DEBUG_H__ */
