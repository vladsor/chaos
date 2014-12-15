/**
 * @file                system_registers.h
 * @brief               Descriptions of most significal system registers.
 * @author              Vladimir Sorokin
 * @version             0.1
 * @date                2002-2004
 */

#ifndef __SYSTEM_ENVIROMENT_IA32_SYSTEM_REGISTERS_H__
#define __SYSTEM_ENVIROMENT_IA32_SYSTEM_REGISTERS_H__

typedef struct
{
    /**
     * @brief           Requested Privilege Level (RPL) (Bits 0 and 1). 
     *
     * Specifies the privilege level of the selector. The privilege level can 
     * range from 0 to 3, with 0 being the most privileged level. Refer to 
     * Section 4.5., "Privilege Levels" in Chapter 4, Protection for a 
     * description of the relationship of the RPL to the CPL of the executing 
     * program (or task) and the descriptor privilege level (DPL) of the
     * descriptor the segment selector points to.
     */
    uint16_t RPL   : 2;

    /**
     * @brief           TI (table indicator) flag (Bit 2).
     *
     * Specifies the descriptor table to use: clearing this flag selects the 
     * GDT; setting this flag selects the current LDT.
     */
    uint16_t TI    : 1;

    /**
     * @brief           Index (Bits 3 through 15). 
     *
     * Selects one of 8192 descriptors in the GDT or LDT. The processor 
     * multiplies the index value by 8 (the number of bytes in a segment 
     * descriptor) and adds the result to the base address of the GDT or LDT 
     * (from the GDTR or LDTR register, respectively).
     */
    uint16_t index : 12;
} selector_t PACKED;

/**
 * @brief               Segment selector.
 */
#define SELECTOR(index,ldt,rpl)           (((index) << 3) | (ldt << 2) | rpl)

#define SELECTOR_GET_DESCRIPTOR_INDEX(selector) ((selector) >> 3)

/**
 * @brief               Structure of system register CR2.
 *
 * Contains system control flags that control operating mode and states of the
 * processor.
 */
