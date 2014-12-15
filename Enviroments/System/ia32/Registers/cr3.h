/**
 * @file                ia32/Registers/cr3.h
 * @brief               Descriptions of CR3 register.
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
 * @defgroup group_system_register_cr3 CR3 register
 *
 * @brief               CR3 register.
 *
 * @{
 */

#ifndef __SYSTEM_ENVIROMENT_IA32_REGISTERS_CR3_H__
#define __SYSTEM_ENVIROMENT_IA32_REGISTERS_CR3_H__

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
    uint32_t            writes_transparent : 1;

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
    uint32_t            cache_disable : 1;

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
#define CPU_CR3_PWT (BIT_VALUE (3))

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
#define CPU_CR3_PCD (BIT_VALUE (4))

#define cpu_cr3_load(load_cr3)           \
    asm volatile ("movl %0, %%cr3"       \
                  : /* no output */      \
                  :                      \
                  "r" (load_cr3))

#define cpu_cr3_save(save_cr3)           \
    asm volatile ("movl %%cr3, %0"       \
                  :                      \
                  "=a" (save_cr3))

#endif /* !__SYSTEM_ENVIROMENT_IA32_REGISTERS_CR3_H__ */

/**
 * }@ // end of group group_system_register_cr3
 */

/**
 * }@ // end of group group_system_registers
 */


