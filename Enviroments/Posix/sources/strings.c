#include <enviroment.h>
#include <memory_inlines.h>

#include <strings.h>

//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

/* Copy N bytes of SRC to DEST (like memmove, but args reversed).  */
void bcopy (__const void *__src, void *__dest, size_t __n)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p ,%p, %u)\n",
        __FILE__, __FUNCTION__, __src, __dest, __n);

    memory_move (__dest, __src, __n);
}

/* Set N bytes of S to 0.  */
void bzero (void *__s, size_t __n)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p, %u)\n",
        __FILE__, __FUNCTION__, __s, __n);
        
    memory_set_uint8 ((uint8_t *) __s, 0, __n);
}

