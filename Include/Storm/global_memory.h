enum
{
    /* The function call suceeded. */

    MEMORY_RETURN_SUCCESS,

    /* Out of memory. */
  
    MEMORY_RETURN_OUT_OF_MEMORY,

    /* The SLAB system we tried to access was broken. */

    MEMORY_RETURN_SLAB_BROKEN,

    MEMORY_RETURN_UNSUCCESSFULL,
};

extern return_t global_memory_init (int argc, char *argv[]);

/**
 * @brief               Allocate global memory. 
 * @param pointer       A double-pointer to the allocated memory.
 * @param size          The size of the memory area to allocate.
 * @return              STORM_RETURN_SUCCESS if successful.
 */
extern return_t global_memory_allocate (void **pointer, unsigned int size);

/**
 * @brief               Deallocate global memory. 
 * @param pointer       A pointer to the memory that should be deallocated.
 * @return              STORM_RETURN_SUCCESS if successful.
 */
extern return_t global_memory_deallocate (void *pointer);


