#include <ipool.h>

#define INTERNAL_MEMORY_SIZE 1000

extern void internal_memory_init (p_physical_memory_t memory);
extern void internal_memory_deinit (p_physical_memory_t memory);

extern void * internal_memory_allocate (p_raw_memory_t memory);
extern void internal_memory_deallocate (p_raw_memory_t memory, void *pointer);

extern range_node_t node_pool_global[];

typedef union
{
    pool_of_integers_t pool;
    uint8_t data[INTERNAL_MEMORY_SIZE];
} static_pool_of_integers_t;

extern static_pool_of_integers_t node_allocator_global;
