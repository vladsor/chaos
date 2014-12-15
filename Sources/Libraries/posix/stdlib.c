#include <enviroment.h>

#include <stdlib.h>

//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>
/*
char *getenv (__const char *__name)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);

    return NULL;
}
*/
/* Abort execution and generate a core-dump.  */
void abort (void)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);

    while (1);
}

/* Convert a string to a floating-point number.  */
double atof (__const char *__nptr)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);
        
    return 0.0;
}

/* Convert a string to an integer.  */
int atoi (__const char *__nptr)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);
        
    return 0;
}

/* Convert a string to a long integer.  */
long int atol (__const char *__nptr)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);
        
    return 0;
}

long int __strtol_internal (__const char *__restrict __nptr,
				   char **__restrict __endptr,
				   int __base, int __group)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);
        
    return 0;
}

/* Allocate SIZE bytes of memory.  */
void *malloc (size_t __size)
{
    void *addr = NULL;
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%u)\n",
        __FILE__, __FUNCTION__, __size);

    memory_allocate (&addr, __size);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s addr=%p\n",
        __FILE__, __FUNCTION__, addr);
        
    return addr;
}

/* Re-allocate the previously allocated block
   in PTR, making the new block SIZE bytes long.  */
void *realloc (void *__ptr, size_t __size)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p, %u)\n",
        __FILE__, __FUNCTION__, __ptr, __size);
        
    return __ptr;
}

/* Free a block allocated by `malloc', `realloc' or `calloc'.  */
void free (void *__ptr)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p)\n",
        __FILE__, __FUNCTION__, __ptr);
}

/* Sort NMEMB elements of BASE, of SIZE bytes each,
   using COMPAR to perform the comparisons.  */
void qsort (void *__base, size_t __nmemb, size_t __size,
		   __compar_fn_t __compar)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p, %u, %u, %p)\n",
        __FILE__, __FUNCTION__, __base, __nmemb, __size, __compar);
}



