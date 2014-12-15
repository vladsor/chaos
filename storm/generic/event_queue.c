#include <storm/event_queue.h>
#include <storm/limits.h>
#include <storm/return_values.h>
#include <storm/state.h>

#include <storm/generic/hash_table.h>

#include <storm/generic/id_pool.h>

#include <storm/generic/event_queue.h>
#include <storm/generic/memory.h>
#include <storm/generic/memory_global.h>
#include <storm/generic/dispatch.h>
#include <storm/generic/thread.h>
#include <storm/generic/debug.h>
#include <storm/generic/log.h>

/* Определите эту константу как TRUE, если вы хотите отладить зтот модуль. */

#define DEBUG           FALSE

/* Глубокая отладка. Ее включение сделает систему невозможной для
   использования. */

#define VERBOSE_DEBUG   FALSE


/* Хэш-таблица, хранящая очереди событий */
hash_table_type *event_queue_hash_table;

/* Хранилище идентификаторов очередей */
id_pool_type *event_queue_id_pool;

range_type id_range = { 0, MAX_UINT };
range_type interrupt_range = { SYSTEM_EVENT_QUEUE_INTERRUPTS_0, 
                               SYSTEM_EVENT_QUEUE_INTERRUPTS_15 };
/*
  FUNCTION:     event_queue_init
  DESCRIPTION:  инициализация подсистемы
  ARGUMENTS:    нет
  RETURN VALUE: нет
*/
void event_queue_init (void)
{
  IDEBUG_MESSAGE (VERBOSE_DEBUG, "Called");

  /* Создание хэш-таблицы. */
  hash_table_create (&event_queue_hash_table, limit_event_queue_hash_entries);

  /* Создание хранилища идентификаторов. */
  id_pool_create (&event_queue_id_pool, id_range);

  /* Резервирование идентификаторов для системных очередей. */
  IDEBUG_MESSAGE (VERBOSE_DEBUG, "Reserving system queues");

  id_pool_reserve_id (event_queue_id_pool, SYSTEM_EVENT_QUEUE_LOG);
  id_pool_reserve_id (event_queue_id_pool, SYSTEM_EVENT_QUEUE_EXEPTIONS);
  id_pool_reserve_range (event_queue_id_pool, interrupt_range);

  /* Создание системных очередей. */
  IDEBUG_MESSAGE (VERBOSE_DEBUG, "Creating system queues");
}

/*
  FUNCTION:     event_queue_deinit
  DESCRIPTION:  деинициализация подсистемы.
  ARGUMENTS:    нет.
  RETURN VALUE: нет.
*/
void event_queue_deinit (void)
{
  IDEBUG_MESSAGE (VERBOSE_DEBUG, "Called");

  /* Удаляем хэш-таблицу */
  hash_table_destroy (event_queue_hash_table);

  /* Удаляем хранилище идентификаторов */
  id_pool_destroy (event_queue_id_pool);
}

