#include <enviroment.h>

#define MODULE_NAME "Repository"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>
#include <exception/macros.h>

#if defined (REPOSITORY_EXTERNAL)
#define EID_POOL_LIMIT 1000
#define EID_HASH_TABLE_ENTRIES 100

static pool_of_integers_t *exception_ids_pool = NULL;
static hash_table_t *exceptions_table = NULL;
#endif

void repository_exception_init (void)
{
#if defined (REPOSITORY_EXTERNAL)
    memory_allocate ((void **) &exception_ids_pool, 
        SIZEOF_POOL_OF_INTEGERS (EID_POOL_LIMIT));
    pool_of_integers_init (exception_ids_pool, EID_POOL_LIMIT);
    pool_of_integers_reserve (exception_ids_pool, ID_NONE);

    memory_allocate ((void **) &exceptions_table, 
        SIZEOF_HASH_TABLE (EID_HASH_TABLE_ENTRIES));
    hash_table_create (exceptions_table, EID_HASH_TABLE_ENTRIES, id_to_hash, 
        id_compare);
#endif

}
