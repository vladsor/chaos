#define INTERNAL_MEMORY_SIZE 1000

extern raw_memory_interface_t imemory;

extern void internal_memory_init (void);
extern void internal_memory_deinit (void);
extern void * internal_memory_allocate (void);
extern void internal_memory_deallocate (void *range);
