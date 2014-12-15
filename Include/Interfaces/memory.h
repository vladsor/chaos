#ifndef __INTERFACE_MEMORY_H__
#define __INTERFACE_MEMORY_H__

#define IID_MEMORY 0x00000501

enum
{
    MID_MEMORY_ALLOCATE,
    MID_MEMORY_DEALLOCATE,
};

typedef return_t (memory_allocate_function_t) (void **pointer, unsigned int size);

typedef return_t (memory_deallocate_function_t) (void *pointer);

typedef struct
{
    memory_allocate_function_t *allocate;
    memory_deallocate_function_t *deallocate;
} memory_interface_t;

#define memory$allocate(handle,pointer,size) \
    ((memory_interface_t *) ((handle)->functions))->allocate ( \
        (pointer), (size))

#define memory$deallocate(handle,pointer) \
    ((memory_interface_t *) ((handle)->functions))->deallocate ( \
        (pointer))

#endif /* !__INTERFACE_MEMORY_H__ */


