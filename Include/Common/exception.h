/* Copyright 2004 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/** 
 * @file exception.h
 * @brief Exception handling. 
 */

#ifndef __COMMON_EXCEPTION_H__
#define __COMMON_EXCEPTION_H__

#include <list.h>
#include "thread.h"

enum 
{
    EXCEPTION_TYPE_HARDWARE,
    EXCEPTION_TYPE_SYSTEM,
    EXCEPTION_TYPE_USER,
};

enum
{
    EXCEPTION_INVALID_PARAMETERS,
    EXCEPTION_NOT_IMPLEMENTED,
    EXCEPTION_NOT_SUPPORTED,
    EXCEPTION_ACCESS_DENIED,
    EXCEPTION_IS_LOCKED,
    EXCEPTION_NOT_ENOUGH_RESOURCES,
    EXCEPTION_INTERNAL_FAULT,
};


typedef struct
{
    uint32_t            pc;
    uint32_t            type;
    uint32_t            id;
} exception_info_t;

typedef exception_info_t *p_exception_info_t;

typedef struct
{
    exception_info_t    header;

    uint32_t            cs, ss, gs, fs, es, ds;
    uint32_t            eflags;
    uint32_t            edi, esi, ebp, esp;
    uint32_t            ebx, edx, ecx, eax;

} exception_hardware_info_t;

typedef struct
{
    exception_hardware_info_t    header;
    
    segment_error_t     segment_error;

} exception_hardware_segment_info_t;

typedef struct
{
    exception_hardware_info_t    header;
    
    page_error_t        page_error;
    address_t           address;

} exception_hardware_page_info_t;

typedef struct
{
    exception_hardware_info_t    header;
    
    uint32_t            error_code;
    
} exception_hardware_with_error_code_info_t;

typedef struct
{
    LIST_NODE_PART;
    
    cpu_state_t state;
    p_exception_info_t info;
    bool raised;
   
} exception_context_t;

typedef exception_context_t *p_exception_context_t;

#endif /* !__COMMON_EXCEPTION_H__ */
