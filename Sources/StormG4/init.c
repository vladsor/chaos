/* $chaos: main.c,v 1.32 2002/11/14 12:26:26 per Exp $ */
/* Abstract: Main startup file. */
/* Author: Vladimir Sorokin */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <enviroment.h>
#include <string.h>

#define DEBUG_MODULE_NAME "Init"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include <debug/macros.h>

#include "Include/subsystems.h"

storm_info_t storm_info =
{
    version: STORM_VERSION_STRING,
    compiler: COMPILER,
    compiler_version: __VERSION__,
    maintainer: CREATOR,
    build_date: __DATE__,
    build_time: __TIME__,
    command_line: "",
    memory_size: 0,
    number_of_memory_maps: 0,
    memory_map:
    {
        {
            size: 0,
            base_address: NULL,
            length: 0,
            type: 0,
        },
    },
    number_of_modules: 0,
    module_info:
    {
        {
            start: 0,
            end: 0,
            name: "",
        },
    }
};

subsystem_built_in_t subsystem_built_in[] =
{
#ifdef SUBSYSTEM_SYSTEM_DEBUG
    {"system_debug",      &system_debug_init,     TRUE,  ""},
#endif

#ifdef SUBSYSTEM_CPU
    {"cpu",               &cpu_init,              TRUE,  ""},
#endif

#ifdef SUBSYSTEM_EXCEPTION    
    {"exception",         &exception_init,        TRUE,  ""},
#endif

#ifdef SUBSYSTEM_PHYSICAL_MEMORY    
    {"physical_memory",   &physical_memory_init,  TRUE,  ""},
#endif    

#ifdef SUBSYSTEM_VIRTUAL_MEMORY    
    {"virtual_memory",    &virtual_memory_init,   TRUE,  ""},
#endif

#ifdef SUBSYSTEM_PORT
    {"port",              &port_init,             TRUE,  ""},
#endif

#ifdef SUBSYSTEM_DMA
    {"dma",               &dma_init,              TRUE,  ""},
#endif

#ifdef SUBSYSTEM_IRQ
    {"irq",               &irq_init,              TRUE,  ""},
#endif

#ifdef SUBSYSTEM_CLOCK
    {"clock",             &clock_init,            TRUE,  ""},
#endif

#if defined (SUBSYSTEM_TIMER) 
    {"timer",             &timer_init,            TRUE,  ""},
#endif

#if defined (SUBSYSTEM_TASK_STATE) 
    {"task_state",        &task_state_init,       TRUE,  ""},
#endif

#if defined (SUBSYSTEM_SYSTEM_CALL)
    {"system_call",       &system_call_init,      TRUE,  ""},
#endif

#if defined (SUBSYSTEM_REPOSITORY)
    {"repository",        &repository_init,       TRUE,  ""},
#endif
};

extern unsigned int arguments_parse (
  char *source, 
  char **array_of_pointers);

static bool subsystem_set_enabled (char *name, bool enabled)
{
    unsigned int i;

    for(i = 0; i < NUMBER_OF_BUILT_IN; i++)
    {
        if (!string_compare (subsystem_built_in[i].name, name))
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
                "Set subsystem: \'%s\'[%u] enabled to %s\n", 
                subsystem_built_in[i].name, i,
                subsystem_built_in[i].enabled ? "true" : "false");

            subsystem_built_in[i].enabled = enabled;
        
            return TRUE;
        }
    }

    DEBUG_PRINT (DEBUG_LEVEL_WARNING,
        "Try to configure unknown subsystem."); 
    
    return FALSE;
}

static bool subsystem_set_parameters (char *name, char *parameters)
{
    unsigned int i;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s: %s (%s, %s)\n", 
        DEBUG_MODULE_NAME, __FUNCTION__, name, parameters);

    for(i = 0; i < NUMBER_OF_BUILT_IN; i++)
    {
        if (!string_compare (subsystem_built_in[i].name, name))
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
                "Set subsystem: \'%s\'[%u] parameters to %s\n", 
                subsystem_built_in[i].name, i,
                parameters);

            string_copy (subsystem_built_in[i].parameters, parameters);
        
            return TRUE;
        }
    }

    DEBUG_PRINT (DEBUG_LEVEL_WARNING,
        "Try to configure unknown subsystem.\n"); 
    
    return FALSE;
}