/*
  FUNCTION:     event_queue_create_kernel
  DESCRIPTION:  внутренняя функция создания очереди.
  ARGUMENTS:    event_queue_id - идентификатор создаваемой очереди,
                user_process_id - идентификатор процесса,
                user_cluster_id - идентификатор кластера,
                user_thread_id - идентификатор нити,
                max_number_of_events - максимальное количество событий,
                которые могут одновременно находится в очереди.
  RETURN VALUE: если достаточно памяти, указатель на созданную структуру
                очереди, иначе NULL.
*/
event_queue_type * event_queue_create_kernel (
    event_queue_id_type event_queue_id,
    process_id_type user_process_id, 
    cluster_id_type user_cluster_id,
    thread_id_type user_thread_id,
    unsigned int max_number_of_events)
{
  event_queue_type *new_event_queue;

  IDEBUG_MESSAGE (VERBOSE_DEBUG, "event_queue_id = %u, max_number_of_events ="
                  " %u", event_queue_id, max_number_of_events);

  /* Пытаемся выделить память под структуру очереди. */
  if ( (new_event_queue = (event_queue_type *) 
       memory_global_allocate (sizeof (event_queue_type))) == NULL)
  {
    /* Если не удалось, то возвращаем NULL. */
    return NULL;
  }

  /* Заполняем информацию о владельце. */
  new_event_queue->owner_process_id = user_process_id;
  new_event_queue->owner_cluster_id = user_cluster_id;
  new_event_queue->owner_thread_id = user_thread_id;

  /*  */
  new_event_queue->number_of_rejections = 0;

  /**/
  new_event_queue->max_number_of_events = max_number_of_events;

  /* Первоначально очередь событий пуста. */
  new_event_queue->number_of_events = 0;
  new_event_queue->first_event = NULL;
  new_event_queue->last_event = NULL;

  /* Нет никаких слушателей. */
  new_event_queue->number_of_listeners = 0;
  new_event_queue->first_listener = NULL;
  new_event_queue->last_listener = NULL;

  /**/
  new_event_queue->id = event_queue_id;

  /* Добавляем заполненную структуру в хэш-таблицу. */
  hash_table_add_element (event_queue_hash_table,
                          (hash_element_type *) new_event_queue);

  new_event_queue->control_flag = FALSE;

  /* Возвращаем указатель на созданную структуру очереди. */
  return new_event_queue;
}

/*
  FUNCTION:     event_queue_create
  DESCRIPTION:  Системная функция создания очереди.
  ARGUMENTS:    event_queue_id - указатель на переменную типа
                event_queue_id_type, которая в результате работы функции будет
                содержать идентификатор созданной очереди,
                max_number_of_events - максимальное количество событий,
                которые могут одновременно находится в очереди.
  RETURN VALUE:
    STORM_RETURN_SUCCESS,
    STORM_RETURN_OUT_OF_ID_POOL,
    STORM_RETURN_OUT_OF_MEMORY
*/
return_type event_queue_create (
    event_queue_id_type *event_queue_id, 
    unsigned int max_number_of_events)
{
  DEBUG_MESSAGE (VERBOSE_DEBUG, "&event_queue_id = %p, max number of events = "
                 "%u", event_queue_id, max_number_of_events);

  mutex_kernel_wait (&tss_tree_mutex);

  /**/
  if (!id_pool_allocate_id (event_queue_id_pool, event_queue_id))
  {
    mutex_kernel_signal (&tss_tree_mutex);

    return STORM_RETURN_OUT_OF_ID_POOL;
  }

  /**/
  if (event_queue_create_kernel (*event_queue_id, current_process_id,
                                 current_cluster_id, current_thread_id,
                                 max_number_of_events) == NULL)
  {
    mutex_kernel_signal (&tss_tree_mutex);

    return STORM_RETURN_OUT_OF_MEMORY;
  }

  mutex_kernel_signal (&tss_tree_mutex);

  return STORM_RETURN_SUCCESS;
}

/*
  FUNCTION:     event_queue_destroy_kernel
  DESCRIPTION:  внутренняя функция удаления очереди.
  ARGUMENTS:    event_queue - указатель на структуру удаляемой очереди.
  RETURN VALUE: нет.
*/
void event_queue_destroy_kernel (event_queue_type *event_queue)
{
  listener_type *current_listener, *temporary_listener;

  IDEBUG_MESSAGE (VERBOSE_DEBUG, "event_queue->id = %u", event_queue->id);
  
  /* */
  current_listener = event_queue->first_listener;
  while (current_listener != NULL)
  {
    temporary_listener = current_listener;
    current_listener = (listener_type *) current_listener->next;

    memory_global_deallocate (temporary_listener);
  }

  /* */
  event_queue_absolute_flush_kernel (event_queue);

  /**/
  id_pool_deallocate_id (event_queue_id_pool, event_queue->id);

  /**/
  hash_table_delete_element (event_queue_hash_table, event_queue->id);
}


