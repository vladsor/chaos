/* $Id: mailbox.c,v 1.2 2000/10/15 11:17:51 plundis Exp $ */
/* Abstract: Events mailbox functions for the LPC (local process
   communication). */
/* Authors: Sorokin Vladimir */

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
   USA. */

/* Define this as TRUE if you are debugging this module. */

#define DEBUG           FALSE

/* Extra verbose debugging. This will make the system pretty unusable,
   so be warned. */

#define VERBOSE_DEBUG   FALSE

#include <storm/state.h>
#include <storm/generic/event_queue.h>
#include <storm/generic/cpu.h>
#include <storm/generic/debug.h>
#include <storm/generic/defines.h>
#include <storm/generic/dispatch.h>
#include <storm/generic/limits.h>
#include <storm/generic/memory.h>
#include <storm/generic/memory_global.h>
#include <storm/generic/return_values.h>
#include <storm/generic/thread.h>
#include <storm/current-arch/tss.h>
#include <storm/generic/string.h>

#include <storm/generic/log.h>

//static mutex_kernel_type mailbox_mutex = MUTEX_UNLOCKED;
//static mutex_kernel_type hash_mutex = MUTEX_UNLOCKED;
//static mutex_kernel_type free_id_mutex = MUTEX_UNLOCKED;
static event_queue_id_type event_queue_get_free_id (void);

unsigned int event_queue_numbers = 0;
event_queue_id_type system_event_queue_id;

/* The mailbox hash is an array of pointers. */

event_queue_type **event_queue_hash_table;
static event_queue_id_type free_event_queue_id = 0;

/* Gets the hash value for the given events mailbox ID. */

static int hash (event_queue_id_type event_queue_id)
{
  return (event_queue_id % limit_event_queue_hash_entries);
}

/* The init function for the events mailbox system. */

void event_queue_init (void)
{
  /* Allocate memory for the hash table. */

  event_queue_hash_table = (event_queue_type **) memory_global_allocate
    (sizeof (event_queue_type *) * limit_event_queue_hash_entries);
/*
  DEBUG_MESSAGE (VERBOSE_DEBUG, "event_queue_hash_table = %p, size = %u",
                 event_queue_hash_table, sizeof (event_queue_type *) *
                 limit_event_queue_hash_entries);
*/
  /* Initially set all pointers to NULL. This isn't entirely nice, but
     doing this as a for loop wouldn't even be close to cool. */

  memory_set_u8 ((u8 *) event_queue_hash_table, 0,
                 limit_event_queue_hash_entries * 
		 sizeof (event_queue_type *));

  system_event_queue_id = event_queue_get_free_id ();

  event_queue_create_kernel (system_event_queue_id, "SYSTEM", 0, 0, 0);  

}

/* Looks the given event's queue ID up in the hash table. */ 

static event_queue_type *event_queue_find (
  event_queue_id_type event_queue_id)
{
  event_queue_type *node;

  node = event_queue_hash_table[hash (event_queue_id)];

  DEBUG_MESSAGE (VERBOSE_DEBUG, "node = %x", node);

  while (node != NULL && node->id != event_queue_id)
  {
    node = (event_queue_type *) node->next;
    DEBUG_MESSAGE (VERBOSE_DEBUG, "node = %x", node);
  }

  return node;
}

/* Get the first available events mailbox id. */

static event_queue_id_type event_queue_get_free_id (void)
{
  return (++free_event_queue_id) - 1;
}

/* Link in a new queue in the mailbox hash table. Returns TRUE on
   successful linking of the queue, or FALSE otherwise. */

static bool event_queue_link (event_queue_type *new_event_queue)
{
  int index;

  index = hash (new_event_queue->id);

  new_event_queue->next = (struct event_queue_type *) 
    event_queue_hash_table[index];
  event_queue_hash_table[index] = new_event_queue;

  return TRUE;
}

/* Unlink a mailbox with a certain id. Returns TRUE on success, and
   FALSE otherwise. */

