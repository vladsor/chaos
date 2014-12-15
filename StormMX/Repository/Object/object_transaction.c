#include <enviroment.h>

#define MODULE_NAME "Repository"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>
#include <exception/macros.h>

#if defined (TRANSACTION_ENABLED)

void object_create_static_commit (object_reference_t object)
{
    object->transaction = NULL;
    object->slot_index = 0;
}

void object_destroy_static_commit (object_reference_t object)
{
#if defined (REPOSITORY_EXTERNAL)
    pool_of_integers_deallocate (class_ids_pool, object->id);
#endif

    object_destroy_static_internal (object);
}

void object_create_static_rollback (object_reference_t object)
{
#if defined (REPOSITORY_EXTERNAL)
    hash_table_delete_element (objectes_table, (p_hash_element_t) object);
    pool_of_integers_deallocate (class_ids_pool, object->id);
#endif

    object_destroy_static_internal (object);
}

void object_destroy_static_rollback (object_reference_t object)
{
#if defined (REPOSITORY_EXTERNAL)
    hash_table_add_element (objectes_table, (p_hash_element_t) object);
#endif
}

void object_create_commit (object_reference_t object)
{
    object->transaction = NULL;
    object->slot_index = 0;
}

void object_destroy_commit (object_reference_t object)
{
#if defined (REPOSITORY_EXTERNAL)
    pool_of_integers_deallocate (class_ids_pool, object->id);
#endif

    object_destroy_internal (object);
}

void object_create_rollback (object_reference_t object)
{
#if defined (REPOSITORY_EXTERNAL)
    hash_table_delete_element (objectes_table, (p_hash_element_t) object);
    pool_of_integers_deallocate (class_ids_pool, object->id);
#endif

    object_destroy_internal (object);
}

void object_destroy_rollback (object_reference_t object)
{
#if defined (REPOSITORY_EXTERNAL)
    hash_table_add_element (objectes_table, (p_hash_element_t) object);
#endif
}

#endif
