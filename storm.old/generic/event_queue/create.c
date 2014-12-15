/* Create a new mailbox without locking the dispatcher (presuming it
   has already been locked). This function can only be called from
   within the kernel. */

return_type event_queue_create_kernel
  (event_queue_id_type *event_queue_id, unsigned int size,
   process_id_type user_process_id, cluster_id_type user_cluster_id,
   thread_id_type user_thread_id)
{
  event_queue_type *new_event_queue;

  DEBUG_MESSAGE (VERBOSE_DEBUG, "Called");
  
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
  
  new_event_queue->total_size = size;
  new_event_queue->free_size = size;
  new_event_queue->number_of_events = 0;
  new_event_queue->blocked_size = 0;

  new_event_queue->first_event = NULL;
  new_event_queue->last_event = NULL;

  new_event_queue->reader_blocked = FALSE;
  
  new_event_queue->next = NULL;
  
  new_event_queue->id = *event_queue_id = 
    event_queue_get_free_id ();
  
  event_queue_link (new_event_queue);
  
  return STORM_RETURN_SUCCESS;
}

/* Create a new events mailbox. */

return_type event_queue_create
  (event_queue_id_type *event_queue_id, unsigned int size,
   process_id_type user_process_id, cluster_id_type user_cluster_id,
   thread_id_type user_thread_id)
/*
  (
  event_queue_id_type *event_queue_id, //
  char *name                           //
  )
*/   
{
  return_type return_value;

  mutex_kernel_wait (&tss_tree_mutex);
  return_value = event_queue_create_kernel (event_queue_id, size, 
                                               user_process_id, user_cluster_id,
                                               user_thread_id);
  mutex_kernel_signal (&tss_tree_mutex);

  return return_value;
}
