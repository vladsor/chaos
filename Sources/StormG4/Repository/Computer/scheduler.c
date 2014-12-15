#include <enviroment.h>

#define DEBUG_MODULE_NAME "Repository"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include "Include/scheduler.h"

#include <debug/macros.h>
#include <exception/macros.h>

extern volatile list_t computers;

p_computer_t scheduler_get_next_computer (void)
{
    p_computer_t next = NULL;
    
    if (computer_current->node.node.next != NULL)
    {
        next = (p_computer_t) ((p_computer_node_t) 
            computer_current->node.node.next)->computer;
    }
    else if (computers.first != NULL)
    {
        next = (p_computer_t) ((computer_node_t *) computers.first)->computer;
    }    

    return next;
}

void scheduler_add_computer (p_computer_t computer)
{
//    computer->state = COMPUTER_STATE_RUNNING;
    
    list_node_insert ((list_t *) &computers, (list_node_t *) &computer->node, 
        LIST_OPTION_LAST);
}

void scheduler_remove_computer (p_computer_t computer)
{
//    computer->state = COMPUTER_STATE_STOPPED;
    
    list_node_remove ((list_t *) &computers, (list_node_t *) &computer->node);
}

