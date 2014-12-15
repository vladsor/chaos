#include <enviroment.h>

#include "avl.h"
#include "avl_util.h"

//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

unsigned int get_left_level (avl_node_t *node)
{
    return node->left != NULL ? ((avl_node_t *) node->left)->level : 0;
}

unsigned int get_right_level (avl_node_t *node)
{
    return node->right != NULL ? ((avl_node_t *) node->right)->level : 0;
}

static void update_node (avl_node_t *node)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	"%s::%s %p\n", 
	__FILE__, __FUNCTION__, node);
    
    node->level = MAX (get_left_level (node), get_right_level (node));
    node->level++;
}

static bool is_balanced (avl_node_t *node)
{
    unsigned int left_level = get_left_level (node);
    unsigned int right_level = get_right_level (node);
  
    return ((left_level > right_level) ?
	(left_level - right_level <= 1) :
        (right_level - left_level <= 1));
}

static avl_node_t *longest_branch (avl_node_t *node)
{
    return (avl_node_t *)
        (get_left_level (node) > get_right_level (node) ?
        node->left : node->right);
}

static void set_parent (avl_node_t *node, avl_node_t *parent_node)
{
    if (node != NULL)
    {
        (avl_node_t *) node->parent = parent_node;
    }
}

static void swap (avl_node_t **node_a, avl_node_t **node_b)
{
    avl_node_t *temp_node;
    
    temp_node = (*node_a);
    (*node_a) = (*node_b);
    (*node_b) = temp_node;
}

avl_node_t **get_pointer_from_parent (avl_tree_t *avl_tree,
                                                avl_node_t *node)
{
    avl_node_t **pointer_to_node;

    if (node->parent != NULL)
    {
#define current_parent ((avl_node_t *) (node->parent))
        if ((avl_node_t *) current_parent->left == node)
        {
            pointer_to_node = (avl_node_t **) (&(current_parent->left));
        }
        else
        {
            pointer_to_node = (avl_node_t **) (&(current_parent->right));
        }
#undef current_parent
    }
    else
    {
        pointer_to_node = &avl_tree->root;
    }

    return pointer_to_node;
}

void exchange (avl_tree_t *avl_tree, avl_node_t *node_a,
                      avl_node_t *node_b)
{
    swap (get_pointer_from_parent (avl_tree, node_a),
        get_pointer_from_parent (avl_tree, node_b));
    swap ((avl_node_t **) &node_a->parent,
        (avl_node_t **) &node_b->parent);

    swap ((avl_node_t **) &node_a->left, (avl_node_t **) &node_b->left);
    set_parent ((avl_node_t *) node_a->left, node_a);
    set_parent ((avl_node_t *) node_b->left, node_b);
  
    swap ((avl_node_t **) &node_a->right, (avl_node_t **) &node_b->right);
    set_parent ((avl_node_t *) node_a->right, node_a);
    set_parent ((avl_node_t *) node_b->right, node_b);

    update_node (node_a);
    update_node (node_b);
}

avl_node_t *get_most_left_node (avl_node_t *node)
{
    while (node->left != NULL)
    {
        node = (avl_node_t *) node->left;
    }

    return node;
}

avl_node_t *get_most_right_node (avl_node_t *node)
{
    while (node->right != NULL)
    {
        node = (avl_node_t *) node->right;
    }

    return node;
}


