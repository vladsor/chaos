/* $chaos: main.c,v 1.32 2002/11/14 12:26:26 per Exp $ */
/* Abstract: Main startup file. */
/* Author: Vladimir Sorokin */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <enviroment.h>

#define DEBUG_MODULE_NAME "Init"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

#include "Init/Include/multiboot.h"

#include "subsystems.h"

storm_info_t storm_info =
{
    STORM_VERSION_STRING, 
    COMPILER,
    __VERSION__,
    CREATOR,
    __DATE__, 
    __TIME__
};

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
        DEBUG_MODULE_NAME, __FUNCTION__, name, parameters);

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

char **storm_environ = (char *[]){0};
extern void main_bootup (int argument_count, char *arguments[]);

/* The main function. */
void main_bootup (int argument_count, char *arguments[])
{
    unsigned int i;
    char temp_buffer[STRING_MAX_LENGTH];
    uint32_t number_of_arguments;
    char *array_of_arguments[STRING_MAX_LENGTH / 2];
    
    for (i = 1; i < (unsigned int) argument_count; i++)
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
            "Argument[%u]=%s\n", i, arguments[i]);

        argument_analyse (arguments[i]);
    }

    for(i = 0; i < NUMBER_OF_BUILT_IN; i++)
    {
        if (subsystem_built_in[i].enabled)
        {
            return_t return_value;
            
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
                "%s: Starting subsystem \'%s\'.\n",
                DEBUG_MODULE_NAME, subsystem_built_in[i].name);

            string_copy (temp_buffer, subsystem_built_in[i].name);
            
            if (!string_is_empty (subsystem_built_in[i].parameters))
            {
                string_append (temp_buffer, " ");
                string_append (temp_buffer, subsystem_built_in[i].parameters);
            }
            
            number_of_arguments = arguments_parse (temp_buffer, 
                array_of_arguments);
            
            return_value = (*subsystem_built_in[i].init) (number_of_arguments, 
                array_of_arguments, storm_environ);
            
            if (return_value != 0)
            {
                subsystem_built_in[i].enabled = FALSE;
            }
        }
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: All done. Idleing now.\n",
        DEBUG_MODULE_NAME);
}
