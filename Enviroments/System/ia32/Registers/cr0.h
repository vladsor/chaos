/**
 * @file                ia32/Registers/cr0.h
 * @brief               Descriptions of CR0 register.
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
 * @defgroup group_system_register_cr0 CR0 register
 *
 * @brief               CR0 register.
 *
 * @{
 */

#ifndef __SYSTEM_ENVIROMENT_IA32_REGISTERS_CR0_H__
#define __SYSTEM_ENVIROMENT_IA32_REGISTERS_CR0_H__

/**
 * @brief               Structure of system register CR0.
 *
 * Contains system control flags that control operating mode and states of the
 * processor.
 */
typedef struct
{
    /**
     * @brief           PE Protection Enable (bit 0 of CR0). Protected mode 
     *                  flag. 
     *
     * Enables protected mode when set; enables real-address mode when clear.
     * This flag does not enable paging directly. It only enables segment-level 
     * protection. To enable paging, both the #PE and #PG flags must be set.
     * Refer to Section 8.8., "Mode Switching" in Chapter 8, Processor
     * Management and Initialization for information using the #PE flag to switch
     * between real and protected mode.
     */
    uint32_t            PE : 1;

    /**
     * @brief           MP Monitor Coprocessor (bit 1 of CR0). 
     *
     * Controls the interaction of the WAIT (or FWAIT) instruction with the
     * @link cpu_register_cr0_t#TS TS flag @endlink. If the MP flag is set, a
     * WAIT instruction generates a @link #EXCEPTION_DEVICE_NOT_AVAILABLE
     * device-not-available exception (#NM) @endlink if the @link
     * cpu_register_cr0_t#TS TS flag @endlink is set. If the #MP flag is clear,
     * the WAIT instruction ignores the setting of the #TS flag. Table 8-2 in
     * Chapter 8, "Processor Management and Initialization" shows the
     * recommended setting of this flag, depending on the Intel Architecture
     * processor and FPU or math coprocessor present in the system. Table 2-1
     * shows the interaction of the #MP, #EM, and #TS flags.
     */
    uint32_t            MP : 1;

    /**
     * @brief           EM Emulation (bit 2 of CR0). 
     *
     * Indicates that the processor does not have an internal or external FPU when 
     * set; indicates an FPU is present when clear. When the EM flag is set, 
     * execution of a floating-point instruction generates a device-not-available 
     * exception (#NM). This flag must be set when the processor does not have an 
     * internal FPU or is not connected to a math coprocessor. If the processor does
     * have an internal FPU, setting this flag would force all floating-point 
     * instructions to be handled by software emulation. Table 8-2 in Chapter 8, 
     * Processor Management and Initialization shows the recommended setting of this
     * flag, depending on the Intel Architecture processor and FPU or math 
     * coprocessor present in the system. Table 2-1 shows the interaction of the #EM,
     * #MP, and #TS flags. Note that the EM flag also affects the execution of the MMX
     * instructions (refer to Table 2-1). When this flag is set, execution of an MMX
     * instruction causes an invalid opcode exception (#UD) to be generated. Thus,
     * if an Intel Architecture processor incorporates MMX technology, the #EM flag 
     * must be set to 0 to enable execution of MMX instructions.
     */
    uint32_t            EM : 1;

    /**
     * @brief           TS Task Switched (bit 3 of CR0).
     *
     * Allows the saving of FPU context on a task switch to be delayed until the FPU
     * is actually accessed by the new task. The processor sets this flag on every 
     * task switch and tests it when interpreting floating-point arithmetic 
     * instructions.    
     *
     * <ul>
     * <li> If the #TS flag is set, a device-not-available exception (#NM) is raised
     * prior to the execution of a floating-point instruction.
     *
     * <li> If the #TS flag and the #MP flag (also in the CR0 register) are both set,
     * an #NM exception is raised prior to the execution of floating-point 
     * instruction or a WAIT/FWAIT instruction.
     * </ul>
     *
     * Table 2-1 shows the actions taken for floating-point, WAIT/FWAIT, MMXT, and
     * Streaming SIMD Extensions based on the settings of the #TS, #EM, and #MP flags.
     * The processor does not automatically save the context of the FPU on a task 
     * switch. Instead it sets the #TS flag, which causes the processor to raise an 
     * #NM exception whenever it encounters a floating-point instruction in the 
     * instruction stream for the new task. The fault handler for the #NM exception
     * can then be used to clear the #TS flag (with the CLTS instruction) and save
     * the context of the FPU. If the task never encounters a floating-point 
     * instruction, the FPU context is never saved.
     */
    uint32_t            TS : 1;

    /**
     * @brief           ET Extension Type (bit 4 of CR0). 
     *
     * Reserved in the P6 family and Pentium R processors. (In the P6 family 
     * processors, this flag is hardcoded to 1.) In the Intel386T and Intel486T 
     * processors, this flag indicates support of Intel 387 DX math coprocessor
     * instructions when set.
     */
    uint32_t            ET : 1;

    /**
     * @brief           NE Numeric Error (bit 5 of CR0). 
     *
     * Enables the native (internal) mechanism for reporting FPU errors when set; 
     * enables the PC-style FPU error reporting mechanism when clear. When the #NE 
     * flag is clear and the IGNNE# input is asserted, FPU errors are ignored. When
     * the #NE flag is clear and the IGNNE# input is deasserted, an unmasked FPU 
     * error causes the processor to assert the FERR# pin to generate an external 
     * interrupt and to stop instruction execution immediately before executing the 
     * next waiting floating-point instruction or WAIT/FWAIT instruction. The FERR# 
     * pin is intended to drive an input to an external interrupt controller (the 
     * FERR# pin emulates the ERROR# pin of the Intel 287 and Intel 387 DX math 
     * coprocessors). The NE flag, IGNNE# pin, and FERR# pin are used with external
     * logic to implement PC-style error reporting. (Refer to "Software Exception 
     * Handling" in Chapter 7, and Appendix D in the Intel Architecture Software 
     * Developer's Manual, Volume 1, for more information about FPU error reporting
     * and for detailed information on when the FERR# pin is asserted, which is
     * implementation dependent.)
     */
    uint32_t            NE : 1;

    /* Unused */
    uint32_t : 10;
    
    /**
     * @brief           WP Write Protect (bit 16 of CR0). 
     *
     * Inhibits supervisor-level procedures from writing into user-level read-only 
     * pages when set; allows supervisor-level procedures to write into user-level 
     * read-only pages when clear. This flag facilitates implementation of the 
     * copy-on-write method of creating a new process (forking) used by operating 
     * systems such as UNIX.
     */
    uint32_t            WP : 1;

    /* Unused */
    uint32_t : 1;

    /**
     * @brief           AM Alignment Mask (bit 18 of CR0). 
     *
     * Enables automatic alignment checking when set; disables alignment checking 
     * when clear. Alignment checking is performed only when the @link
     * cpu_flags_t#alignment_check AM flag @endlink in the @link cpu_flags_t
     * EFLAGS register @endlink is set, the CPL is 3, and the processor is 
     * operating in either protected or virtual-8086 mode.
     */
    uint32_t            AM : 1;

    /* Unused */
    uint32_t : 10;

    /**
     * @brief           NW Not Write-through (bit 29 of CR0). 
     *
     * When the #NW and #CD flags are clear, write-back (for Pentium R and P6 family 
     * processors) or write-through (for Intel486T processors) is enabled for writes
     * that hit the cache and invalidation cycles are enabled. Refer to Table 9-4, 
     * in Chapter 9, Memory Cache Control, for detailed information about the affect
     * of the #NW flag on caching for other settings of the #CD and #NW flags.
     */
    uint32_t            NW : 1;

    /**
     * @brief           CD Cache Disable (bit 30 of CR0). 
     *
     * When the #CD and #NW flags are clear, caching of memory locations for the whole
     * of physical memory in the processor's internal (and external) caches is 
     * enabled. When the CD flag is set, caching is restricted as described in 
     * Table 9-4, in Chapter 9, Memory Cache Control. To prevent the processor from
     * accessing and updating its caches, the #CD flag must be set and the caches 
     * must be invalidated so that no cache hits can occur (refer to Section 9.5.2.,
     * "Preventing Caching", in Chapter 9, Memory Cache Control). Refer to 
     * Section 9.5., "Cache Control", Chapter 9, Memory Cache Control, for a 
     * detailed description of the additional restrictions that can be placed on the
     * caching of selected pages or regions of memory.
     */
    uint32_t            CD : 1;

    /**
     * @brief           PG Paging (bit 31 of CR0).
     *
     * Enables paging when set; disables paging when clear. When paging is disabled,
     * all linear addresses are treated as physical addresses. The #PG flag has no 
     * effect if the #PE flag (bit 0 of register CR0) is not also set; in fact, 
     * setting the PG flag when the PE flag is clear causes a general-protection 
     * exception (#GP) to be generated. Refer to Section 3.6., "Paging (Virtual 
     * Memory)" in Chapter 3, Protected-Mode Memory Management for a detailed 
     * description of the processor's paging mechanism.
     */
    uint32_t            PG : 1;

} cpu_register_cr0_t PACKED;


