#include <enviroment.h>
#include <interface.h>
#include <repository.h>

#include "block_public.h"

#include <debug.h>
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

object_t *debug_object = NULL;
object_t *memory_object = NULL;

return_t module_start (void)
{
    return_t return_value;

    repository_get_object (&debug_object, "/storm/debug");
    repository_get_object (&memory_object, "/storm/memory");

    return_value = vfat_main (0, NULL);
    
    return return_value;
}
