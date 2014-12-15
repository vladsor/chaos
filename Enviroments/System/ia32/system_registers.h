/**
 * @file                system_registers.h
 * @brief               Descriptions of most significal system registers.
 * @author              Vladimir Sorokin
 * @version             0.1
 * @date                2002-2004
 */

/** 
 * @defgroup group_system_registers System registers
 *
 * @brief               System registers in x86 architecture.
 *
 * @{
 */

#ifndef __SYSTEM_ENVIROMENT_IA32_SYSTEM_REGISTERS_H__
#define __SYSTEM_ENVIROMENT_IA32_SYSTEM_REGISTERS_H__

static inline void cpu_tr_load (uint16_t load_tr)
{
    asm volatile ("ltr %0"
                  : /* no output */
                  :
                  "rm" (load_tr));
}

#define cpu_tr_save(save_tr)             \
    asm volatile ("str %0"               \
                  :                      \
                  "=a" (save_tr))

#define cpu_gdtr_save(save_gdtr)         \
    asm volatile ("sgdt %0"              \
                  :                      \
                  "=a" (save_gdtr))

#define cpu_gdtr_load(load_gdtr)         \
    asm volatile ("lgdtr %0"             \
                  : /* no output */      \
                  :                      \
                  "rm" (load_gdtr))

#define cpu_cs_save(save_cs)             \
    asm volatile ("movl %%cs, %0"        \
                  :                      \
                  "=a" (save_cs))

#endif /* !__SYSTEM_ENVIROMENT_IA32_SYSTEM_REGISTERS_H__ */

/**
 * }@ // end of group group_system_registers
 */