/*
  FUNCTION:     event_queue_destroy
  DESCRIPTION:  Системная функция удаления очереди событий.
  ARGUMENTS:    event_queue_id - идентификатор удаляемой очереди.
  RETURN VALUE:
    STORM_RETURN_SUCCESS,
    STORM_RETURN_RESOURCE_UNAVAILABLE,
    STORM_RETURN_ACCESS_DENIED
*/
return_type event_queue_destroy (event_queue_id_type event_queue_id)
{
  event_queue_type *event_queue;

  DEBUG_MESSAGE (VERBOSE_DEBUG, "event_queue_id = %u", event_queue_id);

  mutex_kernel_wait (&tss_tree_mutex);

  /**/
  event_queue = (event_queue_type *) hash_table_search_element (
                 event_queue_hash_table, event_queue_id);

  if (event_queue == NULL)
  {
    mutex_kernel_signal (&tss_tree_mutex);

    return STORM_RETURN_RESOURCE_UNAVAILABLE;
  }

  /**/
  if (!(current_process_id == event_queue->owner_process_id &&
        current_cluster_id == event_queue->owner_cluster_id &&
        current_thread_id  == event_queue->owner_thread_id))
  {
    mutex_kernel_signal (&tss_tree_mutex);

    return STORM_RETURN_ACCESS_DENIED;
  }
  
  /* We are allowed to destroy this queue. */
  event_queue_destroy_kernel (event_queue);
    
  mutex_kernel_signal (&tss_tree_mutex);

  return STORM_RETURN_SUCCESS;
}


/*
  FUNCTION:     event_queue_absolute_flush_kernel
  DESCRIPTION:  внутренняя функция очистки очереди.
  ARGUMENTS:    event_queue - указатель на структуру очищаемой очереди.
  RETURN VALUE: нет.
*/
void event_queue_absolute_flush_kernel (event_queue_type *event_queue)
{
  event_type *current_event, *temporary_event;

  current_event = event_queue->first_event;
  while (current_event != NULL)
  {
    temporary_event = current_event;
    current_event = (event_type *) current_event->next;
    memory_global_deallocate (temporary_event);
  }
  event_queue->number_of_events = 0;
}

/*
  FUNCTION:     event_queue_relative_flush_kernel
  DESCRIPTION:  внутренняя функция очистки очереди.
  ARGUMENTS:    event_queue - указатель на структуру очищаемой очереди.
  RETURN VALUE: нет.
*/
void event_queue_relative_flush_kernel (event_queue_type *event_queue,
    listener_type *listener)
{
  #define event ((event_type *) listener->waiting_event)
  while (event != NULL)
  {
    free_event (event_queue, &event);
  }
  #undef event
}

static listener_type *search_listener (event_queue_type *event_queue,
    storm_tss_type *storm_tss)
{
  listener_type *current_listener;

  current_listener = event_queue->first_listener;

  while (current_listener != NULL)
  {
    if (current_listener->storm_tss == storm_tss)
    {
       return current_listener;
    }
    current_listener = (listener_type *) current_listener->next;
  }

  return NULL;
}