/* CR0 bits. */

/**
 * @brief               PE Protection Enable (bit 0 of CR0). Protected mode 
 *                      flag. 
 *
 * @sa cpu_register_cr0_t#PE
 */
#define CPU_CR0_PE      (BIT_VALUE (0))

/**
 * @brief               MP Monitor Coprocessor (bit 1 of CR0). 
 *
 * @sa cpu_register_cr0_t#MP
 */
#define CPU_CR0_MP      (BIT_VALUE (1))

/**
 * @brief               EM Emulation (bit 2 of CR0). 
 *
 * @sa cpu_register_cr0_t#EM
 */
#define CPU_CR0_EM      (BIT_VALUE (2))

/**
 * @brief               TS Task Switched (bit 3 of CR0).
 *
 * @sa cpu_register_cr0_t#TS
 */
#define CPU_CR0_TS      (BIT_VALUE (3))


/**
 * @brief               ET Extension Type (bit 4 of CR0). 
 *
 * @sa cpu_register_cr0_t#ET
 */
#define CPU_CR0_ET      (BIT_VALUE (4))

/**
 * @brief               NE Numeric Error (bit 5 of CR0). 
 *
 * @sa cpu_register_cr0_t#NE
 */
#define CPU_CR0_NE      (BIT_VALUE (5))

