/** 
 * @addtogroup group_exceptions Exceptions
 *
 * @{
 */

/** 
 * @defgroup group_exception_error_codes Exception error codes
 *
 * @brief               Error codes that pushed in stack then exception occured.
 *
 * @{
 */

/**
 *  @brief
 */
typedef struct
{
    /**
     * @brief           EXT External event (bit 0). 
     *
     * When set, indicates that an event external to the program caused the
     * exception, such as a hardware interrupt. */
    int ext : 1;

    /**
     * @brief           IDT Descriptor location (bit 1).
     *
     * When set, indicates that the index portion of the error code refers to
     * a gate descriptor in the IDT; when clear, indicates that the index
     * refers to a descriptor in the GDT or the current LDT. */
    int idt : 1; 

    /**
     * @brief           TI GDT/LDT (bit 2).
     *
     * Only used when the IDT flag is clear. When set, the TI flag indicates
     * that the index portion of the error code refers to a segment or gate
     * descriptor in the LDT; when clear, it indicates that the index refers to
     * a descriptor in the current GDT. */
    int ti : 1;

    /**
     * @brief           Segment Selector index
     *
     * The segment selector index field provides an index into the IDT, GDT, or 
     * current LDT to the segment or gate selector being referenced by the
     * error code. In some cases the error code is null (that is, all bits in
     * the lower word are clear). A null error code indicates that the error
     * was not caused by a reference to a specific segment or that a null
     * segment descriptor was referenced in an operation. 
     */
    int segment_selector_index : 13;

    /* Not used. */
    int : 16;
} segment_error_t PACKED;

/**
 *  @brief
 */
typedef struct
{
    /**
     * @brief            bit(0) P
     *
     * 0 The fault was caused by a nonpresent page.
     * 1 The fault was caused by a page-level protection violation. 
     */
    int p : 1;

    /**
     * @brief           bit(1) W/R
     *
     * 0 The access causing the fault was a read.
     * 1 The access causing the fault was a write. 
     */
    int w_r : 1;

    /**
     * @brief           bit(2) U/S
     *
     * 0 The access causing the fault originated when the processor
     *   was executing in supervisor mode.
     * 1 The access causing the fault originated when the processor
     *   was executing in user mode. 
     */
    int u_s : 1; 

    /**
     * @brief           bit(3) RSVD
     *
     *  0 The fault was not caused by a reserved bit violation.
     *  1 The page fault occured because a 1 was detected in one of the
     *    reserved bit positions of a page table entry or directory entry
     *    that was marked present. 
     */
    int rsvd : 1;

    /* Not used. */
    int : 28;

} page_error_t PACKED;

#define SEGMENT_ERROR_EXT               BIT_VALUE (0)
#define SEGMENT_ERROR_IDT               BIT_VALUE (1)
#define SEGMENT_ERROR_TI                BIT_VALUE (2)
#define SEGMENT_ERROR_SELECTOR_INDEX(x) 

#define PAGE_ERROR_P                    BIT_VALUE (0)
#define PAGE_ERROR_W_R                  BIT_VALUE (1)
#define PAGE_ERROR_U_S                  BIT_VALUE (2)
#define PAGE_ERROR_RSVD                 BIT_VALUE (3)

/**
 * @} // end of group_exception_error_codes
 */

/**
 * }@ // end of group group_exceptions
 */