static bool rotate (
    avl_tree_t *avl_tree,
    avl_node_t *node_a,
    avl_node_t *node_b,
    avl_node_t *node_c)
{
    avl_node_t *sub_root = NULL;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	"%s::%s a:[%p], b:[%p], c:[%p]\n",
	__FILE__, __FUNCTION__, node_a, node_b, node_c);

    if (is_balanced (node_a))
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
    	    "%s::%s Node is already balanced.\n",
    	    __FILE__, __FUNCTION__);
	    
        return FALSE;
    }

    if (node_b == (avl_node_t *) node_a->left)
    {
        if (node_c == (avl_node_t *) node_b->left)
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "left-left rotating\n");

            (avl_node_t *) node_a->left = (avl_node_t *) node_b->right;

            if (node_a->left != NULL)
            {
                (avl_node_t *) ((avl_node_t *) node_a->left)->parent = node_a;
            }
      
	    (avl_node_t *) node_b->right = node_a;

	    if (node_a == avl_tree->root)
	    {
		avl_tree->root = node_b;
		(avl_node_t *) (avl_tree->root)->parent = NULL;
		(avl_node_t *) node_a->parent = avl_tree->root;
	    }
	    else
	    {
		(avl_node_t *) node_b->parent = 
		    (avl_node_t *) node_a->parent;
		(avl_node_t *) node_a->parent = node_b;
	    }

	    update_node (node_c);
	    update_node (node_a);
	    update_node (node_b);

	    sub_root = node_b;
	}
	else /* if (node_c == (avl_node_type *) node_b->right) */
	{
	    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "left-right rotating\n");

	    (avl_node_t *) node_a->left = (avl_node_t *) node_c->right;

	    if (node_a->left != NULL)
	    {
		(avl_node_t *) ((avl_node_t *) node_a->left)->parent = 
		    node_a;
	    }

	    (avl_node_t *) node_b->right = (avl_node_t *) node_c->left;

	    if (node_b->right != NULL)
	    {
		(avl_node_t *) ((avl_node_t *) node_b->right)->parent = 
		    node_b;
	    }

	    (avl_node_t *) node_b->parent = node_c;
	    (avl_node_t *) node_c->left = node_b;
	    (avl_node_t *) node_c->right = node_a;

	    if (node_a == avl_tree->root)
	    {
		avl_tree->root = node_c;
		(avl_node_t *) (avl_tree->root)->parent = NULL;
		(avl_node_t *) node_a->parent = avl_tree->root;
	    }
	    else
	    {
		(avl_node_t *) node_c->parent = 
		    (avl_node_t *) node_a->parent;
		(avl_node_t *) node_a->parent = node_c;
	    }

	    update_node (node_b);
	    update_node (node_a);
	    update_node (node_c);

	    sub_root = node_c;
	}
    }
    else/* if (node_b == (avl_node_type *) node_a->right) */
    {
	if (node_c == (avl_node_t *) node_b->left)
	{
	    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "right-left rotating\n");

      (avl_node_t *) node_a->right = (avl_node_t *) node_c->left;
      if (node_a->right != NULL)
      {
        (avl_node_t *) ((avl_node_t *) node_a->right)->parent = node_a;
      }

      (avl_node_t *) node_b->left = (avl_node_t *) node_c->right;
      if (node_b->left != NULL)
      {
        (avl_node_t *) ((avl_node_t *) node_b->left)->parent = node_b;
      }

      (avl_node_t *) node_b->parent = node_c;
      (avl_node_t *) node_c->right = node_b;
      (avl_node_t *) node_c->left = node_a;

      if (node_a == avl_tree->root)
      {
        avl_tree->root = node_c;
        (avl_node_t *) (avl_tree->root)->parent = NULL;
        (avl_node_t *) node_a->parent = avl_tree->root;
      }
      else
      {
        (avl_node_t *) node_c->parent = (avl_node_t *) node_a->parent;
        (avl_node_t *) node_a->parent = node_c;
      }
      update_node (node_b);
      update_node (node_a);
      update_node (node_c);

      sub_root = node_c;
    }
	else/* if (node_c == (avl_node_type *) node_b->right) */
	{
	    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "right-right rotating\n");

      (avl_node_t *) node_a->right = (avl_node_t *) node_b->left;
      if (node_a->right != NULL)
      {
        (avl_node_t *) ((avl_node_t *) node_a->right)->parent = node_a;
      }

      (avl_node_t *) node_b->left = node_a;
      if (node_a == avl_tree->root)
      {
        avl_tree->root = node_b;
        (avl_node_t *) (avl_tree->root)->parent = NULL;
        (avl_node_t *) node_a->parent = avl_tree->root;
      }
      else
      {
        (avl_node_t *) node_b->parent = (avl_node_t *) node_a->parent;
        (avl_node_t *) node_a->parent = node_b;
      }
      update_node (node_c);
      update_node (node_a);
      update_node (node_b);

      sub_root = node_b;
    }
  }

  if (sub_root->parent != NULL)
  {
    if ((avl_node_t *) ((avl_node_t *) sub_root->parent)->left ==
        node_a)
    {
      (avl_node_t *) ((avl_node_t *) sub_root->parent)->left = sub_root;
      update_node ((avl_node_t *) ((avl_node_t *) sub_root->parent)->left);
    }
    else/* if ((avl_node_t *) ((avl_node_t *) sub_root->parent)->right == node_a) */
    {
      (avl_node_t *) ((avl_node_t *) sub_root->parent)->right = sub_root;
      update_node ((avl_node_t *) ((avl_node_t *) sub_root->parent)->right);
    }
  }
  
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "end rotaiting\n");

    return TRUE;
}

void update (avl_tree_t *avl_tree, avl_node_t *node)
{
    avl_node_t *node_a, *node_b, *node_c;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s::%s\n",
        __FILE__, __FUNCTION__);

    node_c = node;

    if (node->parent == NULL)
    {
        return;
    }

    node_b = (avl_node_t *) node->parent;

    update_node (node_b);

    node_a = (avl_node_t *) ((avl_node_t *) node->parent)->parent;

    while (node_a != NULL)
    {
        update_node (node_a);

        if (rotate (avl_tree, node_a, node_b, node_c))
        {
            break;
        }

        node_a = (avl_node_t *) node_a->parent;
        node_b = (avl_node_t *) node_b->parent;
        node_c = (avl_node_t *) node_c->parent;
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s::%s EXIT\n",
        __FILE__, __FUNCTION__);
}

void update2 (avl_tree_t *avl_tree, avl_node_t *node)
{
    avl_node_t *node_a, *node_b, *node_c;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
	"%s::%s\n",
	__FILE__, __FUNCTION__);

    node_a = node;

    while (node_a != NULL)
    {
        update_node (node_a);

        if (!is_balanced (node_a))
        {
            node_b = longest_branch (node_a);
            node_c = longest_branch (node_b);
      
            if (rotate (avl_tree, node_a, node_b, node_c))
            {
                break;
            }
        }

        node_a = (avl_node_t *) node_a->parent;
    }
}

