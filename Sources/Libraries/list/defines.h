/* Abstract: . */
/* Author: Vladimir Sorokin */

/* Copyright 1999-2000 chaos development. */

#ifndef __LIBRARY_LIST_DEFINES_H__
#define __LIBRARY_LIST_DEFINES_H__

#define LIST_NODE_PART            \
    struct list_node_t *next;     \
    struct list_node_t *previous

#define LIST_NODE_INIT \
{ \
    next: NULL, \
    previous: NULL, \
}

#define LIST_PART                 \
    struct list_node_t *first;    \
    struct list_node_t *last;     \
    unsigned int number_of_nodes; \
    list_iterator_t iterator

#define LIST_INIT \
{ \
    first: NULL, \
    last: NULL, \
    number_of_nodes: 0, \
    iterator: {NULL, NULL, NULL, FALSE}, \
}

#define LIST_OPTION_FIRST  0x1
#define LIST_OPTION_LAST   0x4

#endif /* !__LIBRARY_LIST_DEFINES_H__ */
