
typedef struct
{
  page_directory_t *page_directory;
} process_t;

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