char parse_enable[] = "--enable-";
#define parse_enable_length (sizeof (parse_enable) - 1)

char parse_disable[] = "--disable-";
#define parse_disable_length (sizeof (parse_disable) - 1)

char parse_parameters[] = "--parameters-";
#define parse_parameters_length (sizeof (parse_parameters) - 1)

static void argument_analyse (char *argument)
{
    if (!string_compare_max (argument, parse_enable, parse_enable_length))
    {
        subsystem_set_enabled (argument + parse_enable_length, TRUE);
    }
    else if (!string_compare_max (argument, parse_disable, 
        parse_disable_length))
    {
        subsystem_set_enabled (argument + parse_disable_length, FALSE);
    }
    else if (!string_compare_max (argument, parse_parameters, 
        parse_disable_length))
    {
        char subsystem[STRING_MAX_LENGTH];
        char parameters[STRING_MAX_LENGTH];
        char sep;
        uint32_t i;
        uint32_t start;
        
        for (i = parse_parameters_length; 
            argument[i] != '=' && argument[i] != 0; 
            i++)
        {
            subsystem[i - parse_parameters_length] = argument[i];
        }
        
        if (argument[i] == '\0')
        {
            return;
        }
        
        subsystem[i - parse_parameters_length] = '\0';
        i++;
        
        if (argument[i] != '"' && argument[i] != '\'')
        {
            return;
        }
        
        sep = argument[i];
        i++;
        start = i;
        
        for (; argument[i] != sep && argument[i] != 0; i++)
        {
            parameters[i - start] = argument[i];
        }
        
        subsystem_set_parameters (subsystem, parameters);
    }
}

static char **storm_environment = (char *[])
{
    NULL,
};

#include "Include/kernel.h"
#include <Classes/kernel.h>

/* The main function. */
void main_bootup (int argument_count, char *arguments[])
{
    unsigned int index;
    uint32_t number_of_arguments;
    return_t return_value;
    char temp_buffer[STRING_MAX_LENGTH];
    char *array_of_arguments[STRING_MAX_LENGTH / 2];
    
    for (index = 1; index < (unsigned int) argument_count; index++)
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
            "Argument[%u]=%s\n", index, arguments[index]);

        argument_analyse (arguments[index]);
    }

    for (index = 0; index < NUMBER_OF_BUILT_IN; index++)
    {
        if (subsystem_built_in[index].enabled)
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
                "%s: Starting subsystem \'%s\'.\n",
                DEBUG_MODULE_NAME, 
                subsystem_built_in[index].name);

            string_copy (temp_buffer, subsystem_built_in[index].name);
            
            if (!string_is_empty (subsystem_built_in[index].parameters))
            {
                string_append (temp_buffer, " ");
                string_append (temp_buffer, 
                    subsystem_built_in[index].parameters);
            }
            
            number_of_arguments = arguments_parse (temp_buffer, 
                array_of_arguments);
            
            return_value = subsystem_built_in[index].init (number_of_arguments, 
                array_of_arguments, storm_environment);
            
            if (return_value != 0)
            {
                DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
                    "%s: Start of subsystem \'%s\' failed.\n",
                    DEBUG_MODULE_NAME, 
                    subsystem_built_in[index].name);
                    
                subsystem_built_in[index].enabled = FALSE;
            }
        }
    }


    {
    handle_reference_t handle;
    kernel_init ();

    handle = kernel_control$handle$create (kernel_object);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s: Invoke Kernel{%p}->init ().\n",
        DEBUG_MODULE_NAME,
        kernel_object);

    kernel_control$init (handle);
    kernel_control$start (handle);
    kernel_control$stop (handle);
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s: All done. Shutdown now.\n",
        DEBUG_MODULE_NAME);
}

