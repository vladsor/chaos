#ifndef __STORM_H__
#define __STORM_H__

typedef struct
{
    char *version;
    char *compiler;
    char *compiler_version;
    char *maintainer;
    char *build_date;
    char *build_time;
} storm_info_t;

extern storm_info_t storm_info;

extern void _start (void);
extern int _end;

/**
 * @brief               The kernel starts at 1 MiB. 
 */
#define KERNEL_START    ((address_t) 1 * MIB)

/**
 * @brief               The kernel end.
 */
#define KERNEL_END      ((address_t) &_end)

/**
 * @brief               Size of kernel. 
 */
#define KERNEL_SIZE     (KERNEL_END - KERNEL_START)

#include "../configuration.h"

#if defined (SUBSYSTEM_SYSTEM_DEBUG)
#   include "Storm/debug.h"
#endif

#if defined (SUBSYSTEM_CPU)
#    include "Storm/cpu.h"
#endif

#if defined (SUBSYSTEM_EXCEPTION)
#    include "Storm/exception.h"
#endif

#if defined (SUBSYSTEM_PHYSICAL_MEMORY)
#    include "Storm/physical_memory.h"
#endif

#if defined (SUBSYSTEM_VIRTUAL_MEMORY)
#    include "Storm/virtual_memory.h"
#endif

#if defined (SUBSYSTEM_GLOBAL_MEMORY)
#    include "Storm/global_memory.h"
#endif

//#define SUBSYSTEM_USER_MEMORY
#if defined (SUBSYSTEM_MEMORY)
#    include "Storm/memory.h"
#endif

#if defined (SUBSYSTEM_IO_PORT)
#    include "Storm/io_port.h"
#endif

#if defined (SUBSYSTEM_DMA)
#    include "Storm/dma.h"
#endif

#if defined (SUBSYSTEM_IRQ)
#    include "Storm/irq.h"
#endif

#if defined (SUBSYSTEM_CLOCK)
#    include "Storm/clock.h"
#endif

#if defined (SUBSYSTEM_TIMER)
#    include "Storm/timer.h"
#endif

#if defined (SUBSYSTEM_THREAD)
#    include "Storm/thread.h"
#endif

#if defined (SUBSYSTEM_PROCESS)
#    include "Storm/process.h"
#endif

#if defined (SUBSYSTEM_REGISTER)
#    include "Storm/register.h"
#    include "Storm/namespace.h"
#endif

#if defined (SUBSYSTEM_REPOSITORY)
#    include "repository.h"
#endif

#endif /* !__STORM_H__ */

