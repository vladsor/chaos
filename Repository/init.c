
static hash_table_t *exceptions_table = NULL;

static pool_of_integers_t *interface_ids_pool = NULL;
static hash_table_t *interfaces_table = NULL;

static pool_of_integers_t *class_ids_pool = NULL;
static hash_table_t *classes_table = NULL;

object_t kernel_object;
class_t kernel_class;

handle_t handle_kernel = HANDLE_KERNEL;

static unsigned int id_to_hash (void *key)
{
    return (unsigned int) (*(uint32_t *) key);
}

static int id_compare (void *key1, void *key2)
{
    return (*(uint32_t *) key1) == (*(uint32_t *) key2) ? 
        CONDITION_EQUAL :
        CONDITION_NOT_EQUAL;
}

void repository_init (int argc UNUSED, char *argv[] UNUSED)
{
    uint32_t i;
    uint32_t number_of_interfaces = 0;
    interface_id_t interface_ids[NUMBER_OF_BUILT_IN];

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);

    TRY
    {
        memory_allocate ((void **) &exceptions_table, 
            SIZEOF_HASH_TABLE (EID_POOL_ENTRIES));
        hash_table_create (exceptions_table, EID_POOL_ENTRIES, id_to_hash, 
            id_compare);

        memory_allocate ((void **) &interface_ids_pool, 
            SIZEOF_POOL_OF_INTEGERS (IID_POOL_LIMIT));
        pool_of_integers_init (interface_ids_pool, IID_POOL_LIMIT);
        pool_of_integers_reserve (interface_ids_pool, IID_NONE);

        memory_allocate ((void **) &interfaces_table, 
            SIZEOF_HASH_TABLE (IID_POOL_ENTRIES));
        hash_table_create (interfaces_table, IID_POOL_ENTRIES, id_to_hash, 
            id_compare);

        memory_allocate ((void **) &class_ids_pool, 
            SIZEOF_POOL_OF_INTEGERS (CID_POOL_LIMIT));

        pool_of_integers_init (class_ids_pool, CID_POOL_LIMIT);
        pool_of_integers_reserve (class_ids_pool, CID_NONE);
        pool_of_integers_reserve (class_ids_pool, CID_KERNEL);

        memory_allocate ((void **) &classes_table, 
            SIZEOF_HASH_TABLE (CID_POOL_ENTRIES));
        hash_table_create (classes_table, CID_POOL_ENTRIES, id_to_hash, 
            id_compare);
        
        hash_table_add_element (classes_table, 
            (p_hash_element_t) &kernel_class);
    }
    CATCH_ALL (e)
    {
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s Registering built-in objects...\n",
        __FILE__, __FUNCTION__);
  
    for (i = 0; i < NUMBER_OF_KERNEL_INTERFACES; i++)
    {
        if (kernel_interfaces_info[i].enabled)
        {
            TRY
            {
                DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
                    "%s::%s Registering: %s...\n",
                    __FILE__, __FUNCTION__, kernel_interfaces_info[i].name);
                
                (*kernel_interfaces_info[i].init) (
                    &interface_ids[number_of_interfaces]);
                
                DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
                    "%s::%s Result of registering %s is OK.\n",
                    __FILE__, __FUNCTION__, kernel_interfaces_info[i].name);
            
                number_of_interfaces++;
            }
            CATCH_ALL (e)
            {
            }
        }
    }
    
    TRY
    {
        register_class_register (&kernel_class_id, CID_KERNEL, CLASS_TYPE_STATIC, 
            number_of_interfaces, interface_ids, IID_NONE);

        register_object_create ((handle_t *) &object_kernel, CID_KERNEL, NULL);
    }
    CATCH_ALL (e)
    {
    }
    
    for (i = 0; i < NUMBER_OF_UTIL_CLASSES; i++)
    {
        if (util_classes_info[i].enabled)
        {
            TRY
            {
                (*util_classes_info[i].init) (
                    &interface_ids[number_of_interfaces]);
            }
            CATCH_ALL (e)
            {
            }
        }
    }
}
