#include <enviroment.h>

#include "avl.h"
#include "avl_util.h"

//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

static bool avl_tree_iterator_has_next (avl_tree_iterator_t *iterator)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s::%s (%p)\n",
        __FILE__, __FUNCTION__, iterator);

    return iterator->current_node != NULL;
}

static avl_node_t * avl_tree_iterator_get_next (avl_tree_iterator_t *iterator)
{
    avl_node_t *current_node;
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s::%s (%p)\n",
        __FILE__, __FUNCTION__, iterator);

    current_node = iterator->current_node;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s::%s (current_node: %p, left: %p, right: %p, parent: %p)\n",
        __FILE__, __FUNCTION__, current_node, current_node->left, 
        current_node->right, current_node->parent);

    if (current_node != NULL)
    {
        avl_node_t *next_node = NULL;

        if (!iterator->is_reverse)
        {
            if (current_node->right != NULL)
            {
                next_node = get_most_left_node (
                    (avl_node_t *) current_node->right);
            }
            else
            {
                avl_node_t *prev_node;

                prev_node = current_node;
                next_node = (avl_node_t *) current_node->parent;

                while (next_node != NULL)
                {
                    if ((avl_node_t *) next_node->left == prev_node)
                    {
                        break;
                    }

                    prev_node = next_node;
                    next_node = (avl_node_t *) next_node->parent;
                }
            }
        }
        else
        {
            if (current_node->left != NULL)
            {
                next_node = get_most_right_node (
                    (avl_node_t *) current_node->left);
            }
            else
            {
                avl_node_t *prev_node;

                prev_node = current_node;
                next_node = (avl_node_t *) current_node->parent;

                while (next_node != NULL)
                {
                    if ((avl_node_t *) next_node->right == prev_node)
                    {
                        break;
                    }

                    prev_node = next_node;
                    next_node = (avl_node_t *) next_node->parent;
                }
            }
        }
        
        iterator->current_node = next_node;
    }

    return current_node;  
}

/*
  FUNCTION:     avl_tree_create
  DESCRIPTION:  create AVL-tree.
  ARGUMENTS:    avl_tree - double pointer to creating struct of tree,
                compare_function - pointer to function to compare two nodes of
                tree.
  RETURN VALUE: none.
*/
void avl_tree_create (avl_tree_t *avl_tree, compare_function_t compare_function)
{
    /* initialising fields of struct. */
    avl_tree->root = NULL;
    avl_tree->childs = 0;
    avl_tree->compare = compare_function;

    avl_tree->iterator.is_reverse = FALSE;    
    avl_tree->iterator.current_node = NULL;
    avl_tree->iterator.has_next = (avl_tree_iterator_has_next_function_t *)
        &avl_tree_iterator_has_next;
    avl_tree->iterator.get_next = (avl_tree_iterator_get_next_function_t *)
        &avl_tree_iterator_get_next;
}

/*
  FUNCTION:     avl_tree_destroy
  DESCRIPTION:  destroy AVL-tree.
  ARGUMENTS:    avl_tree - pointer to struct of tree.
  RETURN VALUE: none.
*/
void avl_tree_destroy (avl_tree_t *avl_tree UNUSED)
{
  /* FIXME: Impelement this. */
}

/*
  FUNCTION:     avl_tree_add_node
  DESCRIPTION:  add node to AVL-tree.
  ARGUMENTS:    avl_tree - pointer to struct of tree,
                new_node - pointer to filled struct of added node.
  RETURN VALUE: none.
*/
void avl_tree_add_node (avl_tree_t *avl_tree, avl_node_t *new_node)
{
    avl_node_t *current_node, *parent_node;
    avl_node_t **pointer_from_parent;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s::%s Node:%p\n",
        __FILE__, __FUNCTION__, new_node);
    
    new_node->parent = NULL;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->level = 1;
      
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "add new node at avl_tree->root");

    /* If root node is empty, */
    if (avl_tree->root == NULL)
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "\n");

        /* add new node in root. */
        avl_tree->root = new_node;

        return;
    }

    /* else search place for adding */
    current_node = avl_tree->root;

    do
    {
        parent_node = current_node;

        if (avl_tree->compare ((void *) current_node->key, 
            (void *) new_node->key) < 0)
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "->left");

            pointer_from_parent = (avl_node_t **) &current_node->left;
            current_node = (avl_node_t *) current_node->left;
        }
        else
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "->right");
            
            pointer_from_parent = (avl_node_t **) &current_node->right;
            current_node = (avl_node_t *) current_node->right;
        }
    } while (current_node != NULL);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "...DONE\n");

    /* adding node in found place on tree */
    (*pointer_from_parent) = new_node;
    (avl_node_t *) new_node->parent = parent_node;

    /* updating tree after adding node. */
    update (avl_tree, new_node);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s::%s EXIT\n",
        __FILE__, __FUNCTION__);
}

