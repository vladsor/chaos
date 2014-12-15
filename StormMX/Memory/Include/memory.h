
typedef struct
{
  page_directory_t *page_directory;
} process_t;

extern void global_memory_init (void);

/**
 * @brief               Allocate global memory. 
 * @param pointer       A double-pointer to the allocated memory.
 * @param size          The size of the memory area to allocate.
 * @return              STORM_RETURN_SUCCESS if successful.
 */
//extern return_t global_memory_allocate (void **pointer, unsigned int size);

/**
 * @brief               Deallocate global memory. 
 * @param pointer       A pointer to the memory that should be deallocated.
 * @return              STORM_RETURN_SUCCESS if successful.
 */
//extern return_t global_memory_deallocate (void *pointer);

extern void physical_memory_init (void);

/**
 * @brief               Allocate a number of pages. 
 * @param pointer       A double pointer to where the function will put
 *                      a pointer to the allocated memory.
 * @param pages         The number of pages to allocate. (1 is O(1),
 *                      more is much, much slower)
 * @param process_id    The process ID for which to allocate the memory.
 *                      Specify PROCESS_ID_NONE if you do not wish this to
 *                      be stored in the list (it will leak the page if the
 *                      process gets killed in a weird way).
 * @return              STORM_RETURN_SUCCESS if successful.
 */
extern return_t physical_memory_allocate (page_number_t *pointer, 
    unsigned int pages);

/**
 * @brief               Deallocate a page.
 * @param pointer       A pointer to the page.
 * @return              STORM_RETURN_SUCCESS if successful.
 *
 * Yes, only one page. If you allocated multiple
 * pages, you need to call this function for each page. I will not
 * keep track of the number of pages you have allocated for you, you
 * will need to do it yourself. 
 */
extern return_t physical_memory_deallocate (page_number_t start_page, 
    unsigned int pages);

extern return_t physical_memory_reserve (page_number_t start_page, 
    unsigned int pages);

