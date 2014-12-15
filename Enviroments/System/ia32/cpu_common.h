/**
 * @file                cpu_common.h
 * @brief               CPU system lowlevel routines.
 * @author              Per Lundberg <per@chaosdev.org>
 * @author              Vladimir Sorokin
 * @version             1.0
 * @date                1999-2004
 */

#ifndef __SYSTEM_ENVIROMENT_IA32_CPU_COMMON_H__
#define __SYSTEM_ENVIROMENT_IA32_CPU_COMMON_H__

static inline void cpu_interrupt_return (void)
{
  asm ("iret");
}

static inline void cpu_interrupts_disable (void)
{
  asm ("cli");
}

static inline void cpu_interrupts_enable (void)
{
  asm ("sti");
}

#define cpuid(command,val1,val2,val3,val4) \
    asm volatile ("cpuid"                  \
                  :                        \
                  "=a" (val1),             \
                  "=b" (val2),             \
                  "=c" (val3),             \
                  "=d" (val4)              \
                  :                        \
                  "a" (command))

/*
 * Access to machine-specific registers (available on 586 and better only)
 * Note: the rd* operations modify the parameters directly (without using
 * pointer indirection), this allows gcc to optimize better
 */

#define rdmsr(msr,val1,val2)      \
    asm volatile ("rdmsr"         \
                  :               \
                  "=a" (val1),    \
                  "=d" (val2)     \
                  :               \
                  "c" (msr))

#define wrmsr(msr,val1,val2)         \
    asm volatile ("wrmsr"            \
                  : /* no outputs */ \
                  :                  \
                  "c" (msr),         \
                  "a" (val1),        \
                  "d" (val2))

#define rdtsc(low,high)        \
    asm volatile ("rdtsc"      \
                  :            \
                  "=a" (low),  \
                  "=d" (high))

#define rdtscl(low)            \
    asm volatile ("rdtsc"      \
                  :            \
                  "=a" (low)   \
                  :            \
                  :            \
                  "edx")

#define rdtscll(val)                   \
     asm volatile ("rdtsc"             \
                   :                   \
                   "=A" (val))

#define write_tsc(val1,val2) wrmsr (0x10, val1, val2)

#define rdpmc(counter,low,high)        \
     asm volatile ("rdpmc"             \
                   :                   \
                   "=a" (low),         \
                   "=d" (high)         \
                   :                   \
                   "c" (counter))

#endif /* !__SYSTEM_ENVIROMENT_IA32_CPU_COMMON_H__ */
