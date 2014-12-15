/* $chaos: tss.h,v 1.3 2002/10/24 21:33:56 per Exp $ */

/**
 * @file                ia32/Segmentation/tss.h
 * @brief               A structure for holding an Intel TSS (Task
 *                      State Segment).
 * @author              Per Lundberg <per@chaosdev.org>,
 * @author              Vladimir Sorokin
 * @version             1.4
 * @date                1998-2002
 *
 * TSS:es are used for doing task switching. All the register values
 * of a task is stored in the TSS.
 */

/** 
 * @addtogroup group_segmentation
 *
 * @{
 */

/** 
 * @defgroup group_segmentation_tss TSS
 *
 * @brief               TSS (Task State Segment).
 *
 * @{
 */

#ifndef __SYSTEM_ENVIROMENT_IA32_TSS_H__
#define __SYSTEM_ENVIROMENT_IA32_TSS_H__

/**
 * @brief               A TSS (Task State Segment).
 *
 * See the Intel Architecture Software Developer's Manual Volume 3:
 * System Programming Guide for more information about what TSS:s are
 * used for.
 */
typedef struct
{
    /**
     * @brief           CPU data. 
     */
    uint16_t            previous_task_link;
    uint16_t            u0;
    
    /**
     * @brief           Stack pointer for PL0 code (system calls). 
     */
    uint32_t            esp0;              

    /**
     * @brief           Stack segment for PL0 code (system calls).
     */
    uint16_t            ss0;

    uint16_t            u1;
    
    /**
     * @brief           Stack pointer for PL1 code (unused).
     */
    uint32_t            esp1;

    /**
     * @brief           Stack segment for PL1 code (unused).
     */
    uint16_t            ss1;
    uint16_t            u2;

    /**
     * @brief           Stack pointer for PL2 code (unused).
     */
    uint32_t            esp2;

    /**
     * @brief           Stack segment for PL2 code (unused).
     */
    uint16_t            ss2;
    uint16_t            u3;

    /**
     * @brief           CR3 (page directory) location.
     */
    uint32_t            cr3;
    
    /**
     * @brief           Instruction pointer.
     */
    uint32_t            eip;

    /**
     * @brief           Processor flags.
     */
    uint32_t            eflags;

    /**
     * @brief           General purpose register #1.
     */
    uint32_t            eax;

    /**
     * @brief           General purpose register #2.
     */
    uint32_t            ecx;

    /**
     * @brief           General purpose register #3.
     */
    uint32_t            edx;

    /**
     * @brief           General purpose register #4.
     */
    uint32_t            ebx;

    /**
     * @brief           Stack pointer. 
     */
    uint32_t            esp;

    /**
     * @brief           Base pointer.
     */
    uint32_t            ebp;

    /**
     * @brief           Source index (for MOVS)
     */
    uint32_t            esi;

    /**
     * @brief           Destination index (for MOVS)
     */
    uint32_t            edi;

    /**
     * @brief           ES segment selector.
     */
    uint16_t            es;
    uint16_t            u4;

    /**
     * @brief           CS segment selector.
     */
    uint16_t            cs;
    uint16_t            u5;

    /**
     * @brief           SS segment selector.
     */
    uint16_t            ss;
    uint16_t            u6;

    /**
     * @brief           DS segment selector.
     */
    uint16_t            ds;
    uint16_t            u7;

    /**
     * @brief           FS segment selector.
     */
    uint16_t            fs;
    uint16_t            u8;

    /**
     * @brief           GS segment selector.
     */
    uint16_t            gs;
    uint16_t            u9;
    
    /**
     * @brief           The selector in the GDT that refers to this
     *                  process LDT (Local Descriptor Table).
     *
     * We do not use this in stormG3.
     */
    uint16_t            ldt_selector;
    uint16_t            u10;
    uint16_t            t: 1;
    uint16_t            u11: 15;

    /**
     * @brief           Base address of I/O map, relative to the TSS 
     *                  location. 
     */
    uint16_t            iomap_base;

#ifdef FPU_ENABLED
    /**
     *
     */
    bool                fpu_initialised;

    /**
     *
     */
    fpu_state_t         fpu_state;
#endif

    /**
     * @brief           Size of I/O map.
     */
    unsigned int        iomap_size;

    /**
     * @brief           I/O map (bit clears means access enabled).
     */
    uint8_t             iomap[0];

} tss_t PACKED;

/**
 * @brief               The CPU flags to use when setting up a new TSS.
 */
#define TSS_NEW_EFLAGS  (CPU_FLAG_INTERRUPT_ENABLE | CPU_FLAG_ADJUST | \
                         CPU_FLAG_PARITY | CPU_FLAG_SET)

#endif /* !__SYSTEM_ENVIROMENT_IA32_TSS_H__ */

/**
 * }@ // end of group group_segmentation_tss
 */

/**
 * }@ // end of group group_segmentation
 */

