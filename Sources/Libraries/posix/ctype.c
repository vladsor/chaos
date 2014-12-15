#include <enviroment.h>

#include <ctype.h>

#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#include <debug/macros.h>


__const unsigned short int *__ctype_b = NULL;	/* Characteristics.  */
__const __int32_t *__ctype_tolower = NULL; /* Case conversions.  */
__const __int32_t *__ctype_toupper = NULL; /* Case conversions.  */


int tolower (int __c)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);

    return -1;
}

int toupper (int __c)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);

    return -1;
}

