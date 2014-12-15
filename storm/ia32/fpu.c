#include <storm/ia32/cpu.h>
#include <storm/ia32/fpu.h>

void fpu_init (void)
{
  u32 cr0 = cpu_get_cr0 ();
  cr0 &= ~(CPU_CR0_EM | CPU_CR0_TS);
  cpu_set_cr0 (cr0);

  asm ("fninit");
}