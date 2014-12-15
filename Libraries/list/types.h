/* $Id: types.h,v 1.2 2001/02/10 21:22:51 jojo Exp $ */
/* Abstract: List type definitions. */
/* Author: Per Lundberg <plundis@chaosdev.org> */

/* Copyright 2000 chaos development. */

#ifndef __LIBRARY_LIST_TYPES_H__
#define __LIBRARY_LIST_TYPES_H__

/* Type definitions. */

typedef struct
{
    LIST_NODE_PART;
} list_node_t;

struct list_iterator_t;

typedef bool (list_iterator_has_next_function_t) (
    struct list_iterator_t *iterator);
typedef list_node_t * (list_iterator_get_next_function_t) (
    struct list_iterator_t *iterator);

/**
 * @brief               Struct of iterator for list.
 */
typedef struct
{
    /**
     * brief            If current node not NULL.
     */
    list_iterator_has_next_function_t *has_next;

    /**
     * brief            Get current node and going to next node.
     */
    list_iterator_get_next_function_t *get_next;
    
    /**
     * brief            Pointer to current node.
     */
    list_node_t *current_node;
    
    /**
     * brief            This iterator is reverse.
     */
    bool is_reverse;
} list_iterator_t;

typedef struct
{
    LIST_PART;
} list_t;

#endif /* !__LIBRARY_LIST_TYPES_H__ */
