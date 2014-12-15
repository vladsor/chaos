/* $chaos: vfs.c,v 1.4 2002/08/09 05:59:42 per Exp $ */
/* Abstract: Virtual filesystem library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#include <vfs/vfs.h>

/* Lookup the first virtual filesystem service provider. FIXME:
   Should be able to return a list. */
return_t vfs_lookup (vfs_service_t *vfs)
{
    size_t services;
    service_t *service;

    /* Find the virtual filesystem service. */
    if (service_lookup ("vfs", NULL, NULL, NULL, 1, &services, &service) != STORM_RETURN_SUCCESS)
    {
        debug_print ("Failed to lookup virtual filesystem service provider.\n");
        return VFS_RETURN_SERVICE_UNAVAILABLE;
    }

    service[0].service_info (vfs);

    // FIXME: Free the memory allocated by service_lookup.
    return VFS_RETURN_SUCCESS;
}

// TODO: Add a vfs_register function for registering a vfs service
// provider.
