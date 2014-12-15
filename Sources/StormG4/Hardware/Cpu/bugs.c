#include <enviroment.h>

#define DEBUG_MODULE_NAME "Cpu"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#include <debug/macros.h>

#include "Include/bugs.h"

void cpu_bugs_search (cpu_info_t *cpu_info)
{
    /* Most 386 processors have a bug where a POPAD can lock the machine even 
       from user space. */
    int res, inp = (int) &res;

    asm volatile (
        "movl $12345678, %%eax\n"
        "movl $0,%%edi\n"
        "pusha\n"
        "popa\n"
        "movl (%%edx, %%edi), %%ecx"
        : 
        "=&a" (res)
        : 
        "d" (inp)
        : 
        "ecx", 
        "edi");

    /* If this fails, it means that any user program may lock the cpu_info 
       hard. Too bad. */
    bug_set (cpu_info, CPU_BUG_POPAD, (res != 12345678));

    /* All current models of Pentium and Pentium with MMX technology CPUs
       have the F0 0F bug, which lets nonpriviledged users lock up the system. 
     */
    if ((cpu_info->cpu_type_id == CPU_TYPE_INTEL_Pentium) && 
        (cpu_info->vendor_id == CPU_VENDOR_INTEL))
    {
        bug_set (cpu_info, CPU_BUG_F0_0F, TRUE);
    }
}

