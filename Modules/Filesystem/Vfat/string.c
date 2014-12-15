#include <enviroment.h>
#include <string.h>

#include "string.h"

#include <debug.h>
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

#if FALSE
/*
 * FUNCTION: Initialize a string for use with a long file name
 */
void vfat_initstr (uint8_t *wstr, uint32_t wsize)
{
  uint32_t i;
  uint8_t nc = 0;
  for(i=0; i<wsize; i++)
  {
    *wstr=nc;
    wstr++;
  }
  wstr=wstr-wsize;
}

/*
 * FUNCTION: Append a string for use with a long file name
 */
uint8_t * vfat_wcsncat (uint8_t *dest, uint8_t *src, uint32_t wstart, uint32_t wcount)
{
  uint32_t i;

  dest += wstart;
  for(i=0; i<wcount; i++)
  {
    *dest=src[i];
    dest++;
  }

  dest=dest-(wcount+wstart);

  return dest;
}
#endif

uint8_t* wcscpy (uint8_t* str1, const uint8_t* str2)
{
  uint8_t *s = str1;
   while ((*str2)!=0)
     {
	*s = *str2;
	s++;
	str2++;
     }
   *s = 0;

  return str1;
}

uint8_t* wcsncpy (uint8_t *dest, const uint8_t *src, uint32_t count)
{
  uint32_t i;
   
  for (i = 0; i < count; i++)
  {
      dest[i] = src[i];
      if (src[i] == 0)
        {
          return dest;
        }
    }
  dest[i] = 0;

  return dest;
}

uint32_t wcslen (const uint8_t *s)
{
  unsigned int len = 0;

  while (s[len] != 0)
    {
      len++;
    }

  return len;
}

uint8_t *wcscat (uint8_t *dest, const uint8_t *src)
{
  int i, j;

  for (j = 0; dest[j] != 0; j++)
    ;
  for (i = 0; src[i] != 0; i++)
    {
      dest[j + i] = src[i];
    }
  dest[j + i] = 0;

  return dest;
}

#if FALSE
/*
 * FUNCTION: Copy a string for use with long file names
 */
uint8_t * vfat_wcsncpy (uint8_t *dest, uint8_t *src, uint32_t wcount)
{
  uint32_t i;
   
  for (i=0;i<wcount;i++)
  {
    dest[i]=src[i];
    if(!dest[i]) break;
  }

  return(dest);
}

/*
 * FUNCTION: Move the characters in a string to a new position in the same
 *           string
 */
uint8_t * vfat_movstr (uint8_t *src, uint32_t dpos, uint32_t spos, uint32_t len)
{
  uint32_t i;

  if (dpos <= spos)
  {
    for(i=0; i<len; i++)
    {
      src[dpos++]=src[spos++];
    }
  }
  else
  {
    dpos+=len-1;
    spos+=len-1;
    for(i=0; i<len; i++)
    {
      src[dpos--]=src[spos--];
    }
  }

  return(src);
}
#endif

/*
 * FUNCTION: Compare to wide character strings
 * return TRUE if s1==s2
 */
bool wstrcmpi (uint8_t *s1, uint8_t *s2)
{
  while (char_to_lower_case (*s1) == char_to_lower_case (*s2))
  {
    if ((*s1)==0 && (*s2)==0)
    {
      return(TRUE);
    }
	
    s1++;
    s2++;	
  }

  return(FALSE);
}

/*
 * FUNCTION: Compare two wide character strings, s2 with jokers (* or ?)
 * return TRUE if s1 like s2
 */
bool wstrcmpjoki (uint8_t *s1, uint8_t *s2)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	"Vfat: %s (%s, %s)\n",
	__FUNCTION__, s1, s2);

   while ((*s2=='*') || (*s2=='?') || 
          (char_to_lower_case (*s1) == char_to_lower_case (*s2)))
   {
     if ((*s1)==0 && (*s2)==0)
     {
       return TRUE;
     }
     
     if (*s2=='*')
     {
       s2++;
       while (*s1)
        if (wstrcmpjoki(s1,s2)) return TRUE;
         else s1++;
      }
      else
      {
        s1++;
        s2++;
      }
   }
   if ((*s2)=='.')
   {
   	for (;((*s2)=='.')||((*s2)=='*')||((*s2)=='?');s2++) {}
   }

  if ((*s1)==0 && (*s2)==0)
  {
    return TRUE;
  }

  return FALSE;
}

uint8_t * vfat_get_next_path_element (uint8_t *file_name)
{
  if (file_name[0] == '\0')
  {
    return  0;
  }

  while (file_name[0] != '\0' && file_name[0] != '\\')
  {
    file_name++;
  }

  return file_name;
}

void vfat_sub_string (uint8_t *target, const uint8_t *source, uint32_t length)
{
  wcsncpy (target, source, length);
  target [length] = '\0';
}


bool vfat_is_file_name_valid (uint8_t *file_name)
{
  uint8_t *c;

  c = file_name;
  while (*c != 0)
  {
    if (*c == '*' || *c == '?')
    {
      return FALSE;
    }
    c++;
  }

  return TRUE;
}

int wcscmp (const uint8_t *cs, const uint8_t *ct)
{
  while (*cs != '\0' && *ct != '\0' && *cs == *ct)
    {
      cs++;
      ct++;
    }
  return *cs - *ct;
}

uint8_t * wcschr (const uint8_t *str, uint8_t ch)
{
  while ((*str) != ((uint8_t) 0))
    {
      if ((*str) == ch)
        {
          return (uint8_t *) str;
        }
      str++;
    }

  return NULL;
}

uint8_t * wcsrchr (const uint8_t *str, uint8_t ch)
{
  unsigned int len = 0;
  while (str[len] != ((uint8_t) 0))
  {
    len++;
  }
   
  for (; len > 0; len--)
  {
    if (str[len-1]==ch)
    {
      return (uint8_t *) &str[len - 1];
    }
  }

  return NULL;
}
