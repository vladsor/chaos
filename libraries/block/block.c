/* $chaos: block.c,v 1.3 2002/08/09 05:59:38 per Exp $ */
/* Abstract: Block library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#include <block/block.h>

/* Lookup the first block service provider. FIXME: Should be able to
   return a list. */
return_t block_lookup (block_service_t *block)
{
    size_t services;
    service_t *service;

    /* Find the block service. */
    if (service_lookup ("block", NULL, NULL, NULL, 1, &services, &service) != STORM_RETURN_SUCCESS)
    {
        debug_print ("Failed to lookup block service provider.\n");
        return BLOCK_RETURN_SERVICE_UNAVAILABLE;
    }

    service[0].service_info (block);

    // FIXME: Free the memory allocated by service_resolve.

    return BLOCK_RETURN_SUCCESS;
}
