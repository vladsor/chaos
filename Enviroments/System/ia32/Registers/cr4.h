/**
 * @file                ia32/Registers/cr4.h
 * @brief               Descriptions of CR4 register.
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
 * @defgroup group_system_register_cr4 CR4 register
 *
 * @brief               CR4 register.
 *
 * @{
 */

#ifndef __SYSTEM_ENVIROMENT_IA32_REGISTERS_CR4_H__
#define __SYSTEM_ENVIROMENT_IA32_REGISTERS_CR4_H__

/**
 * @brief               Structure of system register CR4.
 *
 * Contains a group of flags that enable several architectural extensions, as
 * well as indicating the level of OS support for the Streaming SIMD Extensions.
 */
typedef struct
{
    /**
     * @brief           VME Virtual-8086 Mode Extensions (bit 0 of CR4).
     *
     * Enables interrupt- and exception-handling extensions in virtual-8086 mode
     * when set; disables the extensions when clear. Use of the virtual mode
     * extensions can improve the performance of virtual-8086 applications by
     * eliminating the overhead of calling the virtual-8086 monitor to handle
     * interrupts and exceptions that occur while executing an 8086 program and,
     * instead, redirecting the interrupts and exceptions back to the 8086
     * program's handlers. It also provides hardware support for a virtual
     * interrupt flag (VIF) to improve reliability of running 8086 programs in
     * multitasking and multiple-processor environments. Refer to Section 16.3.,
     * "Interrupt and Exception Handling in Virtual-8086 Mode" in Chapter 16,
     * 8086 Emulation for detailed information about the use of this feature.
     */
    uint32_t            VME        : 1;

    /**
     * @brief           PVI Protected-Mode Virtual Interrupts (bit 1 of CR4).
     *
     * Enables hardware support for a virtual interrupt flag (VIF) in protected
     * mode when set; disables the VIF flag in protected mode when clear. Refer
     * to Section 16.4., "Protected-Mode Virtual Interrupts" in Chapter 16,
     * 8086 Emulation for detailed information about the use of this feature.
     */
    uint32_t            PVI        : 1;

    /**
     * @brief           TSD Time Stamp Disable (bit 2 of CR4).
     *
     * Restricts the execution of the RDTSC instruction to procedures running
     * at privilege level 0 when set; allows RDTSC instruction to be executed
     * at any privilege level when clear.
     */
    uint32_t            TSD        : 1;

    /**
     * @brief           DE Debugging Extensions (bit 3 of CR4).
     *
     * References to debug registers DR4 and DR5 cause an undefined opcode
     * (#UD) exception to be generated when set; when clear, processor aliases
     * references to registers DR4 and DR5 for compatibility with software 
     * written to run on earlier Intel Architecture processors. Refer to
     * Section 15.2.2., "Debug Registers DR4 and DR5", in Chapter 15, Debugging
     * and Performance Monitoring, for more information on the function of this
     * flag.
     */
    uint32_t            DE         : 1;

    /**
     * @brief           PSE Page Size Extensions (bit 4 of CR4).
     *
     * Enables 4-MByte pages when set; restricts pages to 4 KBytes when clear.
     * Refer to Section 3.6.1., "Paging Options" in Chapter 3, Protected-Mode
     * Memory Management for more information about the use of this flag.
     */
    uint32_t            PSE        : 1;

    /**
     * @brief           PAE Physical Address Extension (bit 5 of CR4).
     *
     * Enables paging mechanism to reference 36-bit physical addresses when set;
     * restricts physical addresses to 32 bits when clear. Refer to Section
     * 3.8., "Physical Address Extension" in Chapter 3, Protected-Mode Memory
     * Management for more information about the physical address extension.
     */
    uint32_t            PAE        : 1;

    /**
     * @brief           MCE Machine-Check Enable (bit 6 of CR4).
     *
     * Enables the machine-check exception when set; disables the machine-check
     * exception when clear. Refer to Chapter 13, Machine-Check Architecture,
     * for more information about the machine-check exception and machine-check
     * architecture.
     */
    uint32_t            MCE        : 1;

    /**
     * @brief           PGE Page Global Enable (bit 7 of CR4). 
     *
     * (Introduced in the P6 family processors.) Enables the global page feature
     * when set; disables the global page feature when clear. The global page 
     * feature allows frequently used or shared pages to be marked as global to
     * all users (done with the global flag, bit 8, in a page-directory or 
     * page-table entry). Global pages are not flushed from the 
     * translation-lookaside buffer (TLB) on a task switch or a write to 
     * register CR3. In addition, the bit must not be enabled before paging is 
     * enabled via CR0.PG. Program correctness may be affected by reversing this
     * sequence, and processor performance will be impacted. Refer to Section 
     * 3.7., "Translation Lookaside Buffers (TLBs)" in Chapter 3, 
     * Protected-Mode Memory Management for more information on the use of this
     * bit.
     */
    uint32_t            PGE        : 1;
 
    /**
     * @brief           PCE Performance-Monitoring Counter Enable (bit 8 of 
     *                  CR4). 
     *
     * Enables execution of the RDPMC instruction for programs or procedures 
     * running at any protection level when set; RDPMC instruction can be 
     * executed only at protection level 0 when clear.
     */
    uint32_t            PCE        : 1;

    /**
     * @brief           OSFXSR Operating Sytsem FXSAVE/FXRSTOR Support (bit 9 
     *                  of CR4). 
     *
     * The operating system will set this bit if both the CPU and the OS support
     * the use of FXSAVE/FXRSTOR for use during context switches.
     */
    uint32_t            OSFXSR     : 1;

    /**
     * @brief           OSXMMEXCPT Operating System Unmasked Exception Support 
     *                  (bit 10 of CR4). 
     *
     * The operating system will set this bit if it provides support for 
     * unmasked SIMD floating-point exceptions.
     */
    uint32_t            OSXMMEXCPT : 1;

    /* Not used. */
    uint32_t                       : 21;
} cpu_register_cr4_t PACKED;

   /* Enable global page directory entries. */
#define CPU_CR4_PGE (BIT_VALUE (7))

#define cpu_cr4_load(load_cr4)           \
    asm volatile ("movl %0, %%cr4"       \
                  : /* no output */      \
                  :                      \
                  "r" (load_cr4))

#define cpu_cr4_save(save_cr4)           \
    asm volatile ("movl %%cr4, %0"       \
                  :                      \
                  "=a" (save_cr4))

#endif /* !__SYSTEM_ENVIROMENT_IA32_REGISTERS_CR4_H__ */

/**
 * }@ // end of group group_system_register_cr4
 */

/**
 * }@ // end of group group_system_registers
 */



