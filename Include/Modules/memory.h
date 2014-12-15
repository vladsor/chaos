extern handle_t handle_memory;

static inline return_t memory_allocate (void **pointer, unsigned int size)
{
    return memory$allocate (&handle_memory, pointer, size);
}

static inline return_t memory_deallocate (void *pointer)
{
    return memory$deallocate (&handle_memory, pointer);
}

