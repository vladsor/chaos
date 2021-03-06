/* $Id: functions.h,v 1.2 2000/09/29 21:08:47 hal Exp $ */
/* Abstract: Event library functions. */
/* Author: Vladimir Sorokin */

/* Copyright 2000 chaos development. */

/* This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public License
   as published by the Free Software Foundation; either version 2 of
   the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
   USA. */

#ifndef __LIBRARY_EVENT_FUNCTIONS_H__
#define __LIBRARY_EVENT_FUNCTIONS_H__

#include <system/system.h>

typedef void (* event_handler_type) (void);

extern return_type event_generate
  (event_queue_id_type event_queue_id,
  event_parameter_type *event_parameter);

extern return_type event_wait
  (event_queue_id_type event_queue_id,
  event_parameter_type *event_parameter);

extern return_type event_set_handler
  (event_handler_type event_handler,
  event_queue_id_type event_queue_id,
  event_parameter_type *event_parameter);

#endif /* !__LIBRARY_EVENT_FUNCTIONS_H__ */
