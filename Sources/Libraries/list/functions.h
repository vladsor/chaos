/* $Id: functions.h,v 1.2 2001/02/10 21:22:46 jojo Exp $ */
/* Abstract: List library functions. */
/* Author: Per Lundberg <plundis@chaosdev.org> */

/* Copyright 2000 chaos development. */

#ifndef __LIBRARY_LIST_FUNCTIONS_H__
#define __LIBRARY_LIST_FUNCTIONS_H__

extern return_t list_create (
    list_t *list);

extern return_t list_node_insert (
    list_t *list, 
    list_node_t *node,
    unsigned int options);
  
extern return_t list_node_remove (
    list_t *list, 
    list_node_t *node);

extern return_t list_node_remove_last (list_t *list);

extern list_iterator_t * list_get_iterator (list_t *list);
extern list_iterator_t * list_get_reverse_iterator (list_t *list);

#endif /* !__LIBRARY_LIST_FUNCTIONS_H__ */
