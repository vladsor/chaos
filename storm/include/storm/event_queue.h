#ifndef __STORM_EVENT_QUEUE_H__
#define __STORM_EVENT_QUEUE_H__

#include <storm/limits.h>
#include <storm/types.h>

/* Those parameters are passed to the event's system calls. */

typedef struct
{
  unsigned int event_class;
    
  unsigned int length;
  void *data;
} event_parameter_type;

#define EVENT_CLASS_NONE          MAX_UINT

typedef struct
{
  unsigned int max_number_of_events;
  unsigned int number_of_rejections;
  unsigned int number_of_listeners;

  process_id_type owner_process_id;
  cluster_id_type owner_cluster_id;
  thread_id_type  owner_thread_id;
} event_queue_info_type;

#define SYSTEM_EVENT_QUEUE_LOG           6
#define SYSTEM_EVENT_QUEUE_EXEPTIONS     7

#define SYSTEM_EVENT_QUEUE_INTERRUPTS_0     10
#define SYSTEM_EVENT_QUEUE_INTERRUPTS_1     11
#define SYSTEM_EVENT_QUEUE_INTERRUPTS_2     12
#define SYSTEM_EVENT_QUEUE_INTERRUPTS_3     13
#define SYSTEM_EVENT_QUEUE_INTERRUPTS_4     14
#define SYSTEM_EVENT_QUEUE_INTERRUPTS_5     15
#define SYSTEM_EVENT_QUEUE_INTERRUPTS_6     16
#define SYSTEM_EVENT_QUEUE_INTERRUPTS_7     17
#define SYSTEM_EVENT_QUEUE_INTERRUPTS_8     18
#define SYSTEM_EVENT_QUEUE_INTERRUPTS_9     19
#define SYSTEM_EVENT_QUEUE_INTERRUPTS_10    20
#define SYSTEM_EVENT_QUEUE_INTERRUPTS_11    21
#define SYSTEM_EVENT_QUEUE_INTERRUPTS_12    22
#define SYSTEM_EVENT_QUEUE_INTERRUPTS_13    23
#define SYSTEM_EVENT_QUEUE_INTERRUPTS_14    24
#define SYSTEM_EVENT_QUEUE_INTERRUPTS_15    25

#define KERNEL_LOG_PRINT 0
#define IRQ_OCCURED 0

#endif /* !__STORM_EVENT_QUEUE_H__ */
