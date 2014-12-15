/* $Id: sound.h,v 1.1 2001/02/10 22:58:06 jojo Exp $ */
/* Abstract: sound server IPC message types. */
/* Author: Erik Moren <nemo@chaosdev.org> */

/* Copyright 2000 chaos development */

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

#ifndef __LIBRARY_IPC_SOUND_H__
#define __LIBRARY_IPC_SOUND_H__

/* Message types. */

enum
{
  IPC_SOUND_REGISTER,
  IPC_SOUND_UNREGISTER,
  IPC_SOUND_CONFIGURE_PLAYMODE,
  IPC_SOUND_PLAY_SAMPLE,
  IPC_SOUND_PLAY_STREAM,
  IPC_SOUND_STOP
};

#endif /* !__LIBRARY_IPC_SOUND_H__ */
