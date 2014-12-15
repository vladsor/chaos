/**
 * @file                ia32/Registers/cr2.h
 * @brief               Descriptions of CR2 register.
 * @author              Vladimir Sorokin
 * @version             1.0
 * @date                2002-2004
 */

/** 
 * @addtogroup group_system_registers
 *
 * @{
 */

/** 
 * @defgroup group_system_register_cr2 CR2 register
 *
 * @brief               CR2 register.
 *
 * @{
 */

#ifndef __SYSTEM_ENVIROMENT_IA32_REGISTERS_CR2_H__
#define __SYSTEM_ENVIROMENT_IA32_REGISTERS_CR2_H__

/**
 * @brief               Structure of system register CR2.
 *
 * Contains the page-fault linear address (the linear address that caused a 
 * page fault).
 */
typedef struct
{
    /**
     * @brief           Page-fault linear address (the linear address that 
     *                  caused a page fault)
     */
    uint32_t page_fault_linear_address;

} cpu_register_cr2_t PACKED;

#define cpu_cr2_save(save_cr2)           \
    asm volatile ("movl %%cr2, %0"       \
                  :                      \
                  "=a" (save_cr2))

#endif /* !__SYSTEM_ENVIROMENT_IA32_REGISTERS_CR2_H__ */

/**
 * }@ // end of group group_system_register_cr2
 */

/**
 * }@ // end of group group_system_registers
 */