static bool event_queue_unlink (event_queue_id_type event_queue_id)
{
  int index;
  event_queue_type *event_queue, *previous_event_queue;

  index = hash (event_queue_id);
  
  event_queue = event_queue_hash_table[index];

  if (event_queue->id == event_queue_id)
  {
    event_queue_hash_table[index] = 
      (event_queue_type *) event_queue->next;
    memory_global_deallocate (event_queue);
    return TRUE;
  }
  else
  {
    while (event_queue != NULL && event_queue->id != event_queue_id)
    {
      previous_event_queue = event_queue;
      event_queue = (event_queue_type *) event_queue->next;
    }
    if (event_queue == NULL)
    {
      return FALSE;
    }
    else
    {
      previous_event_queue->next = event_queue->next;
      memory_global_deallocate (event_queue);
      return TRUE;
    }
  }
}

/* Create a new mailbox without locking the dispatcher (presuming it
   has already been locked). This function can only be called from
   within the kernel. */

return_type event_queue_create_kernel
  (event_queue_id_type event_queue_id, char *name,
   process_id_type user_process_id, cluster_id_type user_cluster_id,
   thread_id_type user_thread_id)
{
  event_queue_type *new_event_queue;

  event_queue_numbers++;

  new_event_queue = (event_queue_type *)
    memory_global_allocate (sizeof (event_queue_type));

  new_event_queue->owner_process_id = current_process_id;
  new_event_queue->owner_cluster_id = current_cluster_id;
  new_event_queue->owner_thread_id = current_thread_id;
  
  new_event_queue->user_process_id = user_process_id;
  new_event_queue->user_cluster_id = user_cluster_id;
  new_event_queue->user_thread_id = user_thread_id;
  
  /* FIXME: Check for allowed limits. */
  
  new_event_queue->number_of_events = 0;
  new_event_queue->blocked_size = 0;

  new_event_queue->first_event = NULL;
  new_event_queue->last_event = NULL;

  new_event_queue->reader_blocked = FALSE;
  
  new_event_queue->number_of_readers = 0;
  new_event_queue->first_event_reader = NULL;
  new_event_queue->last_event_reader = NULL;
  
  new_event_queue->next = NULL;
  
  new_event_queue->id = event_queue_id;

  new_event_queue->name = (char *)
    memory_global_allocate ( string_length(name) + 1 );
  string_copy(new_event_queue->name, name);
  
  event_queue_link (new_event_queue);

/*
  DEBUG_MESSAGE (VERBOSE_DEBUG, "queue create: name=%s,id=%u", name, 
    event_queue_id);  
*/
  kernel_log_print("Event queue create successfull");
  
  return STORM_RETURN_SUCCESS;
}

/* Create a new event's queue. */

return_type event_queue_create(event_queue_id_type *event_queue_id,char *name)
{
  return_type return_value;

  mutex_kernel_wait (&tss_tree_mutex);

  if( string_length(name) > MAX_EVENT_QUEUE_NAME_LENGTH )
  {
    return STORM_RETURN_INVALID_ARGUMENT;
  }

  *event_queue_id = event_queue_get_free_id ();

  return_value = event_queue_create_kernel (*event_queue_id, name,
                                               0, 0, 0);
  mutex_kernel_signal (&tss_tree_mutex);

  return return_value;
}

/* Destroy a event's queue. */

return_type event_queue_destroy (event_queue_id_type event_queue_id)
{
  event_queue_type *event_queue;

  mutex_kernel_wait (&tss_tree_mutex);

  event_queue = event_queue_find (event_queue_id);

  if (event_queue == NULL)
  {
    mutex_kernel_signal (&tss_tree_mutex);

    return STORM_RETURN_EVENT_QUEUE_UNAVAILABLE;
  }

  if (current_process_id == event_queue->owner_process_id &&
      current_cluster_id == event_queue->owner_cluster_id &&
      current_thread_id  == event_queue->owner_thread_id)
  {
    /* We are allowed to destroy this mailbox. */
    event_queue_numbers--;

    event_queue_unlink (event_queue_id);
    
    /* No need to close the mailbox, since it is destroyed. */

    mutex_kernel_signal (&tss_tree_mutex);

    return STORM_RETURN_SUCCESS;
  }
  else
  {
    debug_print ("Segmentation fault.\n");
    mutex_kernel_signal (&tss_tree_mutex);

    return STORM_RETURN_ACCESS_DENIED;
  }
}

