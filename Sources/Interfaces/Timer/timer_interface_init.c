#include <enviroment.h>

#include "../interfaces.h"
#include "../classes.h"
//#include <Interfaces/init.h>
//#include <Interfaces/namespace.h>
#include <Classes/kernel.h>

#include "timer_interface.h"

#define DEBUG_MODULE_NAME "Timer"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

static uint32_t read_milli (context_t context UNUSED)
{
    uint32_t ticks;
    
    timer_read (0, &ticks);
    
    return ticks * 1000 / 100;
}

static timer_interface_table_t table = 
{
    &read_milli,
};

/* Main function. */

interface_reference_t timer_interface_init (void)
{
    return timer_interface_register (&table);
}

