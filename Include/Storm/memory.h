static inline return_t memory_allocate (void **pointer, unsigned int size)
{
    return global_memory_allocate (pointer, size);
}

static inline return_t memory_deallocate (void *pointer)
{
    return global_memory_deallocate (pointer);
}
