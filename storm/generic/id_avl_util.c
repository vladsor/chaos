#include <storm/generic/id_avl.h>
#include <storm/generic/id_avl_util.h>

#define DEBUG             FALSE
#define VERBOSE_DEBUG     FALSE

unsigned int get_left_level (_avl_node_type *node)
{
  return node->left != NULL ? ((_avl_node_type *) node->left)->level : 0;
}

unsigned int get_right_level (_avl_node_type *node)
{
  return node->right != NULL ? ((_avl_node_type *) node->right)->level : 0;
}

static void update_node (_avl_node_type *node)
{
  DEBUG_MESSAGE (VERBOSE_DEBUG, "updating node %u\n", node);
  
  node->level = MAX_OF_TWO (get_left_level (node), get_right_level (node));
  node->level++;
}

static bool is_balanced (_avl_node_type *node)
{
  unsigned int left_level = get_left_level (node);
  unsigned int right_level = get_right_level (node);
  
  return ( (left_level > right_level) ?
           (left_level - right_level <= 1) :
           (right_level - left_level <= 1) );
}

static _avl_node_type *longest_branch (_avl_node_type *node)
{
  return (_avl_node_type *)
    (get_left_level (node) > get_right_level (node) ? node->left : node->right);
}

static void set_parent (_avl_node_type *node, _avl_node_type *parent_node)
{
  if (node != NULL)
  {
    (_avl_node_type *) node->parent = parent_node;
  }
}

static void swap (_avl_node_type **node_a, _avl_node_type **node_b)
{
  _avl_node_type *temp_node;
  temp_node = (*node_a);
  (*node_a) = (*node_b);
  (*node_b) = temp_node;
}

_avl_node_type **get_pointer_from_parent (_avl_tree_type *_avl_tree,
                                                _avl_node_type *node)
{
  _avl_node_type **pointer_to_node;

  if (node->parent != NULL)
  {
    #define current_parent ((_avl_node_type *) (node->parent))
    if ((_avl_node_type *) current_parent->left == node)
    {
      pointer_to_node = (_avl_node_type **) (&(current_parent->left));
    }
    else
    {
      pointer_to_node = (_avl_node_type **) (&(current_parent->right));
    }
    #undef current_parent
  }
  else
  {
    pointer_to_node = &_avl_tree->root;
  }

  return pointer_to_node;
}

void exchange (_avl_tree_type *_avl_tree, _avl_node_type *node_a,
                      _avl_node_type *node_b)
{
  swap (get_pointer_from_parent (_avl_tree, node_a),
        get_pointer_from_parent (_avl_tree, node_b));
  swap ((_avl_node_type **) &node_a->parent,
        (_avl_node_type **) &node_b->parent);

  swap ((_avl_node_type **) &node_a->left, (_avl_node_type **) &node_b->left);
  set_parent ((_avl_node_type *) node_a->left, node_a);
  set_parent ((_avl_node_type *) node_b->left, node_b);
  
  swap ((_avl_node_type **) &node_a->right, (_avl_node_type **) &node_b->right);
  set_parent ((_avl_node_type *) node_a->right, node_a);
  set_parent ((_avl_node_type *) node_b->right, node_b);

  update_node (node_a);
  update_node (node_b);
}

_avl_node_type *get_most_left_node (_avl_node_type *node)
{
  while (node->left != NULL)
  {
    node = (_avl_node_type *) node->left;
  }

  return node;
}

_avl_node_type *get_most_right_node (_avl_node_type *node)
{
  while (node->right != NULL)
  {
    node = (_avl_node_type *) node->right;
  }

  return node;
}


