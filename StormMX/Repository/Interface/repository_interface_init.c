#include <enviroment.h>

#define MODULE_NAME "Repository"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>
#include <exception/macros.h>

#if defined (REPOSITORY_EXTERNAL)
#define IID_POOL_LIMIT 1000
#define IID_HASH_TABLE_ENTRIES 100

static pool_of_integers_t *interface_ids_pool = NULL;
static hash_table_t *interfaces_table = NULL;
#endif

void repository_exception_init (void)
{
#if defined (REPOSITORY_EXTERNAL)
    memory_allocate ((void **) &interface_ids_pool, 
        SIZEOF_POOL_OF_INTEGERS (IID_POOL_LIMIT));
    pool_of_integers_init (interface_ids_pool, IID_POOL_LIMIT);
    pool_of_integers_reserve (interface_ids_pool, ID_NONE);

    memory_allocate ((void **) &interfaces_table, 
        SIZEOF_HASH_TABLE (IID_HASH_TABLE_ENTRIES));
    hash_table_create (interfaces_table, IID_HASH_TABLE_ENTRIES, id_to_hash, 
        id_compare);
#endif

}
