/* Abstract: String generic functions. */
/* Author: Vladimir Sorokin */

/* Copyright 2000 chaos development. */

#include <enviroment.h>
#include "string.h"

#ifndef HAVE_ARCHITECTURE_WSTRING_COPY
wchar_t * wstring_copy (wchar_t *destination, const wchar_t *source)
{
    wchar_t *result_string = destination;

    while ((*destination++ = *source++) != L'\0')
    {
        /* nothing */
    }
    
    return result_string;
}
#endif

#ifndef HAVE_ARCHITECTURE_WSTRING_COPY_MAX
wchar_t * wstring_copy_max (wchar_t *destination, const wchar_t *source, 
    unsigned int count)
{
    wchar_t *result_string = destination;

    while ((count-- != 0) && (*destination++ = *source++) != L'\0')
    {
        if (count == 0) 
        {
            (*destination) = L'\0';
            break;
        }
    }
  
    return result_string;
}
#endif

#ifndef HAVE_ARCHITECTURE_WSTRING_APPEND
wchar_t * wstring_append (wchar_t *destination, const wchar_t *source)
{
    wchar_t *result = destination;

    while (*destination != L'\0')
    {
        /* nothing */
    }
  
    while ((*destination++ = *source++) != L'\0')
    {
        /* nothing */  
    }
  
    return result;
}
#endif

#ifndef HAVE_ARCHITECTURE_WSTRING_APPEND_MAX
wchar_t * wstring_append_max (wchar_t *destination, const wchar_t *source,
    unsigned int count)
{
    wchar_t *result = destination;

    while (*destination++ != L'\0')
    {
        /* nothing */
    }  
      
    while ((count-- != 0) && (*destination++ = *source++) != L'\0') 
    {
        if (count == 0) 
        {
            (*destination) = L'\0';
            break;
        }
    }
  
    return result;
}
#endif

#ifndef HAVE_ARCHITECTURE_WSTRING_COMPARE
wchar_t wstring_compare (const wchar_t *cs, const wchar_t *ct)
{
    register wchar_t result;

    while (TRUE) 
    {
        if ((result = *cs - *ct++) != 0 || !*cs++)
        {
            break;
        }
    }

    return result;
}
#endif

#ifndef HAVE_ARCHITECTURE_WSTRING_COMPARE_MAX
wchar_t wstring_compare_max (const wchar_t *cs, const wchar_t *ct, 
    unsigned int count)
{
    register wchar_t result = L'\0';

    for (; count != 0; count--) 
    {
        if ((result = *cs - *ct++) != 0 || !*cs++)
        {
            break;
        }
    }
  
    return result;
}
#endif

#ifndef HAVE_ARCHITECTURE_WSTRING_LENGTH
unsigned int wstring_length (const wchar_t *string)
{
    const wchar_t *string_counter;

    for (string_counter = string; (*string_counter) != L'\0'; ++string_counter)
    {
        /* nothing */
    }

    return string_counter - string;
}
#endif

#ifndef HAVE_ARCHITECTURE_WSTRING_LENGTH_MAX
unsigned int wstring_length_max (const wchar_t *string, unsigned int count)
{
    const wchar_t *string_counter;

    for (string_counter = string; count-- && (*string_counter) != L'\0'; 
        ++string_counter)
    {
        /* nothing */  
    }

    return string_counter - string;
}
#endif

#ifndef HAVE_ARCHITECTURE_WSTRING_FIND_FIRST_CHAR
wchar_t * wstring_find_first_char (const wchar_t *string, wchar_t character)
{
    for (; (*string) != character; ++string)
    {
        if ((*string) == L'\0')
        {
            return NULL;
        }
    }
    
    return (wchar_t *) string;
}
#endif

#ifndef HAVE_ARCHITECTURE_WSTRING_FIND_LAST_CHAR
wchar_t * wstring_find_last_char (const wchar_t *string, wchar_t character)
{
    const wchar_t *pointer = string + wstring_length (string);
    
    do 
    {
        if ((*pointer) == character)
        {
            return (wchar_t *) pointer;
        }
    } while (--pointer >= string);

    return NULL;
}
#endif

#ifndef HAVE_ARCHITECTURE_WSTRING_FIND_SUBSTRING
wchar_t * wstring_find_substring (const wchar_t *string, 
    const wchar_t *substring)
{
    unsigned int length_string;
    unsigned int length_substring;

    length_substring = wstring_length (substring);

    if (length_substring == 0)
    {
        return (wchar_t *) string;
    }
  
    length_string = wstring_length (string);

    while (length_string >= length_substring) 
    {
        if (memory_compare ((void *) string, (void *) substring, 
            length_substring))
        {
            return (wchar_t *) string;
        }

        string++;
        length_string--;
    }

    return NULL;
}
#endif

#ifndef HAVE_ARCHITECTURE_WSTRING_COMPARE_TEMPLATE
bool wstring_compare_template (wchar_t *s1, wchar_t *s2)
{
    while ((*s2 == L'*') || (*s2 == L'?') || ((*s1) == (*s2)))
    {
        if ((*s1)==0 && (*s2)==0)
        {
            return TRUE;
        }
        
        if(*s2=='*')
        {
            s2++;
            
            while (*s1)
            {
                if (wstring_compare_template (s1, s2)) 
                {
                    return TRUE;
                }
                else 
                {
                    s1++;
                }
            }
        }
        else
        {
            s1++;
            s2++;
        }
    }
   
    if ((*s2) == L'.')
    {
        for (;((*s2)==L'.')||((*s2)==L'*')||((*s2)==L'?');s2++) 
        {
        }
    }
    
    if ((*s1)==0 && (*s2)==0)
    {
        return TRUE;
    }
    
    return FALSE;
}
#endif

