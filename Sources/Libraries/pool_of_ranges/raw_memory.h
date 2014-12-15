typedef struct raw_memory_t * p_raw_memory_t;

typedef void * (raw_memory_allocate_t) (p_raw_memory_t memory);
typedef raw_memory_allocate_t * p_raw_memory_allocate_t;

typedef void (raw_memory_deallocate_t) (p_raw_memory_t memory, void *);
typedef raw_memory_deallocate_t * p_raw_memory_deallocate_t;

typedef struct
{
	p_void_t data;
    p_raw_memory_allocate_t     allocate;
    p_raw_memory_deallocate_t   deallocate;
} raw_memory_t;


