/* $Id: process.h,v 1.2 2001/02/10 21:26:12 jojo Exp $ */
/* Abstract: Process control. */
/* Author: Per Lundberg <plundis@chaosdev.org> */

/* Copyright 1999-2000 chaos development. */

#ifndef __COMMON_PROCESS_H__
#define __COMMON_PROCESS_H__

#include <rpool.h>

/* Structure used by process_create. */

typedef struct
{
    uint32_t first_instruction;

    uint8_t *code_section_address;
    uint32_t code_section_base;
    uint32_t code_section_size;

    uint8_t *data_section_address;
    uint32_t data_section_base;
    uint32_t data_section_size;

    uint32_t bss_section_base;
    uint32_t bss_section_size;
    
    char *parameter_string;
  
} process_info_t;

typedef struct
{
    LIST_NODE_PART;
    
    char name[STRING_MAX_LENGTH];

    uint32_t entry_point;

    page_directory_t *page_directory;
    tss_t *tss;
    
    pool_t memory_pool;
    
    list_t threads_list;
} process_t;

#endif /* __COMMON_PROCESS_H__ */

