
extern page_directory_t page_directory_global[];

//extern void page_system_init (p_page_directory_t page_directory);
//extern void page_enable (p_page_directory_t page_directory);
extern void page_init (void);

extern return_t page_map (p_page_directory_t page_directory,
    page_number_t virtual_page, page_number_t physical_page,
    unsigned int pages, unsigned int flags);

extern return_t page_map_4mb (page_directory_t *page_directory,
    page_number_t virtual_page_4mb, page_number_t physical_page_4mb, 
    unsigned int pages_4mb, unsigned int flags);

extern return_t page_lookup (p_page_directory_t page_directory,
    page_number_t virtual_page, p_page_number_t physical_page,
    unsigned int *flags);
