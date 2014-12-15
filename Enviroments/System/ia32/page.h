/* $chaos: defines.h,v 1.24 2002/10/23 07:26:06 per Exp $ */

/** 
 * @file                page.h
 * @brief               Page description and functions. 
 * @author              Per Lundberg <per@chaosdev.org>
 * @author              Henrik Hallin <hal@chaosdev.org>
 * @author              Vladimir Sorokin          
 * @version             1.0
 * @date                2002-2004
 */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#ifndef __SYSTEM_ENVIROMENT_IA32_PAGE_H__
#define __SYSTEM_ENVIROMENT_IA32_PAGE_H__

/**
 * @brief               The size of a physical page. 
 */
#define PAGE_SIZE       (0x1000U)

/**
 * @brief               The number of bits of a page.
 */
#define PAGE_BITS       12

/**
 * @brief               The address of page.
 */
#define PAGE_ADDRESS(x) ((x) << PAGE_BITS)

#define PAGE_DIRECTORY_INDEX(x) ((x) >> 10)
#define PAGE_TABLE_INDEX(x)     ((x) & 0x03FF)

#define PAGE_OFFSET(x) ((x) & 0x0FFF)

/**
 * @brief               Round address to nearest page.
 */
#define PAGE_ALIGN_DOWN(x) \
                        ((void *) (((uint32_t) (x)) & 0xFFFFF000))

/**
 * @brief               The page number of an address.
 */
#define PAGE_NUMBER(x)  ((page_number_t) (((address_t) (x)) >> PAGE_BITS))

/**
 * @brief               The maximum memory amount that we support. 
 */
#define MAX_MEMORY      ((uint32_t) 2 * GIB)

/* Page directory/table flags. */
/**
 * @brief               Pages owned by the kernel.
 *
 * Supervisor-only, read-only (since we don't set WP bit, it isn't
 * really read-only for the kernel..), and global. 
 */
#define PAGE_KERNEL     (PAGE_PRESENT)

/**
 * @brief               Pages owned by user processes.
 */
#define PAGE_USER       (PAGE_PRESENT | PAGE_NON_PRIVILEGED | PAGE_WRITABLE | \
                         PAGE_WRITE_THROUGH)


#define PAGE_PRESENT    BIT_VALUE (0)

/**
 * @brief               Is the page writable?
 */
#define PAGE_WRITABLE   BIT_VALUE (1)

/**
 * @brief               Can the page be accessed from nonprivileged (ring 3)
 *                      code?
 */
#define PAGE_NON_PRIVILEGED \
                        BIT_VALUE (2)

/**
 * @brief               Is write-through cache enabled for the page?
 */
#define PAGE_WRITE_THROUGH \
                        BIT_VALUE (3)

/**
 * @brief               Is caching completely disabled for this page?
 *
 * This flag is neccessary to use when mapping I/O devices.
 */
#define PAGE_CACHE_DISABLE \
                        BIT_VALUE (4)

/**
 * @brief               Is this a global page, shared between all page
 *                      directories?
 */
#define PAGE_GLOBAL     BIT_VALUE (8)

/**
 * @brief               A page number.
 */
typedef                 uint32_t page_number_t;

/**
 * @brief               Flags used when creating new entries in the page
 *                      directory.
 *
 * We let the page table set everything, so we need to have this
 * all-privileged.
 */
#define PAGE_DIRECTORY_FLAGS \
                        (PAGE_PRESENT | PAGE_WRITABLE | PAGE_NON_PRIVILEGED)

/**
 * @brief               A page directory entry (PDE) when using 4MiB pages.
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
     * the page, it generates a page-fault exception (#PF). The processor does 
     * not set or clear this flag; it is up to the operating system or executive
     * to maintain the state of the flag.
     */
    uint32_t            present              : 1;


    uint32_t            flags                : 4;

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
     * @brief           Should always be one (4 MiB pages, no page
     *                  tables).
     */
    uint32_t            page_size            : 1;

    /**
     * Global (G) flag, bit 8
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

    uint32_t            available            : 3;

    /**
     * @brief           Should always be zero.
     */
    uint32_t            zero                 : 10;

    /**
     * @brief           The physical base of this page, shifted 20 steps
     *                  to the right.
     *
     * Specifies the physical address of the first byte of a 4-MByte page. Only 
     * bits 22 through 31 of this field are used (and bits 12 through 21 are 
     * reserved and must be set to 0, for Intel Architecture processors through
     * the Pentium R II processor). The base address bits are interpreted as the
     * 10 most-significant bits of the physical address, which forces 4-MByte 
     * pages to be aligned on 4-MByte boundaries.   
     */
    uint32_t            page_base            : 10;
} page_directory_4mb_t;

/**
 * @brief               A page directory entry (PDE).
 */
typedef struct
{
    uint32_t            present              : 1;
    uint32_t            flags                : 4;
    uint32_t            accessed             : 1;
    uint32_t            zero                 : 1;

    /**
     * @brief           Should always be zero (4 KiB pages).
     */
    uint32_t            page_size            : 1;
    uint32_t            global               : 1;
    uint32_t            available            : 3;

    /**
     * @brief           Page base address, bits 12 through 32
     *
     * Specifies the physical address of the first byte of a page table. The 
     * bits in this field are interpreted as the 20 most-significant bits of the
     * physical address, which forces page tables to be aligned on 4-KByte 
     * boundaries.
     */
    uint32_t            page_table_base      : 20;
} page_directory_t;

/**
 * @brief A page table entry (PTE).
 */
typedef struct
{
    uint32_t present              : 1;
    uint32_t flags                : 4;
    uint32_t accessed             : 1;
    uint32_t dirty                : 1;
    uint32_t zero                 : 1;
    uint32_t global               : 1;
    uint32_t available            : 3;

    /**
     * @brief           Page base address, bits 12 through 32
     *
     * Specifies the physical address of the first byte of a 4-KByte page. The 
     * bits in this field are interpreted as the 20 most-significant bits of the
     * physical address, which forces pages to be aligned on 4-KByte boundaries.
     */
    uint32_t page_base            : 20;
} page_table_t;

#define PAGE_TABLE_ENTRY(physical_page,flags) (                                \
  (flags) |                                                                    \
  ((physical_page) << 12))                                                    

#define PAGE_DIRECTORY_ENTRY(page_table_page,flags) (                          \
  (flags) |                                                                    \
  ((page_table_page) << 12))  

/**
 * @brief               Create an entry in a page table. 
 */
static inline void page_table_fill_entry (page_table_t *page_table, 
        uint16_t entry, page_number_t physical_page, unsigned int flags)
{
    ((uint32_t *) page_table)[entry] = PAGE_TABLE_ENTRY (physical_page, flags);
}

/**
 * @brief               Create an entry in a page directory. 
 */
static inline void page_directory_fill_entry (page_directory_t *page_directory,
        uint16_t entry, page_number_t page_table_page, unsigned int flags)
{
    ((uint32_t *) page_directory)[entry] = PAGE_DIRECTORY_ENTRY (
        page_table_page, flags);
}

#define PAGE_DIRECTORY_IS_PRESENT
#define PAGE_TABLE_IS_PRESENT
#define PAGE_IS_PRESENT

#endif /* !__SYSTEM_ENVIROMENT_IA32_PAGE_H__ */
