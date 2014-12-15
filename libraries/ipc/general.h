/* $Id: general.h,v 1.2 2001/02/10 21:22:40 jojo Exp $ */
/* Abstract: General IPC messages. */
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

#ifndef __LIBRARY_IPC_GENERAL_H__
#define __LIBRARY_IPC_GENERAL_H__

enum
{
  IPC_GENERAL_ECHO_REQUEST,
  IPC_GENERAL_ECHO_REPLY,
  IPC_GENERAL_IDENTIFY_REQUEST,
  IPC_GENERAL_IDENTIFY_REPLY,
  IPC_GENERAL_CONNECTION_REQUEST,
  IPC_GENERAL_CONNECTION_REPLY,
  IPC_GENERAL_CONNECTION_REFUSED,
  IPC_GENERAL_CONNECTION_CLOSE,
};

#endif /* !__LIBRARY_IPC_GENERAL_H__ */
