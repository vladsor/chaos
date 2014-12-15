#include <enviroment.h>

#include "../interfaces.h"

#include "../Classes/storm_program.h"

#include <Interfaces/storm_program_factory.h>

#include "storm_program_factory_interface.h"

#define DEBUG_MODULE_NAME "Kernel{StormProgramFactory}"

#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE1
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include <debug/macros.h>
#include <exception/macros.h>

static uint64_t storm_program_create (context_t context UNUSED, 
    elf_header_t *elf_header)
{
    return_t return_value;

    p_storm_program_data_t data;
    virtual_memory_t virtual_memory;
    memory_reference_t memory;
    address_t main_function;
    description_reference_t method_description_main;
    sequence_t empty_seq = {data: NULL, count: 0};

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s: %s (%p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        elf_header);

    memory_allocate ((void **) &data, sizeof (storm_program_data_t));
    memory_clear (data, sizeof (storm_program_data_t));

    return_value = elf_parse_program (elf_header, &data->elf_parsed);
    
    if (return_value != STORM_RETURN_SUCCESS)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
            "%s: Failed parse ELF.\n",
            DEBUG_MODULE_NAME);
        
        EXCEPTION_THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
    }

    return_value = virtual_memory_create (&virtual_memory,
        &physical_memory_global, LEVEL_USER);

    if (return_value != STORM_RETURN_SUCCESS)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
            "%s: Failed virtual memory creating.\n",
            DEBUG_MODULE_NAME);
    }    

    /* Allocate pages and copy the sections to this space. */
    return_value = elf_load_program (&data->elf_parsed, &virtual_memory);
    
    if (return_value != STORM_RETURN_SUCCESS)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
            "%s: Failed loading ELF.\n",
            DEBUG_MODULE_NAME);
        
        EXCEPTION_THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
    }

    memory = memory_create (FALSE, &virtual_memory);
    data->computer = computer_create (CPU_KERNEL, memory, SECURITY_ABSOLUTE);

    return_value = elf_get_entry_point (&data->elf_parsed, 
        &main_function);
    
    if (return_value != STORM_RETURN_SUCCESS)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
            "%s: Failed getting entry point.\n",
            DEBUG_MODULE_NAME);

        EXCEPTION_THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s: %s: Main: %p\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        (p_void_t) main_function);

    method_description_main = method_description_register (
        0,
        L"main",
        METHOD_TYPE_DYNAMIC,
        NULL,
        empty_seq,
        empty_seq);

    data->main = method_create_dynamic (
        method_description_main, REFERENCE_NULL, memory, 
        (p_function_dynamic_t) main_function, 0, 0);

    return (address_t) data;
}

static void storm_program_destroy (context_t context UNUSED, uint64_t data)
{
    p_storm_program_data_t program;
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s: %s (%llX)\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        data);

    program = (p_storm_program_data_t) (address_t) data;

    memory_deallocate (program);
}

static storm_program_factory_interface_table_t table = 
{
    create: &storm_program_create,
    destroy: &storm_program_destroy,
    clone: NULL,
};

/* Main function. */

interface_reference_t storm_program_factory_interface_init (void)
{
    return storm_program_factory_interface_register (&table);
}


