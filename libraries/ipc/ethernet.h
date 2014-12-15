/* $Id: ethernet.h,v 1.2 2001/02/10 21:22:39 jojo Exp $ */
/* Abstract: Protocol used by Ethernet servers. */
/* Author: Per Lundberg <plundis@chaosdev.org> */

/* Copyright 1999-2000 chaos development. */

/* This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public License
   as published by the Free Software Foundation; either version 2 of
   the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
   USA. */

#ifndef __LIBRARY_IPC_ETHERNET_H__
#define __LIBRARY_IPC_ETHERNET_H__

#include <ipc/protocols.h>

enum
{
  IPC_ETHERNET_REGISTER_TARGET = (IPC_PROTOCOL_ETHERNET << 16),
  IPC_ETHERNET_PACKET_SEND,
  IPC_ETHERNET_PACKET_RECEIVED,
  IPC_ETHERNET_ADDRESS_GET,
};

#endif /* !__IPC_LIBRARY_ETHERNET_H__ */
