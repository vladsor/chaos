/* Copyright 2004 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/** 
 * @file exception.h
 * @brief Exception handling. 
 */

#ifndef __STORM_EXCEPTION_H__
#define __STORM_EXCEPTION_H__

/**
 * @brief Initialize exception handling. 
 */
extern return_t exception_init (int argc, char *argv[], char **envp);

/**
 * @brief               Register an Exception handler. 
 * @param exception_number
 * @param function
 * @param parameter
 * @return
 */
extern return_t exception_register (unsigned int exception_number, 
    p_exception_handler_t function, p_void_t parameter);

/**
 * @brief               Unregister an Exception handler. 
 * @param exception_number
 * @return
 */
extern return_t exception_unregister (unsigned int exception_number);

extern void exception_print_screen (uint32_t class_id, const char *description, 
    const char *reason, uint32_t error_code_type, 
    exception_hardware_info_t *exception_info);

#define NUMBER_OF_EXCEPTIONS (20)

enum
{
    EXCEPTION_CODE_NONE,
    EXCEPTION_CODE_SEGMENT,
    EXCEPTION_CODE_PAGE,
};

typedef struct
{
    void *handler;
    unsigned int class_id;
    const char *description;
    const char *reason;
    uint32_t error_code_type;
} exception_hardware_description_t;

extern exception_hardware_description_t exception_hardware_descriptions[];

#endif /* !__STORM_EXCEPTION_H__ */
