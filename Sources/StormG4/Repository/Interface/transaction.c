#include <enviroment.h>

#include "Include/transaction.h"

#define MODULE_NAME "Repository"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>
#include <exception/macros.h>

#if defined (TRANSACTION_ENABLED)

void interface_create_static_commit (interface_reference_t interface)
{
    interface->transaction = NULL;
    interface->slot_index = 0;
}

void interface_destroy_static_commit (interface_reference_t interface)
{
#   if defined (REPOSITORY_EXTERNAL)
    pool_of_integers_deallocate (interface_ids_pool, interface->id);
#   endif

    interface_destroy_static_internal (interface);
}

void interface_create_static_rollback (interface_reference_t interface)
{
#   if defined (REPOSITORY_EXTERNAL)
    hash_table_delete_element (interfacees_table, (p_hash_element_t) interface);
    pool_of_integers_deallocate (interface_ids_pool, interface->id);
#   endif

    interface_destroy_static_internal (interface);
}

void interface_destroy_static_rollback (interface_reference_t interface)
{
#   if defined (REPOSITORY_EXTERNAL)
    hash_table_add_element (interfaces_table, (p_hash_element_t) interface);
#   endif
}

void interface_create_commit (interface_reference_t interface)
{
    interface->transaction = NULL;
    interface->slot_index = 0;
}

void interface_destroy_commit (interface_reference_t interface)
{
#   if defined (REPOSITORY_EXTERNAL)
    pool_of_integers_deallocate (interface_ids_pool, interface->id);
#   endif

    interface_destroy_internal (interface);
}

void interface_create_rollback (interface_reference_t interface)
{
#   if defined (REPOSITORY_EXTERNAL)
    hash_table_delete_element (interfacees_table, (p_hash_element_t) interface);
    pool_of_integers_deallocate (interface_ids_pool, interface->id);
#   endif

    interface_destroy_internal (interface);
}

void interface_destroy_rollback (interface_reference_t interface)
{
#   if defined (REPOSITORY_EXTERNAL)
    hash_table_add_element (interfaces_table, (p_hash_element_t) interface);
#   endif
}

#endif /* defined (TRANSACTION_ENABLED) */

