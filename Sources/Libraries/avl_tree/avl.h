
#ifndef __LIBRARY_AVL_AVL_H__
#define __LIBRARY_AVL_AVL_H__

/**
 * @brief               Struct node of AVL-tree(AVL-nodes). 
 */
typedef struct
{
    /**
     * @brief           Pointer to parent node. 
     */
    struct avl_node_t *parent;

    /**
     * @brief           Pointer to left child. 
     */
    struct avl_node_t *left;

    /**
     * @brief           Pointer to right child. 
     */
    struct avl_node_t *right;

    /**
     * @brief           Level of node. 
     */
    unsigned int level;

    /**
     * @brief           Pointer to key of node. 
     */
    int key[0];
  
} avl_node_t;

#define AVL_NODE_PART(x) \
    avl_node_t *parent;  \
    avl_node_t *left;    \
    avl_node_t *right;   \
    unsigned int level;  \
    x key

struct avl_tree_iterator_t;

typedef bool (avl_tree_iterator_has_next_function_t) (
    struct avl_tree_iterator_t *iterator);
typedef avl_node_t * (avl_tree_iterator_get_next_function_t) (
    struct avl_tree_iterator_t *iterator);

/**
 * @brief               Struct of iterator for AVL-tree.
 */
typedef struct
{
    /**
     * brief            If current node not NULL.
     */
    avl_tree_iterator_has_next_function_t *has_next;

    /**
     * brief            Get current node and going to next node.
     */
    avl_tree_iterator_get_next_function_t *get_next;
    
    /**
     * brief            Pointer to current node.
     */
    avl_node_t *current_node;
    
    /**
     * brief            This iterator is reverse.
     */
    bool is_reverse;
    
} avl_tree_iterator_t;

/**
 * @brief               Struct of AVL-tree. 
 */
typedef struct
{
    /**
     * @brief           Pointer to root node of AVL-tree. 
     */
    avl_node_t *root;

    /**
     * @brief           Number childs in AVL-tree. 
     */
    unsigned int childs;

    /**
     * @brief           Function of compare two keys of AVL-nodes. 
     */
    compare_function_t compare;

    /**
     * @brief           Iterator for AVL-tree.
     */  
    avl_tree_iterator_t iterator;
    
} avl_tree_t;

#define AVL_TREE_PART              \
    avl_node_t *root;              \
    unsigned int childs;           \
    compare_function_t compare

/**
 * @brief               Create AVL-tree. 
 * @param avl_tree      Pointer to the struct of tree.
 * @param compare_function
 *                      Pointer to function for compare two nodes of tree.
 */
extern void avl_tree_create (avl_tree_t *avl_tree, compare_function_t compare_function);

/**
 * @brief               Destroy AVL-tree. 
 * @param avl_tree      Pointer to the struct of tree.
 */
extern void avl_tree_destroy (avl_tree_t *avl_tree);

/**
 * @brief               Add node to AVL-tree. 
 * @param avl_tree      Pointer to the struct of tree.
 * @param new_node      Pointer to filled struct of added node.
 */
extern void avl_tree_add_node (avl_tree_t *avl_tree, avl_node_t *new_node);

/**
 * @brief               Delete node from AVL-tree.
 * @param avl_tree      Pointer to the struct of tree.  
 * @param node          Pointer to struct of deleted node.
 */
extern void avl_tree_delete_node (avl_tree_t *avl_tree, avl_node_t *node);

/**
 * @brief               Update node in AVL-tree after key modification.
 * @param avl_tree      Pointer to the struct of tree.  
 * @param node          Pointer to struct of updated node.
 */
extern void avl_tree_update_node (avl_tree_t *avl_tree, avl_node_t *node);

/**
 * @brief               Search node wirh given key in AVL-tree. 
 * @param avl_tree      Pointer to the struct of tree.
 * @param key           Pointer to key.
 * @param condition     Condition of node`s equals.
 * @return              Pointer to node - if found, NULL - otherwise.
 */
extern avl_node_t * avl_tree_search_node (avl_tree_t *avl_tree, void *key, 
    unsigned int condition);

/**
 * @brief               Search node nearest to given key or equal.
 * @param avl_tree      Pointer to the struct of tree.
 * @param key           Pointer to key.
 * @param condition     Pointer to condition (must be CONDITION_LESS or 
 *                          CONDITION_MORE), if found equal node, condition
 *                          changed to CONDITION_EQUAL.
 * @return              Pointer to node - if found, NULL - otherwise.    
 */
extern avl_node_t *avl_tree_search_nearest_node (avl_tree_t *avl_tree, 
    void *key, unsigned int *condition);

/**
 * @brief               Get smallest node stored in AVL-tree.
 * @param avl_tree      Pointer to the struct of tree.
 * @return              Pointer to node - if tree not empty, NULL - otherwise.
 */
extern avl_node_t * avl_tree_get_smallest_node (avl_tree_t *avl_tree);

/**
 * @brief               Get largest node stored in AVL-tree.
 * @param avl_tree      Pointer to the struct of tree.
 * @return              Pointer to node - if tree not empty, NULL - otherwise.
 */
extern avl_node_t * avl_tree_get_largest_node (avl_tree_t *avl_tree);

/**
 * @brief               Get iterator from smaller to larger node.
 * @param avl_tree      Pointer to the struct of tree.
 * @return              Pointer to iterator.
 */
extern avl_tree_iterator_t * avl_tree_get_iterator (avl_tree_t *avl_tree);

/**
 * @brief               Get iterator from larger to smaller node.
 * @param avl_tree      Pointer to the struct of tree.
 * @return              Pointer to iterator.
 */
extern avl_tree_iterator_t * avl_tree_get_reverse_iterator (
    avl_tree_t *avl_tree);

#define AVL_TREE_INIT \
{ \
    root: NULL, \
    childs: 0, \
    compare: NULL, \
    iterator: {NULL,NULL,NULL,FALSE}, }

#endif /* !__LIBRARY_AVL_AVL_H__ */

