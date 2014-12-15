
#include <storm/generic/id_avl.h>
#include <storm/generic/id_avl_util.h>
#include <storm/generic/id_pool.h>

/*
  FUNCTION:     range_compare
  DESCRIPTION:  compare given ranges.
  ARGUMENTS:    key1 - pointer to first range,
                key2 - pointer to second range.
  RETURN VALUE: 0 - if first is subset of second,
                <0 - if first is below than second,
                >0 - if first is above than second.
*/
static int range_compare (void *key1, void *key2)
{
  #define range1 ((range_type *) key1)
  #define range2 ((range_type *) key2)

  if (range1->begin < range2->begin)
  {
    if (range1->end < range2->begin)
    {
      return range1->end - range2->begin;
    }

    return 0;
  }

  if (range2->end < range1->begin)
  {
    return range1->begin - range2->end;
  }

  return 0;

  #undef range1
  #undef range2
}

/*
  FUNCTION:     add_range
  DESCRIPTION:  add given range to store.
  ARGUMENTS:    id_pool - pointer to struct of store,
                range - added range.
  RETURN VALUE: none.
*/
static void add_range (id_pool_type *id_pool, range_type range)
{
  id_node_type *node;

  node = (id_node_type *) memory_global_allocate (sizeof (id_node_type));

  node->key = range;
  node->left = node->right = node->parent = NULL;
  node->level = 1;

  _avl_tree_add_node ((_avl_tree_type *) id_pool, (_avl_node_type *) node);
}

/*
  FUNCTION:     is_node_empty
  DESCRIPTION:  check range of node for empty.
  ARGUMENTS:    node - checked node.
  RETURN VALUE: TRUE - if range is empty,
                FALSE - otherwise.
*/
static inline bool is_node_empty (id_node_type *node)
{
  return node->key.begin > node->key.end;
}

/*
  FUNCTION:     id_pool_create
  DESCRIPTION:  create store.
  ARGUMENTS:    id_pool - double pointer to struct of store,
                range - range stored in store.
  RETURN VALUE: none.
*/
void id_pool_create (id_pool_type **id_pool, range_type range)
{
  /* create AVL-tree. */
  _avl_tree_create ((_avl_tree_type **) id_pool, range_compare);

  /* store range. */
  (*id_pool)->range = range;

  /* at first time store is full. */
  add_range (*id_pool, range);
}


/*
  FUNCTION:     id_pool_destroy
  DESCRIPTION:  destroy store.
  ARGUMENTS:    id_pool - pointer to struct of store.
  RETURN VALUE: none.
*/
void id_pool_destroy (id_pool_type *id_pool)
{
  _avl_tree_destroy ((_avl_tree_type *) id_pool);
}

/*
  FUNCTION:     id_pool_allocate_id
  DESCRIPTION:  allocate ID from store.
  ARGUMENTS:    id_pool - pointer to struct of store,
                id - pointer to allocated ID.
  RETURN VALUE: TRUE - if successfull,
                FALSE - otherwise.
*/
bool id_pool_allocate_id (id_pool_type *id_pool, id_type *id)
{
  id_node_type *current_node;

  /* if store is empty, */
  if (id_pool_is_empty (id_pool))
  {
    /* than fail. */
    return FALSE;
  }

  current_node = (id_node_type *) get_most_left_node (
                 (_avl_node_type *) id_pool->root);

  (*id) = current_node->key.begin;

  current_node->key.begin++;

  if (is_node_empty (current_node))
  {
    _avl_tree_delete_node ((_avl_tree_type *) id_pool,
                          (_avl_node_type *) current_node);
  }

  return TRUE;
}

/*
  FUNCTION:     id_pool_reserve_id
  DESCRIPTION:  reserve given ID in store.
  ARGUMENTS:    id_pool - pointer to struct of store,
                id - reserved ID.
  RETURN VALUE: TRUE - if successfull,
                FALSE - otherwise.
*/
bool id_pool_reserve_id (id_pool_type *id_pool, id_type id)
{
  id_node_type *current_id_node;
  range_type reserve_range;
  reserve_range.begin = reserve_range.end = id;
  
  current_id_node = (id_node_type *) _avl_tree_search_node (
                                     (_avl_tree_type *) id_pool,
                                     (void *) &reserve_range);

  if (current_id_node == NULL)
  {
    return FALSE;
  }

  if (id == current_id_node->key.begin)
  {
     current_id_node->key.begin++;
     
     if (is_node_empty (current_id_node))
     {
       _avl_tree_delete_node ((_avl_tree_type *) id_pool,
                             (_avl_node_type *) current_id_node);
     }
  }
  else if (id == current_id_node->key.end)
  {
    current_id_node->key.end--;
  }
  else
  {
    range_type new_range;

    new_range.begin = id + 1;
    new_range.end = current_id_node->key.end;
    current_id_node->key.end = id - 1;

    add_range (id_pool, new_range);
  }  

  return TRUE;
}

