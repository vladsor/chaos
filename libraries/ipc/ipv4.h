/* $Id: ipv4.h,v 1.2 2000/09/29 21:08:47 hal Exp $ */
/* Abstract: IPv4 protocol */
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

#ifndef __LIBRARY_IPC_IPV4_H__
#define __LIBRARY_IPC_IPV4_H__

/* This file is a little ugly; we have to include network/network.h in
   the middle, because it needs some of us and we need some of
   it... FIXME: This should be resolved. */

typedef unsigned int ipv4_socket_id_type;

typedef struct
{
  ipv4_socket_id_type socket_id;
  unsigned int length;
  u8 data[0];
} ipv4_send_type;

typedef struct
{
  u32 address;
  u16 port;
  unsigned int protocol;
} ipv4_connect_type;

typedef struct
{
  /* FIXME: We can't use the define yet... but we should, in some
     way. */

  u8 ethernet_address[6];
  u32 ip_address;
} ipv4_arp_entry_type;

#include <network/network.h>

enum
{
  IPC_IPV4_INTERFACE_CONFIGURE = (IPC_PROTOCOL_IPV4 << 16),
  IPC_IPV4_INTERFACE_QUERY,

  /* FIXME: Think about how this should really work. */
  
  IPC_IPV4_CONNECT,
  IPC_IPV4_LISTEN,
  IPC_IPV4_SEND,
  IPC_IPV4_RECEIVE,
  IPC_IPV4_SET_HOST_NAME,
  IPC_IPV4_GET_HOST_NAME,
  IPC_IPV4_INTERFACE_GET_AMOUNT,
  IPC_IPV4_INTERFACE_GET_NUMBER,
  IPC_IPV4_SET_FLAGS,
  IPC_IPV4_GET_FLAGS,
  IPC_IPV4_ARP_GET_AMOUNT,
  IPC_IPV4_ARP_GET_NUMBER,
};

enum
{
  IPC_IPV4_PROTOCOL_UDP,
  IPC_IPV4_PROTOCOL_TCP
};

/* Flags. */

enum
{
  IPC_IPV4_FLAG_FORWARD = (1 << 0),
};

/* FIXME: Use a tag item for this one. */

#define IPV4_HOST_NAME_LENGTH 32

#define IPV4_INTERFACE_IDENTIFICATION_LENGTH 32

/* IP configuration. */

typedef struct
{
  char identification[IPV4_INTERFACE_IDENTIFICATION_LENGTH];

  /* Is the specified interface up? */

  bool up;

  /* Is the specified interface using DHCP? */

  bool dhcp;
  u32 ip_address;
  u32 netmask;
  u32 gateway;
  u8 hardware_address[NETWORK_ETHERNET_ADDRESS_LENGTH];
} ipv4_interface_type;

#endif /* !__LIBRARY_IPC_IPV4_H__ */
