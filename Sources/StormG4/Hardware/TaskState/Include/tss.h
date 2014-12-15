
extern void tss_create (p_tss_t tss, p_page_directory_t page_directory,
    uint16_t selector_code, uint16_t selector_data,
    uint32_t instruction_pointer, uint32_t kernel_stack_pointer, 
    uint32_t user_stack_pointer,
    uint32_t eflags);

extern void tss_switch_prepare (p_tss_t tss);

extern uint32_t jump_data[2];

