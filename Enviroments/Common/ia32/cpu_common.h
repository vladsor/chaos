/**
 * @file                ia32/cpu_common.h
 * @brief               CPU lowlevel routines.
 * @author              Per Lundberg <per@chaosdev.org>,
 *                      Vladimir Sorokin
 * @version             1.0
 * @date                1999-2004
 */

/* Copyright 1999-2001 chaos development. */

#ifndef __ENVIROMENT_IA32_CPU_COMMON_H__
#define __ENVIROMENT_IA32_CPU_COMMON_H__

/**
 *  @brief              Save all registers in stack.
 */
static inline void cpu_push_all (void)
{
    asm ("pusha");
}

/**
 *  @brief              Load all registers from stack.
 */
static inline void cpu_pop_all (void)
{
   asm ("popa");
}

/**
 *  @brief              Empty operation.
 */
static inline void cpu_no_operation (void)
{
    asm ("nop");
}

/**
 *  @brief              Get state of ESP register.
 *  @return             State of ESP register.
 */
static inline uint32_t cpu_esp_get (void)
{
    uint32_t return_value;

    asm volatile (
        "movl %%esp, %0"
        : "=a" (return_value));

    return return_value;
}

#endif /* !__ENVIROMENT_IA32_CPU_COMMON_H__ */
