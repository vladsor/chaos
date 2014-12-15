#include <enviroment.h>

#include "../Include/internal.h"

#define DEBUG_MODULE_NAME "Repository"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include <debug/macros.h>
#include <exception/macros.h>

#if defined (REPOSITORY_EXTERNAL)

#define MID_POOL_LIMIT 1000
#define MID_HASH_TABLE_ENTRIES 100

#include "Include/repository_external.h"

pool_of_integers_t *method_ids_pool = NULL;
hash_table_t *methods_table = NULL;

#endif

void repository_method_init (void)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s ()\n",
        DEBUG_MODULE_NAME, __FUNCTION__);

#if defined (REPOSITORY_EXTERNAL)
    memory_allocate ((void **) &method_ids_pool, 
        SIZEOF_POOL_OF_INTEGERS (MID_POOL_LIMIT));
    pool_of_integers_init (method_ids_pool, MID_POOL_LIMIT);
    pool_of_integers_reserve (method_ids_pool, ID_NONE);

    memory_allocate ((void **) &methods_table, 
        SIZEOF_HASH_TABLE (MID_HASH_TABLE_ENTRIES));
    hash_table_create (methods_table, MID_HASH_TABLE_ENTRIES, id_to_hash, 
        id_compare);
#endif
}
