#ifndef __STORM_GENERIC_ID_AVL_H__
#define __STORM_GENERIC_ID_AVL_H__

#include <storm/defines.h>
#include <storm/types.h>

#include <storm/generic/memory.h>
#include <storm/generic/memory_global.h>

#include <storm/generic/debug.h>

/* struct node of AVL-tree(AVL-nodes). */
typedef struct
{
  /* pointer to parent node. */
  struct _avl_node_type *parent;

  /* pointer to left child. */
  struct _avl_node_type *left;

  /* pointer to right child. */
  struct _avl_node_type *right;

  /* level of node. */
  unsigned int level;

  /* pointer to key of node. */
  int key[0];
} _avl_node_type;

#define AVL_NODE_PART(x)  \
  _avl_node_type *parent;  \
  _avl_node_type *left;    \
  _avl_node_type *right;   \
  unsigned int level;     \
  x key

/* type of function for compare two keys of AVL-nodes. */
typedef int (*compare_function_type) (void *key1, void *key2);

/* struct AVL-tree. */
typedef struct
{
  /* pointer to root node of AVL-tree. */
  _avl_node_type *root;

  /* number childs in AVL-tree. */
  unsigned int childs;

  /* function of compare two keys of AVL-nodes. */
  compare_function_type compare;
} _avl_tree_type;

#define AVL_TREE_PART            \
  _avl_node_type *root;           \
  unsigned int childs;           \
  compare_function_type compare

/* create AVL-tree. */
extern void _avl_tree_create (_avl_tree_type **_avl_tree,
                      compare_function_type compare_function);

/* destroy AVL-tree. */
extern void _avl_tree_destroy (_avl_tree_type *_avl_tree);

/* add node to AVL-tree. */
extern void _avl_tree_add_node (_avl_tree_type *_avl_tree, 
                               _avl_node_type *new_node);

/* delete node from AVL-tree. */
extern void _avl_tree_delete_node (_avl_tree_type *_avl_tree, 
                                  _avl_node_type *node);

/* search node wirh given key in AVL-tree. */
extern _avl_node_type * _avl_tree_search_node (_avl_tree_type *_avl_tree, 
                                             void *key);

#endif /* __STORM_GENERIC_ID_AVL_H__ */
