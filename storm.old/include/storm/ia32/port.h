/* $Id: port.h,v 1.1.1.1 2000/09/26 19:08:18 plundis Exp $ */
/* Abstract: Function prototypes and structure definitions of port in
   and output. */
/* Author: Per Lundberg <plundis@chaosdev.org> */

/* Copyright 1998-2000 chaos development. */

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

#ifndef __STORM_IA32_PORT_H__
#define __STORM_IA32_PORT_H__

#include <storm/generic/types.h>

#define MAX_PORTS MAX_U16

extern void register_internal_ports (void);
extern void port_fix (unsigned int start, unsigned int ports);

/* Inlines. */

/* I/O functions. */

static inline void port_out_u8 (u16 port, u8 data)
{
  asm ("outb %1, %0"
       :
       : "Nd" (port),
         "a" (data));
}

static inline void port_out_u16 (u16 port, u16 data)
{
  asm ("outw %1, %0"
       :
       : "Nd" (port),
         "a" (data));
}

static inline void port_out_u32 (u16 port, u32 data)
{
  asm ("outl %1, %0"
       :
       : "Nd" (port),
         "a" (data));
}

static inline u8 port_in_u8 (u16 port)
{
  u8 return_value;

  asm volatile ("inb %1, %0"
                : "=a" (return_value)
                : "Nd" (port));

  return return_value;
}

static inline u16 port_in_u16 (u16 port)
{
  u16 return_value;

  asm volatile ("inw %1, %0"
                : "=a" (return_value)
                : "Nd" (port));

  return return_value;
}

static inline u32 port_in_u32 (u16 port)
{
  u32 return_value;

  asm volatile ("inl %1, %0"
                : "=a" (return_value)
                : "Nd" (port));

  return return_value;
}

/* String operations. */

static inline void port_out_u8_string (u16 port, u8 *data, u32 length)
{
  asm volatile
  ("\
    cld
    rep
    outsb
   "
   :
   : "c" (length),
     "S" (data),
     "d" (port));
}

static inline void port_out_u32_string (u16 port, u32 *data, u32 length)
{
  asm volatile 
  ("\
    cld
    rep
    outsl
   "
   :
   : "c" (length),
     "S" (data),
     "d" (port));

}

static inline void port_in_u32_string (u16 port, u32 *data, u32 length)
{
  asm volatile 
  ("\
    cld
    rep
    insl
   "
   :
   : "c" (length),
     "D" (data),
     "d" (port));

}

#endif /* !__STORM_IA32_PORT_H__ */
