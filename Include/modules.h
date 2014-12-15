#ifndef __STORM_H__
#define __STORM_H__

#include "Storm/register.h"

#include "Classes/kernel.h"

#include "Modules/debug.h"

#include "../configuration.h"

extern return_t module_start (int argc, char *argv[]);
extern return_t module_stop (void);

#include "Modules/namespace.h"

#if defined (SUBSYSTEM_CPU)
#    include "Modules/cpu.h"
#endif

#if defined (SUBSYSTEM_EXCEPTION)
//#    include "Storm/exception.h"
#endif

#if defined (SUBSYSTEM_PHYSICAL_MEMORY)
//#    include "Storm/physical_memory.h"
#endif

#if defined (SUBSYSTEM_PHYSICAL_MEMORY) && defined (SUBSYSTEM_VIRTUAL_MEMORY)
//#    include "Storm/virtual_memory.h"
#endif

#if defined (SUBSYSTEM_PHYSICAL_MEMORY) && defined (SUBSYSTEM_GLOBAL_MEMORY)
//#    include "Storm/global_memory.h"
#endif

//#define SUBSYSTEM_USER_MEMORY
#if defined (SUBSYSTEM_MEMORY)
#    include "Modules/memory.h"
#endif

#if defined (SUBSYSTEM_IO_PORT)
#    include "Modules/io_port.h"
#endif

#if defined (SUBSYSTEM_DMA)
#    include "Modules/dma.h"
#endif

#if defined (SUBSYSTEM_IRQ)
#    include "Modules/irq.h"
#endif

#if defined (SUBSYSTEM_IRQ) && defined (SUBSYSTEM_TIMER)
#    include "Modules/timer.h"
#endif

#if defined (SUBSYSTEM_THREAD)
#    include "Modules/thread.h"
#endif

#endif /* !__STORM_H__ */

