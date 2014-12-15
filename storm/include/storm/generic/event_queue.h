#ifndef __STORM_GENERIC_EVENT_QUEUE_H__
#define __STORM_GENERIC_EVENT_QUEUE_H__

#include <storm/event_queue.h>

#include <storm/generic/defines.h>
#include <storm/generic/mutex.h>
#include <storm/generic/types.h>
#include <storm/generic/hash_table.h>

#include <storm/current-arch/tss.h>

/* ������������ ���� */

/* ��������� ����������� ������� ���������� � �������. */
typedef struct
{
  /* ��������� �� �������� ������� */
  struct event_type *next;

  /* ����� ������� */
  unsigned int class;

  /* ���������� ����������, ������� ��� �� ���������� ��� ������� */
  unsigned int waiting_listeners;

  /* ����� ����������� ������� */
  unsigned int length;

  /* ������ ����������� ������� */
  u8 data[0];
} event_type;

#define FORWARD_EVENT             0x1

#define FIRST_LISTENER            0x0
#define LAST_LISTENER             0x1

#define PEEK_EVENT                0x1
#define NOT_BLOCKED               0x2

/* ��������� ����������� ���������� � ������������������ ��������� */
typedef struct
{
  /* ��������� �� ���������� ��������� */
  struct listener_type *next;

  /* ��������� �� ����������� ��������� */
  struct listener_type *previous;

  /* ��������� �� TSS ���� ��������� */
  storm_tss_type *storm_tss;

  /* ���������� ��������� ������� */
  unsigned int number_of_waiting_events;

  /* ��������� �� ������ ��������� ������� */
  event_type *waiting_event;

  /* ���������� ���������� ������� ��� ������� ��������� */
  unsigned int number_of_rejections;

  /* ���� ����������� ������� �� ��������� ������� */
  bool waiting;

  /* ... */
  event_parameter_type *event_parameter;
} listener_type;


/* ��������� ����������� ������� �������. */
typedef struct
{
  /* ����� ����������� ��� �������� � ���-������� */
  HASH_ELEMENT_PART;

  /* �������������� ����-��������� */
  process_id_type owner_process_id;
  cluster_id_type owner_cluster_id;
  thread_id_type owner_thread_id;

  /* ���������� �������, ����������� � ��������� ����� � ������� */
  unsigned int number_of_events;

  /* ������������ ���������� �������, ������� ����� ��������� � ������� */
  unsigned int max_number_of_events;

  /* ����� ���������� ���������� ������� */
  unsigned int number_of_rejections;  

  /* ���������� ����������, ������������������ �� ������ �������� */
  unsigned int number_of_listeners;

  /* ������������ ���������� ����������, ������� ����� ���� �������������� ��
  ������ �������� */
  unsigned int max_number_of_listeners;

  /* ��������� �� ������� ��������� */
  listener_type *first_listener;

  /* ��������� �� ���������� ��������� */
  listener_type *last_listener;

  /* ��������� �� ������ ������� � ������� */
  event_type *first_event;

  /* ��������� �� ��������� ������� � ������� */
  event_type *last_event;

  bool control_flag;
} event_queue_type;

/* ���-������� �������� ������� ������� */
extern hash_table_type *event_queue_hash_table;

/* ��������� ������� */
/* ����������� ������� ������� ������: ���� �������, ���������� ��� ���������
   ������, � ���������� �������, ������� �������� �������������� ��������,
   ��������� �� ���� ������� ��� ��������� ����� ���������� �������� ����������
   � ����������� ������������� �� ����� �������������� �����. ��� �������-
   �������� ���������� �������� ���� return_type, ��. ��������������� ����
   �� ���������� ����������. */

/****************************************************************************/
/* ���� ������� ����������� �������� ������� ������� */

/* �������-�������� �������� ������� �������. event_queue_id �.�. != NULL;
   max_number_of_listeners - ����������� ���������� ���������� �����������������
   �� ��������; max_number_of_events - ������������ ���������� ������� � 
   �������.  �� ������ ������� �� ������ event_queue_id ����� ��������� 
   ������������� ����� �������. */
extern return_type event_queue_create (
       event_queue_id_type *event_queue_id, 
       unsigned int max_number_of_listeners,
       unsigned int max_number_of_events);

/* ���������� ������� �������� �������. event_queue_id �������������
   ����������� �������; user_process_id,user_cluster_id,user_thread_id
   �������������� ���� ���������. ���������� ��������� �� ��������� ���������
   �������. */
extern event_queue_type * event_queue_create_kernel (
       event_queue_id_type event_queue_id,
       process_id_type user_process_id, 
       cluster_id_type user_cluster_id,
       thread_id_type user_thread_id,
       unsigned int max_number_of_listeners,
       unsigned int max_number_of_events);

/****************************************************************************/
/* ���� ������� ����������� �������� ������� */

/* �������-�������� �������� ������� �������. event_queue_id ������ ���������
   �� ������������ ������� � ���������� ���� �.�. ���������� �������. */
extern return_type event_queue_destroy (
       event_queue_id_type event_queue_id);

/* ���������� ������� �������� �������. event_queue ��������� �� ���������
   �������. */
extern void event_queue_destroy_kernel (
       event_queue_type *event_queue);

