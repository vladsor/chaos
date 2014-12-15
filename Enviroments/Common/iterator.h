
struct iterator_t;

typedef bool (iterator_has_next_function_t) (struct iterator_t *iterator);
typedef void * (iterator_get_next_function_t) (struct iterator_t *iterator);

typedef struct
{
    iterator_has_next_function_t *has_next;
    iterator_get_next_function_t *get_next;
} iterator_t;

#define iterator$has_next(iterator) \
    (((iterator_t *) (iterator))->has_next ((struct iterator_t *) iterator))

#define iterator$get_next(iterator) \
    (((iterator_t *) (iterator))->get_next ((struct iterator_t *) iterator))
