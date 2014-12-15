
typedef struct
{
    reference_struct_t header;
    
    bool is_global;
    p_virtual_memory_t virtual_memory;
    
} memory_t;

typedef memory_t * p_memory_t;

#if defined (__STORM_KERNEL__)

extern memory_t memory_global;
#define MEMORY_GLOBAL ((memory_reference_t) &memory_global)

#endif

extern memory_reference_t memory_create (bool is_global, 
    p_virtual_memory_t virtual_memory);
    