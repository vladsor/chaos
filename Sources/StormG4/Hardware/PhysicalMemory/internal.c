#include <enviroment.h>

#include "Include/internal.h"

#define DEBUG_MODULE_NAME "PhysicalMemory"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include <debug/macros.h>

range_node_t node_pool_global[INTERNAL_MEMORY_SIZE];

static_pool_of_integers_t node_allocator_global;

void internal_memory_init (p_physical_memory_t memory)
{
    pool_of_integers_init (memory->node_allocator, INTERNAL_MEMORY_SIZE);
}

void internal_memory_deinit (p_physical_memory_t memory UNUSED)
{
}

void * internal_memory_allocate (p_raw_memory_t interface)
{
    uint32_t index;
    return_t return_value;
    void *pointer;
    p_physical_memory_t memory;
    
    memory = ((raw_memory_t *) interface)->data;

    return_value = pool_of_integers_allocate (memory->node_allocator, &index);
   
    pointer = (void *) ((uint32_t) memory->node_pool + 
        (index * sizeof (range_node_t)));
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1, 
        "Internal Allocate: %u, %p\n", 
        index, pointer);
    
    return pointer;
}

void internal_memory_deallocate (p_raw_memory_t interface, void *pointer)
{
    uint32_t index;
    p_physical_memory_t memory;
    
    memory = ((raw_memory_t *) interface)->data;
    
    index = ((int32_t) pointer - (uint32_t) memory->node_pool) / 
        (sizeof (range_node_t));

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1, 
        "Internal Dellocate: %u, %p\n", 
        index, pointer);
    
    pool_of_integers_deallocate (memory->node_allocator, index);
}

