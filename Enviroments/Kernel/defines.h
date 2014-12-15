#ifndef STORM_DEFINES
#define STORM_DEFINES

#define COMMAND_LINE_SIZE       (256)

/**
 * @brief Information about the memory in the system. 
 */
typedef struct
{
    uint32_t size;
    p_uint8_t base_address;
    size_t length;
    uint32_t type;
} storm_memory_map_t;

typedef storm_memory_map_t * p_storm_memory_map_t;

#define MEMORY_MAP_TYPE_RAM (1)

#define MAX_NUMBER_OF_STORM_MEMORY_MAPS (100)

/**
 * @brief Information about storm module. 
 */
typedef struct
{
    uint32_t start;
    uint32_t end;
    char name[STRING_MAX_LENGTH];

} storm_module_info_t;

typedef storm_module_info_t * p_storm_module_info_t;

#define MAX_NUMBER_OF_STORM_MODULES (100)

typedef struct
{
    const char *version;
    const char *compiler;
    const char *compiler_version;
    const char *maintainer;
    const char *build_date;
    const char *build_time;

    char command_line[COMMAND_LINE_SIZE];
    
    uint32_t memory_size;
    
    uint32_t number_of_memory_maps;
    storm_memory_map_t memory_map[MAX_NUMBER_OF_STORM_MEMORY_MAPS];
    
    uint32_t number_of_modules;
    storm_module_info_t module_info[MAX_NUMBER_OF_STORM_MODULES];
} storm_info_t;

extern storm_info_t storm_info;

extern void _start (void);
extern int _end;

/**
 * @brief               The kernel starts at 1 MiB. 
 */
#define KERNEL_START    ((address_t) 1 * MIB)

/**
 * @brief               The kernel end.
 */
#define KERNEL_END      ((address_t) &_end)

/**
 * @brief               Size of kernel. 
 */
#define KERNEL_SIZE     (KERNEL_END - KERNEL_START)

#define THREAD_STACK_SIZE PAGE_SIZE
#define THREAD_NEW_EFLAGS (CPU_FLAG_INTERRUPT_ENABLE | CPU_FLAG_ADJUST | \
                           CPU_FLAG_PARITY | CPU_FLAG_SET)

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



/**
 * @brief               Flags used when creating new entries in the page
 *                      directory.
 *
 * We let the page table set everything, so we need to have this
 * all-privileged.
 */
#define PAGE_DIRECTORY_FLAGS \
                        (PAGE_PRESENT | PAGE_WRITABLE | PAGE_NON_PRIVILEGED)


#define BASE_DMA                        (128 * KIB)

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
    (SELECTOR (DESCRIPTOR_INDEX_KERNEL_CODE, 0, PRIVILEGE_LEVEL_KERNEL))

#define SELECTOR_KERNEL_DATA \
    (SELECTOR (DESCRIPTOR_INDEX_KERNEL_DATA, 0, PRIVILEGE_LEVEL_KERNEL))

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
    (SELECTOR (DESCRIPTOR_INDEX_TSS1, 0, PRIVILEGE_LEVEL_KERNEL))

/**
 * @brief               The second TSS selector.
 */
#define SELECTOR_TSS2 \
    (SELECTOR (DESCRIPTOR_INDEX_TSS2, 0, PRIVILEGE_LEVEL_KERNEL))


#endif
