
typedef uint32_t transaction_id_t;

enum
{
    OPERATION_CREATE_OBJECT,
    OPERATION_DESTROY_OBJECT,
    
    OPERATION_OPEN_OBJECT,
    OPERATION_CLOSE_OBJECT,
    
    OPERATION_CLONE_HANDLE,
    
    OPERATION_EXCEPTION_REGISTER,
    OPERATION_EXCEPTION_UNREGISTER,
   
    OPERATION_INTERFACE_REGISTER,
    OPERATION_INTERFACE_UNREGISTER,
    
    OPERATION_CLASS_REGISTER,
    OPERATION_CLASS_UNREGISTER,
};

typedef struct
{
    uint32_t operation_id;
    
    union
    {
        handle_t handle;
    };
} operation_t;

typedef struct
{
    transaction_t *parent_transaction;

    handle_t filtered_handles[];

    bool is_begin;
    uint32_t last_operation;
    operation_t operations[0];
} transaction_t;

typedef transaction_t * p_transaction_t;

void transaction_create (p_transaction_t transaction, 
    int number_of_filtered, 
    handle_t filtered_handles[], uint32_t history_depth, uint32_t options)
{
    memory_allocate (transaction, sizeof (transaction_t) + 
        sizeof (operation_t) * history_depth);

    transaction->last_operation = 0;
    is_begin = FALSE;
}

void transaction_destroy (transaction_t transaction)
{
    memory_deallocate (transaction)
}

void transaction_add_objects (transaction_t transaction, 
    uint32_t number_of_objects, handle_t objects[])
{
}

void transaction_delete_objects (transaction_id_t, int, handle_t[])
{
}



void transaction_add_operations (transaction_t transaction, operation_t operation)
{
    if (!is_begin)
    {
        THROW ();
    }
    
    transaction->operations[transaction->last_operation] = operation;
    transaction->last_operation++;
}

transaction_delete_operations ()
{
}

void transaction_begin (transaction_id_t)
{
}

void transaction_commit (transaction_id_t)
{
}

void transaction_flush (transaction_id_t)
{
}

void transaction_rollback (transaction_id_t)
{
}

uint32_t transaction_get_status (transaction_id_t)
{
    return 0;
}

uint32_t transaction_get_options (transaction_id_t)
{
    return 0;
}

void transaction_set_options (transaction_id_t, uint32_t)
{
}


