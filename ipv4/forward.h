/* $Id: forward.h,v 1.2 2001/02/10 21:24:37 jojo Exp $ */
/* Abstract: Function prototypes for the packet forwarding code. */
/* Author: Per Lundberg <plundis@chaosdev.org> */

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

#ifndef __FORWARD_H__
#define __FORWARD_H__

#include "config.h"

/* Function prototypes. */

extern void forward_packet (ipv4_ethernet_header_type *ethernet_header, 
                            unsigned int length);

/* Globals. */

extern bool forwarding;

#endif /* !__FORWARD_H__ */
