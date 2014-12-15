/* $chaos: info.c,v 1.2 2002/10/04 19:01:05 per Exp $ */
/* Abstract: vfs_info () implementation. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include "vfs.h"

/* Get information about a file. */
return_t vfs_info (char *filename, vfs_file_info_t *info)
{
    /* Find out which filesystem this file is located on. */
    assign_t *assign = find_filesystem (filename);
    if (assign == NULL || assign->mount == NULL)
    {
        debug_print ("Not found");
        return STORM_RETURN_NOT_FOUND;
    }

    /* Strip the volume path from our filename. */
    filename = normalize (assign, filename);

    /* This does the real opening (checking of permissions etc). */
    return assign->mount->filesystem.info (filename, info); 
}

