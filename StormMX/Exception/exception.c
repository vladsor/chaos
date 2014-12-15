#include <enviroment.h>

#include "Include/exception.h"

#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#include <debug/macros.h>

return_t exception_init (int argc UNUSED, char *argv[] UNUSED) 
{
    exception_hardware_init (argc, argv);
    exception_software_init (argc, argv);

    return 0;
}
