/* $Id: list.c,v 1.2 2001/02/10 21:22:48 jojo Exp $ */
/* Abstract: Linked list code. */
/* Author: Per Lundberg <plundis@chaosdev.org> */

/* Copyright 2000 chaos development. */

#include <enviroment.h>

#include "list.h"

static bool list_iterator_has_next (list_iterator_t *iterator)
{
    return iterator->current_node != NULL;
}

static list_node_t * list_iterator_get_next (list_iterator_t *iterator)
{
    list_node_t *current_node;
    
    current_node = iterator->current_node;
    
    if (current_node != NULL)
    {
        if (!iterator->is_reverse)
        {
            iterator->current_node = (list_node_t *) current_node->next;
        }
        else
        {
            iterator->current_node = (list_node_t *) current_node->previous;
        }
    }
    
    return current_node;
}

return_t list_create (
    list_t *list)
{
    if (list == NULL)
    {
        return LIST_RETURN_INVALID_ARGUMENT;
    }

    list->first = NULL;
    list->last = NULL;
    list->number_of_nodes = 0;

    list->iterator.is_reverse = FALSE;    
    list->iterator.current_node = NULL;
    list->iterator.has_next = (list_iterator_has_next_function_t *)
        &list_iterator_has_next;
    list->iterator.get_next = (list_iterator_get_next_function_t *)
        &list_iterator_get_next;

    return LIST_RETURN_SUCCESS;
}

/* Insert a node into the list. */

return_t list_node_insert (
    list_t *list, 
    list_node_t *node,
    unsigned int options)
{
    /* Check the input arguments. */

    if (list == NULL || node == NULL)
    { 
        return LIST_RETURN_INVALID_ARGUMENT;
    }

    list->number_of_nodes++;

    if (options & LIST_OPTION_LAST)
    {
        (struct list_node_t *) node->previous = 
            (struct list_node_t *) list->last;

        node->next = NULL;
    
        if (list->last != NULL)
        {
            (list_node_t *) ((list_node_t *) list->last)->next = node;
        }
        else
        {
            (list_node_t *) list->first = node;
        }
        (list_node_t *) list->last = node;
    }
    else
    {
        node->previous = NULL;
        node->next = list->first;

        if (list->first != NULL)
        {
            (list_node_t *) ((list_node_t *) list->first)->previous = node;
        }
        else
        {
            (list_node_t *) list->last = node;
        }
        (list_node_t *) list->first = node;
    }

    return LIST_RETURN_SUCCESS;
}

/* Delete a node from a list. */

return_t list_node_remove (
    list_t *list, 
    list_node_t *node)
{
    list_node_t *next, *previous;

    /* Check the input arguments. */

    if (list == NULL || node == NULL)
    {
        return LIST_RETURN_INVALID_ARGUMENT;
    }

    list->number_of_nodes--;

    previous = (list_node_t *) node->previous;
    next = (list_node_t *) node->next;

    /* First entry in the list? */

    if (previous == NULL)
    {
        (list_node_t *) list->first = next;
    }
    else
    {
        (list_node_t *) previous->next = next;
    }

    if (next == NULL)
    {
        (list_node_t *) list->last = previous;
    }
    else
    {
        (list_node_t *) next->previous = previous;
    }

    return LIST_RETURN_SUCCESS;
}

/* Delete a last node from a list. */

return_t list_node_remove_last (
    list_t *list)
{
    list_node_t *node;
    list_node_t *next, *previous;
    
    node = (list_node_t *) list->last;

    /* Check the input arguments. */

    if (list == NULL || node == NULL)
    {
        return LIST_RETURN_INVALID_ARGUMENT;
    }

    list->number_of_nodes--;

    previous = (list_node_t *) node->previous;
    next = (list_node_t *) node->next;

    /* First entry in the list? */

    if (previous == NULL)
    {
        (list_node_t *) list->first = next;
    }
    else
    {
        (list_node_t *) previous->next = next;
    }

    if (next == NULL)
    {
        (list_node_t *) list->last = previous;
    }
    else
    {
        (list_node_t *) next->previous = previous;
    }

    return LIST_RETURN_SUCCESS;
}

list_iterator_t * list_get_iterator (list_t *list)
{
    list->iterator.is_reverse = FALSE;
    list->iterator.current_node = (list_node_t *) list->first;
    
    return &(list->iterator);
}

list_iterator_t * list_get_reverse_iterator (list_t *list)
{
    list->iterator.is_reverse = TRUE;
    list->iterator.current_node = (list_node_t *) list->last;
    
    return &(list->iterator);
}