/*
  FUNCTION:     simple_delete_node
  DESCRIPTION:  simple deletion of AVL-node, e.g. there is no even one child.
  ARGUMENTS:    avl_tree - pointer to struct of tree,
                node - pointer to struct of deleted node.
  RETURN VALUE: TRUE - if successfull,
                FALSE - if node have both childs.
*/
static bool simple_delete_node (avl_tree_t *avl_tree, avl_node_t *node)
{
    avl_node_t **pointer_to_node;
    avl_node_t *pointer_to_parent;

    pointer_to_node = get_pointer_from_parent (avl_tree, node);

    pointer_to_parent = (avl_node_t *) node->parent;

    if ((node->left == NULL) && (node->right == NULL))
    {
        (*pointer_to_node) = NULL;
    }
    else if (node->left == NULL)
    {
        (*pointer_to_node) = (avl_node_t *) node->right;
        (*pointer_to_node)->parent = node->parent;
    }
    else if (node->right == NULL)
    {
        (*pointer_to_node) =  (avl_node_t *) node->left;
        (*pointer_to_node)->parent = node->parent;
    }
    else
    {
        return FALSE;
    }

    if (pointer_to_parent != NULL)
    {
        /* updating tree after deleting node. */
        update2 (avl_tree, pointer_to_parent);
    }

    return TRUE;
}


/*
  FUNCTION:     avl_tree_delete_node
  DESCRIPTION:  delete AVL-node.
  ARGUMENTS:    avl_tree - pointer to struct of tree,
                node - pointer to struct of deleted node.
  RETURN VALUE: none.
*/
void avl_tree_delete_node (avl_tree_t *avl_tree, avl_node_t *node)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s::%s Node: %p\n",
        __FILE__, __FUNCTION__, node);
    

    if (!simple_delete_node (avl_tree, node))
    {
        if (get_left_level (node) > get_right_level (node))
        {
            exchange (avl_tree, node,
                get_most_right_node ((avl_node_t *) node->left));
                
            simple_delete_node (avl_tree, node);
        }
        else
        {
            exchange (avl_tree, node,
                get_most_left_node ((avl_node_t *) node->right));
                
            simple_delete_node (avl_tree, node);
        }
    }
}

void avl_tree_update_node (avl_tree_t *avl_tree, avl_node_t *node)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s::%s Node: %p\n",
        __FILE__, __FUNCTION__, node);

    avl_tree_delete_node (avl_tree, node);
    avl_tree_add_node (avl_tree, node);
}

/*
  FUNCTION:     avl_tree_search_node
  DESCRIPTION:  search AVL-node with given key.
  ARGUMENTS:    avl_tree - pointer to struct of tree,
                key - pointer to key.
  RETURN VALUE: pointer to node - if found,
                NULL - otherwise.
*/
avl_node_t * avl_tree_search_node (avl_tree_t *avl_tree, void *key, 
    unsigned int condition)
{
    int compare_result;
    avl_node_t *current_node;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s::%s Tree: %p, Key: %p, Condition: %u.\n", 
        __FILE__, __FUNCTION__, avl_tree, key, condition);

    current_node = (avl_node_t *) avl_tree->root;

    while (current_node != NULL)
    {
        compare_result = avl_tree->compare (current_node->key, key);

        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
            "%s::%s Current node: %p; Compare: %i.\n", 
            __FILE__, __FUNCTION__, current_node, compare_result);

        if ((condition == CONDITION_EQUAL) && (compare_result == 0))
        {
            break;
        }
        else if ((condition == CONDITION_MORE) && (compare_result < 0))
        {
            break;
        }
        else if ((condition == CONDITION_LESS) && (compare_result > 0))
        {
            break;
        }
        else if ((condition == CONDITION_NOT_EQUAL) && (compare_result != 0))
        {
            break;
        }
        else if ((condition == CONDITION_EQUAL_OR_MORE) && (compare_result <= 0))
        {
           break;
        }
        else if ((condition == CONDITION_EQUAL_OR_LESS) && (compare_result >= 0))
        {
           break;
        }
        else if (compare_result < 0)
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
                "%s::%s Next is left.\n", 
                __FILE__, __FUNCTION__);
        
           current_node = (avl_node_t *) current_node->left;
        }
        else /* compare_result > 0 */
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
                "%s::%s Next is right.\n", 
                __FILE__, __FUNCTION__);
        
            current_node = (avl_node_t *) current_node->right;
        }
    }
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s::%s Returns: %p.\n", 
        __FILE__, __FUNCTION__, current_node);

    return current_node;
}

