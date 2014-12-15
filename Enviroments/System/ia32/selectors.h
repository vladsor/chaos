/**
 * @file                selectors.h
 * @brief               Segment selectors description.
 * @author              Vladimir Sorokin
 * @version             0.1
 * @date                2002-2004
 */

#ifndef __SYSTEM_ENVIROMENT_IA32_SELECTORS_H__
#define __SYSTEM_ENVIROMENT_IA32_SELECTORS_H__

enum descriptor_index_t
{
    DESCRIPTOR_INDEX_NULL = 0,
    DESCRIPTOR_INDEX_KERNEL_CODE = 1,
    DESCRIPTOR_INDEX_KERNEL_DATA = 2,
    DESCRIPTOR_INDEX_PROCESS_CODE = 3,
    DESCRIPTOR_INDEX_PROCESS_DATA = 4,
    DESCRIPTOR_INDEX_TSS1 = 5,
    DESCRIPTOR_INDEX_TSS2 = 6,
};

#define SELECTOR_KERNEL_CODE \
    (SELECTOR (DESCRIPTOR_INDEX_KERNEL_CODE, 0, PRIVILEGE_LEVEL_SYSTEM))

#define SELECTOR_KERNEL_DATA \
    (SELECTOR (DESCRIPTOR_INDEX_KERNEL_DATA, 0, PRIVILEGE_LEVEL_SYSTEM))

#define SELECTOR_PROCESS_CODE \
    (SELECTOR (DESCRIPTOR_INDEX_PROCESS_CODE, 0, PRIVILEGE_LEVEL_USER))

#define SELECTOR_PROCESS_DATA \
    (SELECTOR (DESCRIPTOR_INDEX_PROCESS_DATA, 0, PRIVILEGE_LEVEL_USER))

/**
 * @brief               The first TSS selector.
 *
 * We use two TSS selectors for task switching, which makes the GDT
 * very small which is good. Besides, it does not put a limit on the
 * number of running threads in the system which is *very* good.
 */
#define SELECTOR_TSS1 \
    (SELECTOR (DESCRIPTOR_INDEX_TSS1, 0, PRIVILEGE_LEVEL_SYSTEM))

/**
 * @brief               The second TSS selector.
 */
#define SELECTOR_TSS2 \
    (SELECTOR (DESCRIPTOR_INDEX_TSS2, 0, PRIVILEGE_LEVEL_SYSTEM))

#endif /* !__SYSTEM_ENVIROMENT_IA32_SELECTORS_H__ */