/*
  FUNCTION:     event_queue_flush
  DESCRIPTION:  Системная функция очистки очереди событий.
  ARGUMENTS:    event_queue_id - идентификатор очищаемой очереди.
  RETURN VALUE:
    STORM_RETURN_SUCCESS,
    STORM_RETURN_RESOURCE_UNAVAILABLE,
    STORM_RETURN_ACCESS_DENIED.
*/
return_type event_queue_flush (event_queue_id_type event_queue_id)
{
  event_queue_type *event_queue;

  mutex_kernel_wait (&tss_tree_mutex);

  event_queue = (event_queue_type *) hash_table_search_element (
                 event_queue_hash_table, event_queue_id);

  if (event_queue == NULL)
  {
    mutex_kernel_signal (&tss_tree_mutex);

    return STORM_RETURN_RESOURCE_UNAVAILABLE;
  }

  if (current_process_id == event_queue->owner_process_id &&
      current_cluster_id == event_queue->owner_cluster_id &&
      current_thread_id  == event_queue->owner_thread_id)
  {
     /**/
     event_queue_absolute_flush_kernel (event_queue);
  }
  else
  {
    listener_type *this_listener;

    this_listener = search_listener (event_queue, current_tss);
    if (this_listener == NULL)
    {
       mutex_kernel_signal (&tss_tree_mutex);

       return STORM_RETURN_ACCESS_DENIED;
    }

    /**/
    event_queue_relative_flush_kernel (event_queue, this_listener);
  }

  mutex_kernel_signal (&tss_tree_mutex);

  return STORM_RETURN_SUCCESS;
}


/*
  FUNCTION:     event_queue_register_listener_kernel
  DESCRIPTION:  .
  ARGUMENTS:    storm_tss - ,
                event_queue - ,
                options - .
  RETURN VALUE: указатель на структуру зарегистрированного слушателя или NULL.
*/
listener_type * event_queue_register_listener_kernel (
       storm_tss_type *storm_tss,
       event_queue_type *event_queue,
       unsigned int options)
{
  listener_type *new_listener;

  IDEBUG_MESSAGE (VERBOSE_DEBUG, "event_queue->id = %u, tss = %p, options = %u",
                 event_queue->id, storm_tss, options);

  if ( (new_listener = (listener_type *)
                 memory_global_allocate (sizeof (listener_type))) == NULL)
  {
    return NULL;
  }

  new_listener->storm_tss = storm_tss;
  new_listener->waiting = FALSE;
  new_listener->waiting_event = NULL;
  new_listener->number_of_waiting_events = 0;
  new_listener->number_of_rejections = 0;

  /*FIXME*/
  if (options & LAST_LISTENER)
  {
    IDEBUG_MESSAGE (VERBOSE_DEBUG, "register as last.");
    
    (listener_type *) new_listener->previous = event_queue->last_listener;
    (listener_type *) new_listener->next = NULL;
    event_queue->last_listener = new_listener;
    if (event_queue->first_listener == NULL)
    {
      event_queue->first_listener = new_listener;
    }
  }
  else
  {
    IDEBUG_MESSAGE (VERBOSE_DEBUG, "register as first.");

    (listener_type *) new_listener->next = event_queue->first_listener;
    (listener_type *) new_listener->previous = NULL;
    event_queue->first_listener = new_listener;
    if (event_queue->last_listener == NULL)
    {
      event_queue->last_listener = new_listener;
    }
  }
  
  event_queue->number_of_listeners++;

  return new_listener;
}


/*
  FUNCTION:     event_queue_register_listener
  DESCRIPTION:  .
  ARGUMENTS:    event_queue_id - ,
                options - .
  RETURN VALUE:
    STORM_RETURN_SUCCESS,
    STORM_RETURN_RESOURCE_UNAVAILABLE,
    STORM_RETURN_ALREADY_DONE.
*/
return_type event_queue_register_listener (
       event_queue_id_type event_queue_id,
       unsigned int options)
{
  event_queue_type *event_queue;

  DEBUG_MESSAGE (VERBOSE_DEBUG, "event_queue_id = %u", event_queue_id);

  mutex_kernel_wait (&tss_tree_mutex);

  event_queue = (event_queue_type *) hash_table_search_element (
                 event_queue_hash_table, event_queue_id);

  if (event_queue == NULL)
  {
    mutex_kernel_signal (&tss_tree_mutex);

    return STORM_RETURN_RESOURCE_UNAVAILABLE;
  }

  if (search_listener (event_queue, current_tss) != NULL)
  {
    mutex_kernel_signal (&tss_tree_mutex);

    return STORM_RETURN_ALREADY_DONE;
  }

  event_queue_register_listener_kernel (current_tss, event_queue, options);

  mutex_kernel_signal (&tss_tree_mutex);

  return STORM_RETURN_SUCCESS;
}


