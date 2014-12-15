/* $Id: ipc.c,v 1.4 2000/10/09 21:06:42 plundis Exp $ */
/* Abstract: IPC library. */
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

#include <console/console.h>
#include <ipc/ipc.h>
#include <memory/memory.h>
#include <string/string.h>
#include <system/system.h>

#include "config.h"

/* FIXME: Use more defines. */

/* Create a service. */

return_type ipc_service_create
  (const char *service_name, ipc_structure_type *ipc_structure,
   tag_type *tag)
{
  switch (system_call_service_create
          (service_name, &ipc_structure->input_mailbox_id, tag))
  {
    case STORM_RETURN_OUT_OF_MEMORY:
    {
      return IPC_RETURN_OUT_OF_MEMORY;
    }

    case STORM_RETURN_SUCCESS:
    {
      return IPC_RETURN_SUCCESS;
    }
  }

  /* We should never get here, really... */

  system_call_debug_print_simple (__FUNCTION__ " failed.");
  while (TRUE);
}

/* Resolve the given service and put a maximum of
   'number_of_mailbox_ids' mailbox ID:s into mailbox_id. */
/* FIXME: number_of_mailbox_ids should be a pointer to an int, where
   we store the number of available service handlers. */

return_type ipc_service_resolve 
  (const char *service_name, mailbox_id_type *mailbox_id,
   unsigned int *number_of_mailbox_ids, time_type timeout,
   tag_type *tag)
{
  service_parameter_type service_parameter;
  unsigned int time = 0;

  service_parameter.max_services = *number_of_mailbox_ids;
  service_parameter.mailbox_id = mailbox_id;

  do
  {
    switch (system_call_service_get (service_name, &service_parameter, tag))
    {
      case STORM_RETURN_TOO_MANY_SERVICES:
      {
        *number_of_mailbox_ids = service_parameter.max_services;
        return IPC_RETURN_TOO_MANY_SERVICES;
      }
      
      case STORM_RETURN_PROTOCOL_UNAVAILABLE:
      {
        break;
      }
      
      case STORM_RETURN_SUCCESS:
      {
        *number_of_mailbox_ids = service_parameter.max_services;
        return IPC_RETURN_SUCCESS;
      }
    }

    /* If timeout is 0 we never block. If it is MAX_TIME, we block as
       long as we like. */

    if (timeout != 0)
    {
      system_sleep (1000);
    }
    time++;
  } while (time <= timeout || timeout == MAX_TIME);


 return IPC_RETURN_SERVICE_UNAVAILABLE;
}

/* Wait for a connection request. */

return_type ipc_service_connection_wait (ipc_structure_type *ipc_structure)
{
  message_parameter_type message_parameter;
  bool done = FALSE;
  u8 *buffer;
  unsigned int buffer_size = 1024;

  memory_allocate ((void **) &buffer, buffer_size);

  /* Check the input parameter. */

  if (ipc_structure == NULL)
  {
    return IPC_RETURN_INVALID_ARGUMENT;
  }

  message_parameter.data = buffer;
  message_parameter.protocol = IPC_PROTOCOL_GENERAL;
  
  while (!done)
  {
    message_parameter.message_class = IPC_CLASS_NONE;
    message_parameter.length = buffer_size;
    message_parameter.block = TRUE;

    switch (system_call_mailbox_receive (ipc_structure->input_mailbox_id,
                                         &message_parameter))
    {
      case STORM_RETURN_MAILBOX_UNAVAILABLE:
      case STORM_RETURN_ACCESS_DENIED:
      {
        memory_deallocate ((void **) &buffer);
        return IPC_RETURN_INVALID_ARGUMENT;
      }
      
      /* The message didn't fit into this mailbox. General IPC
         messages must fit into 1024 bytes, so it was probably some
         bogus message. We ignore it. */
      
      case STORM_RETURN_MAILBOX_MESSAGE_TOO_LARGE:
      {
        continue;
      }
      
      case STORM_RETURN_SUCCESS:
      {
        mailbox_id_type reply_mailbox_id =
          *(mailbox_id_type *) message_parameter.data;
        
        switch (message_parameter.message_class)
        {
          case IPC_GENERAL_ECHO_REQUEST:
          {
            message_parameter.message_class = IPC_GENERAL_ECHO_REPLY;
            message_parameter.length = 0;
            message_parameter.block = TRUE;

            system_call_mailbox_send (reply_mailbox_id, &message_parameter);
            break;
          }

          case IPC_GENERAL_IDENTIFY_REQUEST:
          {
            message_parameter.message_class = IPC_GENERAL_IDENTIFY_REPLY;

            /* FIXME: Fill in better stuff here! */

            string_copy ((char *) message_parameter.data,
                         PACKAGE_NAME " " PACKAGE_VERSION);

            message_parameter.length =
              string_length ((char *) message_parameter.data);
            
            system_call_mailbox_send (reply_mailbox_id, &message_parameter);
            break;
          }
          
          case IPC_GENERAL_CONNECTION_REQUEST:
          {
            ipc_structure->output_mailbox_id =
              *(mailbox_id_type *) message_parameter.data;
            {
              memory_deallocate ((void **) &buffer);
              return IPC_RETURN_CONNECTION_REQUESTED;
            }
 
            break;
          }
          
          /* Unknown command; for now make sure this is acknowledged. */
          
          default:
          {
            char string[100];
            
            string_print (string, "Bad packet received (class = %x).",
                          message_parameter.message_class);
            system_call_debug_print_simple (string);
            break;
          }
        }
      }
    }
  }
  
  /* We should never get here, really... */

  system_call_debug_print_simple (__FUNCTION__ " failed.");
  while (TRUE);
}

