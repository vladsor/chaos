
#ifndef __LIBRARY_RPOOL_RPOOL_H__
#define __LIBRARY_RPOOL_RPOOL_H__

#include <avl.h>
#include "raw_memory.h"

struct range_node_t;

typedef struct
{
    uint32_t start;
    uint32_t length;
} range_t;

typedef range_t * p_range_t;

typedef struct
{
    AVL_NODE_PART (range_t);
  
    struct range_node_t *opposite;
} range_node_t;

typedef range_node_t * p_range_node_t;

typedef struct
{
    range_node_t length_node;
    range_node_t index_node;
} double_range_node_t;

/* struct of store. */
typedef struct
{
    avl_tree_t free_by_length;
    avl_tree_t free_by_index;

    range_t range;

    uint32_t free_count;

    p_raw_memory_t memory;
} pool_t;

#define POOL_INIT \
{ \
    free_by_length: AVL_TREE_INIT, \
    free_by_index: AVL_TREE_INIT, \
    range: {0, 0}, \
    free_count: 0, \
    memory: NULL, \
}

typedef pool_t * p_pool_t;

extern void pool_init (p_pool_t pool, range_t range, p_raw_memory_t memory);

extern return_t pool_allocate (p_pool_t pool, p_range_t range);
extern return_t pool_reserve (p_pool_t pool, range_t range);
extern return_t pool_deallocate (p_pool_t pool, range_t range);

extern iterator_t * pool_get_iterator (p_pool_t pool);

extern bool pool_is_full (p_pool_t pool);
extern bool pool_is_empty (p_pool_t pool);

#endif /* !__LIBRARY_RPOOL_RPOOL_H__ */

