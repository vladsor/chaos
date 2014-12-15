/* $Id: tag.h,v 1.1.1.1 2000/09/26 19:08:17 plundis Exp $ */
/* Abstract: Tag item management. */
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

#ifndef __STORM_GENERIC_TAG_H__
#define __STORM_GENERIC_TAG_H__

#include <storm/generic/defines.h>
#include <storm/generic/types.h>
#include <storm/tag.h>

extern unsigned int tag_get_length (tag_type *tag);
extern bool tag_masked_compare (tag_type *tag, tag_type *tag_mask);

#endif /* !__STORM_GENERIC_TAG_H__ */
