extern return_t page_map (page_directory_t *page_directory,
                             page_number_t virtual_page,
                             page_number_t physical_page,
                             unsigned int pages, unsigned int flags);

extern void page_system_init (page_directory_t *page_directory);

extern void page_enable (page_directory_t *page_directory);

extern return_t page_lookup (page_directory_t *page_directory,
                              page_number_t virtual_page,
                              page_number_t *physical_page,
                              unsigned int *flags);
