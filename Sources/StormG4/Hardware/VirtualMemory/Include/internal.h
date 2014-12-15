
#define USER_MEMORY_START (PAGE_NUMBER (UINT32_MAX / 2 + 1))
#define USER_MEMORY_SIZE (PAGE_NUMBER (UINT32_MAX / 2))

//extern uint32_t last_address;
//#define GLOBAL_MEMORY_START (0 + PAGE_SIZE)
//#define GLOBAL_MEMORY_END     (last_address)
//#define GLOBAL_MEMORY_SIZE (GLOBAL_MEMORY_END - GLOBAL_MEMORY_START)

#define INTERNAL_MEMORY_SIZE 1000

#define INTERNAL_MEMORY_INIT(mdata)\
{ \
    data: (mdata), \
    allocate: internal_memory_allocate2, \
    deallocate: internal_memory_deallocate2, \
}    

extern void internal_memory_init2 (p_virtual_memory_t memory);
extern void internal_memory_deinit2 (p_physical_memory_t memory);

extern void * internal_memory_allocate2 (p_raw_memory_t memory);
extern void internal_memory_deallocate2 (p_raw_memory_t memory, void *pointer);

