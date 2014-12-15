#include <enviroment.h>

#include <sys/stat.h>
#include <errno.h>

#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>
#include <exception/macros.h>

#if 0
struct stat
  {
    __dev_t st_dev;			/* Device.  */
    unsigned short int __pad1;

    __ino_t st_ino;			/* File serial number.	*/

    __mode_t st_mode;			/* File mode.  */
    __nlink_t st_nlink;			/* Link count.  */
    __uid_t st_uid;			/* User ID of the file's owner.	*/
    __gid_t st_gid;			/* Group ID of the file's group.*/
    __dev_t st_rdev;			/* Device number, if device.  */
    unsigned short int __pad2;

    __off_t st_size;			/* Size of file, in bytes.  */
    __blksize_t st_blksize;		/* Optimal block size for I/O.  */


    __blkcnt_t st_blocks;		/* Number 512-byte blocks allocated. */
    __time_t st_atime;			/* Time of last access.  */
    unsigned long int __unused1;
    __time_t st_mtime;			/* Time of last modification.  */
    unsigned long int __unused2;
    __time_t st_ctime;			/* Time of last status change.  */
    unsigned long int __unused3;

    unsigned long int __unused4;
    unsigned long int __unused5;
  };
#endif
extern char current_directory[];
static void convert_to_absolute (char *rel, char *abs)
{
    if (string_compare (rel, ".") == 0)
    {
        string_copy (abs, current_directory);
    }
    else
    {
        string_copy (abs, rel);
    }
}

int __fxstat (int __ver, int __fildes, struct stat *__stat_buf)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%i, %i, %p)\n",
        __FILE__, __FUNCTION__, __ver, __fildes, __stat_buf);
        
    return -1;
}

int __xstat (int __ver, __const char *__filename,
		    struct stat *__stat_buf)
{
    handle_t handle;
    char path[256];
        exception_context_t context; 
        exception_info_t info; 
        context.info = &info; 
        context.raised = FALSE; 
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%i, %s, %p)\n",
        __FILE__, __FUNCTION__, __ver, __filename, __stat_buf);

    convert_to_absolute ((char *) __filename, (char *) path);
    memory_set_uint8 ((uint8_t *) __stat_buf, 0, sizeof (__stat_buf));

    {
finaly:

        context.state.irq_cpu_registers.eip = (uint32_t) &&finaly;
        context.state.irq_cpu_registers.esp = cpu_esp_get (); 
        
        if (!context.raised)
        {
            exception_add_handler (thread_get_current (), &context);

            global_namespace_resolve (path, &handle);
        
            __stat_buf->st_dev = 0;//get_repository (handle);
            __stat_buf->st_ino = (uint32_t) handle.context.object_data;
        }
        else
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Exception.\n");
            errno = ENOENT;        
        
            return -1;
        
        }
        
        exception_remove_handler (thread_get_current ());
    }

    return 0;
}

int __lxstat (int __ver, __const char *__filename,
		     struct stat *__stat_buf)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%i, %s, %p)\n",
        __FILE__, __FUNCTION__, __ver, __filename, __stat_buf);

    memory_set_uint8 ((uint8_t *) __stat_buf, 0, sizeof (__stat_buf));
    errno = ENOENT;        
        
    return -1;
}

/* Set the file creation mask of the current process to MASK,
   and return the old creation mask.  */
__mode_t umask (__mode_t __mask)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);
        
    return -1;
}

