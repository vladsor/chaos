#include <enviroment.h>

#include "../Include/init.h"

#define DEBUG_MODULE_NAME "Repository"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include <debug/macros.h>
#include <exception/macros.h>

#if defined (REPOSITORY_EXTERNAL)

#define CID_POOL_LIMIT 1000
#define CID_HASH_TABLE_ENTRIES 100

#include "Include/repository_external.h"

pool_of_integers_t *class_ids_pool = NULL;
hash_table_t *classes_table = NULL;

#endif

void repository_class_init (void)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s ()\n",
        DEBUG_MODULE_NAME, __FUNCTION__);

#if defined (REPOSITORY_EXTERNAL)
    memory_allocate ((void **) &class_ids_pool, 
        SIZEOF_POOL_OF_INTEGERS (CID_POOL_LIMIT));
    pool_of_integers_init (class_ids_pool, CID_POOL_LIMIT);
    pool_of_integers_reserve (class_ids_pool, ID_NONE);

    memory_allocate ((void **) &classes_table, 
        SIZEOF_HASH_TABLE (CID_HASH_TABLE_ENTRIES));
    hash_table_create (classes_table, CID_HASH_TABLE_ENTRIES, id_to_hash, 
        id_compare);
#endif

}
