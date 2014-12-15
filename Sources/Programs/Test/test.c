
#include <enviroment.h>

#include "test.h"

#define DEBUG_MODULE_NAME "StartUp"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include <debug/macros.h>

return_t main (int argc, char *argv[])
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%u, %p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        argc, argv);

//    ((uint8_t *) NULL)[0] = 1;

    return 0;
}
