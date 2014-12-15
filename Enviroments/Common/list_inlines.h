
#define LIST_INIT(list) \
do { \
    (list)->first = NULL; \
    (list)->last = NULL; \
    (list)->number_of_nodes = 0; \
} while (0)


#define LIST_ADD_HEAD_NODE(list,node) \
do { \
    list->number_of_nodes++; \
    node->previous = NULL; \
    node->next = list->first; \
    if (list->first != NULL) \
    { \
        list->first->previous = node; \
    } \
    else \
    { \
        list->last = node; \
    } \
    list->first = node; \
} while (0)

#define LIST_ADD_TAIL_NODE(list,node) \
do ( \
    list->number_of_nodes++; \
    node->next = NULL; \
    node->previous = list->last; \
    if (list->last != NULL) \
    { \
        list->last->next = node; \
    } \
    else \
    { \
        list->first = node; \
    } \
    list->last = node; \
} while (0)

#define LIST_REMOVE_NODE(list, node) \
do { \
    if (list->number_of_nodes > 0) \
    { \
        list_node_t *next, *previous; \
        list->number_of_nodes--; \
        previous = node->previous; \
        next = node->next; \
        if (previous == NULL) \
        { \
            list->first = next; \
        } \
        else \
        { \
            previous->next = next; \
        } \
        if (next == NULL) \
        { \
            list->last = previous; \
        } \
        else \
        { \
            next->previous = previous; \
        } \
    } \
} while (0)    


#define LIST_REMOVE_HEAD_NODE(list) \
do { \
    if (list->number_of_nodes > 0) \
    { \
        list_node_t *next, *previous; \
        list->number_of_nodes--; \
        next = node->next; \
        previous = node->previous; \
        list->first = next; \
        if (next == NULL) \
        { \
            list->last = NULL; \
        } \
        else \
        { \
            next->previous = NULL; \
        } \
    } \
} while (0)

#define LIST_REMOVE_TAIL_NODE(list) \
do { \
    if (list->number_of_nodes > 0) \
    { \
        list_node_t *next, *previous; \
        list->number_of_nodes--; \
        next = node->next; \
        previous = node->previous; \
        list->last = previous; \
        if (previous == NULL) \
        { \
            list->first = NULL; \
        } \
        else \
        { \
            previous->next = NULL; \
        } \
    } \
} while (0)

