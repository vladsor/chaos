#ifndef __STORM_H__
#define __STORM_H__

#include "../../Sources/configuration.h"

#include "defines.h"
#include "limits.h"

extern uint8_t kernel_stack[];

extern void main_bootup (int argument_count, char *arguments[]);

#if defined (SUBSYSTEM_SYSTEM_DEBUG)
#   include "Common/debug.h"
#   include "System/debug.h"
#endif

#if defined (SUBSYSTEM_CPU)
#   include "Common/cpu.h"
#   include "System/cpu.h"
#endif

#if defined (SUBSYSTEM_EXCEPTION)
#   include "Common/exception.h"
#   include "System/exception.h"
#endif

#if defined (SUBSYSTEM_PHYSICAL_MEMORY)
#   include "System/physical_memory.h"
#endif

#if defined (SUBSYSTEM_VIRTUAL_MEMORY)
#   include "System/virtual_memory.h"
#endif

#if defined (SUBSYSTEM_IO_PORT)
#   include "System/io_port.h"
#endif

#if defined (SUBSYSTEM_DMA)
#   include "Common/dma.h"
#   include "System/dma.h"
#endif

#if defined (SUBSYSTEM_IRQ)
#   include "Common/irq.h"
#   include "System/irq.h"
#endif

#if defined (SUBSYSTEM_CLOCK)
#   include "System/clock.h"
#endif

#if defined (SUBSYSTEM_TIMER)
#   include "Common/timer.h"
#   include "System/timer.h"
#endif

#if defined (SUBSYSTEM_TASK_STATE)
#   include "System/task_state.h"
#endif

#if defined (SUBSYSTEM_ELF)
#   include "System/elf.h"
#endif

#if defined (SUBSYSTEM_SYSTEM_CALL)
#   include "System/system_call.h"
#endif

#endif /* !__STORM_H__ */


