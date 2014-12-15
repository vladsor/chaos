#include <enviroment.h>

#define DEBUG_MODULE_NAME "Repository"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE1
#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include "../Include/internal.h"

#include <debug/macros.h>
#include <exception/macros.h>

memory_t memory_global =
{
    header: 
    {
        node: LIST_NODE_INIT,  
        type: REFERENCE_TYPE_SECURITY,    
        magic_number: REFERENCE_MAGIC_NUMBER_SECURITY,
        owner: NULL,
        number_of_references: ATOMIC_UINT32_INIT (0),
        lock: SPIN_INIT,
        is_static: TRUE,
    },
    is_global: TRUE,
    virtual_memory: &virtual_memory_global,
};

memory_reference_t memory_create (bool is_global, 
    p_virtual_memory_t virtual_memory)
{
    p_memory_t memory;
    page_number_t page;

    physical_memory_allocate (&physical_memory_global, &page, 1);
    memory = (p_memory_t) PAGE_ADDRESS (page);

    memory->is_global = is_global;
    memory->virtual_memory = virtual_memory;
    
    reference_create_internal (&memory->header, 0);
    
    return memory;
}

/*
typedef struct
{
    AVL_NODE_PART;
    
    p_data_type_t type;
    p_data_type_info_t type_info;
} data_t;    


uint64_t data_create_internal (p_memory_t memory, 
    p_data_type_t type, p_data_type_parameters_t type_parameters);
{
    return_t return_value;
    page_number_t start;
    unsigned int pages;
    
    pages = SIZE_IN_PAGES (size);
    return_value = physical_memory_allocate (&start, pages);
    
    (*pointer) = (p_void_t) PAGE_ADDRESS (start);
    
    return return_value;
}
    
void data_destroy_internal (p_memory_t memory, uint64_t data)
{
}    
*/

void repository_memory_init (void)
{
}
    
