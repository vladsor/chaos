#ifndef __STORM_GENERIC_EVENT_QUEUE_H__
#define __STORM_GENERIC_EVENT_QUEUE_H__

#include <storm/event_queue.h>

#include <storm/generic/defines.h>
#include <storm/generic/mutex.h>
#include <storm/generic/types.h>
#include <storm/generic/hash_table.h>

#include <storm/current-arch/tss.h>

/* Заголовочный файл */

/* Структура описывающая событие хранящееся в очереди. */
typedef struct
{
  /* Указатель на следущее событие */
  struct event_type *next;

  /* Класс события */
  unsigned int class;

  /* Количество слушателей, которые еще не обработали это событие */
  unsigned int waiting_listeners;

  /* Длина содержимого события */
  unsigned int length;

  /* Данные описывающие событие */
  u8 data[0];
} event_type;

#define FORWARD_EVENT             0x1
#define LAST_LISTENER             0x1
#define PEEK_EVENT                0x1
#define NOT_BLOCKED               0x2

/* Структура описывающая информацию о зарегестрированном слушателе */
typedef struct
{
  /* Указатель на следующего слушателя */
  struct listener_type *next;

  /* Указатель на предидущего слушателя */
  struct listener_type *previous;

  /* Указатель на TSS нити слушателя */
  storm_tss_type *storm_tss;

  /* Количество ожидающих событий */
  unsigned int number_of_waiting_events;

  /* Указатель на первое ожидаемое событие */
  event_type *waiting_event;

  /* Количество потерянных событий */
  unsigned int number_of_rejections;

  /* Флаг оповещающий ожидает ли слушатель событие */
  bool waiting;

  /* ... */
  event_parameter_type *event_parameter;
} listener_type;


/* Структура описывающая очередь событий. */
typedef struct
{
  /* Часть определения для хранения в хэш-таблице */
  HASH_ELEMENT_PART;

  /* Идентификаторы нити-владельца */
  process_id_type owner_process_id;
  cluster_id_type owner_cluster_id;
  thread_id_type owner_thread_id;

  /* Количество событий находящихся в настоящее время в очереди */
  unsigned int number_of_events;

  /* Максимальное количество событий которое может находится в очереди */
  unsigned int max_number_of_events;

  /* Общее количество потерянных событий */
  unsigned int number_of_rejections;  

  /* Количество слушателей зарегистрированных за данной очередью */
  unsigned int number_of_listeners;

  /* Указатель на первого слушателя */
  listener_type *first_listener;

  /* Указатель на последнего слушателя */
  listener_type *last_listener;

  /* Указатель на первое событие в очереди */
  event_type *first_event;

  /* Указатель на последнее событие в очереди */
  event_type *last_event;

  bool control_flag;
} event_queue_type;

/* Хэш-таблица хранящая очереди событий */
extern hash_table_type *event_queue_hash_table;

/* Прототипы функций */
/* Большинство функций описано парами: сама функция-вызываемая при системном
   вызове и внутренняя функция несущая основную функциональную нагрузку,
   разбивка на пары сделана для отделения части выполяющей проверку параметров
   и выполняющей синхронизацию от самой функциональной части. Все функции-
   оболочки возвращают значения типа return_type, см. соответствующий файл
   за возможными значениями. */

/****************************************************************************/
/* Пара функций выполняющих создание очереди событий */

/* Функция-оболочка создания очереди событий. event_queue_id д.б. != NULL,
   length любое допустимое безнаковое целое число.  На выходе функции по
   адресу event_queue_id будет находится идентификатор новой очереди. */
extern return_type event_queue_create (
       event_queue_id_type *event_queue_id, 
       unsigned int max_number_of_events);

/* Внутренняя функция создания очереди. event_queue_id идентификатор
   создаваемой очереди; user_process_id,user_cluster_id,user_thread_id
   идентификаторы нити владельца. Возвращает указатель на структуру созданной
   очереди. */
extern event_queue_type * event_queue_create_kernel (
       event_queue_id_type event_queue_id,
       process_id_type user_process_id, 
       cluster_id_type user_cluster_id,
       thread_id_type user_thread_id,
       unsigned int max_number_of_events);

/****************************************************************************/
/* Пара функций выполняющих удаление очереди */

/* Функция-оболочка удаления очереди событий. event_queue_id должен указывать
   на существующую очередь и вызывающая нить д.б. владельцем очереди. */
extern return_type event_queue_destroy (
       event_queue_id_type event_queue_id);

/* Внутренняя функция удаления очереди. event_queue указатель на стрктуру
   очереди. */
extern void event_queue_destroy_kernel (
       event_queue_type *event_queue);

/****************************************************************************/
/* Внутренняя функция выполяющая поиск слушателя по заданным идентификаторам.
   event_queue указатель на стрктуру очереди; user_process_id,user_cluster_id,user_thread_id
   идентификаторы нити владельца. Возвращает указатель на структуру слушателя. */