/**
 * @brief               WP Write Protect (bit 16 of CR0). 
 *
 * @sa cpu_register_cr0_t#WP
 */
#define CPU_CR0_WP      (BIT_VALUE (16))

/**
 * @brief               AM Alignment Mask (bit 18 of CR0). 
 *
 * @sa cpu_register_cr0_t#AM
 */
#define CPU_CR0_AM      (BIT_VALUE (18))

/**
 * @brief               NW Not Write-through (bit 29 of CR0). 
 *
 * @sa cpu_register_cr0_t#NW
 */
#define CPU_CR0_NW      (BIT_VALUE (29))

/**
 * @brief               CD Cache Disable (bit 30 of CR0). 
 *
 * @sa cpu_register_cr0_t#CD
 */
#define CPU_CR0_CD      (BIT_VALUE (30))

/**
 * @brief               PG Paging (bit 31 of CR0). Paging enabled.
 *
 * @sa cpu_register_cr0_t#PG
 */
#define CPU_CR0_PG      (BIT_VALUE (31))

#define cpu_cr0_save(save_cr0)           \
    asm volatile ("movl %%cr0, %0"       \
                  :                      \
                  "=r" (save_cr0))

#define cpu_cr0_load(load_cr0)           \
    asm volatile ("movl %0, %%cr0"       \
                  : /* no output */      \
                  :                      \
                  "r" (load_cr0))

#define cpu_cr0_enable(enable_cr0)       \
{                                        \
    register uint32_t temp_cr0;          \
    asm volatile ("movl %%cr0, %0\n"     \
                  "orl %1, %0\n"         \
                  "movl %0, %%cr0"       \
                  :                      \
                  "=&r" (temp_cr0)       \
                  :                      \
                  "g" (enable_cr0));     \
}

static inline void cpu_cr0_disable (uint32_t mask_cr0)
{
    register uint32_t temp_cr0;
    
    asm volatile (
        "movl %%cr0, %0\n"
        "andl %1, %0\n"      
        "movl %0, %%cr0" 
        :
            "=&r" (temp_cr0)
        :
            "g" (~mask_cr0));
}

#endif /* !__SYSTEM_ENVIROMENT_IA32_REGISTERS_CR0_H__ */

/**
 * }@ // end of group group_system_register_cr0
 */

/**
 * }@ // end of group group_system_registers
 */