/* Delete all queued events in the queue. */
/* FIXME: Write this code. */

return_type event_queue_flush (event_queue_id_type event_queue_id)
{
  event_queue_id = event_queue_id;

  return STORM_RETURN_SUCCESS;
}

/* Post a event in a queue. */

return_type event_queue_send (event_queue_id_type event_queue_id, 
  event_parameter_type *event_parameter)
{
  event_type *event;
  event_queue_type *event_queue;

  /* Perform some sanity checking on the input parameters. */

  if (event_parameter == NULL || (event_parameter->data == NULL &&
                                    event_parameter->length > 0))
  {
    DEBUG_SDB (DEBUG, "Invalid argument.");
    return STORM_RETURN_INVALID_ARGUMENT;
  }

  DEBUG_MESSAGE (VERBOSE_DEBUG,
                 "Called (event_parameter = %p, data = %p, protocol = %u, type = %u, id = %u)",
                 event_parameter, event_parameter->data,
                 event_parameter->protocol,event_parameter->event_class,
                 event_queue_id);

  event_queue = event_queue_find (event_queue_id);

  if (event_queue == NULL)
  {
    DEBUG_SDB (DEBUG, "event's queue == NULL.");

    return STORM_RETURN_EVENT_QUEUE_UNAVAILABLE;
  }

  if( (event_queue->number_of_readers == 0) )
  {

    return STORM_RETURN_EVENT_QUEUE_NO_READERS;
  }

  mutex_kernel_wait (&tss_tree_mutex);

  /* When we come here, we are guaranteed to send to the queue. */
//#FIXME if reader present directive copy to him
  DEBUG_MESSAGE (VERBOSE_DEBUG, "Delivering...");
  
#if 0
  if( event_queue->number_of_readers > 0 )
  {
    /* direct copy to readers. */
    current_reader = event_queue->first_reader;
    while(current_reader != NULL)
    {
//      current_reader->event_parameter->sender_process_id = current_process_id;
//      current_reader->event_parameter->sender_cluster_id = current_cluster_id;
//      current_reader->event_parameter->sender_thread_id = current_thread_id;

    DEBUG_MESSAGE (VERBOSE_DEBUG,
                   "event_queue_id = %u, event_queue->events = %u, event_queue->first_event = %x", 
                   event_queue_id, event_queue->number_of_events,
                   event_queue->first_event);
    DEBUG_MESSAGE (VERBOSE_DEBUG, "Unblocking...");

      current_reader->event_parameter->protocol = event_parameter->protocol;
      current_reader->event_parameter->event_class = event_parameter->event_class;

      current_reader->event_parameter->length = 0;
      current_reader->event_parameter->data = NULL;

      current_reader->tss->state = DISPATCH;
      // set_next_task(current_reader->tss);
      /*
        temporary = current_reader;
	deallocate(temporary);
      */
      current_reader = current_reader->next;
    }
  }
  else
  {
    event = memory_global_allocate (sizeof (event_type) +
                                    event_parameter->length);

    DEBUG_MESSAGE (VERBOSE_DEBUG, "Got %p (%u bytes)", event,
                   sizeof (event_type) + event_parameter->length);

    event->sender_process_id = current_process_id;
    event->sender_cluster_id = current_cluster_id;
    event->sender_thread_id = current_thread_id;

    event->protocol = event_parameter->protocol;
    event->class = event_parameter->event_class;

    event->next = NULL;

    event->length = event_parameter->length; 
    memory_copy (event->data, event_parameter->data,
                 event_parameter->length);

  /* Add the event to the linked list. */

    if (event_queue->last_event != NULL)
    {
      event_queue->last_event->next = (struct event_type *) event;
    }

    event_queue->last_event = event;

    if (event_queue->number_of_events == 0)
    {
      event_queue->first_event = event;
    }

    event_queue->number_of_events++;

#endif
  mutex_kernel_signal (&tss_tree_mutex);

  return STORM_RETURN_SUCCESS;
}

/* Receive a event from the queue. */

return_type event_queue_receive (event_queue_id_type event_queue_id,
                             event_parameter_type *event_parameter)
{
  event_queue_type *event_queue;
  event_type *temporary;

  DEBUG_MESSAGE (VERBOSE_DEBUG, "Called (id %u).", event_queue_id);

  if (event_parameter == NULL)
  {
    DEBUG_SDB (DEBUG, "event_parameter == NULL");

    return STORM_RETURN_INVALID_ARGUMENT;
  }

  event_queue = event_queue_find (event_queue_id);

  /* When we get here, we are allowed to access the queue. */

  if (event_queue == NULL)
  {
    DEBUG_SDB (DEBUG, "Event's queue was NULL");

    return STORM_RETURN_EVENT_QUEUE_UNAVAILABLE;
  }
  
  if ( (event_queue->number_of_events == 0) && 
    (event_parameter->time_out == 0) )
  {
    return STORM_RETURN_EVENT_QUEUE_TIME_OUT;
  }

  /* If the event's queue is empty, block. */

  mutex_kernel_wait (&tss_tree_mutex);

  if (event_queue->number_of_events == 0)
  {
      /* Block ourselves until the mailbox gets populated. */

      event_queue->reader_blocked = TRUE;
      event_queue->number_of_readers++;

      DEBUG_MESSAGE (VERBOSE_DEBUG, "Blocking ourselves.");
      /* 
      
      add_event_reader(current_tss, timeslice + event_parameter->time_out, 
      event_parameter);
      
      */

      /* Modify this task's entry in the TSS structure. */

      current_tss->state = STATE_EVENT_WAIT;
      current_tss->event_queue_id = event_queue_id;
      current_tss->mutex_time = timeslice;
      mutex_kernel_signal (&tss_tree_mutex);

      dispatch_next ();

      mutex_kernel_wait (&tss_tree_mutex);
      event_queue->reader_blocked = FALSE;

      /* A event has arrived. We open the mailbox again, so that we
         can read out the event. */
      
      DEBUG_MESSAGE (VERBOSE_DEBUG,
                     "event_queue_id = %u, event_queue->number_of_events = %u, event_queue->first_event = %x", 
                     event_queue_id, event_queue->number_of_events,
                     event_queue->first_event);
  }

  /* Receive the event. */
  /* FIXME: Allow conditional reception. */
#if 0  
  if (event_parameter->length >= event_queue->first_event->length)
  {
    /* This one fits into our bag. */
    
    event_parameter->protocol = event_queue->first_event->protocol;
    event_parameter->event_class = event_queue->first_event->class;
    event_parameter->length = event_queue->first_event->length;
    
    memory_copy (event_parameter->data, event_queue->first_event->data,
                 event_queue->first_event->length);
    temporary = event_queue->first_event;

    event_queue->first_event = (event_type *) event_queue->first_event->next;

    if (event_queue->first_event == NULL)
    {
      event_queue->last_event = NULL;
    }

    memory_global_deallocate (temporary);

    event_queue->number_of_events--;

    mutex_kernel_signal (&tss_tree_mutex);

    return STORM_RETURN_SUCCESS;
  }
  else
  {
    /* Need more space. */
    
    event_parameter->length = event_queue->first_event->length;
    mutex_kernel_signal (&tss_tree_mutex);

    return STORM_RETURN_EVENT_TOO_LARGE;
  }
#endif
  mutex_kernel_signal (&tss_tree_mutex);

  return STORM_RETURN_SUCCESS;
}

#if 0
return_type kernel_event_queue_update (void)
{
/* for each event queue reader*/
/* and for each event*/
  current_event_reader = current_event_queue_id->first_reader;
  while(current_event_reader != NULL)
  {
    if(current_event_reader->time_incomming + current_event_reader->time_out >
      current_time)
    {
      unblocking current reader
    }
  }

  return STORM_RETURN_SUCCESS;
}
#endif