avl_node_t * avl_tree_search_nearest_node (avl_tree_t *avl_tree, void *key, 
    unsigned int *condition)
{
    int compare_result;
    avl_node_t *current_node = NULL;
    avl_node_t *optimum_node = NULL;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s::%s Tree: %p, Key: %p, Condition: %p.\n", 
        __FILE__, __FUNCTION__, avl_tree, key, condition);

    if (((*condition) != CONDITION_LESS) && ((*condition) != CONDITION_MORE))
    {
        return NULL;
    }
    
    current_node = (avl_node_t *) avl_tree->root;

    while (current_node != NULL)
    {
        compare_result = avl_tree->compare (current_node->key, key);

        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
            "%s::%s Current node: %p; Compare: %i.\n", 
            __FILE__, __FUNCTION__, current_node, compare_result);

        if (compare_result == 0)
        {
            optimum_node = current_node;
            (*condition) = CONDITION_EQUAL;
            
            break;
        }
        else if (compare_result < 0)
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
                "%s::%s Next is left.\n", 
                __FILE__, __FUNCTION__);

            if ((*condition) == CONDITION_MORE)
            {
                optimum_node = current_node;
            }
        
            current_node = (avl_node_t *) current_node->left;
        }
        else /* compare_result > 0 */
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
                "%s::%s Next is right.\n", 
                __FILE__, __FUNCTION__);

            if ((*condition) == CONDITION_LESS)
            {
                optimum_node = current_node;
            }
        
            current_node = (avl_node_t *) current_node->right;
        }
    }

    return optimum_node;
}

avl_node_t * avl_tree_get_smallest_node (avl_tree_t *avl_tree)
{
    avl_node_t *current_node;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s::%s Tree: %p.\n", 
        __FILE__, __FUNCTION__, avl_tree);

    current_node = (avl_node_t *) avl_tree->root;

    while (current_node->left != NULL)
    {
        current_node = (avl_node_t *) current_node->left;
    }
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s::%s Returns: %p.\n", 
        __FILE__, __FUNCTION__, current_node);

    return current_node;
}

avl_node_t * avl_tree_get_largest_node (avl_tree_t *avl_tree)
{
    avl_node_t *current_node;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s::%s Tree: %p.\n", 
        __FILE__, __FUNCTION__, avl_tree);

    current_node = (avl_node_t *) avl_tree->root;

    while (current_node->right != NULL)
    {
        current_node = (avl_node_t *) current_node->right;
    }
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s::%s Returns: %p.\n", 
        __FILE__, __FUNCTION__, current_node);

    return current_node;
}

avl_tree_iterator_t * avl_tree_get_iterator (avl_tree_t *avl_tree)
{
    avl_tree->iterator.is_reverse = FALSE;
    avl_tree->iterator.current_node = avl_tree_get_smallest_node (avl_tree);
    
    return &(avl_tree->iterator);
}

avl_tree_iterator_t * avl_tree_get_reverse_iterator (avl_tree_t *avl_tree)
{
    avl_tree->iterator.is_reverse = TRUE;
    avl_tree->iterator.current_node = avl_tree_get_largest_node (avl_tree);
    
    return &(avl_tree->iterator);
}

