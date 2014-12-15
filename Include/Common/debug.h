/* $chaos: debug.h,v 1.16 2002/10/23 21:06:45 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> 
           Henrik Hallin <hal@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/** @file               debug.h
    @brief              Functions used for debugging. */

#ifndef __COMMON_DEBUG_H__
#define __COMMON_DEBUG_H__

enum
{
    DEBUG_LEVEL_PANIC = -2,
    DEBUG_LEVEL_ERROR,
    DEBUG_LEVEL_NONE,
    DEBUG_LEVEL_WARNING,
    DEBUG_LEVEL_INFORMATIVE,
    DEBUG_LEVEL_INFORMATIVE1,
    DEBUG_LEVEL_INFORMATIVE2,
    DEBUG_LEVEL_INFORMATIVE3,
};

#endif /* !__COMMON_DEBUG_H__ */
