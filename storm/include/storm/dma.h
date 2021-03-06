/* $Id: dma.h,v 1.2 2000/10/10 20:04:13 plundis Exp $ */
/* Abstract: Global DMA defines. */
/* Authors: Henrik Hallin <hal@chaosdev.org> 
            Erik Moren <nemo@chaosdev.org> */

/* Copyright 2000 chaos development. */

/* This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
   USA. */

#ifndef __STORM_DMA_H__
#define __STORM_DMA_H__

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

#endif /* !__STORM_DMA_H__ */
