/* Receive a event from the mailbox. */

return_type event_queue_receive (event_queue_id_type event_queue_id,
                             event_parameter_type *event_parameter)
{
  event_queue_type *event_queue;
  event_type *temporary;

  mutex_kernel_wait (&tss_tree_mutex);
  DEBUG_MESSAGE (VERBOSE_DEBUG, "Called (id %u).", event_queue_id);
  event_queue = event_queue_find (event_queue_id);

  if (event_parameter == NULL)
  {
    DEBUG_SDB (DEBUG, "event_parameter == NULL");
    mutex_kernel_signal (&tss_tree_mutex);

    return STORM_RETURN_INVALID_ARGUMENT;
  }

  /* When we get here, we are allowed to access the mailbox. */

  if (event_queue == NULL)
  {
    mutex_kernel_signal (&tss_tree_mutex);
    DEBUG_SDB (DEBUG, "Event's queue was NULL");
    return STORM_RETURN_MAILBOX_UNAVAILABLE;
  }

  if (!(current_process_id == event_queue->owner_process_id &&
        current_cluster_id == event_queue->owner_cluster_id/* &&
        current_thread_id == mailbox->owner_thread_id*/))
  {
    /* We don't have read-access to this mailbox, since we are not the
       owner. */

    DEBUG_MESSAGE (DEBUG, "Access denied for process/thread %u/%u (should have been %u/%u) mailbox ID %u",
                   current_process_id, current_thread_id, 
                   event_queue->owner_process_id, event_queue->owner_thread_id,
                   event_queue_id);
    mutex_kernel_signal (&tss_tree_mutex);

    while (TRUE);
    return STORM_RETURN_ACCESS_DENIED;
  }

  /* If the event's queue is empty, block. */

  if (event_queue->number_of_events == 0)
  {
    if (event_parameter->block)
    {
      /* Block ourselves until the mailbox gets populated. */

      event_queue->reader_blocked = TRUE;

      DEBUG_MESSAGE (VERBOSE_DEBUG, "Blocking ourselves.");

      mutex_kernel_signal (&tss_tree_mutex);

      /* Modify this task's entry in the TSS structure. */
    
      mutex_kernel_wait (&tss_tree_mutex);
      current_tss->state = STATE_MAILBOX_RECEIVE;
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
    else
    {
      /* There was no mail, return. */

      mutex_kernel_signal (&tss_tree_mutex);

      return STORM_RETURN_MAILBOX_EMPTY;
    }
  }

  /* Receive the event. */
  /* FIXME: Allow conditional reception. */
  
  if (event_parameter->length >= event_queue->first_event->length)
  {
    /* This one fits into our bag. */
    
    event_parameter->protocol = event_queue->first_event->protocol;
    event_parameter->event_class = event_queue->first_event->class;
    event_parameter->length = event_queue->first_event->length;
    
    event_queue->free_size += (event_queue->first_event->length + 
                           sizeof (event_parameter_type));

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

    /* Check if we can unblock our boy. */

    if (event_queue->blocked_size != 0 &&
        event_queue->blocked_size < event_queue->free_size)
    {
      thread_unblock_mailbox_send (event_queue_id);
      event_queue->blocked_size = 0;
    }

    mutex_kernel_signal (&tss_tree_mutex);

    return STORM_RETURN_SUCCESS;
  }
  else
  {
    /* Need more space. */
    
    event_parameter->length = event_queue->first_event->length;
    mutex_kernel_signal (&tss_tree_mutex);

    return STORM_RETURN_MAILBOX_MESSAGE_TOO_LARGE;
  }
}
