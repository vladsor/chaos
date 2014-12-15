
#ifndef __LIBRARY_AVL_AVL_UTIL_H__
#define __LIBRARY_AVL_AVL_UTIL_H__

extern void update (avl_tree_t *avl_tree, avl_node_t *node);
extern void update2 (avl_tree_t *avl_tree, avl_node_t *node);

extern avl_node_t **get_pointer_from_parent (avl_tree_t *avl_tree,
                                                avl_node_t *node);

extern unsigned int get_left_level (avl_node_t *node);
extern unsigned int get_right_level (avl_node_t *node);
extern avl_node_t *get_most_left_node (avl_node_t *node);
extern avl_node_t *get_most_right_node (avl_node_t *node);

extern void exchange (avl_tree_t *avl_tree, avl_node_t *node_a,
                      avl_node_t *node_b);

enum
{
    NODE_ROOT,
    NODE_LEFT,
    NODE_RIGHT,
};

static inline int get_node_type (avl_node_t *node)
{
    if (node->parent == NULL)
    {
        return NODE_ROOT;
    }
    
    if (((avl_node_t *) ((avl_node_t *) node->parent)->left) == node)
    {
        return NODE_LEFT;
    }
    
    return NODE_RIGHT;
}

#endif /* !__LIBRARY_AVL_AVL_UTIL_H__ */
