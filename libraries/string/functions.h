/* $Id: functions.h,v 1.2 2001/02/10 21:23:13 jojo Exp $ */
/* Abstract: Function prototypes. */
/* Author: Per Lundberg <plundis@chaosdev.org> */

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

#ifndef __LIBRARY_STRING_FUNCTIONS_H__
#define __LIBRARY_STRING_FUNCTIONS_H__

#include <standart_types/standart_types.h>

extern return_type string_to_number (const char *string, int *number,
    int *characters);

extern char *number_to_string (char *string, unsigned long number, int base,
    int size, int precision, int flags);


extern return_type string_print (char *output, const char *format_string, ...)
    __attribute__ ((format (printf, 2, 3)));

extern return_type string_print_va (char *output, const char *format_string, 
    va_list arguments);

extern u32 arguments_parse (char *source, char *destination, u32 delta);

#endif /* !__LIBRARY_STRING_FUNCTIONS_H__ */
