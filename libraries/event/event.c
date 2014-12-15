/* $Id: ipc.c,v 1.4 2000/10/09 21:06:42 plundis Exp $ */
/* Abstract: Event library. */
/* Author: Vladimir Sorokin */

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

#include <event/event.h>
#include <system/system.h>

#include "config.h"

return_type event_generate(
  event_queue_id_type event_queue_id,
  event_parameter_type *event_parameter)
{
  return_type return_value = system_call_event_queue_generate_event (
    event_queue_id, event_parameter, 0);
    
  if(return_value == STORM_RETURN_SUCCESS)
  {
    return EVENT_RETURN_SUCCESS;
  }
  return EVENT_RETURN_EVENT_BREAK;
}

return_type event_wait(
  event_queue_id_type event_queue_id,
  event_parameter_type *event_parameter)
{
  return_type return_value = system_call_event_queue_wait_event (
    event_queue_id, event_parameter, 0);
    
  if (return_value == STORM_RETURN_SUCCESS)
    return EVENT_RETURN_SUCCESS;
  return EVENT_RETURN_EVENT_BREAK;
}

return_type event_set_handler(event_queue_id_type event_queue_id,
  event_handler_type event_handler,
  event_parameter_type *event_parameter)
{

  if (system_thread_create () == SYSTEM_RETURN_THREAD_NEW)
  {
    return_type return_value;
    system_thread_name_set ("event handler");
    system_call_event_queue_register_listener (event_queue_id, 0);
    event_parameter->event_class = EVENT_CLASS_NONE;

    while(TRUE)
    {
      return_value = event_wait(event_queue_id, event_parameter);  

      event_handler (event_parameter);
    }
  }

  return EVENT_RETURN_SUCCESS;
}
