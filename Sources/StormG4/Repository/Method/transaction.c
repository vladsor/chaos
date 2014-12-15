#include <enviroment.h>

#include "Include/transaction.h"

#if defined (REPOSITORY_EXTERNAL)
#	include "Include/repository_external.h"
#endif

#define MODULE_NAME "Repository"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>
#include <exception/macros.h>

#if defined (TRANSACTION_ENABLED)

void exception_create_static_commit (exception_reference_t exception)
{
    exception->transaction = NULL;
    exception->slot_index = 0;
}

void exception_destroy_static_commit (exception_reference_t exception)
{
#if defined (REPOSITORY_EXTERNAL)
    pool_of_integers_deallocate (exception_ids_pool, exception->id);
#endif

    exception_destroy_static_internal (exception);
}

void exception_create_static_rollback (exception_reference_t exception)
{
#if defined (REPOSITORY_EXTERNAL)
    hash_table_delete_element (exceptiones_table, (p_hash_element_t) exception);
    pool_of_integers_deallocate (exception_ids_pool, exception->id);
#endif

    exception_destroy_static_internal (exception);
}

void exception_destroy_static_rollback (exception_reference_t exception)
{
#if defined (REPOSITORY_EXTERNAL)
    hash_table_add_element (exceptiones_table, (p_hash_element_t) exception);
#endif
}

void exception_create_commit (exception_reference_t exception)
{
    exception->transaction = NULL;
    exception->slot_index = 0;
}

void exception_destroy_commit (exception_reference_t exception)
{
#if defined (REPOSITORY_EXTERNAL)
    pool_of_integers_deallocate (exception_ids_pool, exception->id);
#endif

    exception_destroy_internal (exception);
}

void exception_create_rollback (exception_reference_t exception)
{
#if defined (REPOSITORY_EXTERNAL)
    hash_table_delete_element (exceptiones_table, (p_hash_element_t) exception);
    pool_of_integers_deallocate (exception_ids_pool, exception->id);
#endif

    exception_destroy_internal (exception);
}

void exception_destroy_rollback (exception_reference_t exception)
{
#if defined (REPOSITORY_EXTERNAL)
    hash_table_add_element (exceptiones_table, (p_hash_element_t) exception);
#endif
}

#endif /* defined (TRANSACTION_ENABLED) */

