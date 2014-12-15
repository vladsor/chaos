/* Abstract: Startup code file for chaos binaries. This code is what executes
   the main () function. */
/* Author: Vladimir Sorokin */

/* Copyright 2004 chaos development. */

#include <enviroment.h>

#include "test.h"

/* Function prototypes. */

extern return_t main (int argc, char **argv);
void startup (void);

/* Start of code. */

void startup (void)
{
    handle_t process = HANDLE_THIS_PROCESS;
    return_t return_value;
    uint32_t number_of_arguments;
    char *array_of_arguments[100];
    
    {
        char parameters[STRING_MAX_LENGTH];
        memory_clear (parameters, STRING_MAX_LENGTH);
        process$parameters_get (process, parameters);

        number_of_arguments = arguments_parse (parameters, array_of_arguments);
    }

    return_value = main (number_of_arguments, (char **) array_of_arguments);

    process$exit (process, return_value);

    while (TRUE);
}

