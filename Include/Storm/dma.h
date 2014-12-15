/* $Id: dma.h,v 1.2 2001/02/10 21:26:10 jojo Exp $ */
/* Abstract: Global DMA defines. */
/* Authors: Henrik Hallin <hal@chaosdev.org> 
            Erik Moren <nemo@chaosdev.org> */

/* Copyright 2000 chaos development. */


#ifndef __STORM_DMA_H__
#define __STORM_DMA_H__

#include <Common/dma.h>

extern return_t dma_init (int argc, char *argv[]);
extern return_t dma_register (int dma_channel, void **buffer);
extern return_t dma_unregister (int dma_channel);
extern return_t dma_transfer (unsigned int channel, unsigned int length, 
    unsigned int operation, unsigned int transfer_mode, bool autoinit);

#endif /* !__STORM_DMA_H__ */
