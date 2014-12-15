/* $Id: stat.h,v 1.2 2001/02/10 21:23:06 jojo Exp $ */
/* Abstract: sys/stat.h */
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

#ifndef _SYS_STAT_H
#define _SYS_STAT_H 1

/* Phony... */

struct stat
{
  unsigned int st_dev;
  unsigned int st_ino;
};

#endif /* !_SYS_STAT_H */
