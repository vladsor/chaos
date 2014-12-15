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
            
            number_of_arguments = string_slice (temp_buffer, 
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

    scene_reference_t controlling;
    role_reference_t controlled;
    role_reference_t controller;
    
    kernel_init ();

    controlling = scene_create ();
    controlled = kernel_control$invoked$create (controlling, kernel_object);
    controller = kernel_control$invoker$create (controlling);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE2,
        "%s: Invoke Kernel{%p}->init ().\n",
        DEBUG_MODULE_NAME,
        kernel_object);

    kernel_control$init (controller);
    kernel_control$start (controller);
    kernel_control$stop (controller);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s: All done. Shutdown now.\n",
        DEBUG_MODULE_NAME);
}

