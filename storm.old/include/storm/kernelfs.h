/* $Id: kernelfs.h,v 1.2 2000/09/29 20:05:07 plundis Exp $ */
/* Abstract: Function prorotypes for the kernel file system. */
/* Authors: Per Lundberg <plundis@chaosdev.org>
            Henrik Hallin <hal@chaosdev.org> */

/* Copyright 1999-2000 chaos development. */

/* This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the

   GNU General Public License for more details.  You should have
   received a copy of the GNU General Public License along with this
   program; if not, write to the Free Software Foundation, Inc., 59
   Temple Place, Suite 330, Boston, MA 02111-1307 USA. */

#ifndef __STORM_KERNELFS_H__
#define __STORM_KERNELFS_H__

#include <storm/types.h>
#include <storm/limits.h>
//#include <ia32/cpuid.h>

/* Command classes. When adding things here, ***ALWAYS*** put it at
   the end of the list. */

enum
{
  KERNELFS_CLASS_THREAD_AMOUNT,
  KERNELFS_CLASS_THREAD_INFO,
  KERNELFS_CLASS_THREAD_INFO_VERBOSE,

  KERNELFS_CLASS_PROCESS_AMOUNT,
  KERNELFS_CLASS_PROCESS_INFO,

  KERNELFS_CLASS_UPTIME_INFO,
  KERNELFS_CLASS_MEMORY_INFO,

  KERNELFS_CLASS_CPU_AMOUNT,
  KERNELFS_CLASS_CPU_INFO,

  KERNELFS_CLASS_STORM_INFO,
  KERNELFS_CLASS_VIDEO_INFO,
  KERNELFS_CLASS_SELF_INFO,

  KERNELFS_CLASS_PORT_AMOUNT,
  KERNELFS_CLASS_PORT_INFO,

  KERNELFS_CLASS_IRQ_AMOUNT,
  KERNELFS_CLASS_IRQ_INFO,  

  KERNELFS_CLASS_LOG_READ,

  KERNELFS_CLASS_TIME_READ,

  KERNELFS_CLASS_IPC_INFO,

  KERNELFS_CLASS_EVENT_QUEUE_AMOUNT,
  
  KERNELFS_CLASS_EVENT_QUEUE_INFO,

};

/* Type definitions. */
/* "Meta"-type which all other kernelfs types are derived from. */

typedef struct
{
  unsigned int kernelfs_class;
} kernelfs_generic_type;

typedef struct
{
  unsigned int kernelfs_class;

  /* Input parameters. */
  /* The process index number in the tables. */
  
  unsigned int process_number;

  /* Output parameters. */
  /* The real process ID. */

  process_id_type process_id;
  unsigned int number_of_threads;
  char name[MAX_PROCESS_NAME_LENGTH];
} kernelfs_process_info_type;

typedef struct
{
  unsigned int kernelfs_class;

  /* Input parameters. */

  unsigned int thread_number;
  process_id_type process_id;

  /* Output parameters. */

  thread_id_type thread_id;
  char name[MAX_THREAD_NAME_LENGTH];
  char state[MAX_STATE_NAME_LENGTH];

  /* Memory usage (in bytes). */

  u32 memory_usage;
} kernelfs_thread_info_type;

typedef struct
{
  unsigned int kernelfs_class;

  /* Input parameters. */

  unsigned int thread_number;
  process_id_type process_id;

  /* Output parameters. */

  thread_id_type thread_id;

  /* The number of timeslices this thread has been given. */

  time_type timeslices;

  /* The number of memory bytes this process is using. */

  u32 main_memory;
  u32 stack_memory;

  char process_name[MAX_PROCESS_NAME_LENGTH];
  char thread_name[MAX_THREAD_NAME_LENGTH];

  /* The current instruction pointer of the thread. */

  u32 instruction_pointer;
} kernelfs_thread_info_verbose_type;

typedef struct
{
  /* Input parameters. */

  unsigned int kernelfs_class;

  /* Output parameters. */

  process_id_type process_id;
  cluster_id_type cluster_id;
  thread_id_type thread_id;
} kernelfs_self_type;

typedef struct
{
  unsigned int kernelfs_class;

  /* Output parameters. */
  full_cpu_info info;

} kernelfs_cpu_info_type;

typedef struct
{
  unsigned int kernelfs_class;

  /* Output parameters. */

  u32 total_memory;
  u32 free_memory;

  u32 total_global_memory;
  u32 free_global_memory;
} kernelfs_memory_info_type;

typedef struct
{
  unsigned int kernelfs_class;
  
  /* Output parameters. */

  u32 mode_type;
  u32 width;
  u32 height;
  u32 depth;
  void *frame_buffer_address;
} kernelfs_video_info_type;

typedef struct
{
  unsigned int kernelfs_class;

  /* Output parameters. */

  char version[16];
} kernelfs_storm_info_type;

typedef struct
{
  unsigned int kernelfs_class;

  /* Input parameters. */
  
  unsigned int port;

  /* Output parameters. */

  unsigned int base;
  unsigned int length;
  process_id_type process_id;
  cluster_id_type cluster_id;
  thread_id_type thread_id;
  
  /* FIXME: Have a define for the max length of this. */

  char description[128];
} kernelfs_port_info_type;

typedef struct
{
  unsigned int kernelfs_class;

  /* Input parameter. */

  unsigned int which;
  
  /* Output parameters. */

  unsigned int level;
  process_id_type process_id;
  cluster_id_type cluster_id;
  thread_id_type thread_id;
  unsigned long long occurred;
  char description[128];
} kernelfs_irq_info_type;

typedef struct
{
  unsigned int kernelfs_class;

  /* Input parameter. */

  unsigned int max_string_length;
  bool block;

  /* Output and input parameter. */

  char *string;
} kernelfs_log_type;

typedef struct
{
  unsigned int kernelfs_class;

  /* The current time, in chaos format (milliseconds since the
     beginning of year 0. Yes, we know there were no such year, but it
     makes things easier if we pretend it actually existed...). */

  time_type time;
} kernelfs_time_type;

typedef struct
{
  unsigned int kernelfs_class;

  unsigned int mailbox_numbers;
  unsigned int event_queue_numbers;

} kernelfs_ipc_info_type;


typedef struct
{
  unsigned int kernelfs_class;

  /* Output parameters. */
  
  char name[MAX_EVENT_QUEUE_NAME_LENGTH];

  event_queue_id_type event_queue_id;
  
  unsigned int number_of_events;

} kernelfs_event_queue_info_type;


#endif /* !__STORM_KERNELFS_H__ */
