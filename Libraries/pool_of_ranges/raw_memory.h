
typedef void * (raw_memory_allocate_t) (void);
typedef void (raw_memory_deallocate_t) (void *);

typedef struct
{
    raw_memory_allocate_t   *allocate;
    raw_memory_deallocate_t *deallocate;
} raw_memory_interface_t;
