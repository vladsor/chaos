/* $Id: endian.h,v 1.1 2001/02/10 22:58:14 jojo Exp $ */
/* Abstract: Endian conversion. */
/* Author: Per Lundberg <plundis@chaosdev.org> */

/* Copyright 2000 chaos development. */

#ifndef __LIBRARY_SYSTEM_ENDIAN_H__
#define __LIBRARY_SYSTEM_ENDIAN_H__

#if defined __i386__

#  include "endian_little.h"

#elif defined __sparc__

#  include "endian_big.h"

#else

#  error "I don't know whether your system is little or big endian. Please \
          instruct me."

#endif

#endif /* !__LIBRARY_SYSTEM_ENDIAN_H__ */