/*
  FUNCTION:     id_pool_reserve_range
  DESCRIPTION:  reserve given ID range in store.
  ARGUMENTS:    id_pool - pointer to struct of store,
                id_range - reserved ID range.
  RETURN VALUE: TRUE - if successfull,
                FALSE - otherwise.
*/
bool id_pool_reserve_range (id_pool_type *id_pool, range_type id_range)
{
  id_node_type *current_id_node;
  
  current_id_node = (id_node_type *) _avl_tree_search_node (
                                     (_avl_tree_type *) id_pool,
                                     (void *) &id_range);

  if ((current_id_node == NULL)
 || 
      (id_range.end > current_id_node->key.end)
 ||
      (id_range.begin < current_id_node->key.begin))
  {
    return FALSE;
  }
    

  if (id_range.begin == current_id_node->key.begin)
  {
    current_id_node->key.begin = id_range.end + 1;
     
    if (is_node_empty (current_id_node))
    {
      _avl_tree_delete_node ((_avl_tree_type *) id_pool,
                             (_avl_node_type *) current_id_node);
    }
  }
  else if (id_range.end == current_id_node->key.end)
  {
    current_id_node->key.end = id_range.begin - 1;
  }
  else
  {
    range_type new_range;

    new_range.begin = id_range.end + 1;
    new_range.end = current_id_node->key.end;
    current_id_node->key.end = id_range.begin - 1;

    add_range (id_pool, new_range);
  }  

  return TRUE;
}


/*
  FUNCTION:     id_pool_deallocate_id
  DESCRIPTION:  deallocate ID to store.
  ARGUMENTS:    id_pool - pointer to struct of store,
                id - deallocated ID.
  RETURN VALUE: TRUE - if successfull,
                FALSE - otherwise.
*/
bool id_pool_deallocate_id (id_pool_type *id_pool, id_type id)
{
  id_node_type *current_id_node;
  int compare_result;
  range_type new_range;
  new_range.begin = new_range.end = id;
  
  current_id_node = (id_node_type *) id_pool->root;

  while (current_id_node != NULL)
  {
    compare_result = range_compare (&new_range, &current_id_node->key);

    if (compare_result == 0)
    {
       break;
    }
    else if (compare_result == -1)
    {
      current_id_node->key.begin--;

      if (current_id_node->left != NULL &&
          current_id_node->key.begin != 0)
      {
        id_node_type *most_right_node = (id_node_type *) get_most_right_node
          ((_avl_node_type *) current_id_node->left);

        if (range_compare (&most_right_node->key,
                           &current_id_node->key) == -1)
        {
          current_id_node->key.begin = most_right_node->key.begin;

          _avl_tree_delete_node ((_avl_tree_type *) id_pool,
                                (_avl_node_type *) most_right_node);
        }
      }

      return TRUE;
    }
    else if (compare_result == 1)
    {
      current_id_node->key.end++;

      if (current_id_node->right != NULL &&
          current_id_node->key.end != MAX_ID)
      {
        id_node_type *most_left_node = (id_node_type *) get_most_left_node
          ((_avl_node_type *) current_id_node->right);

        if (range_compare (&most_left_node->key,
                           &current_id_node->key) == 1)
        {
          current_id_node->key.end = most_left_node->key.end;

          _avl_tree_delete_node ((_avl_tree_type *) id_pool,
                                (_avl_node_type *) most_left_node);
        }
      }

      return TRUE;
    }
    else if (compare_result < -1)
    {
      current_id_node =  (id_node_type *) current_id_node->left;
    }
    else /* compare_result > 1 */
    {
      current_id_node = (id_node_type *) current_id_node->right;
    }
  }

  if (current_id_node != NULL)
  {
    return FALSE;
  }

  add_range (id_pool, new_range);

  return TRUE;
}

/*
  FUNCTION:     id_pool_empty
  DESCRIPTION:  check store for emptiness.
  ARGUMENTS:    id_pool - pointer to struct of store.
  RETURN VALUE: TRUE - if store is empty,
                FALSE - otherwise.
*/
bool id_pool_is_empty (id_pool_type *id_pool)
{
  return (id_pool->root == NULL);
}

/*
  FUNCTION:     id_pool_full
  DESCRIPTION:  check store for fullness.
  ARGUMENTS:    id_pool - pointer to struct of store.
  RETURN VALUE: TRUE - if store is full,
                FALSE - otherwise.
*/
bool id_pool_is_full (id_pool_type *id_pool)
{
  return ((id_pool->root != NULL) &&
  ( ((id_node_type *) id_pool->root)->key.begin == id_pool->range.begin) &&
  ( ((id_node_type *) id_pool->root)->key.end == id_pool->range.end));
}
