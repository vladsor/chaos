
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

typedef struct
{
    AVL_NODE_PART (range_t);
  
    struct range_node_t *opposite;
} range_node_t;

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

    raw_memory_interface_t memory;
} pool_t;

extern void pool_init (pool_t *pool, range_t range, raw_memory_interface_t memory);

extern return_t pool_allocate (pool_t *pool, range_t *range);
extern return_t pool_reserve (pool_t *pool, range_t range);
extern return_t pool_deallocate (pool_t *pool, range_t range);

extern iterator_t * pool_get_iterator (pool_t *pool);

extern bool pool_is_full (pool_t *pool);
extern bool pool_is_empty (pool_t *pool);

#endif /* !__LIBRARY_RPOOL_RPOOL_H__ */

