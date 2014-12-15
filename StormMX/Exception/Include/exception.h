/* $chaos: exception.h,v 1.7 2002/10/09 12:54:44 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/** 
 * @file exception.h
 * @brief Exception handling. 
 */

#ifndef __STORM_IA32_EXCEPTION_H__
#define __STORM_IA32_EXCEPTION_H__

enum
{
    EXCEPTION_CODE_NONE,
    EXCEPTION_CODE_SEGMENT,
    EXCEPTION_CODE_PAGE,
};

extern void exception_print_screen (uint32_t class_id, char *description, 
    char *reason, uint32_t error_code_type, 
    exception_hardware_info_t *exception_info, volatile thread_t *dump_thread);

extern return_t exception_hardware_init (int argc UNUSED, char *argv[] UNUSED);
extern return_t exception_software_init (int argc UNUSED, char *argv[] UNUSED);

typedef struct
{
    void *handler;
    unsigned int class_id;
    char *description;
    char *reason;
    uint32_t error_code_type;
} exception_hardware_description_t;

extern exception_hardware_description_t exception_hardware_descriptions[];

#endif /* !__STORM_IA32_EXCEPTION_H__ */

