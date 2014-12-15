#include <enviroment.h>

#define DEBUG_MODULE_NAME "Kernel"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include <Classes/kernel.h>

#include "../event_consumer_interfaces.h"
#include "Include/debug_event_class.h"

#include <debug/macros.h>

static void handler (context_t context UNUSED, 
    uint32_t level, const wchar_t *module_name, const wchar_t *function_name, 
    uint32_t line, const wchar_t *message)
{
    system_debug_printw (level, module_name, (const char *) function_name, line, 
        message);
}    

event_consumer_interface_reference_t debug_consumer_init (void)
{
    event_consumer_interface_reference_t interface;
    
    interface = debug_consumer_interface_register (EVENT_CONSUMER_TYPE_PUSH, 
        &handler, REFERENCE_NULL);

    return interface;
}    