/*
  FUNCTION:     event_queue_unregister_listener_kernel
  DESCRIPTION:  .
  ARGUMENTS:    event_queue - ,
                listener - .
  RETURN VALUE: нет.
*/
void event_queue_unregister_listener_kernel (
       event_queue_type *event_queue,
       listener_type *listener)
{
  event_queue_relative_flush_kernel (event_queue, listener);
/*
  if (listener == event_queue->first_listener)
  {
    event_queue->first_listener = (listener_type *) listener->next;
    if (event_queue->first_listener != NULL)
    {
      event_queue->first_listener->previous = NULL;
    }
  }
  else
  {
    (listener->previous)->next = listener->next;
  }

  if (listener == event_queue->last_listener)
  {
    event_queue->last_listener = (listener_type *) listener->previous;
    if (event_queue->last_listener != NULL)
    {
      event_queue->last_listener->next = NULL;
    }
  }
  else
  {
    (listener->next)->previous = listener->previous;
  }
*/
  memory_global_deallocate (listener);

  event_queue->number_of_listeners--;
}


/*
  FUNCTION:     event_queue_unregister_listener
  DESCRIPTION:  .
  ARGUMENTS:    event_queue_id - .
  RETURN VALUE:
    STORM_RETURN_SUCCESS,
    STORM_RETURN_RESOURCE_UNAVAILABLE,
    STORM_RETURN_ACCESS_DENIED.
*/
return_type event_queue_unregister_listener (
       event_queue_id_type event_queue_id)
{
  event_queue_type *event_queue;
  listener_type *current_listener;

  mutex_kernel_wait (&tss_tree_mutex);

  event_queue = (event_queue_type *) hash_table_search_element (
                 event_queue_hash_table, event_queue_id);

  if (event_queue == NULL)
  {
    mutex_kernel_signal (&tss_tree_mutex);

    return STORM_RETURN_RESOURCE_UNAVAILABLE;
  }

  current_listener = search_listener (event_queue, current_tss);

  if (current_listener == NULL)
  {
    mutex_kernel_signal (&tss_tree_mutex);

    return STORM_RETURN_ACCESS_DENIED;
  }

  event_queue_unregister_listener_kernel (event_queue, current_listener);

  mutex_kernel_signal (&tss_tree_mutex);

  return STORM_RETURN_SUCCESS;
}


/*
  FUNCTION:     event_queue_get_info_kernel
  DESCRIPTION:  .
  ARGUMENTS:    event_queue - ,
                event_queue_info - .
  RETURN VALUE: нет.
*/
void event_queue_get_info_kernel (
       event_queue_type *event_queue,
       event_queue_info_type *event_queue_info)
{
  DEBUG_MESSAGE (VERBOSE_DEBUG, "event_queue->id = %u, max number of events = "
     "%u, listeners = %u", event_queue->id, event_queue->max_number_of_events, 
     event_queue->number_of_listeners);

  event_queue_info->max_number_of_events = event_queue->max_number_of_events;
  event_queue_info->number_of_rejections = event_queue->number_of_rejections;
  event_queue_info->number_of_listeners = event_queue->number_of_listeners;

  event_queue_info->owner_process_id = event_queue->owner_process_id;
  event_queue_info->owner_cluster_id = event_queue->owner_cluster_id;
  event_queue_info->owner_thread_id = event_queue->owner_thread_id;
}


