/* $chaos: close.c,v 1.2 2002/10/04 19:01:05 per Exp $ */
/* Abstract: vfs_close () implementation. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include "vfs.h"

/* Close a file. */
return_t vfs_close (vfs_file_handle_t handle)
{
    // FIXME: Remove this file handle from the data structures and so
    // on.
    handle = -1;
    return STORM_RETURN_SUCCESS;
}