extern listener_type * find_listener (event_queue_type *event_queue,
       process_id_type user_process_id, 
       cluster_id_type user_cluster_id,
       thread_id_type user_thread_id);

/****************************************************************************/
/* Пара выполняющих абсолютную/относительную очистку очереди событий */

/* Функция-оболочка очистки очереди от событий. event_queue_id - идентификатор
   очищаемой очереди. */
extern return_type event_queue_flush (
       event_queue_id_type event_queue_id);

/* Функция очистки очереди. event_queue - указатель на структуру очищаемой
   очереди. */
extern void event_queue_absolute_flush_kernel (
       event_queue_type *event_queue);

/**/
extern void event_queue_relative_flush_kernel (
       event_queue_type *event_queue,
       listener_type *listener);

/****************************************************************************/
/* Пара функций выполняющих регистрацию вызывающей нити как слушателя */

/* Функция-оболочка регистрации слушателя. event_queue_id - идентификатор
   очереди за которой регистрируется, options - опции. */
extern return_type event_queue_register_listener (
       event_queue_id_type event_queue_id,
       unsigned int options);

/* Внутренняя функция регистрации слушателя. storm_tss - указатель на
   структуру TSS регистрируемой нити, event_queue - указатель на структуру
   очереди, options - опции. Возвращает указатель на созданную структуру
   слушателя. */
extern listener_type * event_queue_register_listener_kernel (
       storm_tss_type *storm_tss, 
       event_queue_type *event_queue,
       unsigned int options);

/****************************************************************************/
/* Пара функций выполняющих разрегистрацию вызывающей нити как слушателя */

/* Функция-оболочка разрегистации слушателя. event_queue_id - идентификатор
   очереди. */
extern return_type event_queue_unregister_listener (
       event_queue_id_type event_queue_id);

/* Внутренняя функция разрегистрации слушателя. event_queue - указатель на
   структуру очереди, listener - указатель на структуру слушателя. */
extern void event_queue_unregister_listener_kernel (
       event_queue_type *event_queue,
       listener_type *listener);

/****************************************************************************/
/* Пара функций для получения информации об очереди */

/* Функция-оболочка получения текущей информации об очереди. event_queue_id -
   идентификатор очереди, event_queue_info - указатель на структуру куда будет
   помещена информация. */
extern return_type event_queue_get_info (
       event_queue_id_type event_queue_id, 
       event_queue_info_type *event_queue_info);

/* Внутренняя функция получения информации об очереди. event_queue - указатель
   на структуру очереди, event_queue_info - указатель на структуру куда будет
   помещена информация.*/
extern void event_queue_get_info_kernel (
       event_queue_type *event_queue,
       event_queue_info_type *event_queue_info);

/****************************************************************************/
/* Пара функций для генерации события и отправки его в очередь */

/* Функция-оболочка генерации события. event_queue_id - идентификатор очереди,
   event_parameter - указатель на структуру описывающую событие, options -
   опции. */
extern return_type event_queue_generate_event (
       event_queue_id_type event_queue_id, 
       event_parameter_type *event_parameter, 
       unsigned int options);

/* Внутренняя функция генерации события. event_queue - указатель на структуру
   очереди, event_parameter - указатель на структуру описывающую событие,
   options - опции. */
extern return_type event_queue_generate_event_kernel (
       event_queue_type *event_queue, 
       event_parameter_type *event_parameter, 
       unsigned int options);

/****************************************************************************/
/* Внутренняя функция отмечает заданное событие как обработанное и удаляет его
   из очереди, если это необходимо. */
extern bool free_event (event_queue_type *event_queue, event_type **event);

/****************************************************************************/
/* Пара функций для ожидания события и извлечения его изочереди */

/* Функция-оболочка ожидания события. event_queue_id - идентификатор очереди,
   event_parameter - указатель на структуру, которая на выходе будет содержать
   информацию о произошедшем событии, options - опции. */
extern return_type event_queue_wait_event (
       event_queue_id_type event_queue_id, 
       event_parameter_type *event_parameter,
       unsigned int options);

/* Внутренняя функция ожидания события. event_queue - указатель на структуру
   очереди,  event_parameter - указатель на структуру, которая на выходе будет
   содержать информацию о произошедшем событии, options - опции.*/
extern return_type event_queue_wait_event_kernel (
       event_queue_type *event_queue, 
       listener_type *this_listener,
       event_parameter_type *event_parameter,
       unsigned int options);

/****************************************************************************/
/* Функция инициализации модуля, вызывается при загрузке системы. */
extern void event_queue_init (void);

/* Функция деинсталяции модуля. */
/* P.S. В настоящее время не используется (зарезервировано для будущих
   изменений). */
extern void event_queue_deinit (void);

#endif /* !__STORM_GENERIC_EVENT_QUEUE_H__ */

