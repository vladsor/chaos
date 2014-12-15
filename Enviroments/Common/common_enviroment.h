/* $Id: types.h,v 1.2 2001/02/10 21:26:13 jojo Exp $ */
/* Abstract: Basic enviroment of the chaos operating system. */

/* Copyright 1998-2002 chaos development. */

#ifndef __ENVIROMENT_ENVIROMENT_H__
#define __ENVIROMENT_ENVIROMENT_H__

#include "stdint.h"
#include "stdint_ext.h"
/*
#include "iso646.h"
*/
#ifndef __cplusplus
/**
 * @brief              Boolean type with only two values: TRUE and FALSE
 */
typedef int            bool;
#endif

#ifndef _SIZE_T_
#define _SIZE_T_
/**
 * @brief               A size. 
 */
typedef unsigned int    size_t;
#endif

/**
 * @brief               A return value (STORM_RETURN_*) 
 */
typedef int             return_t;

/**
 * @brief               A function pointer. 
 */
typedef return_t        (*function_t)(void);   /* Can be used even if
                                                  the function uses
                                                  arguments. */
/**
 * @brief               A linear/physical address. 
 */
typedef                 uint32_t address_t;

/**
 * @brief               A unique process ID.
 */
typedef unsigned int    process_id_t;

/**
 * @brief               A unique thread ID.
 */
typedef unsigned int    thread_id_t;

/**
 * @brief               A unique service provider ID.
 */
typedef uint64_t        service_id_t;

/**
 * @brief               The process ID of the kernel process (idle thread).
 */
#define PROCESS_ID_KERNEL \
                        0

/**
 * @brief               A process ID indicating 'no process'.
 *
 * Used in memory_allocate() in the beginning when we allocate memory
 * that's not registered in the process-page list.
 */
#define PROCESS_ID_NONE \
                        ((process_id_t) -1)

/**
 * @brief               type of function for compare two keys of AVL-nodes. 
 * @param key1
 * @param key2
 * @return
 */
typedef int (*compare_function_t) (void *key1, void *key2);

/**
 *  @brief              Condition values.
 */
enum condition_t
{
    /**
     * @brief           Keys equals.
     */
    CONDITION_EQUAL,

    /**
     * @brief           Key1 more then key2.
     */
    CONDITION_MORE,

    /**
     * @brief           Key1 less then key2.
     */
    CONDITION_LESS,

    /**
     * @brief           Key1 not equals key2.
     */
    CONDITION_NOT_EQUAL,

    /**
     * @brief           Key1 more then key2 or keys equals.
     */
    CONDITION_EQUAL_OR_MORE,

    /**
     * @brief           Key1 less then key2 or keys equals.
     */
    CONDITION_EQUAL_OR_LESS,

};

//typedef uint16_t wchar_t;

#include "standart_arguments.h"
#include "defines.h"
#include "bit.h"
#include "limits.h"
#include "return_value.h"

#include "iterator.h"

#include "byte_order.h"
#include "endian.h"

#include "ia32/cpu_common.h"
#include "ia32/flags.h"
#include "ia32/port.h"
#include "ia32/page.h"
#include "ia32/cpu_features.h"
#include "ia32/locks.h"

#endif /* __ENVIROMENT_ENVIROMENT_H__ */

