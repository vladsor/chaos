/* Copyright 2004 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/** 
 * @file exception.h
 * @brief Exception handling. 
 */

#ifndef __COMMON_EXCEPTION_H__
#define __COMMON_EXCEPTION_H__

#ifndef _ASM

#include <list.h>

#endif

#define EXCEPTION_TYPE_HARDWARE (0)
#define EXCEPTION_TYPE_SYSTEM   (1)
#define EXCEPTION_TYPE_USER     (2)


#ifndef _ASM

typedef struct
{
    uint32_t            pc;
    uint32_t            type;
    uint32_t            id;
} exception_info_t;

typedef exception_info_t * p_exception_info_t;

typedef struct
{
    LIST_NODE_PART;
    
    volatile bool is_raised;
    p_void_t catch_point;
    p_uint8_t catch_stack_pointer;

    uint32_t eflags;
    uint32_t cs, ss, gs, fs, es, ds;
    uint32_t edi, esi, ebp;
    uint32_t ebx, edx, ecx, eax;
    
    uint32_t invoke_stack_pointer;

} exception_context_t;    

typedef exception_context_t * p_exception_context_t;

typedef struct
{
    exception_info_t    header;

    uint32_t            eflags;
    uint32_t            cs, ss, gs, fs, es, ds;
    uint32_t            edi, esi, ebp, esp;
    uint32_t            ebx, edx, ecx, eax;

} exception_hardware_info_t;

typedef exception_hardware_info_t * p_exception_hardware_info_t;

typedef struct
{
    exception_hardware_info_t    header;
    
    segment_error_t     segment_error;

} exception_hardware_segment_info_t;

typedef exception_hardware_segment_info_t * p_exception_hardware_segment_info_t;

typedef struct
{
    exception_hardware_info_t    header;
    
    page_error_t        page_error;
    address_t           address;

} exception_hardware_page_info_t;

typedef exception_hardware_page_info_t * p_exception_hardware_page_info_t;

typedef struct
{
    exception_hardware_info_t    header;
    
    uint32_t            error_code;
    
} exception_hardware_with_error_code_info_t;

typedef exception_hardware_with_error_code_info_t * 
    p_exception_hardware_with_error_code_info_t;

typedef void (exception_handler_t) (p_void_t data, 
    exception_hardware_info_t info);

typedef exception_handler_t * p_exception_handler_t;

#endif

#endif /* !__COMMON_EXCEPTION_H__ */
