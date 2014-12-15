/* $Id: dma.h,v 1.2 2001/02/10 21:26:10 jojo Exp $ */
/* Abstract: Global DMA defines. */
/* Authors: Henrik Hallin <hal@chaosdev.org> 
            Erik Moren <nemo@chaosdev.org> */

/* Copyright 2000 chaos development. */


#ifndef __COMMON_DMA_H__
#define __COMMON_DMA_H__

enum
{
    STORM_DMA_OPERATION_WRITE,
    STORM_DMA_OPERATION_READ,
    STORM_DMA_OPERATION_VERIFY
};

enum
{
    STORM_DMA_TRANSFER_MODE_DEMAND,
    STORM_DMA_TRANSFER_MODE_SINGLE,
    STORM_DMA_TRANSFER_MODE_BLOCK,
    STORM_DMA_TRANSFER_MODE_CASCADE
};

enum
{
    STORM_DMA_AUTOINIT_ENABLE,
    STORM_DMA_AUTOINIT_DISABLE
};

#endif /* !__COMMON_DMA_H__ */
