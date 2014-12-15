#ifndef __STORM_MODULES_H__
#define __STORM_MODULES_H__

#include <Classes/kernel.h>

extern return_t module_start ( int argc, char *argv[], char **envp);
extern return_t module_stop (void);

#include <Kernel/Common/debug.h>

#endif /* !__STORM_MODULES_H__ */

