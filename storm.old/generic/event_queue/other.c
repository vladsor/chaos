/* The mailbox hash is an array of pointers. */

static event_queue_type **event_queue_hash_table;
static event_queue_id_type free_event_queue_id = 1;

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

//  DEBUG_MESSAGE (VERBOSE_DEBUG, "event_queue_hash_table = %x, size = %u",
//                 event_queue_hash_table, sizeof (event_queue_type *) *
//                 limit_event_queue_hash_entries);

  /* Initially set all pointers to NULL. This isn't entirely nice, but
     doing this as a for loop wouldn't even be close to cool. */

  memory_set_u8 ((u8 *) event_queue_hash_table, 0,
                 limit_event_queue_hash_entries * 
		 sizeof (event_queue_type *));
}

/* Looks the given events mailbox ID up in the hash table. */ 

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
  event_queue_id_type id;

  id = free_event_queue_id;
  free_event_queue_id++;

  return id;
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