/* Request a connection to a service. */

return_type ipc_service_connection_request (ipc_structure_type *ipc_structure)
{
  message_parameter_type message_parameter;
  u8 data[100];

  /* FIXME: Make it possible to specify the size of the mailbox. For
     now, we just set it to one meg and hope it's enough. */

  if (system_call_mailbox_create 
      (&ipc_structure->input_mailbox_id, 1 * MB, PROCESS_ID_NONE,
       CLUSTER_ID_NONE, THREAD_ID_NONE) != STORM_RETURN_SUCCESS)
  {
    system_call_debug_print_simple ("Failed to create a mailbox.");
    while (TRUE);
  }

  message_parameter.length = sizeof (mailbox_id_type);
  message_parameter.protocol = IPC_PROTOCOL_GENERAL;
  message_parameter.message_class = IPC_GENERAL_CONNECTION_REQUEST;
  message_parameter.data = &data;
  message_parameter.block = TRUE;
  *(mailbox_id_type *) message_parameter.data =
    ipc_structure->input_mailbox_id;

  switch (system_call_mailbox_send (ipc_structure->output_mailbox_id,
                                    &message_parameter))
  {
    case STORM_RETURN_MAILBOX_UNAVAILABLE:
    case STORM_RETURN_ACCESS_DENIED:
    {
      return IPC_RETURN_INVALID_ARGUMENT;
    }

    case STORM_RETURN_SUCCESS:
    {
      break;
    }
  }

  message_parameter.protocol = IPC_PROTOCOL_GENERAL;
  message_parameter.message_class = IPC_CLASS_NONE;
  message_parameter.length = 50;
  message_parameter.block = TRUE;

  switch (system_call_mailbox_receive (ipc_structure->input_mailbox_id,
                                       &message_parameter))
  {
    case STORM_RETURN_MAILBOX_UNAVAILABLE:
    case STORM_RETURN_ACCESS_DENIED:
    {
      return IPC_RETURN_INVALID_ARGUMENT;
    }

    case STORM_RETURN_SUCCESS:
    {
      if (message_parameter.message_class == IPC_GENERAL_CONNECTION_REPLY)
      {
        ipc_structure->output_mailbox_id =
          *(mailbox_id_type *) message_parameter.data;
        return IPC_RETURN_SUCCESS;
      }
      else
      {
        return IPC_RETURN_FAILED_MAILBOX_RECEIVE;
      }
    }
  }

  /* We should never get here, really... */

  system_call_debug_print_simple (__FUNCTION__ " failed.");
  while (TRUE);
}

/* Establish the connection. */

return_type ipc_connection_establish (ipc_structure_type *ipc_structure)
{
  message_parameter_type message_parameter;

  /* Create an input mailbox which we will use to get data from this
     connection. */
  /* FIXME: Make the size dynamic. */

  if (system_call_mailbox_create
      (&ipc_structure->input_mailbox_id, 1 * MB,
       PROCESS_ID_NONE, CLUSTER_ID_NONE, THREAD_ID_NONE) !=
      STORM_RETURN_SUCCESS)
  {
    system_call_debug_print_simple ("Failed to create a mailbox.");

    message_parameter.message_class = IPC_GENERAL_CONNECTION_REFUSED;
    message_parameter.length = 0;
    system_call_mailbox_send (ipc_structure->output_mailbox_id,
                              &message_parameter);
    return IPC_RETURN_FAILED_MAILBOX_CREATE;
  }

  message_parameter.protocol = IPC_PROTOCOL_GENERAL;
  message_parameter.message_class = IPC_GENERAL_CONNECTION_REPLY;
  message_parameter.data = &ipc_structure->input_mailbox_id;
  message_parameter.length = sizeof (mailbox_id_type);
  message_parameter.block = TRUE;

  if (system_call_mailbox_send (ipc_structure->output_mailbox_id,
                                &message_parameter) != STORM_RETURN_SUCCESS)
  {
    system_call_debug_print_simple ("Failed to establish the connection.");
    return IPC_RETURN_FAILED_MAILBOX_SEND;
  }

  return IPC_RETURN_SUCCESS;
}

/* FIXME: Write an ipc_connection_deny which denies the connection. */

/* Send an IPC message. The reason for having this wrapper is to make
   the implementation of shared memory regions totally transparent to
   the programs. */

