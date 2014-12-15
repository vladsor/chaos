/* $Id: us.h,v 1.2 2001/02/10 21:25:08 jojo Exp $ */
/* Abstract: A russian keyboard translation map for chaos. */
/* Author: Vladimir Sorokin */

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

#ifndef __RUSSIAN_H__
#define __RUSSIAN_H__

char *russian_keyboard_map[] =
{
  NULL, NULL, "1",  "2",  "3",  "4",  "5",  "6",
  "7",  "8",  "9",  "0",  "-",  "=",  NULL, NULL,
  "й",  "ц",  "у",  "к",  "е",  "н",  "г",  "ш",
  "щ",  "з",  "х",  "ъ",  NULL, NULL, "ф",  "ы",
  "в",  "а",  "п",  "р",  "о",  "л",  "д",  "ж",
  "э",  NULL, NULL, "\\",  "я",  "ч",  "с",  "м",
  "и",  "т",  "ь",  "б",  "ю",  ".",  NULL, "*",
  NULL, " ",  NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, "-",  NULL, NULL, NULL, "+",  NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, "<",  NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL
};

char *russian_keyboard_map_shift[] =
{
  NULL, NULL, "!",  "\"", "№",  ";",  "%",  ":",
  "?",  "*",  "(",  ")",  "_",  "+",  NULL, NULL,
  "Й",  "Ц",  "У",  "К",  "Е",  "Н",  "Г",  "Ш",
  "Щ",  "З",  "Х",  "Ъ",  NULL, NULL, "Ф",  "Ы",
  "В",  "А",  "П",  "Р",  "О",  "Л",  "Д",  "Ж",
  "Э",  NULL, NULL, "|",  "Я",  "Ч",  "С",  "М",
  "И",  "Т",  "Ь",  "Б",  "Ю",  ",",  NULL, "*",
  NULL, " ",  NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, "-",  NULL, NULL, NULL, "+",  NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, ">",  NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL
};

char *russian_keyboard_map_altgr[] =
{
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL
};

#endif /* !__RUSSIAN_H__ */
