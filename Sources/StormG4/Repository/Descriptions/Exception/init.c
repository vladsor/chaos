#include <enviroment.h>

#include "../../Include/init.h"

#define MODULE_NAME "Repository"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>
#include <exception/macros.h>


#define DESCRIPTION_EXCEPTION_HASH_TABLE_ENTRIES 100

#include "Include/external.h"

hash_table_t *exceptions_table = NULL;

void repository_description_exception_init (void)
{
    memory_allocate ((void **) &exceptions_table, 
        SIZEOF_HASH_TABLE (DESCRIPTION_EXCEPTION_HASH_TABLE_ENTRIES));
    hash_table_create (exceptions_table, 
        DESCRIPTION_EXCEPTION_HASH_TABLE_ENTRIES, id_to_hash, id_compare);
}
