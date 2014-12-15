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
#include "ia32/cpu_bugs.h"
#include "ia32/locks.h"
#include "ia32/memory.h"

#endif /* __ENVIROMENT_ENVIROMENT_H__ */

