/* $Id: log.c,v 1.2 2001/02/10 21:25:51 jojo Exp $ */
/* Abstract: Kernel logging functions. */
/* Author: Henrik Hallin <hal@chaosdev.org> */

/* Copyright 2000 chaos development. */

/* This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
   USA. */

#include <storm/event_queue.h>

#include <storm/generic/defines.h>
#include <storm/generic/log.h>
#include <storm/generic/event_queue.h>
#include <storm/generic/string.h>
#include <storm/generic/thread.h>

log_list_type *log_list = NULL;
event_parameter_type event_parameter;
event_queue_type *log_event_queue;

void log_init (void)
{
  log_event_queue = 
    event_queue_create_kernel (SYSTEM_EVENT_QUEUE_LOG, 0, 0, 0, 0, 0);
}

void log_print (char *string)
{
  event_parameter.event_class = KERNEL_LOG_PRINT;
  event_parameter.data = string;
  event_parameter.length = string_length (string);

  tss_tree_mutex = MUTEX_LOCKED;
  event_queue_generate_event_kernel (log_event_queue, &event_parameter, 0);
  mutex_kernel_signal (&tss_tree_mutex);
}