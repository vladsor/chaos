#include <enviroment.h>
#include <avl.h>

#include "id_pool.h"

#include "../pool_of_integers/pool_of_integers.h"
#ifdef TEST

//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL 11
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

static range_node_t temp_buffer[1000];
STATIC_POOL(pool, 1000);

static void internal_memory_init (unsigned int size_of_block UNUSED, 
    unsigned int blocks)
{
    pool_of_integers_init (pool, blocks);
}

static void internal_memory_deinit (void)
{
}

static void *internal_memory_allocate (void)
{
    uint32_t index;
    return_t return_value;
    void *pointer;

    return_value = pool_of_integers_allocate (pool, &index);
   
    pointer = temp_buffer + (index * sizeof (range_node_t));
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE + 1, 
    "IAlloc: %u, %p\n", 
    index, pointer);
    
    return pointer;
}

static void internal_memory_deallocate (void *range)
{
    uint32_t index;
    
    index = ((int32_t) range - (uint32_t) temp_buffer) / 
    (sizeof (range_node_t));
    
    pool_of_integers_deallocate (pool, index);
}

raw_memory_interface_t imemory = { 
    internal_memory_init, 
    internal_memory_deinit,
    internal_memory_allocate, 
    internal_memory_deallocate};

return_t debug_print (unsigned int level, char *module_name, 
    char *function_name, unsigned int line, char *message)
{
    printf (message);
}

void print_pool (pool_t *pool)
{
    iterator_t *i;
    range_node_t *node;
    
    printf ("Printing Pool.................................................\n");
    for (i=pool_get_iterator(pool);iterator$has_next (i); )
    {
        node = (range_node_t *) iterator$get_next (i);
        
        printf ("Node: %u-%u.\n", node->key.start, node->key.start + node->key.length - 1);
    }
    printf ("Printing Pool..............................................END\n");
}

void reverse_print_pool (pool_t *pool)
{
    iterator_t *i;
    range_node_t *node;
    uint32_t end = pool->range.start;
    
    printf ("Reverse Printing Pool*****************************************\n");
    for (i=pool_get_iterator(pool);iterator$has_next (i); )
    {
        node = (range_node_t *) iterator$get_next (i);
        
        if (end == node->key.start)
        {
            end = node->key.start + node->key.length;
            continue;
        }
        
        printf ("Node: %u-%u.\n", end, node->key.start - 1);
        
        end = node->key.start + node->key.length;
    }
    
    if (end != pool->range.start + pool->range.length)
    {
        printf ("Node: %u-%u.\n", end, pool->range.start + pool->range.length - 1);
   
    }
    
    printf ("Reverse Printing Pool**************************************END\n");
}

int main (void)
{
  pool_t pool;
  bool return_value;
  range_t range = {0,10000};
  range_t range1 = {0,1000};
  range_t range2 = {5000,1000};
  range_t range3 = {0,1000};
  range_t range4 = {7000,1000};

  internal_memory_init (sizeof (range_node_t), 1000);

  pool_init (&pool, range, imemory);

    printf ("------------------------------------------------------------------------------------");
  return_value = pool_reserve (&pool, range1);
  printf ("RV: %u\n", return_value);
  print_pool(&pool);

    printf ("------------------------------------------------------------------------------------");
  return_value = pool_reserve (&pool, range2);
  printf ("RV: %u\n", return_value);
  print_pool(&pool);

//  return_value = pool_reserve (&pool, range3);
//  printf ("RV: %u\n", return_value);

    printf ("------------------------------------------------------------------------------------");
  return_value = pool_is_full (&pool);
  printf ("RV: %u\n", return_value);
  print_pool(&pool);

    printf ("------------------------------------------------------------------------------------");
  return_value = pool_reserve (&pool, range4);
  printf ("RV: %u\n", return_value);
  reverse_print_pool(&pool);

    printf ("------------------------------------------------------------------------------------");
  return_value = pool_allocate (&pool, &range3);
  printf ("RV: %u\n", return_value);
  print_pool(&pool);

    printf ("------------------------------------------------------------------------------------");
  return_value = pool_is_full (&pool);
  printf ("RV: %u\n", return_value);

    printf ("------------------------------------------------------------------------------------");
  return_value = pool_deallocate (&pool, range1);
  printf ("RV: %u\n", return_value);
  print_pool(&pool);

    printf ("------------------------------------------------------------------------------------");
  return_value = pool_deallocate (&pool, range2);
  printf ("RV: %u\n", return_value);
  print_pool(&pool);

    printf ("------------------------------------------------------------------------------------");
  return_value = pool_is_full (&pool);
  printf ("RV: %u\n", return_value);
  print_pool(&pool);

    printf ("------------------------------------------------------------------------------------");
  return_value = pool_deallocate (&pool, range3);
  printf ("RV: %u\n", return_value);
  print_pool(&pool);

//  id_pool_destroy (&id_pool);

//  SYSTEM(PAUSE);

    printf ("Exiting...\n");

  return 0;
}

#endif
