/* $Id: us.h,v 1.2 2001/02/10 21:25:08 jojo Exp $ */
/* Abstract: A russian keyboard translation map for chaos. */
/* Author: Vladimir Sorokin */

/* Copyright 1998-2000 chaos development. */

#ifndef __RUSSIAN_H__
#define __RUSSIAN_H__

const char *russian_keyboard_map[] =
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

const char *russian_keyboard_map_shift[] =
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

const char *russian_keyboard_map_altgr[] =
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
