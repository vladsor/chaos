
typedef return_t (main_function_t) (uint32_t argc, char **argv, char **envp);
typedef main_function_t * p_main_function_t;

typedef struct
{
    elf_parsed_program_t elf_parsed;
    
//    virtual_memory_t virtual_memory;

    computer_reference_t computer;
//    p_main_function_t main;
    method_reference_t main;
    
} storm_program_data_t;

typedef storm_program_data_t * p_storm_program_data_t;

extern interface_reference_t storm_program_control_init (void);

