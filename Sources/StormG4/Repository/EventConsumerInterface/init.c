#include <enviroment.h>

#include "../Include/internal.h"

#define DEBUG_MODULE_NAME "Repository"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include <debug/macros.h>
#include <exception/macros.h>


void repository_event_consumer_interface_init (void)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s ()\n",
        DEBUG_MODULE_NAME, __FUNCTION__);
}
