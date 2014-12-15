#include <enviroment.h>

#include <string.h>
#include <memory_inlines.h>

//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

/* Copy N bytes of SRC to DEST.  */
void *memcpy (void *__restrict __dest,
		     __const void *__restrict __src, size_t __n)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p, %p, %u)\n",
        __FILE__, __FUNCTION__, __dest, __src, __n);
        
    return memory_copy (__dest, __src, __n);
}

/* Append SRC onto DEST.  */
char *strcat (char *__restrict __dest, __const char *__restrict __src)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p, %p)\n",
        __FILE__, __FUNCTION__);
        
    return string_append (__dest, __src);
}

/* Append no more than N characters from SRC onto DEST.  */
char *strncat (char *__restrict __dest, __const char *__restrict __src,
		      size_t __n)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p, %p, %u)\n",
        __FILE__, __FUNCTION__, __dest, __src, __n);
        
    return string_append_max (__dest, __src, __n);
}

/* Find the first occurrence of C in S.  */
char *strchr (__const char *__s, int __c)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p, %i)\n",
        __FILE__, __FUNCTION__, __s, __c);

    return string_find_first_char (__s, __c);        
}

/* Find the last occurrence of C in S.  */
char *strrchr (__const char *__s, int __c)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p, %i)\n",
        __FILE__, __FUNCTION__, __s, __c);
        
    return string_find_last_char (__s, __c);
}

/* Compare S1 and S2.  */
int strcmp (__const char *__s1, __const char *__s2)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);
        
    return string_compare (__s1, __s2);
}

/* Compare N characters of S1 and S2.  */
int strncmp (__const char *__s1, __const char *__s2, size_t __n)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);

    return string_compare_max (__s1, __s2, __n);
}

/* Copy SRC to DEST.  */
char *strcpy (char *__restrict __dest, __const char *__restrict __src)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p, %p)\n",
        __FILE__, __FUNCTION__, __dest, __src);

    return string_copy (__dest, __src);
}

/* Copy no more than N characters of SRC to DEST.  */
char *strncpy (char *__restrict __dest,
		      __const char *__restrict __src, size_t __n)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p, %p, %u) from %p\n",
        __FILE__, __FUNCTION__, __dest, __src, __n, 
        ((uint32_t *)&__n)[1]);

    return string_copy_max (__dest, __src, __n);
}

/* Return a string describing the meaning of the `errno' code in ERRNUM.  */
char *strerror (int __errnum)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%u)\n",
        __FILE__, __FUNCTION__, __errnum);

    return NULL;
}


/* Return the length of S.  */
size_t strlen (__const char *__s)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p)\n",
        __FILE__, __FUNCTION__, __s);
        
    return string_length (__s);
}


