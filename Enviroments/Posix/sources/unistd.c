#include <enviroment.h>

#include <unistd.h>

#include <Interfaces/input_stream.h>
#include <Interfaces/output_stream.h>

//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

char **environ = (char *[]){0};
extern handle_t file_handles[100];
extern int last_fileno;

/* Values for the second argument to access.
   These may be OR'd together.  */
//#define	R_OK	4		/* Test for read permission.  */
//#define	W_OK	2		/* Test for write permission.  */
//#define	X_OK	1		/* Test for execute permission.  */
//#define	F_OK	0		/* Test for existence.  */

/* Test for access to NAME using the real UID and real GID.  */
int access (__const char *__name, int __type)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);
        
    return -1;
}

/* Schedule an alarm.  In SECONDS seconds, the process will get a SIGALRM.
   If SECONDS is zero, any currently scheduled alarm will be cancelled.
   The function returns the number of seconds remaining until the last
   alarm scheduled would have signaled, or zero if there wasn't one.
   There is no return value to indicate an error, but you can set `errno'
   to 0 and check its value after calling `alarm', and this might tell you.
   The signal may come late due to processor scheduling.  */
unsigned int alarm (unsigned int __seconds)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);
        
    return -1;
}

/* Change the process's working directory to PATH.  */
int chdir (__const char *__path)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p)\n",
        __FILE__, __FUNCTION__, __path);
    
    return -1;
}

/* Close the file descriptor FD.  */
int close (int __fd)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%i)\n",
        __FILE__, __FUNCTION__, __fd);

    return -1;
}

/* Read NBYTES into BUF from FD.  Return the
   number read, -1 for errors or 0 for EOF.  */
ssize_t read (int __fd, void *__buf, size_t __nbytes)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%i, %p, %u)\n",
        __FILE__, __FUNCTION__, __fd, __buf, __nbytes);

    input_stream$read (&file_handles[__fd], __buf, __nbytes);
        
    return __nbytes;
}

/* Write N bytes of BUF to FD.  Return the number written, or -1.  */
ssize_t write (int __fd, __const void *__buf, size_t __n)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%i, %p, %u)\n",
        __FILE__, __FUNCTION__, __fd, __buf, __n);

    output_stream$write (&file_handles[__fd], __buf, __n);
        
    return __n;
}

/* Get the value of the string-valued system variable NAME.  */
size_t confstr (int __name, char *__buf, size_t __len)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%i, %p, %u)\n",
        __FILE__, __FUNCTION__, __name, __buf, __len);

    return 0;
}

/* Duplicate FD, returning a new file descriptor on the same file.  */
int dup (int __fd)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%i)\n",
        __FILE__, __FUNCTION__, __fd);

    register_handle_clone (&file_handles[__fd], &file_handles[last_fileno], 1);

    last_fileno++;

    return last_fileno - 1;
}

/* Duplicate FD to FD2, closing FD2 and making it open on the same file.  */
int dup2 (int __fd, int __fd2)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%i, %i)\n",
        __FILE__, __FUNCTION__, __fd, __fd2);

    register_handle_clone (&file_handles[__fd], &file_handles[__fd2], 1);

    return __fd2;
}

/* Replace the current process, executing PATH with arguments ARGV and
   environment ENVP.  ARGV and ENVP are terminated by NULL pointers.  */
int execve (__const char *__path, char *__const __argv[],
		   char *__const __envp[])
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);
        
    return -1;
}

/* Terminate program execution with the low-order 8 bits of STATUS.  */
void _exit (int __status)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%i)\n",
        __FILE__, __FUNCTION__, __status);

    while (1);
}

void exit (int __status)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%i)\n",
        __FILE__, __FUNCTION__, __status);

    while (1);
}


/* Clone the calling process, creating an exact copy.
   Return -1 for errors, 0 to the new process,
   and the process ID of the new process to the old process.  */
__pid_t fork (void)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);

    return -1;
}

