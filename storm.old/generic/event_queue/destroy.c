/* Destroy a events mailbox, using some common explosive. */

return_type event_queue_destroy (event_queue_id_type event_queue_id)
{
  event_queue_type *event_queue;

  mutex_kernel_wait (&tss_tree_mutex);

  event_queue = event_queue_find (event_queue_id);

  //  debug_print ("%s: destroying %u\n", __FUNCTION__, mailbox_id);

  if (event_queue == NULL)
  {
    mutex_kernel_signal (&tss_tree_mutex);

    return STORM_RETURN_MAILBOX_UNAVAILABLE;
  }

  if (current_process_id == event_queue->owner_process_id &&
      current_cluster_id == event_queue->owner_cluster_id &&
      current_thread_id  == event_queue->owner_thread_id)
  {
    /* We are allowed to destroy this mailbox. */
    event_queue_numbers--;

    event_queue_unlink (event_queue_id);
    
    //    tree_dump (root);
    
    //    debug_print ("root: %x\n", root);
    
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
