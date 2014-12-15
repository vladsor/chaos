/* $Id: ipc.h,v 1.2 2000/09/29 21:08:47 hal Exp $ */
/* Abstract: Event library interface. */
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

#ifndef __LIBRARY_EVENT_EVENT_H__
#define __LIBRARY_EVENT_EVENT_H__

#include <storm/storm.h>

static inline return_type system_call_event_queue_create 
  (event_queue_id_type *event_queue_id, unsigned int max_number_of_listeners, 
  unsigned int max_number_of_events)
{
  return_type return_value;

  asm volatile
  ("\
     pushl %2
     pushl %3
     pushl %4
     lcall %5, $0
   "
   : "=a" (return_value),
     "=g" (*event_queue_id)
   : "g" (max_number_of_listeners),
     "g" (max_number_of_events),
     "g" (event_queue_id),
     "n" (SYSTEM_CALL_EVENT_QUEUE_CREATE << 3));

  return return_value;
}

/* Destroy the given event's queue ID. */

static inline return_type system_call_event_queue_destroy
  (event_queue_id_type event_queue_id)
{
  return_type return_value;

  asm volatile
  ("\
    pushl %1
    lcall %2, $0
   "
   : "=a" (return_value)
   : "g" (event_queue_id),
     "n" (SYSTEM_CALL_EVENT_QUEUE_DESTROY << 3));

  return return_value;
}

static inline return_type system_call_event_queue_get_info
  (event_queue_id_type event_queue_id, event_queue_info_type *event_queue_info)
{
  return_type return_value;

  asm volatile
  ("\
    pushl %2
    pushl %3
    lcall %4, $0
   "
   : "=a" (return_value),
     "=g" (*event_queue_info)
   : "g" (event_queue_info),
     "g" (event_queue_id),
     "n" (SYSTEM_CALL_EVENT_QUEUE_GET_INFO << 3));

  return return_value;
}

static inline return_type system_call_event_queue_register_listener
  (event_queue_id_type event_queue_id, unsigned int options)
{
  return_type return_value;

  asm volatile
  ("\
    pushl %1
    pushl %2
    lcall %3, $0
   "
   : "=a" (return_value)
   : "g" (options),
     "g" (event_queue_id),
     "n" (SYSTEM_CALL_EVENT_QUEUE_REGISTER_LISTENER << 3));

  return return_value;
}

static inline return_type system_call_event_queue_generate_event
  (event_queue_id_type event_queue_id, event_parameter_type *event_parameter,
  unsigned int options)
{
  return_type return_value;

  asm volatile
  ("\
    pushl %2
    pushl %3
    pushl %4
    lcall %5, $0
   "
   : "=a" (return_value),
     "=g" (*event_parameter)
   : "g" (options),
     "g" (event_parameter),
     "g" (event_queue_id),
     "n" (SYSTEM_CALL_EVENT_QUEUE_GENERATE_EVENT << 3));

  return return_value;
}



static inline return_type system_call_event_queue_wait_event
  (event_queue_id_type event_queue_id,  event_parameter_type *event_parameter,
   unsigned int options)
{
  return_type return_value;

  asm volatile
  ("\
    pushl %2
    pushl %3
    pushl %4
    lcall %5, $0
   "
   : "=a" (return_value),
     "=g" (*event_parameter)
   : "g" (options),
     "g" (event_parameter),
     "g" (event_queue_id),
     "n" (SYSTEM_CALL_EVENT_QUEUE_WAIT_EVENT << 3));

  return return_value;
}

#include <event/functions.h>
#include <event/return_values.h>

#endif /* !__LIBRARY_EVENT_EVENT_H__ */
