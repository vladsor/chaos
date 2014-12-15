/* $Id: mailbox.h,v 1.1.1.1 2000/09/26 19:08:17 plundis Exp $ */
/* Abstract: Function prototypes for the event's IPC system. */
/* Author: Vladimir Sorokin */

/* Copyright 1999-2000 chaos development. */

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
   USA */

#ifndef __STORM_GENERIC_EVENT_QUEUE_H__
#define __STORM_GENERIC_EVENT_QUEUE_H__

#include <storm/current-arch/tss.h>
#include <storm/event_queue.h>
#include <storm/generic/defines.h>
#include <storm/generic/mutex.h>
#include <storm/generic/types.h>

/* Type definitions. */

/* This defines the structure for event inside queue. */

typedef struct
{
  process_id_type sender_process_id;
  cluster_id_type sender_cluster_id;
  thread_id_type sender_thread_id;

  unsigned int protocol;
  unsigned int class;

  struct event_type *next;

  unsigned int length;

  u8 data[0];
} event_type;


/* */

typedef struct
{
  storm_tss_type reader_tss;
  
  time_type time_of_death;
  event_parameter_type *event_parameter;

  struct event_reader_type *next;
} event_reader_type;


/* The format of a event's queue. */

typedef struct
{
  /* Event's queue id. */

  event_queue_id_type id;

  /* Queue name. */

  char* name;

  /* Queue priority. */
  
  unsigned int priority;
  
  /* Queue attributes. */
  
  unsigned int attributes;

  /* Who owns the event's queue. */

  process_id_type owner_process_id;
  cluster_id_type owner_cluster_id;
  thread_id_type owner_thread_id;

  /* Who is allowed to send to the event's queue. */

  process_id_type user_process_id;
  cluster_id_type user_cluster_id;
  thread_id_type user_thread_id;

  /* Size of the event the blocked sender is awaiting to deliver. */

  unsigned int blocked_size;

  /* Number of events in the event's queue. */

  unsigned int number_of_events;

  /* Is the owner of this event's queue blocked on reading? */

  bool reader_blocked;

  unsigned int number_of_readers;
  event_reader_type *first_event_reader;
  event_reader_type *last_event_reader;

  /* Start of the first message in the mailbox. */

  event_type *first_event;
  event_type *last_event;

  /* Tree nodes. */

  struct event_queue_type *next;
} __attribute__ ((packed)) event_queue_type;

extern unsigned int event_queue_numbers;
extern event_queue_id_type system_event_queue_id;
extern event_queue_type **event_queue_hash_table;
/* Function prototypes. */

extern return_type event_queue_create 
(event_queue_id_type *event_queue_id, char *name);

extern return_type event_queue_destroy (event_queue_id_type event_queue_id);

extern return_type event_queue_flush (event_queue_id_type event_queue_id);
/*
extern return_type event_queue_reader_register
  (event_queue_id_type event_queue_id);
extern return_type event_queue_reader_register_kernel
  (event_queue_id_type event_queue_id,
   process_id_type user_process_id, cluster_id_type user_cluster_id,
   thread_id_type user_thread_id);
*/
extern return_type event_queue_send
  (event_queue_id_type event_queue_id, event_parameter_type *event_parameter);

extern return_type event_queue_receive
  (event_queue_id_type event_queue_id, event_parameter_type *event_parameter);

extern void event_queue_init (void) INIT_CODE;

extern return_type event_queue_create_kernel
  (event_queue_id_type event_queue_id, char *name,
   process_id_type user_process_id, cluster_id_type user_cluster_id,
   thread_id_type user_thread_id);

/* extern return_type kernel_event_queue_update (void);*/

#endif /* !__STORM_GENERIC_EVENT_QUEUE_H__ */