typedef struct
{
    /**
     * @brief               PE Protection Enable (bit 0 of CR0). Protected mode 
     *                      flag. 
     *
     * Enables protected mode when set; enables real-address mode when clear. This 
     * flag does not enable paging directly. It only enables segment-level 
     * protection. To enable paging, both the PE and PG flags must be set. Refer to
     * Section 8.8., "Mode Switching" in Chapter 8, Processor Management and 
     * Initialization for information using the PE flag to switch between real and 
     * protected mode.
     */
    uint32_t            PE : 1;

    /**
     * @brief               MP Monitor Coprocessor (bit 1 of CR0). 
     *
     * Controls the interaction of the WAIT (or FWAIT) instruction with the TS flag
     * (bit 3 of CR0). If the MP flag is set, a WAIT instruction generates a 
     * device-not-available exception (#NM) if the TS flag is set. If the MP flag is
     * clear, the WAIT instruction ignores the setting of the TS flag. Table 8-2 in
     * Chapter 8, Processor Management and Initialization shows the recommended 
     * setting of this flag, depending on the Intel Architecture processor and FPU 
     * or math coprocessor present in the system. Table 2-1 shows the interaction of
     * the MP, EM, and TS flags.
     */
    uint32_t            MP : 1;

    /**
     * @brief               EM Emulation (bit 2 of CR0). 
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
     * coprocessor present in the system. Table 2-1 shows the interaction of the EM,
     * MP, and TS flags. Note that the EM flag also affects the execution of the MMX
     * instructions (refer to Table 2-1). When this flag is set, execution of an MMX
     * instruction causes an invalid opcode exception (#UD) to be generated. Thus,
     * if an Intel Architecture processor incorporates MMX technology, the EM flag 
     * must be set to 0 to enable execution of MMX instructions.
     */
    uint32_t            EM : 1;

    /**
     * @brief               TS Task Switched (bit 3 of CR0).
     *
     * Allows the saving of FPU context on a task switch to be delayed until the FPU
     * is actually accessed by the new task. The processor sets this flag on every 
     * task switch and tests it when interpreting floating-point arithmetic 
     * instructions.    
     *
     * <ul>
     * <li> If the TS flag is set, a device-not-available exception (#NM) is raised
     * prior to the execution of a floating-point instruction.
     *
     * <li> If the TS flag and the MP flag (also in the CR0 register) are both set,
     * an #NM exception is raised prior to the execution of floating-point 
     * instruction or a WAIT/FWAIT instruction.
     * </ul>
     *
     * Table 2-1 shows the actions taken for floating-point, WAIT/FWAIT, MMXT, and
     * Streaming SIMD Extensions based on the settings of the TS, EM, and MP flags.
     * The processor does not automatically save the context of the FPU on a task 
     * switch. Instead it sets the TS flag, which causes the processor to raise an 
     * #NM exception whenever it encounters a floating-point instruction in the 
     * instruction stream for the new task. The fault handler for the #NM exception
     * can then be used to clear the TS flag (with the CLTS instruction) and save
     * the context of the FPU. If the task never encounters a floating-point 
     * instruction, the FPU context is never saved.
     */
    uint32_t            TS : 1;

    /**
     * @brief               ET Extension Type (bit 4 of CR0). 
     *
     * Reserved in the P6 family and Pentium R processors. (In the P6 family 
     * processors, this flag is hardcoded to 1.) In the Intel386T and Intel486T 
     * processors, this flag indicates support of Intel 387 DX math coprocessor
     * instructions when set.
     */
    uint32_t            ET : 1;

    /**
     * @brief               NE Numeric Error (bit 5 of CR0). 
     *
     * Enables the native (internal) mechanism for reporting FPU errors when set; 
     * enables the PC-style FPU error reporting mechanism when clear. When the NE 
     * flag is clear and the IGNNE# input is asserted, FPU errors are ignored. When
     * the NE flag is clear and the IGNNE# input is deasserted, an unmasked FPU 
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
     * @brief               WP Write Protect (bit 16 of CR0). 
     *
     * Inhibits supervisor-level procedures from writing into user-level read-only 
     * pages when set; allows supervisor-level procedures to write into user-level 
     * read-only pages when clear. This flag facilitates implementation of the 
     * copy-on-write method of creating a new process (forking) used by operating 
     * systems such as UNIX*.
     */
    uint32_t            WP : 1;

    /* Unused */
    uint32_t : 1;

    /**
     * @brief               AM Alignment Mask (bit 18 of CR0). 
     *
     * Enables automatic alignment checking when set; disables alignment checking 
     * when clear. Alignment checking is performed only when the AM flag is set, the
     * AC flag in the EFLAGS register is set, the CPL is 3, and the processor is 
     * operating in either protected or virtual-8086 mode.
     */
    uint32_t            AM : 1;

    /* Unused */
    uint32_t : 10;

    /**
     * @brief               NW Not Write-through (bit 29 of CR0). 
     *
     * When the NW and CD flags are clear, write-back (for Pentium R and P6 family 
     * processors) or write-through (for Intel486T processors) is enabled for writes
     * that hit the cache and invalidation cycles are enabled. Refer to Table 9-4, 
     * in Chapter 9, Memory Cache Control, for detailed information about the affect
     * of the NW flag on caching for other settings of the CD and NW flags.
     */
    uint32_t            NW : 1;

    /**
     * @brief               CD Cache Disable (bit 30 of CR0). 
     *
     * When the CD and NW flags are clear, caching of memory locations for the whole
     * of physical memory in the processor's internal (and external) caches is 
     * enabled. When the CD flag is set, caching is restricted as described in 
     * Table 9-4, in Chapter 9, Memory Cache Control. To prevent the processor from
     * accessing and updating its caches, the CD flag must be set and the caches 
     * must be invalidated so that no cache hits can occur (refer to Section 9.5.2.,
     * "Preventing Caching", in Chapter 9, Memory Cache Control). Refer to 
     * Section 9.5., "Cache Control", Chapter 9, Memory Cache Control, for a 
     * detailed description of the additional restrictions that can be placed on the
     * caching of selected pages or regions of memory.
     */
    uint32_t            CD : 1;

    /**
     * @brief               PG Paging (bit 31 of CR0). Paging enabled.
     *
     * Enables paging when set; disables paging when clear. When paging is disabled,
     * all linear addresses are treated as physical addresses. The PG flag has no 
     * effect if the PE flag (bit 0 of register CR0) is not also set; in fact, 
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
 * Enables protected mode when set; enables real-address mode when clear. This 
 * flag does not enable paging directly. It only enables segment-level 
 * protection. To enable paging, both the PE and PG flags must be set. Refer to
 * Section 8.8., "Mode Switching" in Chapter 8, Processor Management and 
 * Initialization for information using the PE flag to switch between real and 
 * protected mode.
 */
#define CPU_CR0_PE (BIT_VALUE (0))

/**
 * @brief               MP Monitor Coprocessor (bit 1 of CR0). 
 *
 * Controls the interaction of the WAIT (or FWAIT) instruction with the TS flag
 * (bit 3 of CR0). If the MP flag is set, a WAIT instruction generates a 
 * device-not-available exception (#NM) if the TS flag is set. If the MP flag is
 * clear, the WAIT instruction ignores the setting of the TS flag. Table 8-2 in
 * Chapter 8, Processor Management and Initialization shows the recommended 
 * setting of this flag, depending on the Intel Architecture processor and FPU 
 * or math coprocessor present in the system. Table 2-1 shows the interaction of
 * the MP, EM, and TS flags.
 */
#define CPU_CR0_MP (BIT_VALUE (1))

/**
 * @brief               EM Emulation (bit 2 of CR0). 
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
 * coprocessor present in the system. Table 2-1 shows the interaction of the EM,
 * MP, and TS flags. Note that the EM flag also affects the execution of the MMX
 * instructions (refer to Table 2-1). When this flag is set, execution of an MMX
 * instruction causes an invalid opcode exception (#UD) to be generated. Thus,
 * if an Intel Architecture processor incorporates MMX technology, the EM flag 
 * must be set to 0 to enable execution of MMX instructions.
 */
#define CPU_CR0_EM (BIT_VALUE (2))

/**
 * @brief               TS Task Switched (bit 3 of CR0).
 *
 * Allows the saving of FPU context on a task switch to be delayed until the FPU
 * is actually accessed by the new task. The processor sets this flag on every 
 * task switch and tests it when interpreting floating-point arithmetic 
 * instructions.        
 *
 * <ul>
 * <li> If the TS flag is set, a device-not-available exception (#NM) is raised
 * prior to the execution of a floating-point instruction.
 *
 * <li> If the TS flag and the MP flag (also in the CR0 register) are both set,
 * an #NM exception is raised prior to the execution of floating-point 
 * instruction or a WAIT/FWAIT instruction.
 * </ul>
 *
 * Table 2-1 shows the actions taken for floating-point, WAIT/FWAIT, MMXT, and
 * Streaming SIMD Extensions based on the settings of the TS, EM, and MP flags.
 * The processor does not automatically save the context of the FPU on a task 
 * switch. Instead it sets the TS flag, which causes the processor to raise an 
 * #NM exception whenever it encounters a floating-point instruction in the 
 * instruction stream for the new task. The fault handler for the #NM exception
 * can then be used to clear the TS flag (with the CLTS instruction) and save
 * the context of the FPU. If the task never encounters a floating-point 
 * instruction, the FPU context is never saved.
 */
#define CPU_CR0_TS (BIT_VALUE (3))


/**
 * @brief               ET Extension Type (bit 4 of CR0). 
 *
 * Reserved in the P6 family and Pentium R processors. (In the P6 family 
 * processors, this flag is hardcoded to 1.) In the Intel386T and Intel486T 
 * processors, this flag indicates support of Intel 387 DX math coprocessor
 * instructions when set.
 */
#define CPU_CR0_ET (BIT_VALUE (4))

/**
 * @brief               NE Numeric Error (bit 5 of CR0). 
 *
 * Enables the native (internal) mechanism for reporting FPU errors when set; 
 * enables the PC-style FPU error reporting mechanism when clear. When the NE 
 * flag is clear and the IGNNE# input is asserted, FPU errors are ignored. When
 * the NE flag is clear and the IGNNE# input is deasserted, an unmasked FPU 
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
#define CPU_CR0_NE (BIT_VALUE (5))

/**
 * @brief               WP Write Protect (bit 16 of CR0). 
 *
 * Inhibits supervisor-level procedures from writing into user-level read-only 
 * pages when set; allows supervisor-level procedures to write into user-level 
 * read-only pages when clear. This flag facilitates implementation of the 
 * copy-on-write method of creating a new process (forking) used by operating 
 * systems such as UNIX*.
 */
#define CPU_CR0_WP (BIT_VALUE (16))

/**
 * @brief               AM Alignment Mask (bit 18 of CR0). 
 *
 * Enables automatic alignment checking when set; disables alignment checking 
 * when clear. Alignment checking is performed only when the AM flag is set, the
 * AC flag in the EFLAGS register is set, the CPL is 3, and the processor is 
 * operating in either protected or virtual-8086 mode.
 */
#define CPU_CR0_AM (BIT_VALUE (18))

/**
 * @brief               NW Not Write-through (bit 29 of CR0). 
 *
 * When the NW and CD flags are clear, write-back (for Pentium R and P6 family 
 * processors) or write-through (for Intel486T processors) is enabled for writes
 * that hit the cache and invalidation cycles are enabled. Refer to Table 9-4, 
 * in Chapter 9, Memory Cache Control, for detailed information about the affect
 * of the NW flag on caching for other settings of the CD and NW flags.
 */
#define CPU_CR0_NW (BIT_VALUE (29))

/**
 * @brief               CD Cache Disable (bit 30 of CR0). 
 *
 * When the CD and NW flags are clear, caching of memory locations for the whole
 * of physical memory in the processor's internal (and external) caches is 
 * enabled. When the CD flag is set, caching is restricted as described in 
 * Table 9-4, in Chapter 9, Memory Cache Control. To prevent the processor from
 * accessing and updating its caches, the CD flag must be set and the caches 
 * must be invalidated so that no cache hits can occur (refer to Section 9.5.2.,
 * "Preventing Caching", in Chapter 9, Memory Cache Control). Refer to 
 * Section 9.5., "Cache Control", Chapter 9, Memory Cache Control, for a 
 * detailed description of the additional restrictions that can be placed on the
 * caching of selected pages or regions of memory.
 */
#define CPU_CR0_CD (BIT_VALUE (30))

/**
 * @brief               PG Paging (bit 31 of CR0). Paging enabled.
 *
 * Enables paging when set; disables paging when clear. When paging is disabled,
 * all linear addresses are treated as physical addresses. The PG flag has no 
 * effect if the PE flag (bit 0 of register CR0) is not also set; in fact, 
 * setting the PG flag when the PE flag is clear causes a general-protection 
 * exception (#GP) to be generated. Refer to Section 3.6., "Paging (Virtual 
 * Memory)" in Chapter 3, Protected-Mode Memory Management for a detailed 
 * description of the processor's paging mechanism.
 */
#define CPU_CR0_PG (BIT_VALUE (31))

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

/**
 * @brief               Structure of system register CR3.
 *
 * Contains the physical address of the base of the page directory and two flags 
 * (PCD and PWT). This register is also known as the page-directory base 
 * register (PDBR). Only the 20 most-significant bits of the page-directory base 
 * address are specified; the lower 12 bits of the address are assumed to be 0. 
 * The page directory must thus be aligned to a page (4-KByte) boundary. The PCD
 * and PWT flags control caching of the page directory in the processor's
 * internal data caches (they do not control TLB caching of page-directory 
 * information).
 * When using the physical address extension, the CR3 register contains the base
 * address of the page-directory-pointer table (refer to Section 3.8., "Physical
 * Address Extension" in Chapter 3, Protected-Mode Memory Management).
 */
typedef struct
{
    uint32_t : 3; 

    /**
     * @brief           PWT Page-level Writes Transparent (bit 3 of CR3).
     *
     * Controls the write-through or writeback caching policy of the current 
     * page directory. When the PWT flag is set, writethrough caching is 
     * enabled; when the flag is clear, write-back caching is enabled. This flag
     * affects only the internal caches (both L1 and L2, when present). The 
     * processor ignores this flag if paging is not used (the PG flag in 
     * register CR0 is clear) or the CD (cache disable) flag in CR0 is set. 
     * Refer to Section 9.5., "Cache Control", in Chapter 9, Memory Cache 
     * Control, for more information about the use of this flag. Refer to 
     * Section 3.6.4., "Page-Directory and Page-Table Entries" in Chapter 3, 
     * Protected-Mode Memory Management for a description of a companion PCD 
     * flag in the page-directory and page-table entries.
     */
    uint32_t            PWT : 1;

    /**
     * @brief           PCD Page-level Cache Disable (bit 4 of CR3).
     *
     * Controls caching of the current page directory. When the PCD flag is set,
     * caching of the page-directory is prevented; when the flag is clear, the 
     * page-directory can be cached. This flag affects only the processor's 
     * internal caches (both L1 and L2, when present). The processor ignores 
     * this flag if paging is not used (the PG flag in register CR0 is clear) 
     * or the CD (cache disable) flag in CR0 is set. Refer to Chapter 9, Memory
     * Cache Control, for more information about the use of this flag. Refer to
     * Section 3.6.4., "Page-Directory and Page-Table Entries" in Chapter 3, 
     * Protected-Mode Memory Management for a description of a companion PCD 
     * flag in the page-directory and page-table entries.
     */
    uint32_t            PCD : 1;

    uint32_t : 7;

    /**
     * @brief           Page-directory base address.
     *
     * Only the 20 most-significant bits of the page-directory base address are
     * specified; the lower 12 bits of the address are assumed to be 0. The 
     * page directory must thus be aligned to a page (4-KByte) boundary.
     */
    uint32_t            page_directory_base : 20;

} cpu_register_cr3_t PACKED;

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

enum
{
   /* Enable global page directory entries. */
    CPU_CR4_PGE = BIT_VALUE (7),
};

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

#define cpu_cr0_disable(mask_cr0)        \
{                                        \
    register uint32_t temp_cr0;          \
    asm volatile ("movl %%cr0, %0\n"     \
                  "andl %1, %0\n"        \
                  "movl %0, %%cr0"       \
                  :                      \
                  "=&r" (temp_cr0)       \
                  :                      \
                  "g" (~mask_cr0))       \
}

#define cpu_cr2_save(save_cr2)           \
    asm volatile ("movl %%cr2, %0"       \
                  :                      \
                  "=a" (save_cr2))

#define cpu_cr3_load(load_cr3)           \
    asm volatile ("movl %0, %%cr3"       \
                  : /* no output */      \
                  :                      \
                  "r" (load_cr3))

#define cpu_cr3_save(save_cr3)           \
    asm volatile ("movl %%cr3, %0"       \
                  :                      \
                  "=a" (save_cr3))

#define cpu_cr4_load(load_cr4)           \
    asm volatile ("movl %0, %%cr4"       \
                  : /* no output */      \
                  :                      \
                  "r" (load_cr4))

#define cpu_cr4_save(save_cr4)           \
    asm volatile ("movl %%cr4, %0"       \
                  :                      \
                  "=a" (save_cr4))

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

#define cpu_gdtr_save(save_cr3)          \
    asm volatile ("sgdt %0"              \
                  :                      \
                  "=a" (save_cr3))

#define cpu_gdtr_load(load_tr)           \
    asm volatile ("ltr %0"               \
                  : /* no output */      \
                  :                      \
                  "rm" (load_tr))

#define cpu_cs_save(save_cs)             \
    asm volatile ("movl %%cs, %0"        \
                  :                      \
                  "=a" (save_cs))

#endif /* !__SYSTEM_ENVIROMENT_IA32_SYSTEM_REGISTERS_H__ */

