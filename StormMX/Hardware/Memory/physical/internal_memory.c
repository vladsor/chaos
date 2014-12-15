#include <enviroment.h>

#include <rpool.h>
#include <ipool.h>

#include "internal_memory.h"

//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

static range_node_t temp_buffer[INTERNAL_MEMORY_SIZE];
STATIC_POOL (pool, INTERNAL_MEMORY_SIZE);

void internal_memory_init (void)
{
    pool_of_integers_init (pool, INTERNAL_MEMORY_SIZE);
}

void internal_memory_deinit (void)
{
}

static void * internal_memory_allocate (void)
{
    uint32_t index;
    return_t return_value;
    void *pointer;

    return_value = pool_of_integers_allocate (pool, &index);
   
    pointer = (void *) ((uint32_t) temp_buffer + 
        (index * sizeof (range_node_t)));
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1, 
        "Internal Allocate: %u, %p\n", 
        index, pointer);
    
    return pointer;
}

static void internal_memory_deallocate (void *pointer)
{
    uint32_t index;
    
    index = ((int32_t) pointer - (uint32_t) temp_buffer) / 
        (sizeof (range_node_t));

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1, 
        "Internal Dellocate: %u, %p\n", 
        index, pointer);
    
    pool_of_integers_deallocate (pool, index);
}

raw_memory_interface_t imemory = 
{ 
    internal_memory_allocate, 
    internal_memory_deallocate
};