/*
  FUNCTION:     event_queue_get_info
  DESCRIPTION:  .
  ARGUMENTS:    event_queue_id - ,
                event_queue_info - .
  RETURN VALUE:
    STORM_RETURN_SUCCESS,
    STORM_RETURN_INVALID_ARGUMENT,
    STORM_RETURN_RESOURCE_UNAVAILABLE.
*/
return_type event_queue_get_info (
       event_queue_id_type event_queue_id,
       event_queue_info_type *event_queue_info)
{
  event_queue_type *event_queue;

  DEBUG_MESSAGE (VERBOSE_DEBUG, "event_queue_id = %u, event_queue_info = %p",
                 event_queue_id, event_queue_info);

  if (event_queue_info == NULL)
  {
    return STORM_RETURN_INVALID_ARGUMENT;
  }

  mutex_kernel_wait (&tss_tree_mutex);

  event_queue = (event_queue_type *) hash_table_search_element (
                 event_queue_hash_table, event_queue_id);

  if (event_queue == NULL)
  {
    mutex_kernel_signal (&tss_tree_mutex);

    return STORM_RETURN_RESOURCE_UNAVAILABLE;
  }

  event_queue_get_info_kernel (event_queue, event_queue_info);

  mutex_kernel_signal (&tss_tree_mutex);

  return STORM_RETURN_SUCCESS;
}



static inline bool check_parameter (event_parameter_type *event_parameter)
{
  return ( (event_parameter == NULL) ||
           ( (event_parameter->data == NULL) &&
             (event_parameter->length > 0) ) );
}


/*
  FUNCTION:     event_queue_generate_event_kernel
  DESCRIPTION:  .
  ARGUMENTS:    event_queue - ,
                event_parameter - ,
                options - .
  RETURN VALUE:
    STORM_RETURN_SUCCESS,
    STORM_RETURN_TIME_OUT.
*/
return_type event_queue_generate_event_kernel (
   event_queue_type *event_queue, 
   event_parameter_type *event_parameter,
   unsigned int options)
{
  listener_type *current_listener;
  event_type *new_event;
  unsigned int number_of_ready_listeners = 0;

  if ((event_queue->number_of_listeners == 0) && 
      (event_queue->max_number_of_events == 0))
  {
    return STORM_RETURN_TIME_OUT;
  }

  new_event = (event_type *) memory_global_allocate (sizeof (event_type) + 
              event_parameter->length); 
  new_event->class = event_parameter->event_class;
  new_event->length = event_parameter->length;
  memory_copy (new_event->data, event_parameter->data, new_event->length);

  /* FIXME */
  if (options & FORWARD_EVENT)
  {
  }
  else
  {
    new_event->next = NULL;
  }
  
  if (event_queue->max_number_of_events == 0)
  {
    event_queue->control_flag = TRUE;
    event_queue->first_event = new_event;
    event_queue->last_event = new_event;
  }
  else
  {
    event_queue->control_flag = FALSE;

    if (event_queue->first_event == NULL)
    {
      event_queue->first_event = new_event;
    }
    else
    {
      (event_type *) event_queue->last_event->next = new_event;
    }

    event_queue->last_event = new_event;
  }

  IDEBUG_MESSAGE (VERBOSE_DEBUG, "new_event->class = %u, "
      "new_event->data = %p, new_event->length = %u",
      new_event->class, new_event->data, new_event->length);

  current_listener = event_queue->first_listener;

  while (current_listener != NULL)
  {
    if (current_listener->waiting_event == NULL)
    {
      current_listener->waiting_event = new_event;
    }

    if (current_listener->waiting)
    {
      number_of_ready_listeners++;
      DEBUG_MESSAGE (VERBOSE_DEBUG, "Unblocking listener");
//       scheduler_unblock_thread (current_listener->storm_tss);

      current_listener->storm_tss->state = STATE_DISPATCH;
      current_listener->waiting = FALSE;
    }

    current_listener = (listener_type *) current_listener->next;
  }

  if (event_queue->max_number_of_events == 0)
  {
    new_event->waiting_listeners = number_of_ready_listeners;
  }
  else
  {
    new_event->waiting_listeners = event_queue->number_of_listeners;
  }

  return STORM_RETURN_SUCCESS;
}


