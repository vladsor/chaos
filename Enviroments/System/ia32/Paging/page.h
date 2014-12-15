/** 
 * @file                ia32/Paging/page.h
 * @brief               Page description and functions. 
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
 * @defgroup group_pages Pages
 *
 * @brief               Page in x86 architecture.
 *
 * @{
 */

/**
 * @brief               A page number.
 */
typedef                 uint32_t page_number_t;

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

/* Page directory/table flags. */

/** 
 * @defgroup group_page_flags Page flags
 *
 * @brief               Page flags.
 *
 * @{
 */

/**
 * @brief               Is the page present in memory?
 */
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
 * }@ // end of group group_page_flags
 */

/**
 * }@ // end of group group_page
 */

/**
 * }@ // end of group group_paging
 */

