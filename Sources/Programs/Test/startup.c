/* Abstract: Startup code file for chaos binaries. This code is what executes
   the main () function. */
/* Author: Vladimir Sorokin */

/* Copyright 2004 chaos development. */

#include <enviroment.h>

#include "test.h"

#define DEBUG_MODULE_NAME "StartUp"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include <debug/macros.h>

/* Function prototypes. */

extern return_t main (int argc, char **argv);
extern void _startup (uint64_t function UNUSED, context_t context UNUSED, 
    sequence_t parameters_in UNUSED, sequence_t parameters_inout UNUSED, 
    sequence_t parameters_out UNUSED);

/* Start of code. */

void _startup (uint64_t function UNUSED, context_t context UNUSED, 
    sequence_t parameters_in UNUSED, sequence_t parameters_inout UNUSED, 
    sequence_t parameters_out UNUSED)
{
//    char tmp[256] = "Hello world!\n";
//    system_call_debug_print (0, NULL, NULL, 0, tmp);

    main (0, NULL);

    system_call_computer_return ();
}