/* Get the pathname of the current working directory,
   and put it in SIZE bytes of BUF.  Returns NULL if the
   directory couldn't be determined or SIZE was too small.
   If successful, returns BUF.  In GNU, if BUF is NULL,
   an array is allocated with `malloc'; the array is SIZE
   bytes long, unless SIZE == 0, in which case it is as
   big as necessary.  */
char *getcwd (char *__buf, size_t __size)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p, %u)\n",
        __FILE__, __FUNCTION__, __buf, __size);

    return NULL;
}

/* Return the maximum number of file descriptors
   the current process could possibly have.  */
int getdtablesize (void)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);

    return 100;
}

/* Get the real user ID of the calling process.  */
__uid_t getuid (void)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);

    return 0;
}

/* Set the user ID of the calling process to UID.
   If the calling process is the super-user, set the real
   and effective user IDs, and the saved set-user-ID to UID;
   if not, the effective user ID is set to UID.  */
int setuid (__uid_t __uid)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);

    return -1;
}

/* Get the effective user ID of the calling process.  */
__uid_t geteuid (void)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);

    return 0;
}

/* Get the real group ID of the calling process.  */
__gid_t getgid (void)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);

    return 0;
}

/* Set the group ID of the calling process to GID.
   If the calling process is the super-user, set the real
   and effective group IDs, and the saved set-group-ID to GID;
   if not, the effective group ID is set to GID.  */
int setgid (__gid_t __gid)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);

    return -1;
}

/* Get the effective group ID of the calling process.  */
__gid_t getegid (void)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);

    return 0;
}

/* If SIZE is zero, return the number of supplementary groups
   the calling process is in.  Otherwise, fill in the group IDs
   of its supplementary groups in LIST and return the number written.  */
int getgroups (int __size, __gid_t __list[])
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);

    return -1;
}

/* Put the name of the current host in no more than LEN bytes of NAME.
   The result is null-terminated if LEN is large enough for the full
   name and the terminator.  */
int gethostname (char *__name, size_t __len)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p, %u)\n",
        __FILE__, __FUNCTION__, __name, __len);

    return -1;
}

/* Get the process group ID of the calling process.
   This function is different on old BSD. */
__pid_t getpgrp (void)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);

    return 0;
}

/* Get the process ID of the calling process.  */
__pid_t getpid (void)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);

    return 0;
}

/* Get the process ID of the calling process's parent.  */
__pid_t getppid (void)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);

    return -1;
}

/* Return 1 if FD is a valid descriptor associated
   with a terminal, zero if not.  */
int isatty (int __fd)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%i)\n",
        __FILE__, __FUNCTION__, __fd);

    return -1;
}

/* Move FD's file position to OFFSET bytes from the
   beginning of the file (if WHENCE is SEEK_SET),
   the current position (if WHENCE is SEEK_CUR),
   or the end of the file (if WHENCE is SEEK_END).
   Return the new file position.  */
__off_t lseek (int __fd, __off_t __offset, int __whence)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);

    return -1;
}

/* Create a one-way communication channel (pipe).
   If successful, two file descriptors are stored in PIPEDES;
   bytes written on PIPEDES[1] can be read from PIPEDES[0].
   Returns 0 if successful, -1 if not.  */
int pipe (int __pipedes[2])
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);

    return -1;
}

/* Set the process group ID of the process matching PID to PGID.
   If PID is zero, the current process's process group ID is set.
   If PGID is zero, the process ID of the process is used.  */
int setpgid (__pid_t __pid, __pid_t __pgid)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);

    return -1;
}


/* Return the foreground process group ID of FD.  */
__pid_t tcgetpgrp (int __fd)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);

    return -1;
}

/* Set the foreground process group ID of FD set PGRP_ID.  */
int tcsetpgrp (int __fd, __pid_t __pgrp_id)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%i, %u)\n",
        __FILE__, __FUNCTION__, __fd, __pgrp_id);

    return -1;
}

/* Remove the link NAME.  */
int unlink (__const char *__name)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);

    return -1;
}