return_type ipc_send (mailbox_id_type mailbox_id,
                      message_parameter_type *message_parameter)
{
  return_type return_value = system_call_mailbox_send (mailbox_id,
                                                       message_parameter);
  switch (return_value)
  {
    case STORM_RETURN_SUCCESS:
    {
      return IPC_RETURN_SUCCESS;
    }

    case STORM_RETURN_INVALID_ARGUMENT:
    {
      return IPC_RETURN_INVALID_ARGUMENT;
    }

    case STORM_RETURN_MAILBOX_UNAVAILABLE:
    {
      return IPC_RETURN_MAILBOX_UNAVAILABLE;
    }
    
    case STORM_RETURN_MAILBOX_MESSAGE_TOO_LARGE:
    {
      return IPC_RETURN_MESSAGE_TOO_LARGE;
    }

    case STORM_RETURN_MAILBOX_FULL:
    {
      return IPC_RETURN_MAILBOX_FULL;
    }

    /* This should normally not happen. If it does, it means someone
       has added a return case in mailbox.c in the kernel, without
       adding it here. Thus, if you get this, please fix this library
       and send us a patch. */
    
    default:
    {
      return IPC_RETURN_FAILED_MAILBOX_SEND;
    }
  }
}

/* Receive an IPC message. The reason for having this is the same as
   for ipc_send. */

return_type ipc_receive
  (mailbox_id_type mailbox_id, message_parameter_type *message_parameter,
   unsigned int *buffer_size)
{
  return_type return_value = system_call_mailbox_receive (mailbox_id,
                                                          message_parameter);

  switch (return_value)
  {
    case STORM_RETURN_SUCCESS:
    {
      return IPC_RETURN_SUCCESS;
    }

    case STORM_RETURN_MAILBOX_UNAVAILABLE:
    {
      return IPC_RETURN_MAILBOX_UNAVAILABLE;
    }
    
    case STORM_RETURN_ACCESS_DENIED:
    {
      return IPC_RETURN_ACCESS_DENIED;
    }

    case STORM_RETURN_MAILBOX_EMPTY:
    {
      return IPC_RETURN_MAILBOX_EMPTY;
    }

    case STORM_RETURN_MAILBOX_MESSAGE_TOO_LARGE:
    {
      /* This interpretation of the 'block' flag might not be entirely
         orthodox, but I choose to it like this anyway... */

      if (!message_parameter->block || buffer_size == NULL)
      {
        return IPC_RETURN_MESSAGE_TOO_LARGE;
      }

      /* This might not be entirely beautiful, but I think it is a
         pretty elegant solution. */

      *buffer_size = message_parameter->length;
      //      memory_deallocate (&message_parameter->data);
      memory_allocate (&message_parameter->data, *buffer_size);
      system_call_mailbox_receive (mailbox_id, message_parameter);

      return IPC_RETURN_SUCCESS;
    }

    /* This should normally not happen. If it does, it means someone
       has added a return case in mailbox.c in the kernel, without
       adding it here. Thus, if you get this, please fix this library
       and send us a patch. */

    default:
    {
      return IPC_RETURN_FAILED_MAILBOX_RECEIVE;
    }
  }
}

/*
return_type ipc_generate_event(
  event_queue_id_type event_queue_id,
  event_parameter_type *event_parameter)
{
  return_type return_value = system_call_event_queue_send (event_queue_id,
                                                           event_parameter);
  if(return_value == STORM_RETURN_SUCCESS)
    return IPC_RETURN_SUCCESS;
  return IPC_RETURN_EVENT_BREAK;
}

return_type ipc_wait_event(
  event_queue_id_type event_queue_id,
  event_parameter_type *event_parameter,
  unsigned int *buffer_size)
{
  return_type return_value = system_call_event_queue_receive (event_queue_id,
                                                              event_parameter);
  *buffer_size = 0;
  if(return_value == STORM_RETURN_SUCCESS)
    return IPC_RETURN_SUCCESS;
  return IPC_RETURN_EVENT_BREAK;
}
*/
#if 0
ipc_protocol_get (ipc_structure_type *ipc_structure)
{
}

#endif

/* Close a connection. */

return_type ipc_connection_close (ipc_structure_type *ipc_structure,
                                  bool notify)
{
  message_parameter_type message_parameter;

  if (notify)
  {
    /* Tell the other side we are closing the connection. */
    
    message_parameter.protocol = IPC_PROTOCOL_GENERAL;
    message_parameter.message_class = IPC_GENERAL_CONNECTION_CLOSE;
    message_parameter.length = 0;
    message_parameter.data = NULL;
    
    system_call_mailbox_send (ipc_structure->output_mailbox_id,
                              &message_parameter);
  }

  system_call_mailbox_destroy (ipc_structure->input_mailbox_id);

  /* The other end must do this:

  system_call_mailbox_destroy (ipc_structure->input_mailbox_id);

  */

  return IPC_RETURN_SUCCESS;
}
