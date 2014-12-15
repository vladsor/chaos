
#define INTERFACE_STORM_PROGRAM_FACTORY_ID 0x0012

typedef uint64_t (storm_program_factory_create_t) (context_t context, 
    elf_header_t *elf_header);
typedef storm_program_factory_create_t * p_storm_program_factory_create_t;
        
typedef struct
{
    p_storm_program_factory_create_t create;    
    p_object_factory_destroy_t destroy;
    p_object_factory_clone_t clone;

} storm_program_factory_interface_table_t;

typedef storm_program_factory_interface_table_t * 
    p_storm_program_factory_interface_table_t;

static inline handle_reference_t storm_program_factory$handle$create (
    object_reference_t object)
{
    sequence_t seq_empty = {NULL, 0};

    return handle_create (object, INTERFACE_STORM_PROGRAM_FACTORY_ID, 
        seq_empty, 0);
}    

static inline object_reference_t storm_program_factory$create (
    class_reference_t class, elf_header_t *elf_header)
{
    uint32_t pars[] = {(uint32_t) elf_header};
    sequence_t pars_seq = {data: pars, count: 1};
    
    return object_create (class, SECURITY_CURRENT, pars_seq, 0);
}


