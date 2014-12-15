#include <enviroment.h>

#include "Include/exception.h"

#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#include <debug/macros.h>

bool output_enabled = TRUE;

return_t exception_init (int argc, char *argv[]) 
{
    int i;
    
    for (i = 1; i < argc; i++)
    {
        if (!string_compare (argv[i], "--output-disable"))
        {
            output_enabled = FALSE;
        }
    }

    exception_hardware_init (argc, argv);
    exception_software_init (argc, argv);

    return 0;
}