/****************************************************************************/
/* ���������� ������� ���������� ����� ��������� �� �������� ��������� TSS.
   event_queue - ��������� �� ��������� �������; storm_tss - ��������� �� 
   ��������� TSS. ���������� ��������� �� ��������� ���������, ���� ������� 
   ������, ����� NULL */
extern listener_type * search_listener (event_queue_type *event_queue,
       storm_tss_type *storm_tss);

/****************************************************************************/
/* ���� ����������� ����������/������������� ������� ������� ������� */

/* �������-�������� ������� ������� �� �������. event_queue_id - �������������
   ��������� �������. */
extern return_type event_queue_flush (
       event_queue_id_type event_queue_id);

/* ������� ������ ������� �������. event_queue - ��������� �� ��������� 
   ��������� �������. */
extern void event_queue_absolute_flush_kernel (
       event_queue_type *event_queue);

/* ������� ��������� ������� �������, ������� ������� ��������� ��������� 
   ����������. event_queue - ��������� �� ��������� ��������� �������, listener 
   - ��������� ���������, ��� �������� �������������� �������. */
extern void event_queue_relative_flush_kernel (
       event_queue_type *event_queue,
       listener_type *listener);

/****************************************************************************/
/* ���� ������� ����������� ����������� ���������� ���� ��� ��������� */

/* �������-�������� ����������� ���������. event_queue_id - �������������
   ������� �� ������� ��������������, options - �����. */
extern return_type event_queue_register_listener (
       event_queue_id_type event_queue_id,
       unsigned int options);

/* ���������� ������� ����������� ���������. storm_tss - ��������� ��
   ��������� TSS �������������� ����, event_queue - ��������� �� ���������
   �������, options - �����. ���������� ��������� �� ��������� ���������
   ���������. */
extern listener_type * event_queue_register_listener_kernel (
       storm_tss_type *storm_tss, 
       event_queue_type *event_queue,
       unsigned int options);

/****************************************************************************/
/* ���� ������� ����������� �������������� ���������� ���� ��� ��������� */

/* �������-�������� ������������� ���������. event_queue_id - �������������
   �������. */
extern return_type event_queue_unregister_listener (
       event_queue_id_type event_queue_id);

/* ���������� ������� �������������� ���������. event_queue - ��������� ��
   ��������� �������, listener - ��������� �� ��������� ���������. */
extern void event_queue_unregister_listener_kernel (
       event_queue_type *event_queue,
       listener_type *listener);

/****************************************************************************/
/* ���� ������� ��� ��������� ���������� �� ������� */

/* �������-�������� ��������� ������� ���������� �� �������. event_queue_id -
   ������������� �������, event_queue_info - ��������� �� ��������� ���� �����
   �������� ���������� (�.�. != NULL). */
extern return_type event_queue_get_info (
       event_queue_id_type event_queue_id, 
       event_queue_info_type *event_queue_info);

/* ���������� ������� ��������� ���������� �� �������. event_queue - ���������
   �� ��������� �������, event_queue_info - ��������� �� ��������� ���� �����
   �������� ����������.*/
extern void event_queue_get_info_kernel (
       event_queue_type *event_queue,
       event_queue_info_type *event_queue_info);

/****************************************************************************/
/* ���� ������� ��� ��������� ������� � �������� ��� � ������� */

/* �������-�������� ��������� �������. event_queue_id - ������������� �������,
   event_parameter - ��������� �� ��������� ����������� �������, �.�. != NULL �
   ��������� �� ���������� ���������; options - �����. */
extern return_type event_queue_generate_event (
       event_queue_id_type event_queue_id, 
       event_parameter_type *event_parameter, 
       unsigned int options);

/* ���������� ������� ��������� �������. event_queue - ��������� �� ���������
   �������, event_parameter - ��������� �� ��������� ����������� �������,
   options - �����. */
extern return_type event_queue_generate_event_kernel (
       event_queue_type *event_queue, 
       event_parameter_type *event_parameter, 
       unsigned int options);

/****************************************************************************/
/* ���������� ������� �������� �������� ������� ��� ������������ � ������� ���
   �� �������, ���� ��� ����������. */
extern bool free_event (event_queue_type *event_queue, event_type **event);

/****************************************************************************/
/* ���� ������� ��� �������� ������� � ���������� ��� ��������� */

/* �������-�������� �������� �������. event_queue_id - ������������� �������,
   event_parameter - ��������� �� ���������, ������� �� ������ ����� ���������
   ���������� � ������������ �������, �.�. != NULL � ��������� �� ���������� 
   ���������; options - �����. */
extern return_type event_queue_wait_event (
       event_queue_id_type event_queue_id, 
       event_parameter_type *event_parameter,
       unsigned int options);

/* ���������� ������� �������� �������. event_queue - ��������� �� ���������
   �������,  event_parameter - ��������� �� ���������, ������� �� ������ �����
   ��������� ���������� � ������������ �������, options - �����.*/
extern return_type event_queue_wait_event_kernel (
       event_queue_type *event_queue, 
       listener_type *this_listener,
       event_parameter_type *event_parameter,
       unsigned int options);

/****************************************************************************/
/* ������� ������������� ������, ���������� ��� �������� �������. */
extern void event_queue_init (void);

/* ������� ������������ ������. */
/* P.S. � ��������� ����� �� ������������ (��������������� ��� �������
   ���������). */
extern void event_queue_deinit (void);

#endif /* !__STORM_GENERIC_EVENT_QUEUE_H__ */

