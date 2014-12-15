#include <storm/generic/id_avl.h>
#include <storm/generic/id_avl_util.h>

#define DEBUG                 FALSE
#define VERBOSE_DEBUG         FALSE

/*
  FUNCTION:     _avl_tree_create
  DESCRIPTION:  create AVL-tree.
  ARGUMENTS:    _avl_tree - double pointer to creating struct of tree,
                compare_function - pointer to function to compare two nodes of
                tree.
  RETURN VALUE: none.
*/
void _avl_tree_create (_avl_tree_type **_avl_tree,
                      compare_function_type compare_function)
{
  /* allocate memory for struct of tree. */
  (*_avl_tree) = memory_global_allocate (sizeof (_avl_tree_type));

  /* initialising fields of struct. */
  (*_avl_tree)->root = NULL;
  (*_avl_tree)->childs = 0;
  (*_avl_tree)->compare = compare_function;
}

/*
  FUNCTION:     _avl_tree_destroy
  DESCRIPTION:  destroy AVL-tree.
  ARGUMENTS:    _avl_tree - pointer to struct of tree.
  RETURN VALUE: none.
*/
void _avl_tree_destroy (_avl_tree_type *_avl_tree __attribute__ ((unused)))
{
  /* FIXME: Impelement this. */
}

/*
  FUNCTION:     _avl_tree_add_node
  DESCRIPTION:  add node to AVL-tree.
  ARGUMENTS:    _avl_tree - pointer to struct of tree,
                new_node - pointer to filled struct of added node.
  RETURN VALUE: none.
*/
void _avl_tree_add_node (_avl_tree_type *_avl_tree, _avl_node_type *new_node)
{
  _avl_node_type *current_node, *parent_node;
  _avl_node_type **pointer_from_parent;
  
  DEBUG_MESSAGE (VERBOSE_DEBUG, "add new node at _avl_tree->root");

  /* If root node is empty, */
  if (_avl_tree->root == NULL)
  {
    DEBUG_MESSAGE (VERBOSE_DEBUG, "\n");

    /* add new node in root. */
    _avl_tree->root = new_node;

    return;
  }

  /* else search place for adding */
  current_node = _avl_tree->root;

  do
  {
    parent_node = current_node;

    if (_avl_tree->compare ((void *) new_node->key,
                           (void *) current_node->key) < 0)
    {
      DEBUG_MESSAGE (VERBOSE_DEBUG, "->left");

      pointer_from_parent = (_avl_node_type **) &current_node->left;
      current_node = (_avl_node_type *) current_node->left;
    }
    else
    {
      DEBUG_MESSAGE (VERBOSE_DEBUG, "->right");

      pointer_from_parent = (_avl_node_type **) &current_node->right;
      current_node = (_avl_node_type *) current_node->right;
    }
  } while (current_node != NULL);

  DEBUG_MESSAGE (VERBOSE_DEBUG, "\n");

  /* adding node in found place on tree */
  (*pointer_from_parent) = new_node;
  (_avl_node_type *) new_node->parent = parent_node;

  /* updating tree after adding node. */
  update (_avl_tree, new_node);
}

/*
  FUNCTION:     simple_delete_node
  DESCRIPTION:  simple deletion of AVL-node, e.g. there is no even one child.
  ARGUMENTS:    _avl_tree - pointer to struct of tree,
                node - pointer to struct of deleted node.
  RETURN VALUE: TRUE - if successfull,
                FALSE - if node have both childs.
*/
static bool simple_delete_node (_avl_tree_type *_avl_tree, _avl_node_type *node)
{
  _avl_node_type **pointer_to_node;
  _avl_node_type *pointer_to_parent;

  pointer_to_node = get_pointer_from_parent (_avl_tree, node);

  pointer_to_parent = (_avl_node_type *) node->parent;

  if ((node->left == NULL) && (node->right == NULL))
  {
    (*pointer_to_node) = NULL;
  }
  else if (node->left == NULL)
  {
    (*pointer_to_node) = (_avl_node_type *) node->right;
    (*pointer_to_node)->parent = node->parent;
  }
  else if (node->right == NULL)
  {
    (*pointer_to_node) =  (_avl_node_type *) node->left;
    (*pointer_to_node)->parent = node->parent;
  }
  else
  {
    return FALSE;
  }

  memory_global_deallocate (node);

  if (pointer_to_parent != NULL)
  {
    /* updating tree after deleting node. */
    update2 (_avl_tree, pointer_to_parent);
  }

  return TRUE;
}


/*
  FUNCTION:     _avl_tree_delete_node
  DESCRIPTION:  delete AVL-node.
  ARGUMENTS:    _avl_tree - pointer to struct of tree,
                node - pointer to struct of deleted node.
  RETURN VALUE: none.
*/
void _avl_tree_delete_node (_avl_tree_type *_avl_tree, _avl_node_type *node)
{
  if (!simple_delete_node (_avl_tree, node))
  {
    if (get_left_level (node) > get_right_level (node))
    {
      exchange (_avl_tree, node,
        get_most_right_node ((_avl_node_type *) node->left));

      simple_delete_node (_avl_tree, node);
    }
    else
    {
      exchange (_avl_tree, node,
        get_most_left_node ((_avl_node_type *) node->right));

      simple_delete_node (_avl_tree, node);
    }
  }
}

/*
  FUNCTION:     _avl_tree_search_node
  DESCRIPTION:  search AVL-node with given key.
  ARGUMENTS:    _avl_tree - pointer to struct of tree,
                key - pointer to key.
  RETURN VALUE: pointer to node - if found,
                NULL - otherwise.
*/
_avl_node_type * _avl_tree_search_node (_avl_tree_type *_avl_tree, void *key)
{
  _avl_node_type *current_node = (_avl_node_type *) _avl_tree->root;

  int compare_result;

  while (current_node != NULL)
  {
    compare_result = _avl_tree->compare (key, current_node->key);

    if (compare_result == 0)
    {
      break;
    }
    else if (compare_result < 0)
    {
      current_node = (_avl_node_type *) current_node->left;
    }
    else /* compare_result > 0 */
    {
      current_node = (_avl_node_type *) current_node->right;
    }
  }

  return current_node;
}

