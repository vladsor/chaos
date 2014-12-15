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

  mutex_kernel_wait (&tss_tree_mutex);

  DEBUG_MESSAGE (VERBOSE_DEBUG,
                 "Called (event_parameter = %p, data = %p, protocol = %u, type = %u, id = %u)",
                 event_parameter, event_parameter->data,
                 event_parameter->protocol,event_parameter->event_class,
                 event_queue_id);

  event_queue = event_queue_find (event_queue_id);

  if (event_queue == NULL)
  {
    mutex_kernel_signal (&tss_tree_mutex);
    DEBUG_SDB (DEBUG, "event's queue == NULL.");

    return STORM_RETURN_MAILBOX_UNAVAILABLE;
  }

  /* If the event won't ever fit into this mailbox, fail. */

  if (event_parameter->length + sizeof (event_parameter_type) >
      event_queue->total_size)
  {
    mutex_kernel_signal (&tss_tree_mutex);
    DEBUG_MESSAGE (DEBUG,
                   "Event's size was larger than the event's queue! (%u > %u)",
                   event_parameter->length + sizeof (event_parameter_type),
                   event_queue->total_size);

    return STORM_RETURN_MAILBOX_MESSAGE_TOO_LARGE;
  }

  /* Block or return, depending on how we was called. */

  if (event_parameter->length + sizeof (event_parameter_type) >
      event_queue->free_size)
  {
/*
    if (event_parameter->block)
    {
*/
      /* Block until receiver reads events so that there is room for
         us. */
/*
      current_tss->event_queue_id = event_queue_id;
      current_tss->mutex_time = timeslice;
      event_queue->blocked_size = (event_parameter->length + 
                               sizeof (event_parameter_type));
      current_tss->state = STATE_MAILBOX_SEND;
      mutex_kernel_signal (&tss_tree_mutex);
      dispatch_next ();
    }
    else
*/
    {
      mutex_kernel_signal (&tss_tree_mutex);
      DEBUG_SDB (DEBUG, "Mailbox was full");

      return STORM_RETURN_MAILBOX_FULL;
    }
  }

  /* When we come here, we are guaranteed to send to the mailbox. */

  DEBUG_MESSAGE (VERBOSE_DEBUG, "Delivering...");

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
  event_queue->free_size -= (event_parameter->length + 
                         sizeof (event_parameter_type));

  /* If someone is blocked on this queue, unblock her. */

  if (event_queue->reader_blocked)
  {
    DEBUG_MESSAGE (VERBOSE_DEBUG,
                   "event_queue_id = %u, event_queue->events = %u, event_queue->first_event = %x", 
                   event_queue_id, event_queue->number_of_events,
                   event_queue->first_event);
    DEBUG_MESSAGE (VERBOSE_DEBUG, "Unblocking...");
    thread_unblock_mailbox_receive (event_queue_id);
    DEBUG_MESSAGE (VERBOSE_DEBUG, "Done.");
  }

  mutex_kernel_signal (&tss_tree_mutex);

  return STORM_RETURN_SUCCESS;
