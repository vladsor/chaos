#include <enviroment.h>

#include <fcntl.h>
#include <errno.h>

#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>


/* Do the file control operation described by CMD on FD.
   The remaining arguments are interpreted depending on CMD.  */
int fcntl (int __fd, int __cmd, ...)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%i, %i)\n",
        __FILE__, __FUNCTION__, __fd, __cmd);

    switch (__cmd)
    {
        case F_DUPFD:
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
                "Duplicate file descriptor.\n");
            break;
        }
        
        case F_GETFD:
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
                "Get file descriptor flags.\n");
            break;
        }
        
        case F_SETFD:
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
                "Set file descriptor flags.\n");
            break;
        }
        
        case F_GETFL:
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
                "Get file status flags.\n");
            break;
        }
        
        case F_SETFL:
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
                "Set file status flags.\n");
            break;
        }
        
        default:
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
                "Unknown command.\n");
        }
    }
        
    return -1;
}

/* Open FILE and return a new file descriptor for it, or -1 on error.
   OFLAG determines the type of access used.  If O_CREAT is on OFLAG,
   the third argument is taken as a `mode_t', the mode of the created file.  */
int open (__const char *__file, int __oflag, ...)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%s, %i)\n",
        __FILE__, __FUNCTION__, __file, __oflag);
    
    errno = ENOENT;        
        
    return -1;
}