/*
  FUNCTION:     event_queue_generate_event
  DESCRIPTION:  .
  ARGUMENTS:    event_queue_id - ,
                event_parameter - ,
                options - .
  RETURN VALUE:
    STORM_RETURN_SUCCESS,
    STORM_RETURN_INVALID_ARGUMENT,
    STORM_RETURN_RESOURCE_UNAVAILABLE,
    STORM_RETURN_ACCESS_DENIED.
*/
return_type event_queue_generate_event (
   event_queue_id_type event_queue_id, 
   event_parameter_type *event_parameter,
   unsigned int options)
{
  event_queue_type *event_queue;
  return_type return_value;

  DEBUG_MESSAGE (VERBOSE_DEBUG, "event_queue_id = %u, event_parameter = %p, "
                 "options = %u", event_queue_id, event_parameter, options);

  if (check_parameter (event_parameter))
  {
    return STORM_RETURN_INVALID_ARGUMENT;
  }

  DEBUG_MESSAGE (VERBOSE_DEBUG, "event_parameter->event_class = %u, "
      "event_parameter->data = %p, event_parameter->length = %u",
      event_parameter->event_class, event_parameter->data, 
      event_parameter->length);

  mutex_kernel_wait (&tss_tree_mutex);

  event_queue = (event_queue_type *) hash_table_search_element (
                 event_queue_hash_table, event_queue_id);

  if (event_queue == NULL)
  {
    DEBUG_MESSAGE (VERBOSE_DEBUG, "such event queue not exists.");
    
    mutex_kernel_signal (&tss_tree_mutex);

    return STORM_RETURN_RESOURCE_UNAVAILABLE;
  }

  if (!(current_process_id == event_queue->owner_process_id &&
        current_cluster_id == event_queue->owner_cluster_id &&
        current_thread_id  == event_queue->owner_thread_id))
  {
    DEBUG_MESSAGE (VERBOSE_DEBUG, "you are not owner.");

    mutex_kernel_signal (&tss_tree_mutex);

    return STORM_RETURN_ACCESS_DENIED;
  }

  return_value = 
    event_queue_generate_event_kernel (event_queue, event_parameter, options);

  mutex_kernel_signal (&tss_tree_mutex);

  return return_value;
}

bool free_event (event_queue_type *event_queue, event_type **event)
{
  event_type *temporary_event;

  IDEBUG_MESSAGE (VERBOSE_DEBUG, "FREING EVENT !!!!!!!!!!!.");
  
  temporary_event = (event_type *) (*event)->next;
  (*event)->waiting_listeners--;

  if ((*event)->waiting_listeners == 0)
  {
    IDEBUG_MESSAGE (VERBOSE_DEBUG, "DELETING EVENT !!!!!!!!!!!.");

    if ((*event) == event_queue->first_event)
    {
      event_queue->first_event = (event_type *) event_queue->first_event->next;
    }

    if ((*event) == event_queue->last_event)
    {
      event_queue->last_event = NULL;
    }

    memory_global_deallocate (*event);
    (*event) = temporary_event;

    IDEBUG_MESSAGE (VERBOSE_DEBUG, "next event = %p.", *event);

    return TRUE;
  }

  (*event) = (event_type *) (*event)->next;
  IDEBUG_MESSAGE (VERBOSE_DEBUG, "next event = %p.", *event);

  return FALSE;
}

