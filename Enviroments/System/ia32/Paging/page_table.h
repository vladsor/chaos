/** 
 * @file                ia32/Paging/page_table.h
 * @brief               Page table description and functions. 
 * @author              Per Lundberg <per@chaosdev.org>
 * @author              Henrik Hallin <hal@chaosdev.org>
 * @author              Vladimir Sorokin          
 * @version             1.0
 * @date                2002-2004
 */

/** 
 * @addtogroup group_paging
 *
 * @{
 */

/** 
 * @defgroup group_page_table Page table
 *
 * @brief               Page tables in x86 architecture.
 *
 * @{
 */

/**
 * @brief A page table entry (PTE).
 */
typedef struct
{
    /**
     * @brief           Present (P) flag, bit 0
     *
     * Indicates whether the page or page table being pointed to by the entry is
     * currently loaded in physical memory. When the flag is set, the page is in
     * physical memory and address translation is carried out. When the flag is 
     * clear, the page is not in memory and, if the processor attempts to access
     * the page, it generates a page-fault exception (#PF).<BR>
     * The processor does not set or clear this flag; it is up to the operating
     * system or executive to maintain the state of the flag.<BR>
     * The bit must be set to 1 whenever extended physical addressing mode is
     * enabled. If the processor generates a page-fault exception, the operating
     * system must carry out the following operations in the order below:
     * <OL>
     *    <LI> 
     *        Copy the page from disk storage into physical memory, if needed. 
     *    </LI>
     *    <LI> 
     *        Load the page address into the page-table or page-directory entry
     *        and set its present flag. Other bits, such as the dirty and
     *        accessed flags, may also be set at this time.
     *    </LI>
     *    <LI>
     *        Invalidate the current page-table entry in the TLB (refer to
     *        Section 3.7., "Translation Lookaside Buffers (TLBs)" for a
     *        discussion of TLBs and how to invalidate them).
     *    </LI>
     *    <LI>
     *        Return from the page-fault handler to restart the interrupted
     *        program or task.     
     *    </LI>
     * </OL>
     */
    uint32_t            present              : 1;

    /**
     * @brief           Read/write (R/W) flag, bit 1
     *
     * Specifies the read-write privileges for a page or group of pages (in the
     * case of a page-directory entry that points to a page table). When this
     * flag is clear, the page is read only; when the flag is set, the page can
     * be read and written into. This flag interacts with the U/S flag and the
     * WP flag in register CR0. Refer to Section 4.11., "Page-Level Protection"
     * and Table 4-2 in Chapter 4, Protection for a detailed discussion of the
     * use of these flags.
     */
    uint32_t            read_write           : 1;

    /**
     * @brief           User/supervisor (U/S) flag, bit 2
     *
     * Specifies the user-supervisor privileges for a page or group of pages
     * (in the case of a page-directory entry that points to a page table).
     * When this flag is clear, the page is assigned the supervisor privilege
     * level; when the flag is set, the page is assigned the user privilege
     * level. This flag interacts with the R/W flag and the WP flag in register
     * CR0. Refer to Section 4.11., "Page-Level Protection" and Table 4-2 in
     * Chapter 4, Protection for a detail discussion of the use of these flags.
     */
    uint32_t            user_supervisor      : 1;

    /**
     * @brief           Page-level write-through (PWT) flag, bit 3
     *
     * Controls the write-through or write-back caching policy of individual
     * pages or page tables. When the PWT flag is set, write-through caching is
     * enabled for the associated page or page table; when the flag is clear,
     * write-back caching is enabled for the associated page or page table.
     * The processor ignores this flag if the CD (cache disable) flag in CR0 is
     * set. Refer to Section 9.5., "Cache Control", in Chapter 9, Memory Cache
     * Control, for more information about the use of this flag. Refer to
     * Section 2.5., "Control Registers" in Chapter 2, System Architecture
     * Overview for a description of a companion PWT flag in control register
     * CR3.
     */
    uint32_t            write_through        : 1;

    /**
     * @brief           Page-level cache disable (PCD) flag, bit 4
     *
     * Controls the caching of individual pages or page tables. When the PCD
     * flag is set, caching of the associated page or page table is prevented;
     * when the flag is clear, the page or page table can be cached. This flag
     * permits caching to be disabled for pages that contain memory-mapped I/O
     * ports or that do not provide a performance benefit when cached. The
     * processor ignores this flag (assumes it is set) if the CD (cache disable)
     * flag in CR0 is set. Refer to Chapter 9, Memory Cache Control, for more
     * information about the use of this flag. Refer to Section 2.5. in
     * Chapter 2, System Architecture Overview for a description of a companion
     * PCD flag in control register CR3.
     */
    uint32_t            cache_disable        : 1;

    /**
     * @brief           Accessed (A) flag, bit 5
     *
     * Indicates whether a page or page table has been accessed (read from or 
     * written to) when set. Memory management software typically clears this 
     * flag when a page or page table is initially loaded into physical memory. 
     * The processor then sets this flag the first time a page or page table is
     * accessed. This flag is a "sticky" flag, meaning that once set, the 
     * processor does not implicitly clear it. Only software can clear this 
     * flag. The accessed and dirty flags are provided for use by memory 
     * management software to manage the transfer of pages and page tables into
     * and out of physical memory.
     */
    uint32_t            accessed             : 1;

    /**
     * @brief           Dirty (D) flag, bit 6
     *
     * Indicates whether a page has been written to when set. Memory management
     * software typically clears this flag when a page is initially loaded into 
     * physical memory. The processor then sets this flag the first time a page 
     * is accessed for a write operation. This flag is "sticky," meaning that 
     * once set, the processor does not implicitly clear it. Only software can 
     * clear this flag. The dirty and accessed flags are provided for use by 
     * memory management software to manage the transfer of pages and page 
     * tables into and out of physical memory.
     */
    uint32_t            dirty                : 1;

    /**
     * @brief           Reserved (set to 0), bit 7
     */
    uint32_t            zero                 : 1;

    /**
     * @brief           Global (G) flag, bit 8
     *
     * (Introduced in the Pentium R Pro processor.) Indicates a global page when
     * set. When a page is marked global and the page global enable (PGE) flag 
     * in register CR4 is set, the page-table or page-directory entry for the 
     * page is not invalidated in the TLB when register CR3 is loaded or a task
     * switch occurs. This flag is provided to prevent frequently used pages 
     * (such as pages that contain kernel or other operating system or executive
     * code) from being flushed from the TLB. Only software can set or clear 
     * this flag. Refer to Section 3.7., "Translation Lookaside Buffers (TLBs)"
     * for more information about the use of this flag. (This bit is reserved in
     * Pentium R and earlier Intel Architecture processors.)
     */
    uint32_t            global               : 1;

    /**
     * @brief           Available for system programmer's use, bits 9..11
     */
    uint32_t            available            : 3;

    /**
     * @brief           Page base address, bits 22..31
     *
     * Specifies the physical address of the first byte of a 4-KByte page. The 
     * bits in this field are interpreted as the 20 most-significant bits of the
     * physical address, which forces pages to be aligned on 4-KByte boundaries.
     */
    uint32_t            page_base            : 20;
} page_table_t PACKED;

typedef page_table_t * p_page_table_t;

#define PAGE_TABLE_ENTRY(physical_page,flags) (                                \
  (flags) |                                                                    \
  ((physical_page) << 12))                                                    

#define PAGE_TABLE_INDEX(x)     ((x) & 0x03FF)


/**
 * @brief               Create an entry in a page table. 
 */
static inline void page_table_fill_entry (page_table_t *page_table, 
        uint16_t entry, page_number_t physical_page, unsigned int flags)
{
    ((uint32_t *) page_table)[entry] = PAGE_TABLE_ENTRY (physical_page, flags);
}

/**
 * }@ // end of group group_page_table
 */

/**
 * }@ // end of group group_paging
 */

