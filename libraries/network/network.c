/* $Id: network.c,v 1.3 2000/10/17 19:18:57 plundis Exp $ */
/* Abstract: Network library. */
/* Author: Per Lundberg <plundis@chaosdev.org> */

/* Copyright 2000 chaos development. */

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

#include <ipc/ipc.h>
#include <network/network.h>
#include <string/string.h>

/* Initialise the network support (by contacting the IPv4 server). */
/* FIXME: How do we implement support for different protocols in a
   clean way? */

return_type network_init (ipc_structure_type *network_structure, tag_type *tag)
{
  mailbox_id_type mailbox_id[10];
  unsigned int services = 10;

  /* Try to resolve the IPv4 service. */

  if (ipc_service_resolve ("ipv4", mailbox_id, &services, 0, tag) != 
      IPC_RETURN_SUCCESS)
  {
    return NETWORK_RETURN_SERVICE_UNAVAILABLE;
  }

  network_structure->output_mailbox_id = mailbox_id[0];

  /* Connect to this service. */

  if (ipc_service_connection_request (network_structure) != IPC_RETURN_SUCCESS)
  {
    return NETWORK_RETURN_SERVICE_UNAVAILABLE;
  }

  return NETWORK_RETURN_SUCCESS;
}

/* Get the host name of the system. */

return_type network_host_name_get
  (ipc_structure_type *network_structure, char *host_name)
{
  message_parameter_type message_parameter;

  message_parameter.protocol = IPC_PROTOCOL_IPV4;
  message_parameter.message_class = IPC_IPV4_GET_HOST_NAME;
  message_parameter.data = host_name;
  message_parameter.length = 0;
  ipc_send (network_structure->output_mailbox_id, &message_parameter);

  message_parameter.length = IPV4_HOST_NAME_LENGTH;
  ipc_receive (network_structure->input_mailbox_id, &message_parameter,
               NULL);
  
  return NETWORK_RETURN_SUCCESS;
}

/* Convert a string-based IP address to the binary notation. */

return_type network_string_to_binary_ip_address (u8 *string, u32 *ip_address)
{
  unsigned int characters;
  unsigned int a, b, c, d;
  unsigned int position = 0;
  unsigned int length = string_length (string);

  if (string_to_number (string + position, &a, &characters) != 
      STRING_RETURN_SUCCESS)
  {
    return NETWORK_RETURN_INVALID_ARGUMENT;
  }

  if (a > 255)
  {
    return NETWORK_RETURN_INVALID_ARGUMENT;
  }

  position += characters + 1;

  if (position > length)
  {
    return NETWORK_RETURN_INVALID_ARGUMENT;
  }

  if (string_to_number (string + position, &b, &characters) !=
      STRING_RETURN_SUCCESS)
  {
    return NETWORK_RETURN_INVALID_ARGUMENT;
  }

  if (b > 255)
  {
    return NETWORK_RETURN_INVALID_ARGUMENT;
  }

  position += characters + 1;

  if (position > length)
  {
    return NETWORK_RETURN_INVALID_ARGUMENT;
  }

  if (string_to_number (string + position, &c, &characters) !=
      STRING_RETURN_SUCCESS)
  {
    return NETWORK_RETURN_INVALID_ARGUMENT;
  }

  if (c > 255)
  {
    return NETWORK_RETURN_INVALID_ARGUMENT;
  }

  position += characters + 1;

  if (position > length)
  {
    return NETWORK_RETURN_INVALID_ARGUMENT;
  }

  if (string_to_number (string + position, &d, &characters) !=
      STRING_RETURN_SUCCESS)
  {
    return NETWORK_RETURN_INVALID_ARGUMENT;
  }

  if (d > 255)
  {
    return NETWORK_RETURN_INVALID_ARGUMENT;
  }

  *ip_address = a + (b << 8) + (c << 16) + (d << 24);
  return NETWORK_RETURN_SUCCESS;
}

/* Connect to a remote host (in the case of TCP), or just bind the
   port (in the case of UDP). */

return_type network_connect 
  (ipc_structure_type *network_structure, ipv4_connect_type *ipv4_connect,
   ipv4_socket_id_type *socket_id)
{
  message_parameter_type message_parameter;

  message_parameter.protocol = IPC_PROTOCOL_IPV4;
  message_parameter.message_class = IPC_IPV4_CONNECT;
  message_parameter.data = ipv4_connect;
  message_parameter.length = sizeof (ipv4_connect_type);
  message_parameter.block = TRUE;
  ipc_send (network_structure->output_mailbox_id, &message_parameter);

  message_parameter.data = socket_id;
  message_parameter.length = sizeof (ipv4_socket_id_type);
  message_parameter.block = TRUE;
  ipc_receive (network_structure->input_mailbox_id, &message_parameter, NULL);

  return NETWORK_RETURN_SUCCESS;
}

/* Send data on the given socket. */

return_type network_send 
  (ipc_structure_type *network_structure, ipv4_send_type *ipv4_send)
{
  message_parameter_type message_parameter;

  message_parameter.protocol = IPC_PROTOCOL_IPV4;
  message_parameter.message_class = IPC_IPV4_SEND;
  message_parameter.data = ipv4_send;
  message_parameter.length = sizeof (ipv4_send_type) + ipv4_send->length;
  message_parameter.block = TRUE;
  ipc_send (network_structure->output_mailbox_id, &message_parameter);

  return NETWORK_RETURN_SUCCESS;
}

/* Receive data on the given socket. */

return_type network_receive
  (ipc_structure_type *network_structure, ipv4_socket_id_type socket_id,
   void **data, unsigned int *length)
{
  message_parameter_type message_parameter;

  message_parameter.protocol = IPC_PROTOCOL_IPV4;
  message_parameter.message_class = IPC_IPV4_RECEIVE;
  message_parameter.data = &socket_id;
  message_parameter.length = sizeof (ipv4_socket_id_type);
  message_parameter.block = TRUE;
  ipc_send (network_structure->output_mailbox_id, &message_parameter);

  message_parameter.length = *length;
  message_parameter.data = *data;
  ipc_receive (network_structure->input_mailbox_id, &message_parameter,
               (unsigned int *) &length);
  *data = message_parameter.data;
  
  return NETWORK_RETURN_SUCCESS;
}

/* Set flags. */

return_type network_set_flags 
  (ipc_structure_type *network_structure, unsigned int flags)
{
  message_parameter_type message_parameter;

  message_parameter.protocol = IPC_PROTOCOL_IPV4;
  message_parameter.message_class = IPC_IPV4_SET_FLAGS;
  message_parameter.data = &flags;
  message_parameter.length = sizeof (unsigned int);
  message_parameter.block = TRUE;
  ipc_send (network_structure->output_mailbox_id, &message_parameter);

  return NETWORK_RETURN_SUCCESS;
}

/* Get flags. */

return_type network_get_flags 
  (ipc_structure_type *network_structure, unsigned int *flags)
{
  message_parameter_type message_parameter;

  message_parameter.protocol = IPC_PROTOCOL_IPV4;
  message_parameter.message_class = IPC_IPV4_GET_FLAGS;
  message_parameter.data = flags;
  message_parameter.length = 0;
  message_parameter.block = TRUE;
  ipc_send (network_structure->output_mailbox_id, &message_parameter);

  message_parameter.length = sizeof (unsigned int);
  ipc_receive (network_structure->input_mailbox_id, &message_parameter,
               NULL);

  return NETWORK_RETURN_SUCCESS;
}