static bool rotate (_avl_tree_type *_avl_tree,
                    _avl_node_type *node_a,
                    _avl_node_type *node_b,
                    _avl_node_type *node_c)
{
  _avl_node_type *sub_root = NULL;

  if (is_balanced (node_a))
  {
    return FALSE;
  }

  DEBUG_MESSAGE (VERBOSE_DEBUG, "a:[%u], b:[%u], c:[%u]\n", 
                 node_a, node_b, node_c);

  if (node_b == (_avl_node_type *) node_a->left)
  {
    if (node_c == (_avl_node_type *) node_b->left)
    {
      DEBUG_MESSAGE (VERBOSE_DEBUG, "left-left rotaiting\n");

      (_avl_node_type *) node_a->left = (_avl_node_type *) node_b->right;
      if (node_a->left != NULL)
      {
        (_avl_node_type *) ((_avl_node_type *) node_a->left)->parent = node_a;
      }
      
      (_avl_node_type *) node_b->right = node_a;
      if (node_a == _avl_tree->root)
      {
        _avl_tree->root = node_b;
        (_avl_node_type *) (_avl_tree->root)->parent = NULL;
        (_avl_node_type *) node_a->parent = _avl_tree->root;
      }
      else
      {
        (_avl_node_type *) node_b->parent = (_avl_node_type *) node_a->parent;
        (_avl_node_type *) node_a->parent = node_b;
      }
      update_node (node_c);
      update_node (node_a);
      update_node (node_b);

      sub_root = node_b;
    }
    else /* if (node_c == (_avl_node_type *) node_b->right) */
    {
      DEBUG_MESSAGE (VERBOSE_DEBUG, "left-right rotaiting\n");

      (_avl_node_type *) node_a->left = (_avl_node_type *) node_c->right;
      if (node_a->left != NULL)
      {
        (_avl_node_type *) ((_avl_node_type *) node_a->left)->parent = node_a;
      }

      (_avl_node_type *) node_b->right = (_avl_node_type *) node_c->left;
      if (node_b->right != NULL)
      {
        (_avl_node_type *) ((_avl_node_type *) node_b->right)->parent = node_b;
      }

      (_avl_node_type *) node_b->parent = node_c;
      (_avl_node_type *) node_c->left = node_b;
      (_avl_node_type *) node_c->right = node_a;

      if (node_a == _avl_tree->root)
      {
        _avl_tree->root = node_c;
        (_avl_node_type *) (_avl_tree->root)->parent = NULL;
        (_avl_node_type *) node_a->parent = _avl_tree->root;
      }
      else
      {
        (_avl_node_type *) node_c->parent = (_avl_node_type *) node_a->parent;
        (_avl_node_type *) node_a->parent = node_c;
      }
      update_node (node_b);
      update_node (node_a);
      update_node (node_c);

      sub_root = node_c;
    }
  }
  else/* if (node_b == (_avl_node_type *) node_a->right) */
  {
    if (node_c == (_avl_node_type *) node_b->left)
    {
      DEBUG_MESSAGE (VERBOSE_DEBUG, "right-left rotaiting\n");

      (_avl_node_type *) node_a->right = (_avl_node_type *) node_c->left;
      if (node_a->right != NULL)
      {
        (_avl_node_type *) ((_avl_node_type *) node_a->right)->parent = node_a;
      }

      (_avl_node_type *) node_b->left = (_avl_node_type *) node_c->right;
      if (node_b->left != NULL)
      {
        (_avl_node_type *) ((_avl_node_type *) node_b->left)->parent = node_b;
      }

      (_avl_node_type *) node_b->parent = node_c;
      (_avl_node_type *) node_c->right = node_b;
      (_avl_node_type *) node_c->left = node_a;

      if (node_a == _avl_tree->root)
      {
        _avl_tree->root = node_c;
        (_avl_node_type *) (_avl_tree->root)->parent = NULL;
        (_avl_node_type *) node_a->parent = _avl_tree->root;
      }
      else
      {
        (_avl_node_type *) node_c->parent = (_avl_node_type *) node_a->parent;
        (_avl_node_type *) node_a->parent = node_c;
      }
      update_node (node_b);
      update_node (node_a);
      update_node (node_c);

      sub_root = node_c;
    }
    else/* if (node_c == (_avl_node_type *) node_b->right) */
    {
      DEBUG_MESSAGE (VERBOSE_DEBUG, "right-right rotaiting\n");

      (_avl_node_type *) node_a->right = (_avl_node_type *) node_b->left;
      if (node_a->right != NULL)
      {
        (_avl_node_type *) ((_avl_node_type *) node_a->right)->parent = node_a;
      }

      (_avl_node_type *) node_b->left = node_a;
      if (node_a == _avl_tree->root)
      {
        _avl_tree->root = node_b;
        (_avl_node_type *) (_avl_tree->root)->parent = NULL;
        (_avl_node_type *) node_a->parent = _avl_tree->root;
      }
      else
      {
        (_avl_node_type *) node_b->parent = (_avl_node_type *) node_a->parent;
        (_avl_node_type *) node_a->parent = node_b;
      }
      update_node (node_c);
      update_node (node_a);
      update_node (node_b);

      sub_root = node_b;
    }
  }

  if (sub_root->parent != NULL)
  {
    if ((_avl_node_type *) ((_avl_node_type *) sub_root->parent)->left ==
        node_a)
    {
      (_avl_node_type *) ((_avl_node_type *) sub_root->parent)->left = sub_root;
      update_node ((_avl_node_type *) ((_avl_node_type *) sub_root->parent)->left);
    }
    else/* if ((_avl_node_type *) ((_avl_node_type *) sub_root->parent)->right ==
             node_a) */
    {
      (_avl_node_type *) ((_avl_node_type *) sub_root->parent)->right = sub_root;
      update_node ((_avl_node_type *) ((_avl_node_type *) sub_root->parent)->right);
    }
  }
  
  DEBUG_MESSAGE (VERBOSE_DEBUG, "end rotaiting\n");

  return TRUE;
}

void update (_avl_tree_type *_avl_tree, _avl_node_type *node)
{
  _avl_node_type *node_a, *node_b, *node_c;

  node_c = node;

  if (node->parent == NULL)
  {
    return;
  }

  node_b = (_avl_node_type *) node->parent;

  update_node (node_b);

  node_a = (_avl_node_type *) ((_avl_node_type *) node->parent)->parent;

  while (node_a != NULL)
  {
    update_node (node_a);

    if (rotate (_avl_tree, node_a, node_b, node_c))
    {
      break;
    }

    node_a = (_avl_node_type *) node_a->parent;
    node_b = (_avl_node_type *) node_b->parent;
    node_c = (_avl_node_type *) node_c->parent;
  }
}

void update2 (_avl_tree_type *_avl_tree, _avl_node_type *node)
{
  _avl_node_type *node_a, *node_b, *node_c;

  node_a = node;

  while (node_a != NULL)
  {
    update_node (node_a);

    if (!is_balanced (node_a))
    {
      node_b = longest_branch (node_a);
      node_c = longest_branch (node_b);
      
      if (rotate (_avl_tree, node_a, node_b, node_c))
      {
        break;
      }
    }

    node_a = (_avl_node_type *) node_a->parent;
  }
}
