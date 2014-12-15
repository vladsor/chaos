/* Abstract: Startup code file for chaos binaries. This code is what executes
   the main () function. */
/* Author: Vladimir Sorokin */

/* Copyright 2004 chaos development. */

#include <enviroment.h>

/* Function prototypes. */

extern return_t main (int argc, char **argv);
void startup (void);

/* Start of code. */

void startup (void)
{
    handle_t process = HANDLE_THIS_PROCESS;
    return_t return_value;
    uint32_t number_of_arguments;
    char array_of_arguments[100];
    
    {
        char parameters[256];
        process$parameters_get (process, parameters);

        number_of_arguments = arguments_parse (parameters, array_of_arguments);
    }

    return_value = main (number_of_arguments, (char **) array_of_arguments);

    process$exit_code_set (process, return_value);
    
    process$destroy (process);
}

