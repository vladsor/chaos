/* Abstract: Char conversions functions. */
/* Author: Vladimir Sorokin */

/* Copyright 2000 chaos development. */

#include <enviroment.h>
#include "string.h"

bool char_is_alpha_or_number (char c)
{
  return (char_is_alpha (c)) || (char_is_digit (c));
}

bool char_is_alpha (char c)
{
  if ((c >= 'A' && c <= 'z'))
  {
    return TRUE;
  }
  return FALSE;
}

bool char_is_control (char c)
{
  if (c < '0')
  {
    return TRUE;
  } 
  return FALSE;
}

bool char_is_digit (char c)
{
  if ((c >= '0' && c <= '9'))
  {
    return TRUE;
  }
  return FALSE;
}

bool char_is_lower (char c)
{
  if ((c >= 'a' && c <= 'z'))
  {
    return TRUE;
  }
  return FALSE;
}

bool char_is_space (char c)
{
  if ((c >= 0x09 && c <= 0x0d) || (c == 0x20))
  {
    return TRUE;
  }
  return FALSE;
}

bool char_is_upper (char c)
{
  if ((c >= 'A' && c <= 'Z'))
  {
    return TRUE;
  }
  return FALSE;
}

bool char_is_heximal_digit (char c)
{
  if ((c >= '0' && c <= 'F') || (c >= 'a' && c <= 'f'))
  {
       return TRUE;
  }
  return FALSE;
}

char char_to_upper_case (char c)
{
  if (c >= 'a' && c <= 'z')
  {
    return c - 'a' + 'A';
  }

  return c;
}

char char_to_lower_case (char c)
{
  if (c >= 'A' && c <= 'Z')
  {
    return c - 'A' + 'a';
  }
  
  return c;
}

unsigned int char_to_int (char c)
{
  if (c >= '0' && c <= '9')
  {
    return c - '0';
  }
  else if (c >= 'A' && c <= 'F')
  {
    return c - 'A' + 10;
  }
  else if (c >= 'a' && c <= 'f')
  {
    return c - 'a' + 10;
  }
  
  return c;
}

char int_to_char (int c)
{
  if (c >= 0 && c <= 9)
  {
    return c + '0';
  }
  else if (c >= 10 && c <= 15)
  {
    return c + 'A' - 10;
  }
  
  return c;    
}

bool char_is_number (char c, int base)
{
  static char *digits = "0123456789ABCDEF";
  if ((c >= '0' && c <= digits[base-1]))
  {
    return TRUE;
  }
  
  return FALSE;
}
