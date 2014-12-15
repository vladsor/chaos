#include <enviroment.h>

#include <signal.h>

//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

__const char *__const sys_siglist[_NSIG];

int kill (__pid_t __pid, int __sig)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);
        
    return -1;
}

int killpg (__pid_t __pgrp, int __sig)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);
        
    return -1;
}

/* Get and/or set the action for signal SIG.  */
int sigaction (int __sig, __const struct sigaction *__restrict __act,
		      struct sigaction *__restrict __oact)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);
        
    return -1;
}

/* Clear all signals from SET.  */
int sigemptyset (sigset_t *__set)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);
        
    return -1;
}

/* Add SIGNO to SET.  */
int sigaddset (sigset_t *__set, int __signo)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);
        
    return -1;
}

/* Remove SIGNO from SET.  */
int sigdelset (sigset_t *__set, int __signo)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);
        
    return -1;
}

/* Get and/or change the set of blocked signals.  */
int sigprocmask (int __how, __const sigset_t *__restrict __set,
			sigset_t *__restrict __oset)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);
        
    return -1;
}



