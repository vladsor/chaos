/* Abstract: String generic functions. */
/* Author: Vladimir Sorokin */

/* Copyright 2000 chaos development. */

#include <enviroment.h>
#include "string.h"

#ifndef HAVE_ARCHITECTURE_STRING_COPY
char * string_copy (char * dest, const char *src)
{
  char *tmp = dest;

  while ((*dest++ = *src++) != '\0')
  {
    /* nothing */
  }
  return tmp;
}
#endif

#ifndef HAVE_ARCHITECTURE_STRING_COPY_MAX
char * string_copy_max (char * dest, const char *src, unsigned int count)
{
  char *tmp = dest;

  while ((count-- != 0) && (*dest++ = *src++) != '\0')
  {
    /* nothing */
  }
  return tmp;
}
#endif

#ifndef HAVE_ARCHITECTURE_STRING_APPEND
char * string_append (char *destination, const char *source)
{
  char *tmp = destination;

  while (*destination != 0)
  {
    destination++;
  }
  
  while ((*destination++ = *source++) != '\0')
  {
    /* nothing */  
  }
  
  return tmp;
}
#endif

#ifndef HAVE_ARCHITECTURE_STRING_APPEND_MAX
char * string_append_max (char *destination, const char *source,
  unsigned int count)
{
  char *tmp = destination;

  if (count != 0)
  {
    while (*destination != 0)
    {
      destination++;
    }  
      
    while ((*destination++ = *source++)) 
    {
      if (--count == 0) 
      {
        *destination = '\0';
        break;
      }
    }
  }
  
  return tmp;
}
#endif

#ifndef HAVE_ARCHITECTURE_STRING_COMPARE
int string_compare (const char *cs, const char *ct)
{
  register signed char result;

  while (TRUE) 
  {
    if ((result = *cs - *ct++) != 0 || !*cs++)
    break;
  }

  return result;
}
#endif

#ifndef HAVE_ARCHITECTURE_STRING_COMPARE_MAX
int string_compare_max (const char *cs, const char *ct, unsigned int count)
{
  register signed char result = 0;

  while (count) 
  {
    if ((result = *cs - *ct++) != 0 || !*cs++)
    {
      break;
    }
    count--;
  }
  
  return result;
}
#endif

#ifndef HAVE_ARCHITECTURE_STRING_LENGTH
unsigned int string_length (const char * string)
{
  const char *string_counter;

  for (string_counter = string; *string_counter != '\0'; ++string_counter)
  {
    /* nothing */
  }

  return string_counter - string;
}
#endif

#ifndef HAVE_ARCHITECTURE_STRING_LENGTH_MAX
unsigned int string_length_max (const char *string, unsigned int count)
{
  const char *string_counter;

  for (string_counter = string; count-- && *string_counter != '\0'; 
       ++string_counter)
  {
    /* nothing */  
  }

  return string_counter - string;
}
#endif

#ifndef HAVE_ARCHITECTURE_STRING_I_COMPARE_MAX
int string_i_compare_max (const char *s1, const char *s2, unsigned int length)
{
  unsigned char c1, c2;
  c1 = 0; c2 = 0;

  if (length)
  {
    do 
    {
      c1 = *s1; c2 = *s2;
      s1++; s2++;

      if (!c1)
      {
        break;
      }
      
      if (!c2)
      {
        break;
      }

      if (c1 == c2)
      {
        continue;
      }

      c1 = char_to_lower_case (c1);
      c2 = char_to_lower_case (c2);
      if (c1 != c2)
      {
        break;
      }

    } while (--length);
  }
  return (int) c1 - (int) c2;
}
#endif

#ifndef HAVE_ARCHITECTURE_STRING_FIND_FIRST_CHAR
char * string_find_first_char (const char *string, int character)
{
  for (; *string != (char) character; ++string)
  {
    if (*string == '\0')
    {
      return NULL;
    }
  }
  return (char *) string;
}
#endif

#ifndef HAVE_ARCHITECTURE_STRING_FIND_LAST_CHAR
char * string_find_last_char (const char *string, int character)
{
  const char *pointer = string + string_length (string);
  do 
  {
    if (*pointer == (char) character)
    {
      return (char *) pointer;
    }
  } while (--pointer >= string);

  return NULL;
}
#endif

#ifndef HAVE_ARCHITECTURE_STRING_SPN
unsigned int string_spn (const char *string, const char *accept)
{
  const char *p;
  const char *a;
  unsigned int count = 0;

  for (p = string; *p != '\0'; ++p)
  {
    for (a = accept; *a != '\0'; ++a) 
    {
      if (*p == *a)
      {
        break;
      }
    }
    
    if (*a == '\0')
    {
      return count;
    }
    ++count;
  }

  return count;
}
#endif

#ifndef HAVE_ARCHITECTURE_STRING_SCN
char *string_scn (char *string, char *reject)
{
  char *scan;
  
  while (*string != 0)
  {
    scan = reject;
    while (*scan != 0) 
    {
      if (*string == *scan)
      {
        return string;
      }
      else
      {
        scan++;
      }
    }
    string++;
  }

  return NULL;
}
#endif

#ifndef HAVE_ARCHITECTURE_STRING_PBRK
char * string_pbrk (const char *cs, const char *ct)
{
  const char *sc1, *sc2;

  for (sc1 = cs; *sc1 != '\0'; ++sc1) 
  {
    for( sc2 = ct; *sc2 != '\0'; ++sc2) 
    {
      if (*sc1 == *sc2)
      {
        return (char *) sc1;
      }
    }
  }

  return NULL;
}
#endif

char * ___strtok;

#ifndef HAVE_ARCHITECTURE_STRING_TOK
char * string_tok (char *s, const char *ct)
{
  char *sbegin, *send;

  sbegin  = s ? s : ___strtok;
  if (!sbegin) 
  {
    return NULL;
  }
  
  sbegin += string_spn (sbegin, ct);
  if (*sbegin == '\0') 
  {
    ___strtok = NULL;
    return( NULL );
  }

  send = string_pbrk (sbegin, ct);
  if (send && *send != '\0')
  {
    *send++ = '\0';
  }
  ___strtok = send;
  return (sbegin);
}
#endif

#ifndef HAVE_ARCHITECTURE_STRING_SEP
char * string_sep (char **s, const char *ct)
{
  char *sbegin = *s;
  if (!sbegin)
  {
    return NULL;
  }
        
  sbegin += string_spn (sbegin, ct);
  if (*sbegin == '\0') 
  {
    return NULL;
  }
        
  *s = string_pbrk (sbegin, ct);
  if (*s && **s != '\0')
  {
    *(*s)++ = '\0';
  }
  
  return (sbegin);
}
#endif

#ifndef HAVE_ARCHITECTURE_STRING_FIND_SUBSTRING
char * string_find_substring (const char *string, const char *substring)
{
  unsigned int length_string;
  unsigned int length_substring;

  length_substring = string_length (substring);

  if (length_substring == 0)
  {
    return (char *) string;
  }
  
  length_string = string_length (string);

  while (length_string >= length_substring) 
  {
    if (memory_compare (string, substring, length_substring))
    {
      return (char *) string;
    }

    string++;
    length_string--;
  }

  return NULL;
}
#endif
