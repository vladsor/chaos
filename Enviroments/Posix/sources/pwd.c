#include <enviroment.h>

#include <pwd.h>

//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

/* Rewind the password-file stream.  */
void setpwent (void)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);
}

/* Close the password-file stream.  */
void endpwent (void)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);
}

/* Read an entry from the password-file stream, opening it if necessary.  */
struct passwd *getpwent (void)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);
        
    return NULL;
}

/* Search for an entry with a matching user ID.  */
struct passwd *getpwuid (__uid_t __uid)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);
        
    return NULL;
}

/* Search for an entry with a matching username.  */
struct passwd *getpwnam (__const char *__name)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);
        
    return NULL;
}


