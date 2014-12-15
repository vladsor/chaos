#include <enviroment.h>

#include <errno.h>

#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#include <debug/macros.h>

int errno;

/* Function to get address of global `errno' variable.  */
/*
const int *__errno_location (void)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);
        
    return &errno;
}

*/