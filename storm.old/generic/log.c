/* $Id: log.c,v 1.1.1.1 2000/09/26 19:08:16 plundis Exp $ */
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

#include <storm/generic/defines.h>
#include <storm/generic/log.h>
#include <storm/current-arch/string.h>
#include <storm/generic/return_values.h>
#include <storm/generic/memory.h>
#include <storm/generic/memory_global.h>

log_list_type *log_list = NULL;
log_list_type *end_log_list = NULL;

return_type kernel_log_print( char *message )
{
  log_list_type *log_element;
  log_element = (log_list_type *)memory_global_allocate( sizeof(log_list_type) );
  log_element->string = (char *)memory_global_allocate( string_length(message) );
  string_copy( log_element->string, message );
  log_element->next = NULL;
  
  if(log_list == NULL)
  {
    log_list = end_log_list = log_element;
  }
  else
  {
    (log_list_type *)end_log_list->next = (log_list_type *)log_element;
  }

  return STORM_RETURN_SUCCESS;
}
