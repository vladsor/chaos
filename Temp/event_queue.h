/* $Id: mailbox.h,v 1.1.1.1 2000/09/26 19:08:17 plundis Exp $ */
/* Abstract: Function prototypes for the events IPC system. */

/* Author: Sorokin Vladimir */

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

#include <storm/event.h>
#include <storm/generic/defines.h>
#include <storm/generic/mutex.h>
#include <storm/generic/types.h>

/* Type definitions. */

/* This defines the structure for messages inside events mailboxes. */

typedef struct
{
  process_id_type sender_process_id;
  cluster_id_type sender_cluster_id;
  thread_id_type sender_thread_id;

  unsigned int event_type;

  struct event_type *next;

  unsigned int length;

  u8 data[0];
} event_type;

/* The format of a event's mailbox. */

typedef struct
{
  /* Mailbox id. */

  events_mailbox_id_type id;

  /* Who owns the mailbox. */

  process_id_type owner_process_id;
  cluster_id_type owner_cluster_id;
  thread_id_type owner_thread_id;

  /* Who is allowed to send to the mailbox. */

  process_id_type user_process_id;
  cluster_id_type user_cluster_id;
  thread_id_type user_thread_id;

  /* Size of the mailbox. */

  unsigned int total_size;

  /* Size of the free part of the mailbox. */

  unsigned int free_size;

  /* Size of the message the blocked sender is awaiting to deliver. */

  unsigned int blocked_size;

  /* Number of messages in the mailbox. */

  unsigned int number_of_events;

  /* Is the owner of this mailbox blocked on reading? */

  bool reader_blocked;

  /* Start of the first message in the mailbox. */

  event_type *first_event;
  event_type *last_event;

  /* Tree nodes. */

  struct events_mailbox_type *next;
} __attribute__ ((packed)) events_mailbox_type;

/* Function prototypes. */

extern return_type events_mailbox_create
  (events_mailbox_id_type *events_mailbox_id, unsigned int size,
   process_id_type user_process_id, cluster_id_type user_cluster_id,
   thread_id_type user_thread_id);

extern return_type events_mailbox_destroy (
  events_mailbox_id_type events_mailbox_id);

extern return_type events_mailbox_flush (
  events_mailbox_id_type events_mailbox_id);

extern return_type events_mailbox_send
  (events_mailbox_id_type events_mailbox_id, 
  event_parameter_type *event_parameter);

extern return_type events_mailbox_receive
  (events_mailbox_id_type events_mailbox_id, 
  event_parameter_type *event_parameter);

extern void events_mailbox_init (void) INIT_CODE;
extern return_type events_mailbox_create_kernel
  (events_mailbox_id_type *events_mailbox_id, unsigned int size,
   process_id_type user_process_id, cluster_id_type user_cluster_id,
   thread_id_type user_thread_id);

#endif /* !__STORM_GENERIC_EVENT_QUEUE_H__ */
