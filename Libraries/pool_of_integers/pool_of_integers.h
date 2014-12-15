#ifndef __LIBRARY_IPOOL_IPOOL_H__
#define __LIBRARY_IPOOL_IPOOL_H__

typedef struct 
{
    unsigned int pool_size;
    unsigned int pool_capacity;

    unsigned size;

    uint32_t blocks;
    uint32_t used_blocks;

    uint32_t map[0];
} pool_of_integers_t;

#define STATIC_POOL(name,par_size) \
typedef struct                     \
{                                  \
    unsigned int pool_size;        \
    unsigned int pool_capacity;    \
    unsigned size;                 \
    uint32_t blocks;               \
    uint32_t used_blocks;          \
    uint32_t map[(par_size)];      \
} name_t;                          \
name_t name_impl;                  \
pool_of_integers_t *name = (pool_of_integers_t *) &name_impl

#define POOL_GET(p,i) \
    BIT_GET (((p)->map[((i) - 1) / 32]), (((i) - 1) % 32))

#define POOL_SET_USED(p,i) \
    BIT_SET (((p)->map[((i) - 1) / 32]), (((i) - 1) % 32))

#define POOL_SET_UNUSED(p,i) \
    BIT_CLEAR (((p)->map[((i) - 1) / 32]), (((i) - 1) % 32))

#define SIZEOF_POOL_OF_INTEGERS(integers)  ((integers) * 2 / 8)
    

enum
{
    POI_RETURN_SUCCESS,
    POI_RETURN_OVERFLOW,
    POI_RETURN_ALREADY_USED,
    POI_RETURN_NOT_USED,
};

/**
 * @brief
 * @param pool
 * @param blocks
 * @return
 */
extern return_t pool_of_integers_init (pool_of_integers_t *pool, uint32_t blocks);

/**
 * @brief
 * @param pool
 * @param integer
 * @return
 */
extern return_t pool_of_integers_reserve (pool_of_integers_t *pool, uint32_t integer);

/**
 * @brief
 * @param pool
 * @param ptr_integer
 * @return
 */
extern return_t pool_of_integers_allocate (pool_of_integers_t *pool, uint32_t *ptr_integer);

/**
 * @brief
 * @param pool
 * @param integer
 * @return
 */
extern return_t pool_of_integers_deallocate (pool_of_integers_t *pool, uint32_t integer);

#endif /* !__LIBRARY_IPOOL_IPOOL_H__ */

