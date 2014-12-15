#ifndef __STORM_GENERIC_ID_POOL_H__
#define __STORM_GENERIC_ID_POOL_H__

#include <storm/defines.h>
#include <storm/limits.h>
#include <storm/types.h>

#include <storm/generic/memory.h>
#include <storm/generic/memory_global.h>

#include <storm/generic/id_avl.h>
#include <storm/generic/id_avl_util.h>

/* struct for store ranges of ID values. */
typedef struct
{
  /* begin range */
  id_type begin;
  
  /* end range */
  id_type end;
} range_type;

/* struct of node storing range of ID values. */
typedef struct
{
  /* AVL-node, type of key is range of ID values. */
  AVL_NODE_PART (range_type);
} id_node_type;

/* struct of store. */
typedef struct
{
  /* information about AVL-tree. */
  AVL_TREE_PART;

  /* stored range. */
  range_type range;
} id_pool_type;

/* Create store with given stored range. */
extern void id_pool_create (id_pool_type **id_pool, range_type range);

/* Destroy store. */
extern void id_pool_destroy (id_pool_type *id_pool);

/* Aloocate ID from given store. */
extern bool id_pool_allocate_id (id_pool_type *id_pool, id_type *id);

/* Deallocate ID to given store. */
extern bool id_pool_deallocate_id (id_pool_type *id_pool, id_type id);

/* Reserve given ID in given store. */
extern bool id_pool_reserve_id (id_pool_type *id_pool, id_type id);

/* Reserve given ID range in given store. */
extern bool id_pool_reserve_range (id_pool_type *id_pool, range_type range_id);

/* Check store for fullness. */
extern bool id_pool_is_full (id_pool_type *id_pool);

/* Check store for emptiness. */
extern bool id_pool_is_empty (id_pool_type *id_pool);

#endif /* __STORM_GENERIC_ID_POOL_H__ */
