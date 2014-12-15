#include <enviroment.h>
#include <list.h>

#include "../Include/process.h"

#define DEBUG_MODULE_NAME "Process"

//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

#define THREAD_NEW_EFLAGS (CPU_FLAG_INTERRUPT_ENABLE | CPU_FLAG_ADJUST | \
                           CPU_FLAG_PARITY | CPU_FLAG_SET)

void tss_create (tss_t *tss, page_directory_t *page_directory,
    uint32_t instruction_pointer, uint32_t stack_pointer)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
         "%s: %s (%p, %p, %p, %p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        tss, page_directory, instruction_pointer, stack_pointer);

    memory_set_uint8 ((uint8_t *) tss, 0, sizeof (tss_t));
    
    tss->cr3 = (uint32_t) page_directory;
    tss->eip = instruction_pointer;

    /* We put a 'magic cookie' in the general purpose registers to
       easify debugging. Also, it makes it possible for programs to
       detect if they're running under storm very easily. ;-) */

    tss->eax = tss->ebx = tss->ecx = tss->edx = 0xC0CAC01A;

    /* Fill up the segment registers. */

    tss->cs = SELECTOR_KERNEL_CODE;
//    tss->cs = SELECTOR_PROCESS_CODE;
  
    tss->ds = SELECTOR_PROCESS_DATA;
    tss->es = SELECTOR_PROCESS_DATA;
    tss->fs = SELECTOR_PROCESS_DATA;
    tss->gs = SELECTOR_PROCESS_DATA;

    tss->ss = SELECTOR_KERNEL_DATA;
//    tss->ss = SELECTOR_PROCESS_DATA;

    /* Allocate a PL3 stack. */

    tss->eflags = THREAD_NEW_EFLAGS;
    tss->esp = stack_pointer;
//  process_cpu_task->esp = BASE_PROCESS_STACK + SIZE_PAGE;

    /* Allocate a PL0 stack. */

    tss->ss0 = SELECTOR_KERNEL_DATA;
//    tss->esp0 = BASE_PROCESS_STACK + SIZE_PAGE;
    tss->esp0 = stack_pointer;

  /* Set up an I/O map with no size for now. It will be resized when
     the process registers and/or deregisters ports. */

    tss->iomap_base = (uint8_t *) tss->iomap - (uint8_t *) tss;
    tss->iomap_size = 0;
}
