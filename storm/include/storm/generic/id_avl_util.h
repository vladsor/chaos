#ifndef __STORM_GENERIC_ID_AVL_UTIL_H__
#define __STORM_GENERIC_ID_AVL_UTIL_H__

extern void update (_avl_tree_type *_avl_tree, _avl_node_type *node);
extern void update2 (_avl_tree_type *_avl_tree, _avl_node_type *node);

extern _avl_node_type **get_pointer_from_parent (_avl_tree_type *_avl_tree,
                                                _avl_node_type *node);

extern unsigned int get_left_level (_avl_node_type *node);
extern unsigned int get_right_level (_avl_node_type *node);
extern _avl_node_type *get_most_left_node (_avl_node_type *node);
extern _avl_node_type *get_most_right_node (_avl_node_type *node);

extern void exchange (_avl_tree_type *_avl_tree, _avl_node_type *node_a,
                      _avl_node_type *node_b);

#endif /* __STORM_GENERIC_ID_AVL_UTIL_H__ */
