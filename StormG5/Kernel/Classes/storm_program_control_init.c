#include <enviroment.h>

#include <Interfaces/storm_program_control.h>

#include "storm_program.h"
#include "storm_program_control_interface.h"

#define DEBUG_MODULE_NAME "StormProgramControl"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE1
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include <debug/macros.h>
#include <exception/macros.h>

static return_t storm_main (context_t context,
    uint32_t argc, char *argv[], char **envp)
{
    p_storm_program_data_t program;
    return_t return_value;

    program = (p_storm_program_data_t) (address_t) context.object_data;
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s: %s (%p, %u, %p, %p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        program, argc, argv, envp);

    {
    uint32_t pars[3] = {(uint32_t) argc, (uint32_t) argv, (uint32_t) envp};
    sequence_t pars_in_seq = {data: pars, count: 3};
    
    sequence_t empty_seq = {data: NULL, count: 0};
    
    uint32_t ret = 0;
    sequence_t pars_out_seq = {data: &ret, count: 1};

    method_invoke (program->main, program->computer, 
        pars_in_seq, empty_seq, pars_out_seq, 0);
        
    return_value = ret;
//    return_value = program->main (argc, argv, envp);
    }
    
    return return_value;
}

static storm_program_control_interface_table_t table = 
{
    main: &storm_main,
};

/* Main function. */

interface_reference_t storm_program_control_init (void)
{
    return storm_program_control_interface_register (&table);
}

