#include <enviroment.h>

#include "pool_of_integers.h"

//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

//#define TEST

return_t pool_of_integers_init (pool_of_integers_t *p, uint32_t blocks)
{
    unsigned int i = 0;
    int cl1 = -1, cl2 = -1;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	"%s::%s\n",
	__FILE__, __FUNCTION__);

    for (i = 0 ; i < 8 * sizeof (uint32_t) ; i++)
    {
        if (blocks % 2 == 1)
	{
	    if(cl2 == -1)
	    {
		cl2 = i;
	    }
	    cl1 = i;
	}
        blocks >>= 1;
    }
  
    p->pool_capacity = cl1 + (cl1 == cl2 ? 0 : 1);
    p->pool_size = 1 << p->pool_capacity;
    p->size = p->pool_size / (sizeof (int) * 8) * 2;
    
    p->blocks = blocks;
    p->used_blocks = 0;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	"%s::%s size: %u\n",
	__FILE__, __FUNCTION__, p->size * sizeof (int));

    memory_set_uint8 ((uint8_t *) p->map, 0, p->size * sizeof (int));
  
    return POI_RETURN_SUCCESS;
}

static int is_used (pool_of_integers_t *p, uint32_t i)
{
  return POOL_GET (p, i + p->pool_size);
}

return_t pool_of_integers_reserve (pool_of_integers_t *p, uint32_t i)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	"%s::%s pool: %p, integer: %u\n",
	__FILE__, __FUNCTION__, p, i);

    if (is_used (p, i) == 0)
    {
      unsigned int curr = i + p->pool_size;
      unsigned int level;

      POOL_SET_USED(p, curr);

    for (level = 0 ; level < p->pool_capacity ; level++)
    {
      curr /= 2;
      if (POOL_GET(p, curr * 2) == 1 && POOL_GET(p, curr * 2 + 1) == 1)
      {
        POOL_SET_USED(p, curr);
      }
      else
      {
        break;
      }
    }
    
    p->used_blocks++;

    return POI_RETURN_SUCCESS;
  }

  return POI_RETURN_ALREADY_USED;
}

return_t pool_of_integers_allocate (pool_of_integers_t *p, uint32_t *ptr_i)
{
    unsigned int curr = 1;
    unsigned int left, right;
    unsigned int level;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	"%s::%s pool: %p, ptr: %p\n",
	__FILE__, __FUNCTION__, p, ptr_i);

    (*ptr_i) = 0;
  
    if (POOL_GET (p, curr))
    {
	return POI_RETURN_OVERFLOW;
    }
  
    for (level = 0 ; level < p->pool_capacity ; level++)
    {
        left = curr * 2;
	right = curr * 2 + 1;
    
        if (POOL_GET(p, left) == 0)
	{
            curr = left;
        }
	else if (POOL_GET(p, right) == 0)
        {
	    curr = right;
        }
	else
        {
	    return POI_RETURN_OVERFLOW;
        }
    }

    pool_of_integers_reserve (p, curr - p->pool_size);
    (*ptr_i) = curr - p->pool_size;
  
    return POI_RETURN_SUCCESS;
}

return_t pool_of_integers_deallocate (pool_of_integers_t *p, uint32_t i)
{
    unsigned int curr;
    unsigned int level;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	"%s::%s\n",
	__FILE__, __FUNCTION__);
    
    curr = i + p->pool_size;

  if (is_used (p, i) == 0)
  {
    return POI_RETURN_NOT_USED;
  }

  POOL_SET_UNUSED(p, curr);

  for (level = 0 ; level < p->pool_capacity ; level++)
  {
    curr /= 2;
    if (POOL_GET(p, curr * 2) == 0 && POOL_GET(p, curr * 2 + 1) == 0)
    {
      break;
    }
    else if (POOL_GET(p, curr * 2) == 0 || POOL_GET(p, curr * 2 + 1) == 0)
    {
      POOL_SET_UNUSED(p, curr);
    }
  }
  
  p->used_blocks--;
  
  return POI_RETURN_SUCCESS;
}

#ifdef TEST

//#include <stdio.h>

STATIC_POOL(pool,16);

static void print_map ()
{
  int i;
  for(i=0;i<16;i++)
  {
    printf("%i ", is_used(pool, i));
  }
  printf("\n --------- \n");
}

int main(void)
{
  int i;

  printf ("\n");

  pool_of_integers_init (pool, 16);
  
  printf ("PS:%u,PC:%u,S:%u\n", pool->pool_size, pool->pool_capacity,pool->size);
  printf ("used:%i\n",pool->used_blocks);

  pool_of_integers_reserve (pool, 0);
  pool_of_integers_reserve (pool, 1);
  pool_of_integers_reserve (pool, 2);
  pool_of_integers_reserve (pool, 5);
  pool_of_integers_reserve (pool, 3);
  pool_of_integers_allocate (pool, &i);

  printf ("used:%i\n",pool->used_blocks);
  print_map();

  printf("d:%i\n", pool_of_integers_deallocate(pool, 1));
  printf("d:%i\n", pool_of_integers_deallocate(pool, 1));

  pool_of_integers_allocate(pool, &i);
  pool_of_integers_allocate(pool, &i);
  
  printf ("used:%i\n",pool->used_blocks);
  
  print_map();

  for(i=13;i<16;i++)
  {
    printf("%i ", pool_of_integers_reserve(pool, i));
  }

  printf("\n --------- \n");
  pool_of_integers_deallocate(pool, 4);
  pool_of_integers_deallocate(pool, 14);

  for(i=0;i<16;i++)
  {
    printf ("%i ", is_used(pool, i));
  }

  printf("\n");
  printf ("used:%i\n", pool->used_blocks);

  return 0;
}
#endif

