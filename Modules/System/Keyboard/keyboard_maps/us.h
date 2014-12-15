/* $chaos: british.h,v 1.2 2002/10/04 19:01:16 per Exp $ */
/* Abstract: A british translation table for chaos. This probably
   needs some fixup before it is usable. */
/* Author: John Hennessy <john@somewhere> */

/* Copyright 2000-2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#ifndef __US_H__
#define __US_H__

const wchar_t us_keyboard_map[] =
{
    L'\0', L'`',  L'1',  L'2',  L'3',  L'4',  L'5',  L'6',
    L'7',  L'8',  L'9',  L'0',  L'-',  L'=',  L'\\', L'\0',
    L'q',  L'w',  L'e',  L'r',  L't',  L'y',  L'u',  L'i',
    L'o',  L'p',  L'[',  L']',  L'\0', L'\0', L'a',  L's',
    L'd',  L'f',  L'g',  L'h',  L'j',  L'k',  L'l',  L';',
    L'\0', L'#',  L'\0', L'\"', L'z',  L'x',  L'c',  L'v',
    L'b',  L'n',  L'm',  L',',  L'.',  L'/',  L'\0', L'*',
    
    L'\0', L'\0', L'\0', L'\0', L'\0', L'\0', L'\0', L'\0',
    L'\0', L'\0', L'\0', L'\0', L'\0', L'\0', L'\0', L'\0',
    L'\0', L'\0', L'-',  L'\0', L'\0', L'\0', L'+',  L'\0',
    L'\0', L'\0', L'\0', L'\0', L'\0', L'\0', L'<',  L'\0',
    L'\0', L'\0', L'\0', L'\0', L'\0', L'\0', L'\0', L'\0',
    L'\0'
};

const wchar_t us_keyboard_map_shift[] =
{
    L'\0', L'~',  L'!',  L'\"', L'#',  L'$',  L'%',  L'^',
    L'&',  L'*',  L'(',  L')',  L'_',  L'+',  L'|',  L'\0',
    L'Q',  L'W',  L'E',  L'R',  L'T',  L'Y',  L'U',  L'I',
    L'O',  L'P',  L'\0', L'^',  L'\0', L'\0', L'A',  L'S',
    L'D',  L'F',  L'G',  L'H',  L'J',  L'K',  L'L',  L'\0',
    L'\0', L'\0', L'\0', L'*',  L'Z',  L'X',  L'C',  L'V',
    L'B',  L'N',  L'M',  L';',  L':',  L'_',  L'\0', L'*',
  
    L'\0', L' ',  L'\0', L'\0', L'\0', L'\0', L'\0', L'\0',
    L'\0', L'\0', L'\0', L'\0', L'\0', L'\0', L'\0', L'\0',
    L'\0', L'\0', L'-',  L'\0', L'\0', L'\0', L'+',  L'\0',
    L'\0', L'\0', L'\0', L'\0', L'\0', L'\0', L'>',  L'\0',
    L'\0', L'\0', L'\0', L'\0', L'\0', L'\0', L'\0', L'\0',
    L'\0'
};

const wchar_t us_keyboard_map_altgr[] =
{
    L'\0', L'\0', L'\0', L'@',  L'@',  L'$',  L'\0', L'\0',
    L'{',  L'[',  L']',  L'}',  L'\\', L'\0', L'\0', L'\0',
    L'\0', L'\0', L'\0', L'\0', L'\0', L'\0', L'\0', L'\0',
    L'\0', L'\0', L'\0', L'~',  L'\0', L'\0', L'\0', L'\0',
    L'\0', L'\0', L'\0', L'\0', L'\0', L'\0', L'\0', L'\0',
    L'\0', L'\0', L'\0', L'\0', L'\0', L'\0', L'\0', L'\0',
    L'\0', L'\0', L'\0', L'\0', L'\0', L'\0', L'\0', L'\0',
    L'\0', L' ',  L'\0', L'\0', L'\0', L'\0', L'\0', L'\0',
    L'\0', L'\0', L'\0', L'\0', L'\0', L'\0', L'\0', L'\0',
    L'\0', L'\0', L'\0', L'\0', L'\0', L'\0', L'\0', L'\0',
    L'\0', L'\0', L'\0', L'\0', L'\0', L'\0', L'|',  L'\0',
    L'\0', L'\0', L'\0', L'\0', L'\0', L'\0', L'\0', L'\0',
    L'\0'
};

#endif /* !__US_H__ */
