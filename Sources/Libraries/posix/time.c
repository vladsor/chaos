//#include <common_enviroment.h>

#include <time.h>

//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE
//#include <debug/macros.h>


/* Return a string of the form "Day Mon dd hh:mm:ss yyyy\n"
   that is the representation of TP in this format.  */
char *asctime (__const struct tm *__tp)
{
//    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
//        "%s::%s ()\n",
//        __FILE__, __FUNCTION__);
        
    return NULL;
}

/* Equivalent to `asctime (localtime (timer))'.  */
char *ctime (__const time_t *__timer)
{
//    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
//        "%s::%s ()\n",
//        __FILE__, __FUNCTION__);
        
    return NULL;
}

/* Return the current time and put it in *TIMER if TIMER is not NULL.  */
time_t time (time_t *__timer)
{
//    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
//        "%s::%s ()\n",
//        __FILE__, __FUNCTION__);
        
    return (time_t) -1;
}