/*
  FUNCTION:     event_queue_wait_event_kernel
  DESCRIPTION:  .
  ARGUMENTS:    event_queue - ,
                event_parameter - ,
                options.
  RETURN VALUE:
    STORM_RETURN_SUCCESS,
*/
return_type event_queue_wait_event_kernel (
   event_queue_type *event_queue,
   listener_type *this_listener,
   event_parameter_type *event_parameter,
   unsigned int options)
{
#define our_event ((event_type *) this_listener->waiting_event)

  do
  {
    IDEBUG_MESSAGE (VERBOSE_DEBUG, "Entring in cycle.");
    
    if (our_event == NULL)
    {
      IDEBUG_MESSAGE (VERBOSE_DEBUG, "Blocking ourselves");
      this_listener->waiting = TRUE;

//    scheduler_block_current_thread (STATE_WAIT_EVENT);

      current_tss->state = STATE_WAIT_EVENT;

      mutex_kernel_signal (&tss_tree_mutex);
    
      dispatch_next ();
      
      mutex_kernel_wait (&tss_tree_mutex);
    }

    IDEBUG_MESSAGE (VERBOSE_DEBUG, "We are unblocked.");
    IDEBUG_MESSAGE (VERBOSE_DEBUG, "our_event->class = %u, "
      "our_event->data = %p, our_event->length = %u",
      our_event->class, our_event->data, our_event->length);

    if (event_parameter->event_class != EVENT_CLASS_NONE)
    {
      while ((our_event != NULL) &&
             (our_event->class != event_parameter->event_class))
      {
        IDEBUG_MESSAGE (VERBOSE_DEBUG, "Event not accepted.");
	
        free_event (event_queue, &our_event);
      }
    }
    IDEBUG_MESSAGE (VERBOSE_DEBUG, "After checks our_event = %p.", our_event);

  } while (our_event == NULL);

  IDEBUG_MESSAGE (VERBOSE_DEBUG, "Copying data.");

  event_parameter->event_class = our_event->class;
  event_parameter->length = our_event->length;
  memory_copy (event_parameter->data, our_event->data, our_event->length);

  if (!(options & PEEK_EVENT))
  {
    free_event (event_queue, &our_event);
  }

#undef our_event

  return STORM_RETURN_SUCCESS;
}


/*
  FUNCTION:     event_queue_wait_event
  DESCRIPTION:  .
  ARGUMENTS:    event_queue_id - ,
                event_parameter - ,
                options.
  RETURN VALUE:
    STORM_RETURN_SUCCESS,
    STORM_RETURN_INVALID_ARGUMENT,
    STORM_RETURN_RESOURCE_UNAVAILABLE,
    STORM_RETURN_ACCESS_DENIED.
*/
return_type event_queue_wait_event (
   event_queue_id_type event_queue_id, 
   event_parameter_type *event_parameter,
   unsigned int options)
{
  event_queue_type *event_queue;
  listener_type *this_listener;

  DEBUG_MESSAGE (VERBOSE_DEBUG, "event_queue_id = %u, event_parameter = %p, "
                 "options = %u", event_queue_id, event_parameter, options);

  if (check_parameter (event_parameter))
  {
    return STORM_RETURN_INVALID_ARGUMENT;
  }

  DEBUG_MESSAGE (VERBOSE_DEBUG, "event_parameter->event_class = %u, "
      "event_parameter->data = %p, event_parameter->length = %u",
      event_parameter->event_class, event_parameter->data, 
      event_parameter->length);

  mutex_kernel_wait (&tss_tree_mutex);

  event_queue = (event_queue_type *) hash_table_search_element (
                 event_queue_hash_table, event_queue_id);

  if (event_queue == NULL)
  {
    mutex_kernel_signal (&tss_tree_mutex);

    return STORM_RETURN_RESOURCE_UNAVAILABLE;
  }

  this_listener = search_listener (event_queue, current_tss);

  if (this_listener == NULL)
  {
    mutex_kernel_signal (&tss_tree_mutex);

    return STORM_RETURN_ACCESS_DENIED;
  }

  event_queue_wait_event_kernel (event_queue, this_listener, event_parameter,
                                 options);

  mutex_kernel_signal (&tss_tree_mutex);

  return STORM_RETURN_SUCCESS;
}

